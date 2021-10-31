#include "BasicTypes.hh"

#include <bit>

std::uint16_t BasicTypes::readUint16(std::istream &is)
{
  std::uint16_t res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap16(res);
}

std::uint64_t BasicTypes::readUint64(std::istream &is)
{
  std::uint64_t res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap64(res);
}

void BasicTypes::writeUint16(std::ostream &os, std::uint16_t value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap16(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}

void BasicTypes::writeUint64(std::ostream &os, std::uint64_t value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap64(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}