#pragma once

#include <iostream>
#include <sstream>

#include "RawTypeHandler.hh"
#include "NetworkTypeHandlers.hh"
#include "Packet.hh"

class PingPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  template<NetworkTypeReader<std::uint64_t> PayloadReader = RawTypeHandler>
  friend std::istream &operator>>(std::istream &is, PingPacket &packet)
  {
    packet.payload = PayloadReader::template read<std::uint64_t>(is);
    return is;
  }

  std::int64_t getPayload() const
  {
    return payload;
  }

 private:
  std::int64_t payload;
};