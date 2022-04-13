#include "PlayProtocol.hh"

#include "Session.hh"

namespace miplus
{
namespace network
{

PlayProtocol::PlayProtocol(Session *session) : session(session) {}

void PlayProtocol::inbound(std::istream& is)
{
  session->terminate();
}

void PlayProtocol::on_error(const boost::system::error_code& error)
{
  session->terminate();
}

}  // namespace network
}  // namespace miplus