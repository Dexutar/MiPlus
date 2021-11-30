#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "BasicTypes.hh"
#include "ConnectionState.hh"
#include "Packet.hh"
#include "VarNumber.hh"
#include "VarString.hh"

class HandshakePacket : Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  friend std::istream &operator>>(std::istream &is, HandshakePacket &packet)
  {
    packet.version = VarNumber::read<std::int32_t>(is);
    packet.server_address = VarString::read<std::string>(is);
    packet.server_port = BasicTypes::read<std::uint16_t>(is);
    packet.requested_state = static_cast<ConnectionState>(VarNumber::read<std::int32_t>(is));
    
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const HandshakePacket &packet)
  {
    std::stringbuf sb;
    std::ostream data{&sb};

    VarNumber::write(data, HandshakePacket::opcode);
    VarNumber::write(data, packet.version);
    VarString::write(data, packet.server_address);
    BasicTypes::write(data, packet.server_port);
    VarNumber::write(data, static_cast<std::int8_t>(packet.requested_state));

    return packet.write_header(os, data);
  }

  ConnectionState getRequestedState() const;

 private:
  int version;
  std::string server_address;
  std::uint16_t server_port;
  ConnectionState requested_state;
};