#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "NetworkTypeHandlerMock.hh"
#include "PacketTest.hh"
#include "PingPacket.hh"

using ::testing::_;
using ::testing::Return;

class PingPacketTest : public PacketTest
{
 protected:
  static constexpr std::int64_t PAYLOAD = 1638704181000;
};

TEST_F(PingPacketTest, ReadsPacket)
{
  NetworkTypeHandlerMock<std::int64_t> mock;
  NetworkTypeHandlerMockProxy<std::int64_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(PAYLOAD));

  PingPacket packet;
  operator>> <NetworkTypeHandlerMockProxy<std::int64_t>>
  (stream, packet);

  EXPECT_EQ(PAYLOAD, packet.get_payload());
}