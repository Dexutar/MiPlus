#pragma once

#include <iostream>
#include <sstream>

#include "NetworkTypeHandlerConcepts.hh"
#include "Packet.hh"
#include "RawTypeHandler.hh"

namespace miplus
{
namespace network
{

struct PingPacket : public Packet
{
  static constexpr std::uint8_t opcode = 1;

  template <NetworkTypeReader<std::int64_t> PayloadReader = RawTypeHandler>
  friend std::istream &operator>>(std::istream &is, PingPacket &packet)
  {
    packet.payload = PayloadReader::template read<std::int64_t>(is);
    return is;
  }

  std::int64_t payload;
};

}  // namespace network
}  // namespace miplus