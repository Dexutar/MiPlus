#pragma once

#include <ostream>
#include <sstream>

#include "Packet.hh"

namespace miplus
{
namespace network
{

class RequestPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;
};

}  // namespace network
}  // namespace miplus