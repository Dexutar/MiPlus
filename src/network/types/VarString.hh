#pragma once

#include <string>

class VarString
{
public:
  static std::string readVarString (std::istream &is);

  static void writeVarString (std::ostream &os, const std::string &string);
};