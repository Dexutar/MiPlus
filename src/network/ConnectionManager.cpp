#include "ConnectionManager.hh"

namespace miplus
{
namespace network
{

ConnectionManager::ConnectionManager(std::uint16_t port) : bootstrap{port, sessions}
{
  bootstrap.join();
}

}  // namespace network
}  // namespace miplus