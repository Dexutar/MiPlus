#pragma once

#include <string>

#include <boost/asio.hpp>

#include "Protocol.hh"

class Channel
{
public:

  Channel (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, Protocol &&protocol);

  const std::string& getRemoteAddress() const
  {
    return remoteAddress;
  }
  const std::string& getLocalAddress() const
  {
    return localAddress;
  }

  bool operator== (const Channel &channel) const;

private:

  boost::asio::ip::tcp::socket socket;
  boost::asio::io_context::strand read;
  boost::asio::io_context::strand write;

  Protocol protocol;

  std::string remoteAddress;
  std::string localAddress;
};

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