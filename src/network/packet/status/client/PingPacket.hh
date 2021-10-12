#pragma once

#include "Packet.hh"

class PingPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  friend std::istream &operator>>(std::istream &is, PingPacket &packet);

  std::int64_t getPayload() const;

 private:
  std::ostream &write(std::ostream &os) const override;

  std::int64_t payload;
};