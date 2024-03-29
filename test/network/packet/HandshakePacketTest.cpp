#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "ConnectionState.hh"
#include "HandshakePacket.hh"
#include "NetworkTypeHandlerMock.hh"
#include "PacketTest.hh"

using ::testing::_;
using ::testing::Return;

using namespace miplus::network;
using miplus::testing::network::NetworkTypeHandlerMock;
using miplus::testing::network::NetworkTypeHandlerMockProxy;
using miplus::testing::network::PacketTest;

class HandshakePacketTest : public PacketTest
{
 protected:
  static constexpr int VERSION = 340;
  inline static const std::string SERVER_ADDRESS = "192.168.1.1";
  static constexpr std::uint16_t SERVER_PORT = 25565;
  static constexpr ConnectionState REQUESTED_STATE = ConnectionState::Status;
};

TEST_F(HandshakePacketTest, ReadsPacket)
{
  NetworkTypeHandlerMock<std::int32_t> integerMock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &integerMock;

  NetworkTypeHandlerMock<std::string> stringMock;
  NetworkTypeHandlerMockProxy<std::string>::mock = &stringMock;

  NetworkTypeHandlerMock<std::uint16_t> shortMock;
  NetworkTypeHandlerMockProxy<std::uint16_t>::mock = &shortMock;

  NetworkTypeHandlerMock<ConnectionState> stateMock;
  NetworkTypeHandlerMockProxy<ConnectionState>::mock = &stateMock;

  EXPECT_CALL(integerMock, read(_)).WillOnce(Return(VERSION));
  EXPECT_CALL(stringMock, read(_)).WillOnce(Return(SERVER_ADDRESS));
  EXPECT_CALL(shortMock, read(_)).WillOnce(Return(SERVER_PORT));
  EXPECT_CALL(stateMock, read(_)).WillOnce(Return(REQUESTED_STATE));

  HandshakePacket packet;
  operator>><NetworkTypeHandlerMockProxy<std::int32_t>, 
             NetworkTypeHandlerMockProxy<std::string>, 
             NetworkTypeHandlerMockProxy<std::uint16_t>,
             NetworkTypeHandlerMockProxy<ConnectionState>>
            (stream, packet);

  EXPECT_EQ(REQUESTED_STATE, packet.requested_state);
}