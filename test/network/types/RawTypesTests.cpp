#include <gtest/gtest.h>

#include <limits>
#include <sstream>

#include "RawTypeHandler.hh"
#include "NetworkTypeTest.hh"

class RawTypesTest : public NetworkTypeTest
{
};

TEST_F(RawTypesTest, ReadsUint16Zero)
{
  writeBytes(0x00, 1);

  EXPECT_EQ(0, RawTypeHandler::read<std::uint16_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint16OneByte)
{
  writeBytes(0x00, 1);
  writeBytes(0xff, 1);

  EXPECT_EQ(0xff, RawTypeHandler::read<std::uint16_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint16TwoBytes)
{
  writeBytes(0xff, 2);

  EXPECT_EQ(0xffff, RawTypeHandler::read<std::uint16_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64Zero)
{
  writeBytes(0x00, 1);

  EXPECT_EQ(0, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64OneByte)
{
  writeBytes(0x00, 7);
  writeBytes(0xff, 1);

  EXPECT_EQ(0xff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64TwoBytes)
{
  writeBytes(0x00, 6);
  writeBytes(0xff, 2);

  EXPECT_EQ(0xffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64ThreeBytes)
{
  writeBytes(0x00, 5);
  writeBytes(0xff, 3);

  EXPECT_EQ(0xffffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64FourBytes)
{
  writeBytes(0x00, 4);
  writeBytes(0xff, 4);

  EXPECT_EQ(0xffffffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64FiveBytes)
{
  writeBytes(0x00, 3);
  writeBytes(0xff, 5);

  EXPECT_EQ(0xffffffffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64SixBytes)
{
  writeBytes(0x00, 2);
  writeBytes(0xff, 6);

  EXPECT_EQ(0xffffffffffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64SevenBytes)
{
  writeBytes(0x00, 1);
  writeBytes(0xff, 7);

  EXPECT_EQ(0xffffffffffffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, ReadsUint64EightBytes)
{
  writeBytes(0xff, 8);

  EXPECT_EQ(0xffffffffffffffff, RawTypeHandler::read<std::uint64_t>(stream));
}

TEST_F(RawTypesTest, WritesUint16Zero)
{
  RawTypeHandler::write<std::uint16_t>(stream, 0);

  checkBytes(0x00, 1);
}

TEST_F(RawTypesTest, WritesUint16OneByte)
{
  RawTypeHandler::write<std::uint16_t>(stream, 0xff);

  checkBytes(0x00, 1);
  checkBytes(0xff, 1);
}

TEST_F(RawTypesTest, WritesUint16TwoBytes)
{
  RawTypeHandler::write<std::uint16_t>(stream, 0xffff);

  checkBytes(0xff, 2);
}

TEST_F(RawTypesTest, WritesUint64Zero)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0);

  checkBytes(0x00, 8);
}

TEST_F(RawTypesTest, WritesUint64OneByte)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xff);

  checkBytes(0x00, 7);
  checkBytes(0xff, 1);
}

TEST_F(RawTypesTest, WritesUint64TwoBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffff);

  checkBytes(0x00, 6);
  checkBytes(0xff, 2);
}

TEST_F(RawTypesTest, WritesUint64ThreeBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffffff);

  checkBytes(0x00, 5);
  checkBytes(0xff, 3);
}

TEST_F(RawTypesTest, WritesUint64FourBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffffffff);

  checkBytes(0x00, 4);
  checkBytes(0xff, 4);
}

TEST_F(RawTypesTest, WritesUint64FiveBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffffffffff);

  checkBytes(0x00, 3);
  checkBytes(0xff, 5);
}

TEST_F(RawTypesTest, WritesUint64SixBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffffffffffff);

  checkBytes(0x00, 2);
  checkBytes(0xff, 6);
}

TEST_F(RawTypesTest, WritesUint64SevenBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffffffffffffff);

  checkBytes(0x00, 1);
  checkBytes(0xff, 7);
}

TEST_F(RawTypesTest, WritesUint64EightBytes)
{
  RawTypeHandler::write<std::uint64_t>(stream, 0xffffffffffffffff);

  checkBytes(0xff, 8);
}
