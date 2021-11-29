#include "ResponsePacket.hh"

#include <sstream>

#include "VarString.hh"

std::ostream& ResponsePacket::write(std::ostream& os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::write(data, ResponsePacket::opcode);
  VarString::writeVarString(data, response);

  return write_header(os, data);
}