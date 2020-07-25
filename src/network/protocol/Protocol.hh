#pragma once

#include <iostream>

class Session;

class Protocol
{
public:

  Protocol (Session &session) : session{session}
  {}

  virtual void inbound (std::istream &is) = 0;

protected:
  Session &session;
};