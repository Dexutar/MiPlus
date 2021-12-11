#include "Session.hh"

#include "ProtocolFactory.hh"
#include "SessionRegistry.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;

Session::Session(tcp::socket &&socket, io::io_context &io_context, SessionRegistry &session_registry)
    : channel{std::make_shared<Channel>(std::move(socket), io_context, std::move(ProtocolFactory::create(ConnectionState::Handshake, *this)))},
      session_registry{session_registry}
{
  channel->start();
}

std::string Session::getID() const { return channel->get_remote_address(); }

void Session::set_state(ConnectionState state)
{
  channel->setProtocol(std::move(ProtocolFactory::create(state, *this)));
}

void Session::terminate()
{
  channel->close();
  session_registry.erase(getID());
}