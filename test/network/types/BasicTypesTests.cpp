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

  EXPECT_EQ(0, BasicTypes::readUint16(stream));
}

TEST_F(BasicTypesTest, ReadsUint16OneByte)
{
  writeBytes(0x00, 1);
  writeBytes(0xff, 1);

  EXPECT_EQ(0xff, BasicTypes::readUint16(stream));
}

TEST_F(BasicTypesTest, ReadsUint16TwoBytes)
{
  writeBytes(0xff, 2);

  EXPECT_EQ(0xffff, BasicTypes::readUint16(stream));
}

TEST_F(BasicTypesTest, ReadsUint64Zero)
{
  writeBytes(0x00, 1);

  EXPECT_EQ(0, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64OneByte)
{
  writeBytes(0x00, 7);
  writeBytes(0xff, 1);

  EXPECT_EQ(0xff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64TwoBytes)
{
  writeBytes(0x00, 6);
  writeBytes(0xff, 2);

  EXPECT_EQ(0xffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64ThreeBytes)
{
  writeBytes(0x00, 5);
  writeBytes(0xff, 3);

  EXPECT_EQ(0xffffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64FourBytes)
{
  writeBytes(0x00, 4);
  writeBytes(0xff, 4);

  EXPECT_EQ(0xffffffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64FiveBytes)
{
  writeBytes(0x00, 3);
  writeBytes(0xff, 5);

  EXPECT_EQ(0xffffffffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64SixBytes)
{
  writeBytes(0x00, 2);
  writeBytes(0xff, 6);

  EXPECT_EQ(0xffffffffffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64SevenBytes)
{
  writeBytes(0x00, 1);
  writeBytes(0xff, 7);

  EXPECT_EQ(0xffffffffffffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, ReadsUint64EightBytes)
{
  writeBytes(0xff, 8);

  EXPECT_EQ(0xffffffffffffffff, BasicTypes::readUint64(stream));
}

TEST_F(BasicTypesTest, WritesUint16Zero)
{
  BasicTypes::writeUint16(stream, 0);

  checkBytes(0x00, 1);
}

TEST_F(BasicTypesTest, WritesUint16OneByte)
{
  BasicTypes::writeUint16(stream, 0xff);

  checkBytes(0x00, 1);
  checkBytes(0xff, 1);
}

TEST_F(BasicTypesTest, WritesUint16TwoBytes)
{
  BasicTypes::writeUint16(stream, 0xffff);

  checkBytes(0xff, 2);
}

TEST_F(BasicTypesTest, WritesUint64Zero)
{
  BasicTypes::writeUint64(stream, 0);

  checkBytes(0x00, 1);
}

TEST_F(BasicTypesTest, WritesUint64OneByte)
{
  BasicTypes::writeUint64(stream, 0xff);

  checkBytes(0x00, 7);
  checkBytes(0xff, 1);
}

TEST_F(BasicTypesTest, WritesUint64TwoBytes)
{
  BasicTypes::writeUint64(stream, 0xffff);

  checkBytes(0x00, 6);
  checkBytes(0xff, 2);
}

TEST_F(BasicTypesTest, WritesUint64ThreeBytes)
{
  BasicTypes::writeUint64(stream, 0xffffff);

  checkBytes(0x00, 5);
  checkBytes(0xff, 3);
}

TEST_F(BasicTypesTest, WritesUint64FourBytes)
{
  BasicTypes::writeUint64(stream, 0xffffffff);

  checkBytes(0x00, 4);
  checkBytes(0xff, 4);
}

TEST_F(BasicTypesTest, WritesUint64FiveBytes)
{
  BasicTypes::writeUint64(stream, 0xffffffffff);

  checkBytes(0x00, 3);
  checkBytes(0xff, 5);
}

TEST_F(BasicTypesTest, WritesUint64SixBytes)
{
  BasicTypes::writeUint64(stream, 0xffffffffffff);

  checkBytes(0x00, 2);
  checkBytes(0xff, 6);
}

TEST_F(BasicTypesTest, WritesUint64SevenBytes)
{
  BasicTypes::writeUint64(stream, 0xffffffffffffff);

  checkBytes(0x00, 1);
  checkBytes(0xff, 7);
}

TEST_F(BasicTypesTest, WritesUint64EightBytes)
{
  BasicTypes::writeUint64(stream, 0xffffffffffffffff);

  checkBytes(0xff, 8);
}
