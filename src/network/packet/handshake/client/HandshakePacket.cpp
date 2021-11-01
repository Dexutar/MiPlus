#include "HandshakePacket.hh"

#include <sstream>

#include "BasicTypes.hh"
#include "VarString.hh"

std::ostream &HandshakePacket::write(std::ostream &os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::writeVarNumber(data, HandshakePacket::opcode);
  VarNumber::writeVarNumber(data, version);
  VarString::writeVarString(data, server_address);
  BasicTypes::write(data, server_port);
  VarNumber::writeVarNumber(data, static_cast<std::int8_t>(requested_state));

  return write_header(os, data);
}

ConnectionState HandshakePacket::getRequestedState() const { return requested_state; }
