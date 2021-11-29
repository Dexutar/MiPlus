#include "PingPacket.hh"

#include <sstream>

#include "BasicTypes.hh"

std::istream &operator>>(std::istream &is, PingPacket &packet)
{
  packet.payload = BasicTypes::read<std::uint64_t>(is);
  return is;
}

std::int64_t PingPacket::getPayload() const { return payload; }

std::ostream &PingPacket::write(std::ostream &os) const
{
  std::stringbuf sb;
  std::ostream data{&sb};

  VarNumber::write(data, PingPacket::opcode);
  BasicTypes::write(data, payload);

  return write_header(os, data);
}