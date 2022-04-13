#include "Channel.hh"

#include <chrono>
#include <iostream>

#include "Packet.hh"
#include "ProtocolError.hh"
#include "ValidFrameCondition.hh"
#include "VarNumberHandler.hh"

namespace io = boost::asio;

using error_code = boost::system::error_code;

namespace miplus
{
namespace network
{

Channel::Channel(boost::asio::ip::tcp::socket socket, boost::asio::io_context &io_context, Protocol protocol)
    : active{false},
      socket{std::move(socket)}, 
      input_deadline{io_context}, 
      strand{io_context},
      in_buffer{2*Packet::max_packet_length},
      protocol{std::move(protocol)}
{
}

void Channel::start()
{
  active = true;

  read_frame();
  handle_timeout();
}

void Channel::stop()
{
  active = false;

  input_deadline.cancel();
  boost::asio::post(strand, [&, self = shared_from_this()]()
  {
    boost::system::error_code ignored;
    socket.close(ignored);

    std::cout << "Connection closed" << std::endl;
  });
}

void Channel::set_protocol(Protocol protocol)
{
  this->protocol = protocol;
}

void Channel::read_frame() 
{
  input_deadline.expires_after(std::chrono::seconds(30));

  io::async_read_until(socket, in_buffer, ValidFrameCondition(), [&, self = shared_from_this()](const error_code &error, std::size_t bytes_transferred)
  {
    if (active)
    { 
      if (not error)
      {
        if (bytes_transferred > 3)
          std::visit([](auto&& protocol) { protocol.on_error(protocol_error::packet_length_overflow); }, protocol);
        else
        {
          std::istream is(&in_buffer);
          std::size_t packet_length = VarNumberHandler::read<std::int32_t>(is);

          read_packet(packet_length);
        }  
      }
      else 
      {
        if (error == io::error::eof)
          std::cout << "Client closed connection" << std::endl;
        else
          std::cerr << "read_frame failed: " << error.message() << std::endl;

        std::visit([&error](auto&& protocol) { protocol.on_error(error); }, protocol);
      }
    }
  });
}

void Channel::read_packet(std::size_t packet_length)
{
  std::size_t to_read = packet_length - std::min(in_buffer.size(), packet_length);

  io::async_read(socket, in_buffer, boost::asio::transfer_at_least(to_read), [&, packet_length, self = shared_from_this()](const error_code &error, std::size_t bytes_transferred)
  {
    if (active)
    {
      input_deadline.expires_at(io::steady_timer::time_point::max());
        
      if (not error)
      {
        std::cout << "Received packed with length " << packet_length << std::endl;
        
        std::istream is(&in_buffer);
        std::visit([&is](auto&& protocol) { protocol.inbound(is); }, protocol);

        if (active) 
          read_frame();
      }
      else
      {
        if (error == io::error::eof)
          std::cout << "Client closed connection" << std::endl;
        else
          std::cerr << "read_packet failed: " << error.message() << std::endl;

        std::visit([&error](auto&& protocol) { protocol.on_error(error); }, protocol);
      }
    }
  });
}

void Channel::handle_timeout()
{
  input_deadline.async_wait([&, self = shared_from_this()] (const error_code &error)
  {
    if (active)
    {
      if (input_deadline.expiry() <= io::steady_timer::clock_type::now())
      {
        std::cerr << "Connection timed out" << std::endl;
        std::visit([](auto&& protocol) { protocol.on_error(protocol_error::timeout); }, protocol);
      }
      else
        handle_timeout();
    }
  });
}

}  // namespace network
}  // namespace miplus