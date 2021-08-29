#pragma once

#include <unordered_map>
#include <mutex>

#include "Session.hh"

class SessionRegistry
{
public:

  template <class Key, class ...Value>
  bool emplace (Key &&key, Value && ... value)
  {
    std::lock_guard<std::mutex> lck(sessions_mutex);  
    return sessions.emplace(std::piecewise_construct,std::forward_as_tuple(key),std::forward_as_tuple(std::forward<Value>(value)..., *this)).second;
  }

  void erase (const std::string &key);

private:
  std::mutex sessions_mutex;
  std::unordered_map<std::string, Session> sessions;
};