#pragma once

#include <iostream>
#include <iterator>
#include <tuple>

class VarNumber
{
 public:
  template <std::input_iterator iterator, std::integral number>
  static std::tuple<bool, iterator, number> read(iterator begin, iterator end);

  template <std::integral number>
  static number read(std::istream &is);

  template <std::integral number>
  static void write(std::ostream &os, number value);

 private:
  template <std::integral number>
  struct token {};

  template <std::input_iterator iterator>
  static std::tuple<bool, iterator, std::int32_t> read(iterator begin, iterator end, token<std::int32_t> t);

  template <std::input_iterator iterator>
  static std::tuple<bool, iterator, std::int64_t> read(iterator begin, iterator end, token<std::int64_t> t);
};

template <std::input_iterator iterator, std::integral number>
std::tuple<bool, iterator, number> VarNumber::read(iterator begin, iterator end)
{
  return read(begin,end,token<number>{});
}

template <std::input_iterator iterator>
std::tuple<bool, iterator, std::int32_t> VarNumber::read(iterator begin, iterator end, token<std::int32_t> t)
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
std::tuple<bool, iterator, std::int64_t> VarNumber::read(iterator begin, iterator end, token<std::int64_t> t)
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
void VarNumber::write(std::ostream &os, number value)
{
  constexpr number mask = static_cast<number>(-1) ^ 0x7f;

  while ((value & mask) != 0)
  {
    os << static_cast<std::uint8_t>(value & 0x7F | 0x80);
    value = static_cast<std::make_unsigned<number>::type>(value) >> 7;
  }

  os << static_cast<std::uint8_t>(value);
}