#include "HandshakePacket.hh"

#include <sstream>

#include "BasicTypes.hh"
#include "VarString.hh"

std::ostream &HandshakePacket::write(std::ostream &os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::write(data, HandshakePacket::opcode);
  VarNumber::write(data, version);
  VarString::write(data, server_address);
  BasicTypes::write(data, server_port);
  VarNumber::write(data, static_cast<std::int8_t>(requested_state));

  return write_header(os, data);
}

ConnectionState HandshakePacket::getRequestedState() const { return requested_state; }
