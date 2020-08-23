#include "HandshakeMessage.hh"

#include <sstream>

#include "VarString.hh"
#include "BasicTypes.hh"

std::istream& operator>> (std::istream &is, HandshakeMessage &message)
{
  message.version = VarNumber::readVarInt(is);
  message.server_address = VarString::readVarString(is);
  message.server_port = BasicTypes::readUint16(is);
  message.next_state = VarNumber::readVarInt(is);
  return is;
}

std::ostream& HandshakeMessage::write (std::ostream &os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};
  
  VarNumber::writeVarNumber(data, HandshakeMessage::opcode);
  VarNumber::writeVarNumber(data, version);
  VarNumber::writeVarNumber(data, server_address.size());
  data << server_address;
  BasicTypes::writeUint16(data, server_port);
  VarNumber::writeVarNumber(data, next_state);

  return write_header(os, data);
}

int HandshakeMessage::getState() const
{
  return next_state;
}

void HandshakeMessage::print () const
{
  std::cout << "[Handshake Message]" << std::endl << std::endl;
  std::cout << "Version: " << version << std::endl;
  std::cout << "Server Address: " << server_address << std::endl;
  std::cout << "Server Port: " << server_port << std::endl;
  std::cout << "Next State: " << next_state << std::endl;
  std::cout << "[/Handshake Message]" << std::endl << std::endl;
}