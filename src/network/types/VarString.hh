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
  template <VarNumberReader VN = VarNumber>
  static std::string readVarString(std::istream &is);

  template <VarNumberWriter<std::size_t> VN = VarNumber>
  static void writeVarString(std::ostream &os, std::string_view string);
};

template <VarNumberReader VN>
std::string VarString::readVarString(std::istream &is)
{
  std::string res;
  int size = VN::readVarInt(is);
  std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
  return res;
}

template <VarNumberWriter<std::size_t> VN>
void VarString::writeVarString(std::ostream &os, std::string_view string)
{
  VN::writeVarNumber(os, string.size());
  os << string;
}