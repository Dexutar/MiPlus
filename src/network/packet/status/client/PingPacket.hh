#pragma once

#include <iostream>
#include <sstream>

#include "BasicTypes.hh"
#include "NetworkTypes.hh"
#include "Packet.hh"

class PingPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  template<NetworkTypeReader<std::uint64_t> PayloadReader = BasicTypes>
  friend std::istream &operator>>(std::istream &is, PingPacket &packet)
  {
    packet.payload = PayloadReader::template read<std::uint64_t>(is);
    return is;
  }

  std::int64_t getPayload() const;

 private:
  std::int64_t payload;
};