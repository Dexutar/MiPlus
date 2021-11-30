#pragma once

#include <ostream>
#include <sstream>

#include "BasicTypes.hh"
#include "NetworkTypes.hh"
#include "Packet.hh"
#include "VarNumber.hh"

class PongPacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 1;

  PongPacket(std::int64_t payload) : payload{payload} {}

  template<NetworkTypeWriter<std::uint8_t> OpcodeWriter = VarNumber,
          NetworkTypeWriter<std::int64_t> PayloadWriter = BasicTypes>
  friend std::ostream &operator<<(std::ostream &os, const PongPacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    OpcodeWriter::write(data, PongPacket::opcode);
    PayloadWriter::write(data, packet.payload);

    return packet.write_header(os, data);
  }

 private:
  std::int64_t payload;
};