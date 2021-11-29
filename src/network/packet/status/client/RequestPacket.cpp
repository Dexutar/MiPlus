#include "RequestPacket.hh"

#include <sstream>

#include "VarNumber.hh"

std::ostream& RequestPacket::write(std::ostream& os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::write(data, RequestPacket::opcode);

  return write_header(os, data);
}