#include "HandshakeProtocol.hh"

#include "ProtocolError.hh"
#include "Session.hh"

namespace miplus
{
namespace network
{

HandshakeProtocol::HandshakeProtocol(Session *session) : session(session) {}

void HandshakeProtocol::inbound(std::istream &is)
{
  int32_t opcode = VarNumberHandler::read<std::int32_t>(is);

  if (opcode == HandshakePacket::opcode)
  {
    HandshakePacket packet;
    is >> packet;
    handle(packet);
  }
  else
  {
    std::cerr << "Unexpected opcode:  " << opcode << std::endl;
    on_error(protocol_error::unexpected_opcode);
  }
}

void HandshakeProtocol::on_error(const boost::system::error_code &error)
{
  session->terminate();
}

void HandshakeProtocol::handle(const HandshakePacket &packet)
{
  session->set_state(packet.requested_state);
}

}  // namespace network
}  // namespace miplus