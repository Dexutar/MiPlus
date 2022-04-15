#include <gtest/gtest.h>

#include "ConnectionState.cpp"

using namespace miplus::network;


TEST(ConnectionStateTest, GetsHandshakeFromId)
{
  EXPECT_EQ(ConnectionState::Handshake, get_state_from_id(-1));
}

TEST(ConnectionStateTest, GetsPlayFromId)
{
  EXPECT_EQ(ConnectionState::Play, get_state_from_id(0));
}

TEST(ConnectionStateTest, GetsStatusFromId)
{
  EXPECT_EQ(ConnectionState::Status, get_state_from_id(1));
}

TEST(ConnectionStateTest, GetsLoginFromId)
{
  EXPECT_EQ(ConnectionState::Login, get_state_from_id(2));
}

TEST(ConnectionStateTest, GetsINVALIDFromId)
{
  EXPECT_EQ(ConnectionState::INVALID, get_state_from_id(3));
  EXPECT_EQ(ConnectionState::INVALID, get_state_from_id(2391));
  EXPECT_EQ(ConnectionState::INVALID, get_state_from_id(-2));
  EXPECT_EQ(ConnectionState::INVALID, get_state_from_id(-372));
}