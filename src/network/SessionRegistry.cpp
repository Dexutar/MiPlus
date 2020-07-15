#include "SessionRegistry.hh"

#include <iostream>

bool SessionRegistry::add(Session &&session)
{
  std::lock_guard<std::mutex> lck(sessions_mutex);
  return sessions.insert(std::move(session)).second;
}