#pragma once

#include <ostream>
#include <sstream>
#include <string>

#include "NetworkTypes.hh"
#include "Packet.hh"
#include "VarNumber.hh"
#include "VarString.hh"

class ResponsePacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  ResponsePacket(std::string &&response) : response{response} {}

  template<NetworkTypeWriter<std::uint8_t> OpcodeWriter = VarNumber,
          NetworkTypeWriter<std::string> ResponseWriter = VarString>
  friend std::ostream &operator<<(std::ostream &os, const ResponsePacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    OpcodeWriter::write(data, ResponsePacket::opcode);
    ResponseWriter::write(data, packet.response);

    return packet.write_header(os, data);
  }

 private:
  std::string response;
};