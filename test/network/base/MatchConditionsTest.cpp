#include "MatchConditionsTest.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iterator>
#include <stdexcept>
#include <tuple>

#include "MatchConditions.hh"
#include "NetworkTypeIteratorReaderMock.hh"
#include "Packet.hh"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

using namespace miplus::network;
using miplus::testing::network::MatchConditionTest;
using miplus::testing::network::NetworkTypeIteratorReaderMock;
using miplus::testing::network::NetworkTypeIteratorReaderMockProxy;

using Iterator = std::istreambuf_iterator<char>;

class PacketLengthReaderTest : public MatchConditionTest
{
  protected:
    std::size_t packet_length;
};

TEST_F(PacketLengthReaderTest, ReadsEmpty)
{
  NetworkTypeIteratorReaderMock<Iterator, std::int32_t> mock;
  NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>::mock = &mock;

  auto begin = Iterator(stream);
  auto end = Iterator();

  EXPECT_CALL(mock, read(begin,end)).WillOnce(Return(std::make_tuple(false, begin, -1)));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  auto [it, match_found] = packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end);

  EXPECT_FALSE(match_found);
  EXPECT_EQ(begin, it);
}

TEST_F(PacketLengthReaderTest, ReadsLength)
{
  NetworkTypeIteratorReaderMock<Iterator, std::int32_t> mock;
  NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>::mock = &mock;

  auto begin = Iterator(stream);
  auto end = Iterator();

  EXPECT_CALL(mock, read(begin,end)).WillOnce(Return(std::make_tuple(true, ++begin, 10)));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  auto [it, match_found] = packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end);

  EXPECT_TRUE(match_found);
  EXPECT_EQ(++begin, it);
  EXPECT_EQ(10, packet_length);
}

TEST_F(PacketLengthReaderTest, ReadsOverflow)
{
  NetworkTypeIteratorReaderMock<Iterator, std::int32_t> mock;
  NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>::mock = &mock;

  auto begin = Iterator(stream);
  auto end = Iterator();

  EXPECT_CALL(mock, read(begin,end)).WillOnce(Throw(std::overflow_error("")));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  auto [it, match_found] = packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end);

  EXPECT_TRUE(match_found);
  EXPECT_EQ(end, it);
  EXPECT_GT(packet_length, Packet::max_packet_length);
}