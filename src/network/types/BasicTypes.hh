#pragma once

#include <istream>

class BasicTypes
{
public:
  static std::uint16_t readUint16 (std::istream &is)
  {
    std::uint16_t res = 0;
    is.read(reinterpret_cast<char*>(&res),sizeof(res));
    if constexpr (std::endian::native == std::endian::big)
      return res;
    else
      return __builtin_bswap16(res);
  }
};