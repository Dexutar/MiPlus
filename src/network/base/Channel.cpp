#include "Channel.hh"

#include <chrono>

#include "Packet.hh"
#include "ProtocolError.hh"
#include "VarNumberHandler.hh"

namespace io = boost::asio;

using error_code = boost::system::error_code;

namespace miplus
{
namespace network
{

Channel::Channel(boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol)
    : active{true},
      socket{std::move(socket)},
      input_deadline{io_context},
      write_strand{io_context},
      in_buffer{Packet::max_packet_length},
      protocol{std::move(protocol)},
      remote_address{this->socket.remote_endpoint().address().to_string() + ":" + std::to_string(this->socket.remote_endpoint().port())}
{
}

void Channel::start()
{
  read_header();
  check_timeout();
}

void Channel::setProtocol(std::unique_ptr<Protocol> &&protocol)
{
  this->protocol = std::move(protocol);
}

void Channel::close()
{
  active = false;
  input_deadline.cancel();
  boost::asio::post(write_strand, [&, self = shared_from_this()]()
  {
    boost::system::error_code ignored;
    socket.close(ignored);
    std::cout << "Connection closed" << std::endl;
  });
}

void Channel::read_header()
{
  input_deadline.expires_after(std::chrono::seconds(30));
  io::async_read_until(socket, in_buffer, MatchCondition(packet_length), [&, self = shared_from_this()](const auto &error, std::size_t bytes_transferred)
  {
    if (active)
    {
      if (not error)
      {
        in_buffer.consume(bytes_transferred);

        if (packet_length > Packet::max_packet_length)
        {
          std::cerr << "Received packet with length wider than 21-bit" << std::endl;
          protocol->on_error(protocol_error::packet_length_overflow);
        }
        else
          read_packet();
      }
      else
      {
        if (error == io::error::eof)
          std::cout << "Client closed connection" << std::endl;
        else
          std::cerr << "read_header failed: " << error.message() << std::endl;

        protocol->on_error(error);
      }
    }
  });
}

void Channel::read_packet()
{
  std::size_t to_read = packet_length - std::min(in_buffer.size(), packet_length);
  io::async_read(socket, in_buffer, boost::asio::transfer_at_least(to_read), [&, self = shared_from_this()](const auto &error, std::size_t bytes_transferred)
  {
    if (active)
    {
      if (not error)
      {
        input_deadline.expires_at(io::steady_timer::time_point::max());
        std::cout << remote_address << ": received packed with length " << packet_length << std::endl;
        std::istream stream(&in_buffer);
        protocol->inbound(stream);
        if (active) read_header();
      }
      else
      {
        if (error == io::error::eof)
          std::cout << "Client closed connection" << std::endl;
        else
          std::cerr << "read_packet failed: " << error.message() << std::endl;

        protocol->on_error(error);
      }
    }
  });
}

void Channel::check_timeout()
{
  input_deadline.async_wait([&, self = shared_from_this()] (const auto &error)
  {
    if (active)
    {
      if (input_deadline.expiry() <= io::steady_timer::clock_type::now())
      {
        std::cerr << "Connection timed out" << std::endl;
        protocol->on_error(protocol_error::timeout);
      }
      else
        check_timeout();
    }
  });
}

std::pair<Channel::MatchCondition::iterator, bool> Channel::MatchCondition::operator()(iterator begin, iterator end)
{
  auto [valid, it, value] = VarNumberHandler::read<iterator, std::int32_t>(begin, end);
  packet_length = value;
  return {it, valid};
}

}  // namespace network
}  // namespace miplus