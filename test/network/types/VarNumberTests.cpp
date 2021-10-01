#include <gtest/gtest.h>

#include <sstream>
#include <limits>

#include "VarNumber.hh"


constexpr void writeBytes(std::ostream &os, std::uint8_t byte, std::uint8_t count)
{
  while (count > 0)
  {
    os.put(byte);
    --count;
  }
}


TEST(VarInt, ReadZero) 
{
  std::stringstream ss;
  ss.put(0);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(0, value);
}

TEST(VarInt, ReadOneByte) 
{
  std::stringstream ss;
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(127, value);
}

TEST(VarInt, ReadTwoBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 1);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(16383, value);
}

TEST(VarInt, ReadThreeBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 2);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(2097151, value);
}

TEST(VarInt, ReadFourBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 3);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(268435455, value);
}

TEST(VarInt, ReadFiveBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 4);
  ss.put(0x0f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(-1, value);
}

TEST(VarInt, ReadMaxInt) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 4);
  ss.put(0x07);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(std::numeric_limits<std::int32_t>::max(), value);
}

TEST(VarInt, ReadMinInt) 
{
  std::stringstream ss;
  writeBytes(ss, 0x80, 4);
  ss.put(0x08);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(std::numeric_limits<std::int32_t>::lowest(), value);
}

TEST(VarInt, ReadValidIterator) 
{
  std::stringstream ss;
  ss.put(0x7f);
  ss.put(0xff);

  auto begin = std::istreambuf_iterator<char>(ss);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, value] = VarNumber::readVarInt(begin, end);
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(++begin, it);
  EXPECT_EQ(127, value);
}

TEST(VarInt, ReadMissing) 
{
  std::stringstream ss;
  ss.put(0xff);

  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_FALSE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
}

TEST(VarInt, ReadOverflow) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 5);
  ss.put(0);

  EXPECT_THROW(VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>()), std::overflow_error);
}

TEST(VarInt, ReadStatic) 
{
  std::stringstream ss;
  ss.put(1);
  
  EXPECT_EQ(1, VarNumber::readVarInt(ss));
}

TEST(VarLong, ReadZero) 
{
  std::stringstream ss;
  ss.put(0);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(0, value);
}

TEST(VarLong, ReadOneByte) 
{
  std::stringstream ss;
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(127, value);
}

TEST(VarLong, ReadTwoBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 1);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(16383, value);
}

TEST(VarLong, ReadThreeBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 2);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(2097151, value);
}

TEST(VarLong, ReadFourBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 3);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(268435455, value);
}

TEST(VarLong, ReadFiveBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 4);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(34359738367, value);
}

TEST(VarLong, ReadSixBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 5);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(4398046511103, value);
}

TEST(VarLong, ReadSevenBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 6);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(562949953421311, value);
}

TEST(VarLong, ReadEightBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 7);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(72057594037927935, value);
}

TEST(VarLong, ReadNineBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 8);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(std::numeric_limits<std::int64_t>::max(), value);
}

TEST(VarLong, ReadTenBytes) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 9);
  ss.put(0x01);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(-1, value);
}

TEST(VarLong, ReadMaxInt) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 4);
  ss.put(0x07);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(std::numeric_limits<std::int32_t>::max(), value);
}

TEST(VarLong, ReadMinInt) 
{
  std::stringstream ss;
  writeBytes(ss, 0x80, 4);
  ss.put(0xf8);
  writeBytes(ss, 0xff, 4);
  ss.put(0x01);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(std::numeric_limits<std::int32_t>::lowest(), value);
}

TEST(VarLong, ReadMinLong) 
{
  std::stringstream ss;
  writeBytes(ss, 0x80, 9);
  ss.put(0x01);
  
  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(std::numeric_limits<std::int64_t>::lowest(), value);
}

TEST(VarLong, ReadValidIterator) 
{
  std::stringstream ss;
  ss.put(0x7f);
  ss.put(0xff);

  auto begin = std::istreambuf_iterator<char>(ss);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, value] = VarNumber::readVarLong(begin, end);
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(++begin, it);
  EXPECT_EQ(127, value);
}

TEST(VarLong, ReadMissing) 
{
  std::stringstream ss;
  ss.put(0xff);

  auto [valid, it, value] = VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_FALSE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
}

TEST(VarLong, ReadOverflow) 
{
  std::stringstream ss;
  writeBytes(ss, 0xff, 10);
  ss.put(0);

  EXPECT_THROW(VarNumber::readVarLong(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>()), std::overflow_error);
}

TEST(VarLong, ReadStatic) 
{
  std::stringstream ss;
  ss.put(127);
  
  EXPECT_EQ(127, VarNumber::readVarLong(ss));
}