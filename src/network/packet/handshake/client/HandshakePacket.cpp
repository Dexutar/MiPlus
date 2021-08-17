#include "HandshakePacket.hh"

#include <sstream>

#include "VarString.hh"
#include "BasicTypes.hh"

std::istream& operator>> (std::istream &is, HandshakePacket &packet)
{
  packet.version = VarNumber::readVarInt(is);
  packet.server_address = VarString::readVarString(is);
  packet.server_port = BasicTypes::readUint16(is);
  packet.requested_state = static_cast<ConnectionState>(VarNumber::readVarInt(is));
  return is;
}

std::ostream& HandshakePacket::write (std::ostream &os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};
  
  VarNumber::writeVarNumber(data, HandshakePacket::opcode);
  VarNumber::writeVarNumber(data, version);
  VarString::writeVarString(data, server_address);
  BasicTypes::writeUint16(data, server_port);
  VarNumber::writeVarNumber(data, static_cast<std::int8_t>(requested_state));

  return write_header(os, data);
}

ConnectionState HandshakePacket::getRequestedState() const
{
  return requested_state;
}

void HandshakePacket::print () const
{
  std::cout << "[Handshake Packet]" << std::endl << std::endl;
  std::cout << "Version: " << version << std::endl;
  std::cout << "Server Address: " << server_address << std::endl;
  std::cout << "Server Port: " << server_port << std::endl;
  std::cout << "Requested State: " << static_cast<std::int8_t>(requested_state) << std::endl;
  std::cout << "[/Handshake Packet]" << std::endl << std::endl;
}