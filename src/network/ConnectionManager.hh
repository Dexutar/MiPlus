#pragma once

#include "Bootstrap.hh"
#include "SessionRegistry.hh"

class ConnectionManager
{
 public:
  ConnectionManager(std::uint16_t port);

 private:
  Bootstrap bootstrap;
  SessionRegistry sessions;
};