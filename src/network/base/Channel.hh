#pragma once

#include <string>
#include <memory>

#include <boost/asio.hpp>

#include "Protocol.hh"

class Channel
{
public:

  struct MatchCondition
  {
    using iterator = boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type>;

    MatchCondition () : packet_length{std::make_shared<std::size_t>(0)} {}

    std::pair<iterator, bool> operator() (iterator begin, iterator end);

    std::shared_ptr<std::size_t> packet_length;
  };

  Channel (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol);

  const std::string& getRemoteAddress() const
  {
    return remoteAddress;
  }

  bool operator== (const Channel &channel) const;

private:

  void read_header ();
  void read_packet ();

  boost::asio::ip::tcp::socket socket;
  boost::asio::io_context::strand read_strand;
  boost::asio::io_context::strand write_strand;

  boost::asio::streambuf in_buffer;
  boost::asio::streambuf out_buffer;

  std::unique_ptr<Protocol> protocol;

  std::string remoteAddress;

  MatchCondition match_condition;
};

namespace boost::asio {
  template <> struct is_match_condition<Channel::MatchCondition>
    : public boost::true_type {};
}

namespace std
{
  template <>
  struct hash<Channel>
  {
    size_t operator() (const Channel &channel) const
    {
      return std::hash<std::string>{}(channel.getRemoteAddress());
    }
  };
}