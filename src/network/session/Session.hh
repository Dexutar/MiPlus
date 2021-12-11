#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "Channel.hh"
#include "ConnectionState.hh"
#include "Packet.hh"

class SessionRegistry;

class Session
{
 public:
  Session(boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, SessionRegistry &session_registry);

  std::string getID() const;

  void set_state(ConnectionState state);

  template<typename Packet>
  void send(const Packet &packet);

  void terminate();

 private:
  std::shared_ptr<Channel> channel;
  SessionRegistry &session_registry;
};

template<typename Packet>
void Session::send(const Packet &packet)
{
  channel->send(packet);
}
