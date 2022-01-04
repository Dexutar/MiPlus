#pragma once

#include <bit>
#include <concepts>
#include <istream>
#include <limits>
#include <ostream>

struct RawTypeHandler
{
  template <std::integral number>
  requires(sizeof(number) <= 8) 
  static number read(std::istream &is);
  
  template <std::integral number>
  requires(sizeof(number) <= 8)  
  static void write(std::ostream &os, number value);
};

template <std::integral number>
requires(sizeof(number) <= 8)  
number RawTypeHandler::read(std::istream &is)
{
  number res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));

  if constexpr (std::endian::native == std::endian::big or sizeof(number) <= 1)
    return res;
  else
  {
    if constexpr (sizeof(number) == 2)
      return __builtin_bswap16(res);
    if constexpr (sizeof(number) == 4)
      return __builtin_bswap32(res);
    else
      return __builtin_bswap64(res);
  }
}

template <std::integral number>
requires(sizeof(number) <= 8) 
void RawTypeHandler::write(std::ostream &os, number value)
{
  if constexpr (sizeof(number) > 1 and std::endian::native != std::endian::big) 
  {
    if constexpr (sizeof(number) == 2) 
      value = __builtin_bswap16(value);
    if constexpr (sizeof(number) == 4)
      value = __builtin_bswap32(value);
    if constexpr (sizeof(number) == 8)
      value = __builtin_bswap64(value);
  }
  
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}