#include "PingPacket.hh"

#include "BasicTypes.hh"

std::istream& operator>> (std::istream &is, PingPacket &packet)
{
  packet.payload = BasicTypes::readUint64(is);
  return is;
}

std::int64_t PingPacket::getPayload() const
{
  return payload;
}

std::ostream& PingPacket::write (std::ostream &os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};
  
  VarNumber::writeVarNumber(data, PingPacket::opcode);
  BasicTypes::writeUint64(data, payload);

  return write_header(os, data);
}