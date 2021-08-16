#pragma once

#include <memory>

#include "Protocol.hh"
#include "Session.hh"
#include "HandshakeProtocol.hh"
#include "ConnectionState.hh"

class ProtocolFactory
{
public:
  static std::unique_ptr<Protocol> create (ConnectionState state, Session &session)
  {
    switch (state)
    {
    case ConnectionState::Handshake:
      return std::make_unique<HandshakeProtocol>(session);
    }
    return std::unique_ptr<Protocol>{};
  }
};