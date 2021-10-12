#pragma once

#include <string>

#include "Packet.hh"

class ResponsePacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  ResponsePacket(std::string &&response) : response{response} {}

 private:
  std::ostream &write(std::ostream &os) const override;

  std::string response;
};