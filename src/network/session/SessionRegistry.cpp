#include "SessionRegistry.hh"

void SessionRegistry::erase (const std::string &key)
{
  std::lock_guard<std::mutex> lck(sessions_mutex);
  sessions.erase(key);
}