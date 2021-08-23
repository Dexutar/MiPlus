#include "Channel.hh"

#include "VarNumber.hh"

namespace io = boost::asio;

Channel::Channel (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol) 
  : socket{std::move(socket)}, write_strand{io_context}, in_buffer{Packet::max_packet_length}, protocol{std::move(protocol)},
    remoteAddress{this->socket.remote_endpoint().address().to_string() + ":" + std::to_string(this->socket.remote_endpoint().port())}
{
  read_header();
}

void Channel::setProtocol (std::unique_ptr<Protocol> &&protocol)
{
  this->protocol = std::move(protocol);
}

void Channel::send (const Packet &packet)
{
  std::ostream os(&out_buffer);
  os << packet;
  io::async_write(socket, out_buffer, io::bind_executor(write_strand, [&] (const auto &error, std::size_t bytes_transferred)
  {
    if (error)
    {
      std::cerr << "Send packet failed: " << error.message() << std::endl;
    }
  }));
}

void Channel::read_header ()
{
  io::async_read_until(socket, in_buffer, MatchCondition(packet_length), [&] (const auto &error, std::size_t bytes_transferred)
  {
    if (not error)
    {
      in_buffer.consume(bytes_transferred);

      if (packet_length > Packet::max_packet_length)
      {
        std::cerr << "Received packet with length wider than 21-bit" << std::endl;
      }
      else read_packet();
    }
    else if (error == io::error::eof)
    {
      std::cout << "Client closed connection" << std::endl;
    }
    else std::cout << "read_header failed: " << error.message() << std::endl;
  });
}

void Channel::read_packet ()
{
  std::size_t to_read = packet_length - std::min(in_buffer.size(),packet_length);
  io::async_read(socket, in_buffer, boost::asio::transfer_at_least(to_read), [&] (const auto &error, std::size_t bytes_transferred)
  {
    if (not error)
    {
      std::cout << remoteAddress << ": received packed with length " << packet_length << std::endl;
      std::istream stream(&in_buffer);
      protocol->inbound(stream);
      read_header();
    }
    else if (error == io::error::eof)
    {
      std::cout << "Client closed connection" << std::endl;
    }
    else std::cout << "read_packet failed: " << error.message() << std::endl;
  });
}

std::pair<Channel::MatchCondition::iterator, bool> Channel::MatchCondition::operator() (iterator begin, iterator end)
{
  auto [valid, it, value] = VarNumber::readVarInt(begin,end);
  packet_length = value;
  return {it,valid};
}