# pragma once

#include <gtest/gtest.h>

#include <sstream>

namespace miplus
{
namespace testing
{
namespace network
{

class MatchConditionTest : public ::testing::Test
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

  std::stringstream stream;
};

}  // namespace network
}  // namespace testing
}  // namespace miplus