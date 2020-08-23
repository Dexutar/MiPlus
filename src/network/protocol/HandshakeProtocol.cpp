#include "HandshakeProtocol.hh"

#include "VarNumber.hh"

void HandshakeProtocol::inbound (std::istream &is)
{
  int32_t opcode = VarNumber::readVarInt(is);
  if (opcode == HandshakeMessage::opcode)
  {
    HandshakeMessage message; is >> message;
    handle(message);
  }
  else std::cerr << "Unexpected opcode:  " << opcode << std::endl;
}

void HandshakeProtocol::handle (const HandshakeMessage &message)
{
  
}