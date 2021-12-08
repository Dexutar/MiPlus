#pragma once

#include <cmath>
#include <iostream>
#include <iterator>
#include <tuple>

class VarNumberHandler
{
 public:
  template <std::input_iterator iterator, std::integral number>
  static std::tuple<bool, iterator, number> read(iterator begin, iterator end);

  template <std::integral number>
  static number read(std::istream &is);

  template <std::integral number>
  static void write(std::ostream &os, number value);
};


template <std::input_iterator iterator, std::integral number>
std::tuple<bool, iterator, number> VarNumberHandler::read(iterator begin, iterator end)
{
  number result = 0;
  std::uint8_t index = 0;
  std::uint8_t read = 0;

  iterator it = begin;

  constexpr std::uint8_t max_index =
      std::ceil((std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed) / 7.0);

  do
  {
    if (it == end)
    {
      return {false, end, 0};
    }

    read = *(it++);
    result |= static_cast<number>(read & 0x7F) << (7 * index++);

    if (index > max_index)
    {
      throw std::overflow_error("VarNumber is too big");
    }
  } while (read & 0x80);

  return {true, it, result};
}

template<std::integral number>
number VarNumberHandler::read(std::istream &is)
{
  auto begin = std::istreambuf_iterator<char>(is);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, res] = VarNumberHandler::read<decltype(begin), number>(begin, end);
  return res;
}


template <std::integral number>
void VarNumberHandler::write(std::ostream &os, number value)
{
  constexpr number mask = static_cast<number>(-1) ^ 0x7f;

  while ((value & mask) != 0)
  {
    os << static_cast<std::uint8_t>(value & 0x7F | 0x80);
    value = static_cast<std::make_unsigned<number>::type>(value) >> 7;
  }

  os << static_cast<std::uint8_t>(value);
}