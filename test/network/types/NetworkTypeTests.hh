#pragma once

#include <istream>
#include <ostream>

class NetworkTypeTest
{
 public:
  constexpr static void writeBytes(std::ostream &os, std::uint8_t byte, std::uint8_t count)
  {
    while (count > 0)
    {
      os.put(byte);
      --count;
    }
  }

  void static checkBytes(std::istream &is, std::uint8_t byte, std::uint8_t count)
  {
    while (count > 0)
    {
      EXPECT_EQ(byte, is.get());
      --count;
    }
  }
};