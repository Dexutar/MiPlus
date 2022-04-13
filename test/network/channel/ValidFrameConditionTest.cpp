#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iterator>
#include <stdexcept>
#include <utility>

#include "ValidFrameCondition.hh"

using namespace miplus::network;

using Iterator = std::istreambuf_iterator<char>;

class ValidFrameConditionTest : public ::testing::Test
{
 protected:
  constexpr void writeBytes(std::uint8_t byte, std::uint8_t count)
  {
    while (count > 0)
    {
      stream.put(byte);
      --count;
    }
  }

  std::stringstream stream;
};

TEST_F(ValidFrameConditionTest, DoesNotFindMatchInEmptyScann)
{
  auto begin = Iterator(stream);
  auto end = Iterator();


  ValidFrameCondition<Iterator> valid_frame_condition;
  auto [it, match_found] = valid_frame_condition(begin, end);

  EXPECT_FALSE(match_found);
  EXPECT_EQ(begin, it);
}

TEST_F(ValidFrameConditionTest, FindsMatchInValidScann)
{
  writeBytes(0x7f, 1);

  auto begin = Iterator(stream);
  auto end = Iterator();

  ValidFrameCondition<Iterator> valid_frame_condition;
  auto [it, match_found] = valid_frame_condition(begin, end);

  EXPECT_TRUE(match_found);
  EXPECT_EQ(end, it);
}

TEST_F(ValidFrameConditionTest, ReturnsValidIteratorInMatch)
{
  writeBytes(0x7f, 1);
  writeBytes(0xff, 2);
  writeBytes(0x7f, 1);
  

  auto begin = Iterator(stream);
  auto end = Iterator();

  ValidFrameCondition<Iterator> valid_frame_condition;
  auto [it, match_found] = valid_frame_condition(begin, end);

  auto expected = ++begin;

  EXPECT_TRUE(match_found);
  EXPECT_EQ(expected, it);
}

TEST_F(ValidFrameConditionTest, DoesNotFindMatchInWiderScann)
{
  writeBytes(0xff, 3);
  writeBytes(0x7f, 1);

  auto begin = Iterator(stream);
  auto end = Iterator();

  ValidFrameCondition<Iterator> valid_frame_condition;
  auto [it, match_found] = valid_frame_condition(begin, end);

  EXPECT_TRUE(match_found);
  EXPECT_EQ(end, it);
}