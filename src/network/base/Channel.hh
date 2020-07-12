#pragma once

#include <string>
#include <memory>

#include <boost/asio.hpp>

#include "Protocol.hh"

class Channel
{
public:

  Channel (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol);

  const std::string& getRemoteAddress() const
  {
    return remoteAddress;
  }

  bool operator== (const Channel &channel) const;

private:

  boost::asio::ip::tcp::socket socket;
  boost::asio::io_context::strand read;
  boost::asio::io_context::strand write;

  std::unique_ptr<Protocol> protocol;

  std::string remoteAddress;
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