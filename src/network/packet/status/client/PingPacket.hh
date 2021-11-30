#pragma once

#include <iostream>
#include <sstream>

#include "BasicTypes.hh"
#include "Packet.hh"

class PingPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  friend std::istream &operator>>(std::istream &is, PingPacket &packet)
  {
    packet.payload = BasicTypes::read<std::uint64_t>(is);
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const PingPacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    VarNumber::write(data, PingPacket::opcode);
    BasicTypes::write(data, packet.payload);

    return packet.write_header(os, data);
  }

  std::int64_t getPayload() const;

 private:
  std::int64_t payload;
};