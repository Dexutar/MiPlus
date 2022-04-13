#pragma once

#include <ostream>
#include <sstream>

#include "Packet.hh"

namespace miplus
{
namespace network
{

struct RequestPacket : public Packet
{
  static constexpr std::uint8_t opcode = 0;
};

}  // namespace network
}  // namespace miplus