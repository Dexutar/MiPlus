#include <gtest/gtest.h>

#include <limits>
#include <sstream>

#include "BasicTypes.hh"
#include "NetworkTypeTests.hh"

TEST(BasicTypes, ReadUint16Zero)
{
  std::stringstream ss;
  ss.put(0);

  EXPECT_EQ(0, BasicTypes::readUint16(ss));
}

TEST(BasicTypes, ReadUint16OneByte)
{
  std::stringstream ss;
  ss.put(0x00);
  ss.put(0xff);

  EXPECT_EQ(0xff, BasicTypes::readUint16(ss));
}

TEST(BasicTypes, ReadUint16TwoBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0xff, 2);

  EXPECT_EQ(0xffff, BasicTypes::readUint16(ss));
}

TEST(BasicTypes, ReadUint64Zero)
{
  std::stringstream ss;
  ss.put(0);

  EXPECT_EQ(0, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64OneByte)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0x00, 7);
  ss.put(0xff);

  EXPECT_EQ(0xff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64TwoBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0x00, 6);
  NetworkTypeTest::writeBytes(ss, 0xff, 2);

  EXPECT_EQ(0xffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64ThreeBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0x00, 5);
  NetworkTypeTest::writeBytes(ss, 0xff, 3);

  EXPECT_EQ(0xffffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64FourBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0x00, 4);
  NetworkTypeTest::writeBytes(ss, 0xff, 4);

  EXPECT_EQ(0xffffffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64FiveBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0x00, 3);
  NetworkTypeTest::writeBytes(ss, 0xff, 5);

  EXPECT_EQ(0xffffffffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64SixBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0x00, 2);
  NetworkTypeTest::writeBytes(ss, 0xff, 6);

  EXPECT_EQ(0xffffffffffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64SevenBytes)
{
  std::stringstream ss;
  ss.put(0x00);
  NetworkTypeTest::writeBytes(ss, 0xff, 7);

  EXPECT_EQ(0xffffffffffffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, ReadUint64EightBytes)
{
  std::stringstream ss;
  NetworkTypeTest::writeBytes(ss, 0xff, 8);

  EXPECT_EQ(0xffffffffffffffff, BasicTypes::readUint64(ss));
}

TEST(BasicTypes, WriteUint16Zero)
{
  std::stringstream ss;
  BasicTypes::writeUint16(ss, 0);

  EXPECT_EQ(0, ss.get());
}

TEST(BasicTypes, WriteUint16OneByte)
{
  std::stringstream ss;
  BasicTypes::writeUint16(ss, 0xff);

  NetworkTypeTest::checkBytes(ss, 0x00, 1);
  NetworkTypeTest::checkBytes(ss, 0xff, 1);
}

TEST(BasicTypes, WriteUint16TwoBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint16(ss, 0xffff);

  NetworkTypeTest::checkBytes(ss, 0xff, 2);
}

TEST(BasicTypes, WriteUint64Zero)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0);

  EXPECT_EQ(0, ss.get());
}

TEST(BasicTypes, WriteUint64OneByte)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xff);

  NetworkTypeTest::checkBytes(ss, 0x00, 7);
  NetworkTypeTest::checkBytes(ss, 0xff, 1);
}

TEST(BasicTypes, WriteUint64TwoBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffff);

  NetworkTypeTest::checkBytes(ss, 0x00, 6);
  NetworkTypeTest::checkBytes(ss, 0xff, 2);
}

TEST(BasicTypes, WriteUint64ThreeBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffffff);

  NetworkTypeTest::checkBytes(ss, 0x00, 5);
  NetworkTypeTest::checkBytes(ss, 0xff, 3);
}

TEST(BasicTypes, WriteUint64FourBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffffffff);

  NetworkTypeTest::checkBytes(ss, 0x00, 4);
  NetworkTypeTest::checkBytes(ss, 0xff, 4);
}

TEST(BasicTypes, WriteUint64FiveBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffffffffff);

  NetworkTypeTest::checkBytes(ss, 0x00, 3);
  NetworkTypeTest::checkBytes(ss, 0xff, 5);
}

TEST(BasicTypes, WriteUint64SixBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffffffffffff);

  NetworkTypeTest::checkBytes(ss, 0x00, 2);
  NetworkTypeTest::checkBytes(ss, 0xff, 6);
}

TEST(BasicTypes, WriteUint64SevenBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffffffffffffff);

  NetworkTypeTest::checkBytes(ss, 0x00, 1);
  NetworkTypeTest::checkBytes(ss, 0xff, 7);
}

TEST(BasicTypes, WriteUint64EightBytes)
{
  std::stringstream ss;
  BasicTypes::writeUint64(ss, 0xffffffffffffffff);

  NetworkTypeTest::checkBytes(ss, 0xff, 8);
}
