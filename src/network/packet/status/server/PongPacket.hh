#pragma once

#include <ostream>
#include <sstream>

#include "BasicTypes.hh"
#include "Packet.hh"
#include "VarNumber.hh"

class PongPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  PongPacket(std::int64_t payload) : payload{payload} {}

  friend std::ostream &operator<<(std::ostream &os, const PongPacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    VarNumber::write(data, PongPacket::opcode);
    BasicTypes::write(data, packet.payload);

    return packet.write_header(os, data);
  }

 private:
  std::int64_t payload;
};