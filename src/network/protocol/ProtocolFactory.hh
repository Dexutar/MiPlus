#pragma once

#include <memory>

#include "Protocol.hh"
#include "Session.hh"
#include "HandshakeProtocol.hh"

enum class Protocols { Handshake };

class ProtocolFactory
{
public:
  static std::unique_ptr<Protocol> create (Protocols protocol, Session &session)
  {
    switch (protocol)
    {
    case Protocols::Handshake:
      return std::make_unique<HandshakeProtocol>(session);
    }
    return std::unique_ptr<Protocol>{};
  }
};