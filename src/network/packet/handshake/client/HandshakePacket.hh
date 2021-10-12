#pragma once

#include <string>

#include "ConnectionState.hh"
#include "Packet.hh"

class HandshakePacket : Packet
{
 public:
  static constexpr std::uint8_t opcode = 0;

  friend std::istream &operator>>(std::istream &is, HandshakePacket &packet);

  ConnectionState getRequestedState() const;
  void print() const;

 private:
  std::ostream &write(std::ostream &os) const override;

  int version;
  std::string server_address;
  std::uint16_t server_port;
  ConnectionState requested_state;
};