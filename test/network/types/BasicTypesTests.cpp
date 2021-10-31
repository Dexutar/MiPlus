#include <gtest/gtest.h>

#include <limits>
#include <sstream>

#include "BasicTypes.hh"
#include "NetworkTypeTest.hh"

class BasicTypesTest : public NetworkTypeTest
{
};

TEST_F(BasicTypesTest, ReadsUint16Zero)
{
  writeBytes(0x00, 1);

  EXPECT_EQ(0, BasicTypes::read<std::uint16_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint16OneByte)
{
  writeBytes(0x00, 1);
  writeBytes(0xff, 1);

  EXPECT_EQ(0xff, BasicTypes::read<std::uint16_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint16TwoBytes)
{
  writeBytes(0xff, 2);

  EXPECT_EQ(0xffff, BasicTypes::read<std::uint16_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64Zero)
{
  writeBytes(0x00, 1);

  EXPECT_EQ(0, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64OneByte)
{
  writeBytes(0x00, 7);
  writeBytes(0xff, 1);

  EXPECT_EQ(0xff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64TwoBytes)
{
  writeBytes(0x00, 6);
  writeBytes(0xff, 2);

  EXPECT_EQ(0xffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64ThreeBytes)
{
  writeBytes(0x00, 5);
  writeBytes(0xff, 3);

  EXPECT_EQ(0xffffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64FourBytes)
{
  writeBytes(0x00, 4);
  writeBytes(0xff, 4);

  EXPECT_EQ(0xffffffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64FiveBytes)
{
  writeBytes(0x00, 3);
  writeBytes(0xff, 5);

  EXPECT_EQ(0xffffffffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64SixBytes)
{
  writeBytes(0x00, 2);
  writeBytes(0xff, 6);

  EXPECT_EQ(0xffffffffffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64SevenBytes)
{
  writeBytes(0x00, 1);
  writeBytes(0xff, 7);

  EXPECT_EQ(0xffffffffffffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, ReadsUint64EightBytes)
{
  writeBytes(0xff, 8);

  EXPECT_EQ(0xffffffffffffffff, BasicTypes::read<std::uint64_t>(stream));
}

TEST_F(BasicTypesTest, WritesUint16Zero)
{
  BasicTypes::write<std::uint16_t>(stream, 0);

  checkBytes(0x00, 1);
}

TEST_F(BasicTypesTest, WritesUint16OneByte)
{
  BasicTypes::write<std::uint16_t>(stream, 0xff);

  checkBytes(0x00, 1);
  checkBytes(0xff, 1);
}

TEST_F(BasicTypesTest, WritesUint16TwoBytes)
{
  BasicTypes::write<std::uint16_t>(stream, 0xffff);

  checkBytes(0xff, 2);
}

TEST_F(BasicTypesTest, WritesUint64Zero)
{
  BasicTypes::write<std::uint64_t>(stream, 0);

  checkBytes(0x00, 1);
}

TEST_F(BasicTypesTest, WritesUint64OneByte)
{
  BasicTypes::write<std::uint64_t>(stream, 0xff);

  checkBytes(0x00, 7);
  checkBytes(0xff, 1);
}

TEST_F(BasicTypesTest, WritesUint64TwoBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffff);

  checkBytes(0x00, 6);
  checkBytes(0xff, 2);
}

TEST_F(BasicTypesTest, WritesUint64ThreeBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffffff);

  checkBytes(0x00, 5);
  checkBytes(0xff, 3);
}

TEST_F(BasicTypesTest, WritesUint64FourBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffffffff);

  checkBytes(0x00, 4);
  checkBytes(0xff, 4);
}

TEST_F(BasicTypesTest, WritesUint64FiveBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffffffffff);

  checkBytes(0x00, 3);
  checkBytes(0xff, 5);
}

TEST_F(BasicTypesTest, WritesUint64SixBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffffffffffff);

  checkBytes(0x00, 2);
  checkBytes(0xff, 6);
}

TEST_F(BasicTypesTest, WritesUint64SevenBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffffffffffffff);

  checkBytes(0x00, 1);
  checkBytes(0xff, 7);
}

TEST_F(BasicTypesTest, WritesUint64EightBytes)
{
  BasicTypes::write<std::uint64_t>(stream, 0xffffffffffffffff);

  checkBytes(0xff, 8);
}
