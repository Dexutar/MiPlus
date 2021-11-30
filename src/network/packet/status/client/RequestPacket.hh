#pragma once

#include <ostream>
#include <sstream>

#include "Packet.hh"

class RequestPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;
};