#include <gtest/gtest.h>

#include "ProtocolFactory.hh"

using namespace miplus::network;

TEST(ProtocolFactory, CreateHandshakeProtocol)
{
  // Given a Handshake connection state
  auto state = ConnectionState::Handshake;

  // When creating a protocol from that state
  auto protocol = ProtocolFactory::create(state, nullptr);

  // Then the protocol should be a HandshakeProtocol
  EXPECT_TRUE(std::holds_alternative<HandshakeProtocol>(protocol)) << "The created protocol is not a Handshake protocol";
}

TEST(ProtocolFactory, CreatePlayProtocol)
{
  // Given a Play connection state
  auto state = ConnectionState::Play;

  // When creating a protocol from that state
  auto protocol = ProtocolFactory::create(state, nullptr);

  // Then the protocol should be a PlayProtocol
  EXPECT_TRUE(std::holds_alternative<PlayProtocol>(protocol)) << "The created protocol is not a Play protocol";
}

TEST(ProtocolFactory, CreateStatusProtocol)
{
  // Given a Status connection state
  auto state = ConnectionState::Status;

  // When creating a protocol from that state
  auto protocol = ProtocolFactory::create(state, nullptr);

  // Then the protocol should be a StatusProtocol
  EXPECT_TRUE(std::holds_alternative<StatusProtocol>(protocol)) << "The created protocol is not a Status protocol";
}

TEST(ProtocolFactory, CreateLoginProtocol)
{
  // Given a Login connection state
  auto state = ConnectionState::Login;

  // When creating a protocol from that state
  auto protocol = ProtocolFactory::create(state, nullptr);

  // Then the protocol should be a LoginProtocol
  EXPECT_TRUE(std::holds_alternative<LoginProtocol>(protocol)) << "The created protocol is not a Login protocol";
}

TEST(ProtocolFactory, FailWithAnInvalidConnectionState)
{
  // Given a Invalid connection state
  auto state = ConnectionState::INVALID;

  // When creating a protocol from that state, then it should throw an invalid argument exception
  EXPECT_THROW(ProtocolFactory::create(state, nullptr), std::invalid_argument) << "The factory should have thrown an invalid argument excpetion";
}