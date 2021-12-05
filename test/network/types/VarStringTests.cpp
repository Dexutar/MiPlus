#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string_view>

#include "NetworkTypeHandlerMock.hh"
#include "NetworkTypeTest.hh"
#include "VarStringHandler.hh"

using ::testing::_;
using ::testing::Return;

class VarStringTest : public NetworkTypeTest
{
 protected:
  static constexpr std::string_view TEST_STRING = "OwO";
};

TEST_F(VarStringTest, ReadsEmptyString)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(0));

  EXPECT_EQ("", ([&]{return VarStringHandler::read<std::string, NetworkTypeHandlerMockProxy<std::int32_t>>(stream);}()));
}

TEST_F(VarStringTest, ReadsString)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(TEST_STRING.size()));

  stream << TEST_STRING;

  EXPECT_EQ(TEST_STRING, ([&]{return VarStringHandler::read<std::string, NetworkTypeHandlerMockProxy<std::int32_t>>(stream);}()));
}

TEST_F(VarStringTest, WritesEmptyString)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, write(_, 0));

  VarStringHandler::write<NetworkTypeHandlerMockProxy<std::int32_t>>(stream, "");

  std::string actual;
  stream >> actual;

  EXPECT_EQ("", actual);
}

TEST_F(VarStringTest, WritesString)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, write(_, TEST_STRING.size()));

  VarStringHandler::write<NetworkTypeHandlerMockProxy<std::int32_t>>(stream, TEST_STRING);

  std::string actual;
  stream >> actual;

  EXPECT_EQ(TEST_STRING, actual);
}