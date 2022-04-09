#pragma once

#include "Bootstrap.hh"
#include "SessionRegistry.hh"

namespace miplus
{
namespace network
{

class ConnectionManager
{
 public:
  ConnectionManager(std::uint16_t port);

 private:
  Bootstrap bootstrap;
  SessionRegistry sessions;
};

}  // namespace network
}  // namespace miplus