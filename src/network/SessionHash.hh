#pragma once

#include "Session.hh"

namespace std
{
  template <>
  struct hash<Session>
  {
    size_t operator() (const Session &session) const;
  };
}
