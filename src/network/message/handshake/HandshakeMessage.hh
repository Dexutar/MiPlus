#pragma once

#include <string>

class HandshakeMessage
{
public:

  friend std::istream& operator>> (std::istream &is, HandshakeMessage &message);

  int getState();

  void print (); 

private:
  
  int version;
  std::string server_address;
  std::uint16_t server_port;
  int next_state;
};