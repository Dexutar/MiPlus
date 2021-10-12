#pragma once

#include "HandshakePacket.hh"
#include "Protocol.hh"

class HandshakeProtocol : public Protocol
{
 public:
  HandshakeProtocol(Session &session) : Protocol{session} {}

  void inbound(std::istream &is) override;

 private:
  void handle(const HandshakePacket &packet);
};