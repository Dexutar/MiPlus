#pragma once

#include <ostream>
#include <sstream>

#include "NetworkTypeHandlerConcepts.hh"
#include "Packet.hh"
#include "RawTypeHandler.hh"
#include "VarNumberHandler.hh"

namespace miplus
{
namespace network
{

class PongPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  PongPacket(std::int64_t payload) : payload{payload} {}

  template <NetworkTypeWriter<std::uint8_t>    OpcodeWriter  = VarNumberHandler, 
            NetworkTypeWriter<std::int64_t>    PayloadWriter = RawTypeHandler,
            NetworkTypeWriter<std::streamsize> SizeWriter    = VarNumberHandler>
  friend std::ostream &operator<<(std::ostream &os, const PongPacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    OpcodeWriter::write(data, PongPacket::opcode);
    PayloadWriter::write(data, packet.payload);

    return packet.write_header<SizeWriter>(os, data);
  }

 private:
  std::int64_t payload;
};

}  // namespace network
}  // namespace miplus