#include "Session.hh"

#include "ProtocolFactory.hh"
#include "SessionRegistry.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;

namespace miplus
{
namespace network
{

Session::Session(std::size_t id, boost::asio::ip::tcp::socket socket, boost::asio::io_context &io_context, SessionRegistry &session_registry)
    : id{id},
      channel{std::make_shared<Channel>(std::move(socket), io_context, std::move(ProtocolFactory::create(ConnectionState::Handshake, *this)))},
      session_registry{session_registry}
{
  channel->start();
}

std::size_t Session::get_id() const
{
  return id;
}

void Session::set_state(ConnectionState state)
{
  channel->set_protocol(ProtocolFactory::create(state, *this));
}

void Session::terminate()
{
  channel->stop();
  session_registry.erase(id);
}

}  // namespace network
}  // namespace miplus