#include <gtest/gtest.h>

#include <sstream>

#include "VarNumber.hh"


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
  ss.put(0xff);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(16383, value);
}

TEST(VarInt, ReadThreeBytes) 
{
  std::stringstream ss;
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(2097151, value);
}

TEST(VarInt, ReadFourBytes) 
{
  std::stringstream ss;
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(268435455, value);
}

TEST(VarInt, ReadFiveBytes) 
{
  std::stringstream ss;
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(-1, value);
}

TEST(VarInt, ReadMinusTwo) 
{
  std::stringstream ss;
  ss.put(0xfe);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0x7f);
  
  auto [valid, it, value] = VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>());
  
  EXPECT_TRUE(valid);
  EXPECT_EQ(std::istreambuf_iterator<char>(), it);
  EXPECT_EQ(-2, value);
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
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0xff);
  ss.put(0);

  EXPECT_THROW(VarNumber::readVarInt(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>()), std::overflow_error);
}

TEST(VarInt, ReadStaticInt) 
{
  std::stringstream ss;
  ss.put(1);
  
  EXPECT_EQ(1, VarNumber::readVarInt(ss));
}