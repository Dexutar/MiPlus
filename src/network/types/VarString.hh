#pragma once

#include <string>

#include "VarNumber.hh"

class VarString
{
 public:
  template <typename, typename VN = VarNumber>
  static std::string read(std::istream &is);

  template <typename VN = VarNumber>
  static void write(std::ostream &os, std::string_view string);
};

template <typename, typename VN>
std::string VarString::read(std::istream &is)
{
  std::string res;
  int size = VN::template read<std::int32_t>(is);
  std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
  return res;
}

template <typename VN>
void VarString::write(std::ostream &os, std::string_view string)
{
  VN::write(os, string.size());
  os << string;
}