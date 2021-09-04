#pragma once

#include <memory>

#include <boost/asio.hpp>

#include "Channel.hh"
#include "ConnectionState.hh"
#include "Packet.hh"

class SessionRegistry;

class Session
{
public:
  Session (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, SessionRegistry &session_registry);

  std::string getID () const;

  void setState (ConnectionState state);

  void send (const Packet &message);

  void terminate();

private:
  std::shared_ptr<Channel> channel;
  SessionRegistry &session_registry;  
};
