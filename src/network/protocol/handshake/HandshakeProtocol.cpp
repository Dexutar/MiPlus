#include "HandshakeProtocol.hh"

#include "ProtocolError.hh"
#include "Session.hh"

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

void HandshakeProtocol::handle(const HandshakePacket &packet)
{
  session.set_state(packet.get_requested_state());
}