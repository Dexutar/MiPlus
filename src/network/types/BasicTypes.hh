#pragma once

#include <istream>
#include <ostream>

class BasicTypes
{
 public:
  static std::uint16_t readUint16(std::istream &is);

  static std::uint64_t readUint64(std::istream &is);


  static void writeUint16(std::ostream &os, std::uint16_t value);

  static void writeUint64(std::ostream &os, std::uint64_t value);
};