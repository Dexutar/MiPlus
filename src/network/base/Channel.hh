#pragma once

#include <atomic>
#include <boost/asio.hpp>
#include <concepts>
#include <memory>
#include <string>

#include "Protocol.hh"

namespace miplus
{
namespace network
{

class Channel : public std::enable_shared_from_this<Channel>
{
 public:
  Channel(boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol);

  void start();

  const std::string &get_remote_address() const { return remote_address; }

  void setProtocol(std::unique_ptr<Protocol> &&protocol);

  template<typename Packet>
  void send(const Packet &packet);

  void close();

 private:
  void read_header();
  void read_packet();

  void check_timeout();

  std::atomic_bool active;

  boost::asio::ip::tcp::socket socket;

  boost::asio::steady_timer input_deadline;

  boost::asio::io_context::strand write_strand;

  boost::asio::streambuf in_buffer;
  boost::asio::streambuf out_buffer;

  std::unique_ptr<Protocol> protocol;

  std::string remote_address;

  std::size_t packet_length;
};

template<typename Packet>
void Channel::send(const Packet &packet)
{
  namespace io = boost::asio;

  if (active)
  {
    std::ostream os(&out_buffer);
    os << packet;

    io::async_write(socket, out_buffer, io::bind_executor(write_strand, [&, self = shared_from_this()](const auto &error, std::size_t bytes_transferred)
    {
      if (active and error)
      {
        std::cerr << "Send packet failed: " << error.message() << std::endl;
        protocol->on_error(error);
      }
    }));
  }
}

}  // namespace network
}  // namespace miplus