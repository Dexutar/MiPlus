#include "HandshakeProtocol.hh"

#include "ProtocolError.hh"

#include "Session.hh"

void HandshakeProtocol::inbound (std::istream &is)
{
  int32_t opcode = VarNumber::readVarInt(is);

  if (opcode == HandshakePacket::opcode)
  {
    HandshakePacket packet; is >> packet;
    handle(packet);
  }
  else
  {
    std::cerr << "Unexpected opcode:  " << opcode << std::endl;
    on_error(protocol_error::unexpected_opcode);
  }
}

void HandshakeProtocol::handle (const HandshakePacket &packet)
{
  session.setState(packet.getRequestedState());
}