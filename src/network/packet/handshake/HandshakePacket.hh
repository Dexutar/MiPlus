#pragma once

#include <string>

#include "Packet.hh"
#include "ConnectionState.hh"

class HandshakePacket : Packet
{
public:
  static const std::int16_t opcode = 0;

  friend std::istream& operator>> (std::istream &is, HandshakePacket &packet);

  ConnectionState getRequestedState() const;

  std::ostream& write (std::ostream &os) const override;
  void print () const; 

private:
  
  int version;
  std::string server_address;
  std::uint16_t server_port;
  ConnectionState requested_state;
};