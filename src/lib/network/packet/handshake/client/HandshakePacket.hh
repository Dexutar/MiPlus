#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "ConnectionState.hh"
#include "NetworkTypeHandlerConcepts.hh"
#include "Packet.hh"
#include "RawTypeHandler.hh"
#include "VarNumberHandler.hh"
#include "VarStringHandler.hh"

namespace miplus
{
namespace network
{

struct HandshakePacket : Packet
{
  static constexpr std::uint8_t opcode = 0;

  template <NetworkTypeReader<std::int32_t>  VersionReader = VarNumberHandler, 
            NetworkTypeReader<std::string>   AddressReader = VarStringHandler,
            NetworkTypeReader<std::uint16_t> PortReader    = RawTypeHandler, 
            NetworkTypeReader<std::int32_t>  StateReader   = VarNumberHandler>
  friend std::istream &operator>>(std::istream &is, HandshakePacket &packet)
  {
    packet.version = VersionReader::template read<std::int32_t>(is);
    packet.server_address = AddressReader::template read<std::string>(is);
    packet.server_port = PortReader::template read<std::uint16_t>(is);
    packet.requested_state = static_cast<ConnectionState>(StateReader::template read<std::int32_t>(is));

    return is;
  }

  int version;
  std::string server_address;
  std::uint16_t server_port;
  ConnectionState requested_state;
};

}  // namespace network
}  // namespace miplus