#pragma once

#include <istream>
#include <ostream>

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

  static void writeUint16 (std::ostream &os, std::uint16_t value)
  {
    if constexpr (std::endian::native != std::endian::big)
      value = __builtin_bswap16(value);
    os.write(reinterpret_cast<char*>(&value),sizeof(value));
  }
};