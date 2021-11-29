#pragma once

#include <bit>
#include <concepts>
#include <istream>
#include <limits>
#include <ostream>

class BasicTypes
{
 public:
  template <std::integral number>
  requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 16) 
  static number read(std::istream &is);

  template <std::integral number>
  requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 32) 
  static number read(std::istream &is);

  template <std::integral number>
  requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 64) 
  static number read(std::istream &is);

  
  template <std::integral number>
  requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 16) 
  static void write(std::ostream &os, number value);
  
  template <std::integral number>
  requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 32) 
  static void write(std::ostream &os, number value);
  
  template <std::integral number>
  requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 64) 
  static void write(std::ostream &os, number value);
};

template <std::integral number>
requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 16) 
number BasicTypes::read(std::istream &is)
{
  number res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap16(res);
}

template <std::integral number>
requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 32) 
number BasicTypes::read(std::istream &is)
{
  number res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap32(res);
}

template <std::integral number>
requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 64) 
number BasicTypes::read(std::istream &is)
{
  number res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap64(res);
}

template <std::integral number>
requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 16) 
void BasicTypes::write(std::ostream &os, number value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap16(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}

template <std::integral number>
requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 32) 
void BasicTypes::write(std::ostream &os, number value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap32(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}

template <std::integral number>
requires(std::numeric_limits<number>::digits + std::numeric_limits<number>::is_signed == 64) 
void BasicTypes::write(std::ostream &os, number value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap64(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}