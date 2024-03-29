#pragma once

#include <variant>
#include <stdexcept>

#include "ConnectionState.hh"
#include "HandshakeProtocol.hh"
#include "LoginProtocol.hh"
#include "PlayProtocol.hh"
#include "Protocol.hh"
#include "Session.hh"
#include "StatusProtocol.hh"

namespace miplus
{
namespace network
{

class ProtocolFactory
{
 public:
  static Protocol create(ConnectionState state, Session *session)
  {
    switch (state)
    {
      case ConnectionState::Handshake:
        return HandshakeProtocol(session);
      case ConnectionState::Play:
        return PlayProtocol(session);
      case ConnectionState::Status:
        return StatusProtocol(session);
      case ConnectionState::Login:
        return LoginProtocol(session);
      default:
        throw std::invalid_argument("Invalid state requested");
    }
  }
};

}  // namespace network
}  // namespace miplus