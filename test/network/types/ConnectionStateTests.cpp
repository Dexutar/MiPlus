#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ConnectionState.hh"
#include "ConnectionStateHandler.hh"
#include "NetworkTypeHandlerMock.hh"
#include "NetworkTypeTest.hh"

using ::testing::_;
using ::testing::Return;

using namespace miplus::network;
using miplus::testing::network::NetworkTypeTest;
using miplus::testing::network::NetworkTypeHandlerMock;
using miplus::testing::network::NetworkTypeHandlerMockProxy;

class ConnectionStateTest : public NetworkTypeTest
{
};


TEST_F(ConnectionStateTest, ReadsHandhsake)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(ConnectionState::Handshake));

  EXPECT_EQ(ConnectionState::Handshake, (ConnectionStateHandler::read<ConnectionState, NetworkTypeHandlerMockProxy<std::int32_t>>(stream)));
}

TEST_F(ConnectionStateTest, ReadsPlay)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(ConnectionState::Play));

  EXPECT_EQ(ConnectionState::Play, (ConnectionStateHandler::read<ConnectionState, NetworkTypeHandlerMockProxy<std::int32_t>>(stream)));
}

TEST_F(ConnectionStateTest, ReadsStatus)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(ConnectionState::Status));

  EXPECT_EQ(ConnectionState::Status, (ConnectionStateHandler::read<ConnectionState, NetworkTypeHandlerMockProxy<std::int32_t>>(stream)));
}

TEST_F(ConnectionStateTest, ReadsLogin)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(ConnectionState::Login));

  EXPECT_EQ(ConnectionState::Login, (ConnectionStateHandler::read<ConnectionState, NetworkTypeHandlerMockProxy<std::int32_t>>(stream)));
}

TEST_F(ConnectionStateTest, ReadsInvalid)
{
  NetworkTypeHandlerMock<std::int32_t> mock;
  NetworkTypeHandlerMockProxy<std::int32_t>::mock = &mock;

  EXPECT_CALL(mock, read(_)).WillOnce(Return(-128)).WillOnce(Return(7255));

  EXPECT_EQ(ConnectionState::INVALID, (ConnectionStateHandler::read<ConnectionState, NetworkTypeHandlerMockProxy<std::int32_t>>(stream)));
  EXPECT_EQ(ConnectionState::INVALID, (ConnectionStateHandler::read<ConnectionState, NetworkTypeHandlerMockProxy<std::int32_t>>(stream)));
}