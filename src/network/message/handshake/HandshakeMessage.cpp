#include "HandshakeMessage.hh"

#include "VarNumber.hh"
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

int HandshakeMessage::getState()
{
  return next_state;
}

void HandshakeMessage::print ()
{
  std::cout << "[Handshake Message]" << std::endl << std::endl;
  std::cout << "Version: " << version << std::endl;
  std::cout << "Server Address: " << server_address << std::endl;
  std::cout << "Server Port: " << server_port << std::endl;
  std::cout << "Next State: " << next_state << std::endl;
  std::cout << "[/Handshake Message]" << std::endl << std::endl;
}