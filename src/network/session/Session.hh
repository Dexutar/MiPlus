#pragma once

#include <boost/asio.hpp>

#include "Channel.hh"
#include "ConnectionState.hh"
#include "Packet.hh"


class Session
{
public:
  Session (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context);

  std::string getID () const;

  void setState (ConnectionState state);

  void send (const Packet &message);

private:
  Channel channel;
};
