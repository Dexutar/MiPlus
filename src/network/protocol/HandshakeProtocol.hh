#pragma once

#include "Protocol.hh"

#include "HandshakePacket.hh"

class HandshakeProtocol : public Protocol
{
public:

  HandshakeProtocol (Session &session) : Protocol{session}
  {}

  void inbound (std::istream &is) override;

private:

  void handle (const HandshakePacket &packet);

  bool first = false;
};