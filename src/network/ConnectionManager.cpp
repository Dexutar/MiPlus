#include "ConnectionManager.hh"

ConnectionManager::ConnectionManager (std::uint16_t port) : bootstrap{port, [&] (Session &&session) {sessionRegistry.add(std::move(session));}}
{
  bootstrap.join();
}