#include "ConnectionManager.hh"

ConnectionManager::ConnectionManager(std::uint16_t port) : bootstrap{port, sessions}
{
  bootstrap.join();
}