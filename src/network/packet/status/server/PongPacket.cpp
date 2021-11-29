#include "PongPacket.hh"

#include <sstream>

#include "BasicTypes.hh"

std::ostream& PongPacket::write(std::ostream& os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::write(data, PongPacket::opcode);
  BasicTypes::write(data, payload);

  return write_header(os, data);
}