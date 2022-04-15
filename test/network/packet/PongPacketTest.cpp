#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ostream>

#include "NetworkTypeHandlerMock.hh"
#include "PacketTest.hh"
#include "PongPacket.hh"

using ::testing::_;
using ::testing::Invoke;

using namespace miplus::network;
using miplus::testing::network::NetworkTypeHandlerMock;
using miplus::testing::network::NetworkTypeHandlerMockProxy;
using miplus::testing::network::PacketTest;

class PongPacketTest : public PacketTest
{
 protected:
  static constexpr std::int64_t PAYLOAD = 1638704181000;

  void write_opcode(std::ostream &os)
  {
    os.put(PongPacket::opcode);
  }

  void write_payload(std::ostream &os)
  {
    os.write(reinterpret_cast<const char *>(&PAYLOAD), sizeof(PAYLOAD));
  }
};

TEST_F(PongPacketTest, WritesPacket)
{
  NetworkTypeHandlerMock<std::uint8_t> opcodeMock;
  NetworkTypeHandlerMockProxy<std::uint8_t>::mock = &opcodeMock;

  NetworkTypeHandlerMock<std::int64_t> longMock;
  NetworkTypeHandlerMockProxy<std::int64_t>::mock = &longMock;

  EXPECT_CALL(opcodeMock, write(_, PongPacket::opcode)).WillOnce(Invoke([&](std::ostream &os, std::uint8_t) { write_opcode(os); }));
  EXPECT_CALL(longMock, write(_, PAYLOAD)).WillOnce(Invoke([&](std::ostream &os, std::int64_t) { write_payload(os); }));
  EXPECT_CALL(longMock, write(_, sizeof(PongPacket::opcode) + sizeof(PAYLOAD)));

  PongPacket packet{PAYLOAD};
  operator<<<NetworkTypeHandlerMockProxy<std::uint8_t>, 
             NetworkTypeHandlerMockProxy<std::int64_t>, 
             NetworkTypeHandlerMockProxy<std::streamsize>>
            (stream, packet);
}