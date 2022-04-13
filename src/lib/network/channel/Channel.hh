#pragma once

#include <atomic>
#include <boost/asio.hpp>
#include <variant>

#include "Protocol.hh"

namespace miplus
{
namespace network
{

class Channel : public std::enable_shared_from_this<Channel>
{
 public:
  Channel(boost::asio::ip::tcp::socket socket, boost::asio::io_context &io_context, Protocol protocol);

  void start();
  void stop();

  template <typename Packet>
  void send(const Packet &packet);

  void set_protocol(Protocol protocol);

 private:
  void read_frame();
  void read_packet(std::size_t packet_length);

  void handle_timeout();


  std::atomic_bool active;

  boost::asio::ip::tcp::socket    socket;
  boost::asio::steady_timer       input_deadline;
  boost::asio::io_context::strand strand;

  boost::asio::streambuf in_buffer;
  boost::asio::streambuf out_buffer;

  Protocol protocol;
};

template<typename Packet>
void Channel::send(const Packet &packet)
{
  namespace io = boost::asio;

  if (active)
  {
    std::ostream os(&out_buffer);
    os << packet;

    io::async_write(socket, out_buffer, io::bind_executor(strand, [&, self = shared_from_this()](const auto &error, std::size_t bytes_transferred)
    {
      if (active and error)
      {
        std::cerr << "Send packet failed: " << error.message() << std::endl;
        std::visit([&error](auto &&protocol) { protocol.on_error(error); }, protocol);
      }
    }));
  }
}

}  // namespace network
}  // namespace miplus