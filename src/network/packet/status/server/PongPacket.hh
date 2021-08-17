#pragma once

#include "Packet.hh"

class PongPacket : public Packet
{
public:
  static const std::uint8_t opcode = 1;

  PongPacket (std::int64_t payload) : payload {payload} {}

private:
  std::ostream& write (std::ostream &os) const override;

  std::int64_t payload;
};