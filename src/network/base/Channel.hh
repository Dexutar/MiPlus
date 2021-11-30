#pragma once

#include <atomic>
#include <boost/asio.hpp>
#include <concepts>
#include <memory>
#include <string>

#include "Protocol.hh"

class Channel : public std::enable_shared_from_this<Channel>
{
 public:
  struct MatchCondition
  {
    using iterator = boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type>;

    MatchCondition(std::size_t &packet_length) : packet_length{packet_length} {}
    MatchCondition(const MatchCondition &match_condtion) : packet_length{match_condtion.packet_length}
    {
    }

    std::pair<iterator, bool> operator()(iterator begin, iterator end);

    std::size_t &packet_length;
  };

  Channel(boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol);

  void start();

  const std::string &getRemoteAddress() const { return remoteAddress; }

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

  std::string remoteAddress;

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

namespace boost::asio
{
  template <>
  struct is_match_condition<Channel::MatchCondition> : public boost::true_type
  {
  };
}  // namespace boost::asio