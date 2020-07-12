#pragma once

#include <memory>

#include "Protocol.hh"
#include "HandshakeProtocol.hh"

enum class Protocols { Handshake };

class ProtocolFactory
{
public:
  static std::unique_ptr<Protocol> create (Protocols protocol)
  {
    switch (protocol)
    {
    case Protocols::Handshake:
      return std::make_unique<HandshakeProtocol>();
    }
    return std::unique_ptr<Protocol>{};
  }
};