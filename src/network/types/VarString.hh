#pragma once

#include <concepts>
#include <string>

#include "VarNumber.hh"

template <typename T>
concept VarStringReader = requires(std::istream &is)
{
  {
    T::readVarString(is)
    } -> std::same_as<std::string>;
};

template <typename T>
concept VarStringWriter = requires(std::ostream &os, std::string_view string)
{
  {
    T::writeVarString(os, string)
    } -> std::same_as<void>;
};

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
  int size = VN::readVarInt(is);
  std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
  return res;
}

template <typename VN>
void VarString::writeVarString(std::ostream &os, std::string_view string)
{
  VN::writeVarNumber(os, string.size());
  os << string;
}