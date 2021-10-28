#pragma once

#include <string>

#include "VarNumber.hh"

class VarString
{
 public:
  template <VarNumberReader VN = VarNumber>
  static std::string readVarString(std::istream &is)
  {
    std::string res;
    int size = VN::readVarInt(is);
    std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
    return res;
  }

  template <VarNumberWriter<std::size_t> VN = VarNumber>
  static void writeVarString(std::ostream &os, std::string_view string)
  {
    VN::writeVarNumber(os, string.size());
    os << string;
  }
};