#pragma once

#include <memory>

#include "ConnectionState.hh"
#include "HandshakeProtocol.hh"
#include "Protocol.hh"
#include "Session.hh"
#include "StatusProtocol.hh"

class ProtocolFactory
{
 public:
  static std::unique_ptr<Protocol> create(ConnectionState state, Session &session)
  {
    switch (state)
    {
      case ConnectionState::Handshake:
        return std::make_unique<HandshakeProtocol>(session);
      case ConnectionState::Status:
        return std::make_unique<StatusProtocol>(session);
    }
    return std::unique_ptr<Protocol>{};
  }
};