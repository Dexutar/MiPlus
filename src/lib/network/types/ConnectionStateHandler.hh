#pragma once

#include "ConnectionState.hh"
#include "NetworkTypeHandlerConcepts.hh"
#include "VarNumberHandler.hh"

namespace miplus
{
namespace network
{

struct ConnectionStateHandler
{
  template <typename, NetworkTypeReader<std::int32_t> StateReader = VarNumberHandler>
  static ConnectionState read(std::istream &is);
};

template <typename, NetworkTypeReader<std::int32_t> StateReader>
ConnectionState ConnectionStateHandler::read(std::istream &is)
{
  std::int32_t state = StateReader::template read<std::int32_t>(is);

  if (state < ConnectionState::Handshake or state > ConnectionState::Login)
    return ConnectionState::INVALID;
  
  return static_cast<ConnectionState>(state);
}

}
}