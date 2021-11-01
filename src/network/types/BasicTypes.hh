#pragma once

#include <bit>
#include <concepts>
#include <istream>
#include <ostream>

template <typename T>
concept BasicTypesReader = requires(std::istream &is)
{
  {
    T::template read<std::uint16_t>(is)
    } -> std::same_as<std::uint16_t>;
  {
    T::template read<std::uint64_t>(is)
    } -> std::same_as<std::uint64_t>;
};

template <typename T, typename number>
concept BasicTypesWriter = std::integral<number> and requires(std::ostream &os, number value)
{
  {
    T::write(os, value)
    } -> std::same_as<void>;
};

class BasicTypes
{
 public:
  template <std::integral number>
  static number read(std::istream &is);

  template <std::integral number>
  static void write(std::ostream &os, number value);
};

template <>
std::uint16_t BasicTypes::read(std::istream &is)
{
  std::uint16_t res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap16(res);
}

template <>
std::uint64_t BasicTypes::read(std::istream &is)
{
  std::uint64_t res = 0;
  is.read(reinterpret_cast<char *>(&res), sizeof(res));
  if constexpr (std::endian::native == std::endian::big)
    return res;
  else
    return __builtin_bswap64(res);
}

template <>
void BasicTypes::write(std::ostream &os, std::uint16_t value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap16(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}

template <>
void BasicTypes::write(std::ostream &os, std::uint64_t value)
{
  if constexpr (std::endian::native != std::endian::big) value = __builtin_bswap64(value);
  os.write(reinterpret_cast<char *>(&value), sizeof(value));
}