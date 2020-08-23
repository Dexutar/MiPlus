#pragma once

#include "Protocol.hh"

#include "HandshakeMessage.hh"

class HandshakeProtocol : public Protocol
{
public:

  HandshakeProtocol (Session &session) : Protocol{session}
  {}

  void inbound (std::istream &is) override;

private:

  void handle (const HandshakeMessage &message);

  bool first = false;
};