#pragma once

#include <boost/asio.hpp>

#include "Channel.hh"
#include "ProtocolFactory.hh"


class Session
{
public:
  Session (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context);

  std::string getID () const;

  void setProtocol (Protocols protocol);

private:
  Channel channel;
};
