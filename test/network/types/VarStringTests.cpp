#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <sstream>

#include "NetworkTypeTest.hh"
#include "VarNumberMock.hh"
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
  VarNumberMock<std::int32_t> mock;
  VarNumberMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(0));

  EXPECT_EQ("", ([&]{return VarStringHandler::read<std::string, VarNumberMockProxy<std::int32_t>>(stream);}()));
}

TEST_F(VarStringTest, ReadsString)
{
  VarNumberMock<std::int32_t> mock;
  VarNumberMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(TEST_STRING.size()));

  stream << TEST_STRING;

  EXPECT_EQ(TEST_STRING, ([&]{return VarStringHandler::read<std::string, VarNumberMockProxy<std::int32_t>>(stream);}()));
}

TEST_F(VarStringTest, WritesEmptyString)
{
  VarNumberMock<std::int32_t> mock;
  VarNumberMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, write(_, 0));

  VarStringHandler::write<VarNumberMockProxy<std::int32_t>>(stream, "");

  std::string actual;
  stream >> actual;

  EXPECT_EQ("", actual);
}

TEST_F(VarStringTest, WritesString)
{
  VarNumberMock<std::int32_t> mock;
  VarNumberMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, write(_, TEST_STRING.size()));

  VarStringHandler::write<VarNumberMockProxy<std::int32_t>>(stream, TEST_STRING);

  std::string actual;
  stream >> actual;

  EXPECT_EQ(TEST_STRING, actual);
}