#pragma once

#include <boost/asio.hpp>

#include "Channel.hh"
#include "ProtocolFactory.hh"

class Session;

namespace std
{
  template <>
  struct hash<Session>
  {
    size_t operator() (const Session &session) const;
  };
}

class Session
{
public:
  Session (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context);
  
  bool operator== (const Session &session) const;

  friend size_t std::hash<Session>::operator()(const Session &session) const;

private:
  std::unique_ptr<Channel> channel;
};
