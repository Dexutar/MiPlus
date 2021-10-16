#pragma once

#include <gtest/gtest.h>

#include <sstream>

class NetworkTypeTest : public ::testing::Test
{
 protected:
  constexpr void writeBytes(std::uint8_t byte, std::uint8_t count)
  {
    while (count > 0)
    {
      stream.put(byte);
      --count;
    }
  }

  void checkBytes(std::uint8_t byte, std::uint8_t count)
  {
    while (count > 0)
    {
      EXPECT_EQ(byte, stream.get());
      --count;
    }
  }

  std::stringstream stream;
};