#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ostream>

#include "NetworkTypeHandlerMock.hh"
#include "PacketTest.hh"
#include "PongPacket.hh"

using ::testing::_;
using ::testing::Invoke;

class PongPacketTest : public PacketTest
{
 protected:
  static constexpr std::int64_t PAYLOAD = 1638704181000;

  void writeOpcode(std::ostream &os)
  {
    os.put(PongPacket::opcode);
  }

  void writePayload(std::ostream &os)
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

  EXPECT_CALL(opcodeMock, write(_, PongPacket::opcode)).WillOnce(Invoke([&] (std::ostream &os, std::uint8_t) {writeOpcode(os);}));
  EXPECT_CALL(longMock, write(_, PAYLOAD)).WillOnce(Invoke([&] (std::ostream &os, std::int64_t) {writePayload(os);}));
  EXPECT_CALL(longMock, write(_, sizeof(PongPacket::opcode) + sizeof(PAYLOAD)));


  PongPacket packet{PAYLOAD};
  operator<< <NetworkTypeHandlerMockProxy<std::uint8_t>,
              NetworkTypeHandlerMockProxy<std::int64_t>,
              NetworkTypeHandlerMockProxy<std::streamsize>>
  (stream, packet);
}