#include <gtest/gtest.h>

#include <limits>

#include "NetworkTypeTest.hh"
#include "VarNumberHandler.hh"

using namespace miplus::network;
using miplus::testing::network::NetworkTypeTest;

class VarIntTest : public NetworkTypeTest
{
};

TEST_F(VarIntTest, ReadsZero)
{
  writeBytes(0x00, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(1, stream.tellg());
  EXPECT_EQ(0, value);
}

TEST_F(VarIntTest, ReadsOneByte)
{
  writeBytes(0x7f, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(1, stream.tellg());
  EXPECT_EQ(127, value);
}

TEST_F(VarIntTest, ReadsTwoBytes)
{
  writeBytes(0xff, 1);
  writeBytes(0x7f, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(2, stream.tellg());
  EXPECT_EQ(16383, value);
}

TEST_F(VarIntTest, ReadsThreeBytes)
{
  writeBytes(0xff, 2);
  writeBytes(0x7f, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(3, stream.tellg());
  EXPECT_EQ(2097151, value);
}

TEST_F(VarIntTest, ReadsFourBytes)
{
  writeBytes(0xff, 3);
  writeBytes(0x7f, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(4, stream.tellg());
  EXPECT_EQ(268435455, value);
}

TEST_F(VarIntTest, ReadsFiveBytes)
{
  writeBytes(0xff, 4);
  writeBytes(0x0f, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(5, stream.tellg());
  EXPECT_EQ(-1, value);
}

TEST_F(VarIntTest, ReadsMaxInt)
{
  writeBytes(0xff, 4);
  writeBytes(0x07, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(5, stream.tellg());
  EXPECT_EQ(std::numeric_limits<std::int32_t>::max(), value);
}

TEST_F(VarIntTest, ReadsMinInt)
{
  writeBytes(0x80, 4);
  writeBytes(0x08, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(5, stream.tellg());
  EXPECT_EQ(std::numeric_limits<std::int32_t>::lowest(), value);
}

TEST_F(VarIntTest, ReadsPartialStream)
{
  writeBytes(0x7f, 1);
  writeBytes(0xff, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(1, stream.tellg());
  EXPECT_EQ(127, value);
}

TEST_F(VarIntTest, ReadsIncomplete)
{
  writeBytes(0xff, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);

  EXPECT_EQ(1, stream.tellg());
}

TEST_F(VarIntTest, ReadsOverflow)
{
  writeBytes(0xff, 5);
  writeBytes(0x00, 1);

  EXPECT_THROW((VarNumberHandler::read<std::int32_t>(stream)), std::length_error);
  EXPECT_EQ(6, stream.tellg());
}

TEST_F(VarIntTest, ReadsMultiple)
{
  writeBytes(0xd4, 1);
  writeBytes(0x02, 1);
  writeBytes(0x09, 1);

  std::int32_t value = VarNumberHandler::read<std::int32_t>(stream);
  EXPECT_EQ(2, stream.tellg());
  EXPECT_EQ(340, value);

  value = VarNumberHandler::read<std::int32_t>(stream);
  EXPECT_EQ(3, stream.tellg());
  EXPECT_EQ(9, value);
}


class VarLongTest : public NetworkTypeTest
{
};

TEST_F(VarLongTest, ReadsZero)
{
  writeBytes(0x00, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(1, stream.tellg());
  EXPECT_EQ(0, value);
}

TEST_F(VarLongTest, ReadsOneByte)
{
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(1, stream.tellg());
  EXPECT_EQ(127, value);
}

TEST_F(VarLongTest, ReadsTwoBytes)
{
  writeBytes(0xff, 1);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(2, stream.tellg());
  EXPECT_EQ(16383, value);
}

TEST_F(VarLongTest, ReadsThreeBytes)
{
  writeBytes(0xff, 2);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(3, stream.tellg());
  EXPECT_EQ(2097151, value);
}

TEST_F(VarLongTest, ReadsFourBytes)
{
  writeBytes(0xff, 3);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(4, stream.tellg());
  EXPECT_EQ(268435455, value);
}

TEST_F(VarLongTest, ReadsFiveBytes)
{
  writeBytes(0xff, 4);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(5, stream.tellg());
  EXPECT_EQ(34359738367, value);
}

TEST_F(VarLongTest, ReadsSixBytes)
{
  writeBytes(0xff, 5);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(6, stream.tellg());
  EXPECT_EQ(4398046511103, value);
}

TEST_F(VarLongTest, ReadsSevenBytes)
{
  writeBytes(0xff, 6);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(7, stream.tellg());
  EXPECT_EQ(562949953421311, value);
}

TEST_F(VarLongTest, ReadsEightBytes)
{
  writeBytes(0xff, 7);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(8, stream.tellg());
  EXPECT_EQ(72057594037927935, value);
}

TEST_F(VarLongTest, ReadsNineBytes)
{
  writeBytes(0xff, 8);
  writeBytes(0x7f, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(9, stream.tellg());
  EXPECT_EQ(std::numeric_limits<std::int64_t>::max(), value);
}

TEST_F(VarLongTest, ReadsTenBytes)
{
  writeBytes(0xff, 9);
  writeBytes(0x01, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(10, stream.tellg());
  EXPECT_EQ(-1, value);
}

TEST_F(VarLongTest, ReadsMaxInt)
{
  writeBytes(0xff, 4);
  writeBytes(0x07, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(5, stream.tellg());
  EXPECT_EQ(std::numeric_limits<std::int32_t>::max(), value);
}

TEST_F(VarLongTest, ReadsMinInt)
{
  writeBytes(0x80, 4);
  writeBytes(0xf8, 1);
  writeBytes(0xff, 4);
  writeBytes(0x01, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(10, stream.tellg());
  EXPECT_EQ(std::numeric_limits<std::int32_t>::lowest(), value);
}

TEST_F(VarLongTest, ReadsMinLong)
{
  writeBytes(0x80, 9);
  writeBytes(0x01, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(10, stream.tellg());
  EXPECT_EQ(std::numeric_limits<std::int64_t>::lowest(), value);
}

TEST_F(VarLongTest, ReadsPartialStream)
{
  writeBytes(0x7f, 1);
  writeBytes(0xff, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(1, stream.tellg());
  EXPECT_EQ(127, value);
}

TEST_F(VarLongTest, ReadsIncomplete)
{
  writeBytes(0xff, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);

  EXPECT_EQ(1, stream.tellg());
}

TEST_F(VarLongTest, ReadsOverflow)
{
  writeBytes(0xff, 10);
  writeBytes(0x00, 1);

  EXPECT_THROW((VarNumberHandler::read<std::int64_t>(stream)), std::length_error);
  EXPECT_EQ(11, stream.tellg());
}

TEST_F(VarLongTest, ReadsMultiple)
{
  writeBytes(0xd4, 1);
  writeBytes(0x02, 1);
  writeBytes(0x09, 1);

  std::int64_t value = VarNumberHandler::read<std::int64_t>(stream);
  EXPECT_EQ(2, stream.tellg());
  EXPECT_EQ(340, value);

  value = VarNumberHandler::read<std::int64_t>(stream);
  EXPECT_EQ(3, stream.tellg());
  EXPECT_EQ(9, value);
}


class WriteVarNumberTest : public NetworkTypeTest
{
};

TEST_F(WriteVarNumberTest, WritesZero)
{
  VarNumberHandler::write(stream, 0);

  checkBytes(0x00, 1);
}

TEST_F(WriteVarNumberTest, WritesOneByte)
{
  VarNumberHandler::write(stream, 127);

  checkBytes(0x7f, 1);
}

TEST_F(WriteVarNumberTest, WritesTwoBytes)
{
  VarNumberHandler::write(stream, 128);

  checkBytes(0x80, 1);
  checkBytes(0x01, 1);
}

TEST_F(WriteVarNumberTest, WritesThreeBytes)
{
  VarNumberHandler::write(stream, 25565);

  checkBytes(0xdd, 1);
  checkBytes(0xc7, 1);
  checkBytes(0x01, 1);
}

TEST_F(WriteVarNumberTest, WritesFiveBytes)
{
  VarNumberHandler::write(stream, 2147483647);

  checkBytes(0xff, 4);
  checkBytes(0x07, 1);
}

TEST_F(WriteVarNumberTest, WritesNineBytes)
{
  VarNumberHandler::write(stream, std::numeric_limits<std::int64_t>::max());

  checkBytes(0xff, 8);
  checkBytes(0x7f, 1);
}

TEST_F(WriteVarNumberTest, WritesNegativeOneInt)
{
  VarNumberHandler::write(stream, static_cast<std::int32_t>(-1));

  checkBytes(0xff, 4);
  checkBytes(0x0f, 1);
}

TEST_F(WriteVarNumberTest, WritesNegativeOneLong)
{
  VarNumberHandler::write(stream, static_cast<std::int64_t>(-1));

  checkBytes(0xff, 9);
  checkBytes(0x01, 1);
}

TEST_F(WriteVarNumberTest, WritesMinInt)
{
  VarNumberHandler::write(stream, std::numeric_limits<std::int32_t>::min());

  checkBytes(0x80, 4);
  checkBytes(0x08, 1);
}

TEST_F(WriteVarNumberTest, WritesMinLong)
{
  VarNumberHandler::write(stream, std::numeric_limits<std::int64_t>::min());

  checkBytes(0x80, 9);
  checkBytes(0x01, 1);
}