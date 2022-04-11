#pragma once

#include <ostream>
#include <sstream>
#include <string_view>

#include "NetworkTypeHandlerConcepts.hh"
#include "Packet.hh"
#include "VarNumberHandler.hh"
#include "VarStringHandler.hh"

namespace miplus
{
namespace network
{

class ResponsePacket : public Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  ResponsePacket(std::string_view response) : response{response} {}

  template <NetworkTypeWriter<std::uint8_t>     OpcodeWriter   = VarNumberHandler, 
            NetworkTypeWriter<std::string_view> ResponseWriter = VarStringHandler,
            NetworkTypeWriter<std::streamsize>  SizeWriter     = VarNumberHandler>
  friend std::ostream &operator<<(std::ostream &os, const ResponsePacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    OpcodeWriter::write(data, ResponsePacket::opcode);
    ResponseWriter::write(data, packet.response);

    return packet.write_header<SizeWriter>(os, data);
  }

 private:
  std::string_view response;
};

}  // namespace network
}  // namespace miplus