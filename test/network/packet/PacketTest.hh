#pragma once

#include <gtest/gtest.h>

#include <sstream>

namespace miplus
{
namespace testing
{
namespace network
{

class PacketTest : public ::testing::Test
{
 protected:
  std::stringstream stream;
};

}  // namespace network
}  // namespace testing
}  // namespace miplus