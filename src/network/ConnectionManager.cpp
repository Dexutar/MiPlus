#include "ConnectionManager.hh"

ConnectionManager::ConnectionManager (std::uint16_t port) : bootstrap{port, sessionRegistry}
{
  bootstrap.join();
}