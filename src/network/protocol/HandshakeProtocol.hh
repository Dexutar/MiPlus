#pragma once

#include <array>
#include <memory>
#include <tuple>

#include "Protocol.hh"

#include "HandshakeCodec.hh"
#include "HandshakeHandler.hh"

class HandshakeProtocol : public Protocol
{
public:
  
  void inbound (std::istream &is) override;

private:
  HandshakeCodec handshakeCodec;
  HandshakeHandler handshakeHandler;
};