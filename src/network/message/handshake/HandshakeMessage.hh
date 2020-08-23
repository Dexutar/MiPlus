#pragma once

#include <string>

#include "Message.hh"

class HandshakeMessage : Message
{
public:
  static const std::int16_t opcode = 0;

  friend std::istream& operator>> (std::istream &is, HandshakeMessage &message);

  int getState() const;

  std::ostream& write (std::ostream &os) const override;
  void print () const; 

private:
  
  int version;
  std::string server_address;
  std::uint16_t server_port;
  int next_state;
};