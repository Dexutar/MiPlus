#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <sstream>

#include "NetworkTypeTest.hh"
#include "VarNumberMock.hh"
#include "VarString.hh"

using ::testing::_;
using ::testing::Return;

class VarStringTest : public NetworkTypeTest
{
 protected:
  static constexpr std::string_view TEST_STRING = "OwO";
};

TEST_F(VarStringTest, ReadsEmptyString)
{
  VarNumberMock<std::size_t> mock;
  VarNumberMockProxy<std::size_t>::mock = &mock;

  EXPECT_CALL(mock, readVarInt(_)).WillOnce(Return(0));

  EXPECT_EQ("", VarString::readVarString<VarNumberMockProxy<std::size_t>>(stream));
}

TEST_F(VarStringTest, ReadsString)
{
  VarNumberMock<std::size_t> mock;
  VarNumberMockProxy<std::size_t>::mock = &mock;

  EXPECT_CALL(mock, readVarInt(_)).WillOnce(Return(TEST_STRING.size()));

  stream << TEST_STRING;

  EXPECT_EQ(TEST_STRING, VarString::readVarString<VarNumberMockProxy<std::size_t>>(stream));
}

TEST_F(VarStringTest, WritesEmpty)
{
  VarNumberMock<std::size_t> mock;
  VarNumberMockProxy<std::size_t>::mock = &mock;

  EXPECT_CALL(mock, writeVarNumber(_, 0));

  VarString::writeVarString<VarNumberMockProxy<std::size_t>>(stream, "");

  std::string actual;
  stream >> actual;

  EXPECT_EQ("", actual);
}

TEST_F(VarStringTest, WritesString)
{
  VarNumberMock<std::size_t> mock;
  VarNumberMockProxy<std::size_t>::mock = &mock;

  EXPECT_CALL(mock, writeVarNumber(_, TEST_STRING.size()));

  VarString::writeVarString<VarNumberMockProxy<std::size_t>>(stream, TEST_STRING);

  std::string actual;
  stream >> actual;

  EXPECT_EQ(TEST_STRING, actual);
}