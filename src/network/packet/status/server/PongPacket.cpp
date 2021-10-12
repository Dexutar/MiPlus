#include "PongPacket.hh"

#include "BasicTypes.hh"

std::ostream& PongPacket::write(std::ostream& os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::writeVarNumber(data, PongPacket::opcode);
  BasicTypes::writeUint64(data, payload);

  return write_header(os, data);
}