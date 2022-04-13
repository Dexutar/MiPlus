#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "Channel.hh"
#include "ConnectionState.hh"
#include "Packet.hh"
#include "Session_forwarding.hh"

namespace miplus
{
namespace network
{

class Session
{
 public:
  Session(std::size_t id, boost::asio::ip::tcp::socket socket, boost::asio::io_context &io_context, SessionRegistry &session_registry);

  std::size_t get_id() const;

  void set_state(ConnectionState state);

  template <typename Packet>
  void send(const Packet &packet);

  void terminate();

 private:
  std::size_t     id;
  SessionRegistry &session_registry;

  std::shared_ptr<Channel> channel;
};

template <typename Packet>
void Session::send(const Packet &packet)
{
  channel->send(packet);
}

}  // namespace network
}  // namespace miplus