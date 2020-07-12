#pragma once

#include <unordered_set>
#include <mutex>

#include "Session.hh"

class SessionRegistry
{
public:

  bool add (Session &&session);

private:
  std::mutex sessions_mutex;
  std::unordered_set<Session> sessions;
};