#include <gtest/gtest.h>

#include "ProtocolFactory.hh"

using namespace miplus::network;

TEST(ProtocolFactoryTest, CreatesHandshakeProtocol)
{
  EXPECT_EQ(ConnectionState::Handshake, ProtocolFactory::create(ConnectionState::Handshake, nullptr).index() - 1);
}

TEST(ProtocolFactoryTest, CreatesPlayProtocol)
{
  EXPECT_EQ(ConnectionState::Play, ProtocolFactory::create(ConnectionState::Play, nullptr).index() - 1);
}

TEST(ProtocolFactoryTest, CreatesStatusProtocol)
{
  EXPECT_EQ(ConnectionState::Status, ProtocolFactory::create(ConnectionState::Status, nullptr).index() - 1);
}

TEST(ProtocolFactoryTest, CreatesLoginProtocol)
{
  EXPECT_EQ(ConnectionState::Login, ProtocolFactory::create(ConnectionState::Login, nullptr).index() - 1);
}

TEST(ProtocolFactoryTest, FailsWithInvalidConnectionState)
{
  EXPECT_THROW(ProtocolFactory::create(ConnectionState::INVALID, nullptr), std::invalid_argument);
}