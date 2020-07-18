#pragma once

#include <iostream>

class Protocol
{
public:
  virtual void inbound (std::istream &is) = 0;
};