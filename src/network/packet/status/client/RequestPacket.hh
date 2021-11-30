#pragma once

#include <ostream>
#include <sstream>

#include "Packet.hh"

class RequestPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  friend std::ostream &operator<<(std::ostream &os, const RequestPacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    VarNumber::write(data, RequestPacket::opcode);

    return packet.write_header(os, data);
  }
};