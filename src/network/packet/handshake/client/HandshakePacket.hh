#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "RawTypesHandler.hh"
#include "ConnectionState.hh"
#include "NetworkTypeHandlers.hh"
#include "Packet.hh"
#include "VarNumbersHandler.hh"
#include "VarStringHandler.hh"

class HandshakePacket : Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  template<NetworkTypeReader<std::int32_t> VersionReader = VarNumbersHandler,
          NetworkTypeReader<std::string> AddressReader = VarStringHandler,
          NetworkTypeReader<std::uint16_t> PortReader = RawTypesHandler,
          NetworkTypeReader<std::int32_t> StateReader = VarNumbersHandler>
  friend std::istream &operator>>(std::istream &is, HandshakePacket &packet)
  {
    packet.version = VersionReader::template read<std::int32_t>(is);
    packet.server_address = AddressReader::template read<std::string>(is);
    packet.server_port = PortReader::template read<std::uint16_t>(is);
    packet.requested_state = static_cast<ConnectionState>(StateReader::template read<std::int32_t>(is));
    
    return is;
  }

  ConnectionState getRequestedState() const;

 private:
  int version;
  std::string server_address;
  std::uint16_t server_port;
  ConnectionState requested_state;
};