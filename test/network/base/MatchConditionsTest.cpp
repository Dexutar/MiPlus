#include "MatchConditionsTest.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iterator>
#include <stdexcept>
#include <utility>

#include "MatchConditions.hh"
#include "NetworkTypeIteratorReaderMock.hh"
#include "Packet.hh"

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

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

  EXPECT_CALL(mock, read(begin,end)).Times(Exactly(0));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  auto [it, match_found] = packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end);

  EXPECT_FALSE(match_found);
  EXPECT_EQ(begin, it);
}

TEST_F(PacketLengthReaderTest, ReadsLength)
{
  writeBytes(0x7f, 1);

  NetworkTypeIteratorReaderMock<Iterator, std::int32_t> mock;
  NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>::mock = &mock;

  auto begin = Iterator(stream);
  auto end = Iterator();

  EXPECT_CALL(mock, read(begin,end)).WillOnce(Return(std::make_pair(end, 127)));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  auto [it, match_found] = packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end);

  EXPECT_TRUE(match_found);
  EXPECT_EQ(end, it);
  EXPECT_EQ(127, packet_length);
}

TEST_F(PacketLengthReaderTest, ThrowsReadingWiderPacket)
{
  writeBytes(0xff, 3);
  writeBytes(0x7f, 1);

  NetworkTypeIteratorReaderMock<Iterator, std::int32_t> mock;
  NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>::mock = &mock;

  auto begin = Iterator(stream);
  auto end = Iterator();

  EXPECT_CALL(mock, read(begin,end)).Times(Exactly(0));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  EXPECT_THROW((packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end)), std::length_error);
}

TEST_F(PacketLengthReaderTest, ThrowsReadingInvalidPacket)
{
  writeBytes(0xff, 3);
  writeBytes(0x7f, 1);

  NetworkTypeIteratorReaderMock<Iterator, std::int32_t> mock;
  NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>::mock = &mock;

  auto begin = Iterator(stream);
  auto end = Iterator();

  EXPECT_CALL(mock, read(begin,end)).Times(Exactly(0));

  PacketLengthReader<Iterator> packet_length_reader{packet_length};
  EXPECT_THROW((packet_length_reader.operator()<NetworkTypeIteratorReaderMockProxy<Iterator, std::int32_t>>(begin,end)), std::length_error);
}