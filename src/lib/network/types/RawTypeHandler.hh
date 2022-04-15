#pragma once

#include <bit>
#include <concepts>
#include <istream>
#include <limits>
#include <ostream>

namespace miplus
{
namespace network
{

struct RawTypeHandler
{
  template <std::integral Number>
  requires(sizeof(Number) <= 8) static Number read(std::istream &is);

  template <std::integral Number>
  requires(sizeof(Number) <= 8) static void write(std::ostream &os, Number value);
};

template <std::integral Number>
requires(sizeof(Number) <= 8) Number RawTypeHandler::read(std::istream &is)
{
  Number res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));

  if constexpr (std::endian::native == std::endian::big or sizeof(Number) <= 1)
    return res;
  else
  {
    if constexpr (sizeof(Number) == 2) return __builtin_bswap16(res);
    if constexpr (sizeof(Number) == 4) return __builtin_bswap32(res);
    if constexpr (sizeof(Number) == 8) return __builtin_bswap64(res);
  }
}

template <std::integral Number>
requires(sizeof(Number) <= 8) void RawTypeHandler::write(std::ostream &os, Number value)
{
  if constexpr (sizeof(Number) > 1 and std::endian::native != std::endian::big)
  {
    if constexpr (sizeof(Number) == 2) value = __builtin_bswap16(value);
    if constexpr (sizeof(Number) == 4) value = __builtin_bswap32(value);
    if constexpr (sizeof(Number) == 8) value = __builtin_bswap64(value);
  }

  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}

}  // namespace network
}  // namespace miplus