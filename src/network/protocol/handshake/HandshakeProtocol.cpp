#include "HandshakeProtocol.hh"

#include "Session.hh"

void HandshakeProtocol::inbound (std::istream &is)
{
  int32_t opcode = VarNumber::readVarInt(is);

  if (opcode == HandshakePacket::opcode)
  {
    HandshakePacket packet; is >> packet;
    handle(packet);
  }
  else std::cerr << "Unexpected opcode:  " << opcode << std::endl;
}

void HandshakeProtocol::handle (const HandshakePacket &packet)
{
  session.setState(packet.getRequestedState());
}