#include "SessionRegistry.hh"

#include <iostream>

bool SessionRegistry::add(Session &&session)
{
  std::lock_guard<std::mutex> lck(sessions_mutex);
  std::cout << "session added" << std::endl;
  return sessions.insert(std::move(session)).second;
}