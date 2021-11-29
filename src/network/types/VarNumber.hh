#pragma once

#include <iostream>
#include <iterator>
#include <tuple>

class VarNumber
{
 public:
  template <std::input_iterator iterator>
  static std::tuple<bool, iterator, std::int32_t> readVarInt(iterator begin, iterator end);

  template <std::input_iterator iterator>
  static std::tuple<bool, iterator, std::int64_t> readVarLong(iterator begin, iterator end);

  static std::int32_t readVarInt(std::istream &is);
  static std::int64_t readVarLong(std::istream &is);

  template <std::integral number>
  static void writeVarNumber(std::ostream &os, number value);
};

template <std::input_iterator iterator>
std::tuple<bool, iterator, std::int32_t> VarNumber::readVarInt(iterator begin, iterator end)
{
  std::int32_t result = 0;
  std::uint8_t indx = 0;
  std::uint8_t read = 0;

  iterator it = begin;

  do
  {
    if (it == end)
    {
      return {false, end, 0};
    }

    read = *(it++);
    result |= static_cast<std::int32_t>(read & 0x7F) << (7 * indx++);

    if (indx > 5)
    {
      throw std::overflow_error("VarInt is too big");
    }
  } while (read & 0x80);

  return {true, it, result};
}

template <std::input_iterator iterator>
std::tuple<bool, iterator, std::int64_t> VarNumber::readVarLong(iterator begin, iterator end)
{
  std::int64_t result = 0;
  std::uint8_t indx = 0;
  std::uint8_t read = 0;

  iterator it = begin;

  do
  {
    if (it == end)
    {
      return {false, begin, 0};
    }

    read = *(it++);
    result |= static_cast<std::int64_t>(read & 0x7F) << (indx++ * 7);

    if (indx > 10)
    {
      throw std::overflow_error("VarLong is too big");
    }
  } while (read & 0x80);

  return {true, it, result};
}

template <std::integral number>
void VarNumber::writeVarNumber(std::ostream &os, number value)
{
  constexpr number mask = static_cast<number>(-1) ^ 0x7f;

  while ((value & mask) != 0)
  {
    os << static_cast<std::uint8_t>(value & 0x7F | 0x80);
    value = static_cast<std::make_unsigned<number>::type>(value) >> 7;
  }

  os << static_cast<std::uint8_t>(value);
}