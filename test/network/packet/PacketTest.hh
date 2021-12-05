#pragma once

#include <gtest/gtest.h>

#include <sstream>

class PacketTest : public ::testing::Test
{
 protected:
  std::stringstream stream;
};