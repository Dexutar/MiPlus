#include "SessionRegistry.hh"

namespace miplus
{
namespace network
{

void SessionRegistry::erase(std::size_t id)
{
  std::lock_guard<std::mutex> lck(sessions_mutex);
  sessions.erase(id);
}

}  // namespace network
}  // namespace miplus