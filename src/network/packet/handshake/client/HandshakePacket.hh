#pragma once

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

  template <VarStringReader VS = VarString>
  friend std::istream &operator>>(std::istream &is, HandshakePacket &packet)
  {
    packet.version = VarNumber::readVarInt(is);
    packet.server_address = VS::readVarString(is);
    packet.server_port = BasicTypes::read<std::uint16_t>(is);
    packet.requested_state = static_cast<ConnectionState>(VarNumber::readVarInt(is));
    return is;
  }

  ConnectionState getRequestedState() const;

 private:
  std::ostream &write(std::ostream &os) const override;

  int version;
  std::string server_address;
  std::uint16_t server_port;
  ConnectionState requested_state;
};