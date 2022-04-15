#pragma once

#include <cmath>
#include <iostream>
#include <iterator>

namespace miplus
{
namespace network
{

class VarNumberHandler
{
 public:
  template <std::integral Number>
  static Number read(std::istream &is);

  template <std::integral Number>
  static void write(std::ostream &os, Number value);

 private:
  template <std::input_iterator Iterator, std::integral Number>
  static Number read(Iterator begin, Iterator end);
};

template <std::input_iterator Iterator, std::integral Number>
Number VarNumberHandler::read(Iterator begin, Iterator end)
{
  Number result = 0;
  std::uint8_t index = 0;
  std::uint8_t read = 0;

  Iterator it = begin;

  constexpr std::uint8_t max_index = std::ceil((std::numeric_limits<Number>::digits + std::numeric_limits<Number>::is_signed) / 7.0);

  do
  {
    if (it == end)
      return result;
    
    read = *(it++);
    result |= static_cast<Number>(read & 0x7F) << (7 * index++);

    if (index > max_index)
      throw std::length_error("VarNumber is too big");
  } while (read & 0x80);

  return result;
}

template <std::integral Number>
Number VarNumberHandler::read(std::istream &is)
{
  auto begin = std::istreambuf_iterator<char>(is);
  auto end = std::istreambuf_iterator<char>();

  return VarNumberHandler::read<decltype(begin), Number>(begin, end);
}

template <std::integral Number>
void VarNumberHandler::write(std::ostream &os, Number value)
{
  constexpr Number mask = static_cast<Number>(-1) ^ 0x7f;

  while ((value & mask) != 0)
  {
    os << static_cast<std::uint8_t>(value & 0x7F | 0x80);
    value = static_cast<std::make_unsigned<Number>::type>(value) >> 7;
  }

  os << static_cast<std::uint8_t>(value);
}

}  // namespace network
}  // namespace miplus