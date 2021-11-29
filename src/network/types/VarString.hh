#pragma once

#include <string>

#include "VarNumber.hh"

class VarString
{
 public:
  template <typename VN = VarNumber>
  static std::string readVarString(std::istream &is);

  template <typename VN = VarNumber>
  static void writeVarString(std::ostream &os, std::string_view string);
};

template <typename VN>
std::string VarString::readVarString(std::istream &is)
{
  std::string res;
  int size = VN::template read<std::int32_t>(is);
  std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
  return res;
}

template <typename VN>
void VarString::writeVarString(std::ostream &os, std::string_view string)
{
  VN::write(os, string.size());
  os << string;
}