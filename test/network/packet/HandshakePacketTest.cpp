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
using miplus::testing::network::PacketTest;
using miplus::testing::network::NetworkTypeHandlerMock;
using miplus::testing::network::NetworkTypeHandlerMockProxy;

class HandshakePacketTest : public PacketTest
{
 protected:
  static constexpr int             VERSION         = 340;
  inline static const std::string  SERVER_ADDRESS  = "192.168.1.1";
  static constexpr std::uint16_t   SERVER_PORT     = 25565;

  void test_read_status_request(std::int8_t id, ConnectionState state)
  {
    NetworkTypeHandlerMock<std::int32_t> integerMock;
    NetworkTypeHandlerMockProxy<std::int32_t>::mock = &integerMock;

    NetworkTypeHandlerMock<std::string> stringMock;
    NetworkTypeHandlerMockProxy<std::string>::mock = &stringMock;

    NetworkTypeHandlerMock<std::uint16_t> shortMock;
    NetworkTypeHandlerMockProxy<std::uint16_t>::mock = &shortMock;


    EXPECT_CALL(integerMock, read(_))
        .WillOnce(Return(VERSION))
        .WillOnce(Return(id));
    EXPECT_CALL(stringMock, read(_)).WillOnce(Return(SERVER_ADDRESS));
    EXPECT_CALL(shortMock, read(_)).WillOnce(Return(SERVER_PORT));

    HandshakePacket packet;
    operator>> <NetworkTypeHandlerMockProxy<std::int32_t>, 
                NetworkTypeHandlerMockProxy<std::string>,
                NetworkTypeHandlerMockProxy<std::uint16_t>,
                NetworkTypeHandlerMockProxy<std::int32_t>>
    (stream, packet);

    EXPECT_EQ(state, packet.requested_state);
  }
};


TEST_F(HandshakePacketTest, ReadsHandshakeRequestPacket)
{
  test_read_status_request(-1, ConnectionState::Handshake);
}

TEST_F(HandshakePacketTest, ReadsPlayRequestPacket)
{
  test_read_status_request(0, ConnectionState::Play);
}

TEST_F(HandshakePacketTest, ReadsStatusRequestPacket)
{
  test_read_status_request(1, ConnectionState::Status);
}

TEST_F(HandshakePacketTest, ReadsLoginRequestPacket)
{
  test_read_status_request(2, ConnectionState::Login);
}

TEST_F(HandshakePacketTest, ReadsInvalidRequestPacket)
{
  test_read_status_request(0xf, ConnectionState::INVALID);
}