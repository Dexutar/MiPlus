#pragma once

#include <ostream>
#include <sstream>
#include <string>

#include "Packet.hh"
#include "VarNumber.hh"
#include "VarString.hh"

class ResponsePacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  ResponsePacket(std::string &&response) : response{response} {}

  friend std::ostream &operator<<(std::ostream &os, const ResponsePacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    VarNumber::write(data, ResponsePacket::opcode);
    VarString::write(data, packet.response);

    return packet.write_header(os, data);
  }

 private:
  std::string response;
};