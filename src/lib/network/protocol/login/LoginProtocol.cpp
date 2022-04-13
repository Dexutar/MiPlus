#include "LoginProtocol.hh"

#include "Session.hh"

namespace miplus
{
namespace network
{

LoginProtocol::LoginProtocol(Session* session) : session(session) {}

void LoginProtocol::inbound(std::istream& is)
{
  session->terminate();
}

void LoginProtocol::on_error(const boost::system::error_code& error)
{
  session->terminate();
}

}  // namespace network
}  // namespace miplus