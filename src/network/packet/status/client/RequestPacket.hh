#pragma once

#include "Packet.hh"

class RequestPacket : public Packet
{
public:
  static const std::uint8_t opcode = 0;

private:
  std::ostream& write (std::ostream &os) const override;
};