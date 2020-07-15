#pragma once

#include "SessionRegistry.hh"
#include "Bootstrap.hh"

class ConnectionManager
{
public:
  ConnectionManager (std::uint16_t port);

private:
  Bootstrap bootstrap;
  SessionRegistry sessionRegistry;
};