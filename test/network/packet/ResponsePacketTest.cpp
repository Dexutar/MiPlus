#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ostream>
#include <string>
#include <string_view>

#include "NetworkTypeHandlerMock.hh"
#include "PacketTest.hh"
#include "ResponsePacket.hh"

using ::testing::_;
using ::testing::Invoke;

class ResponsePacketTest : public PacketTest
{
 protected:
  static constexpr std::string_view RESPONSE = "{\"version\":{\"protocol\":340,\"name\":\"1.12.2\"}}";

  void writeOpcode(std::ostream &os)
  {
    os.put(ResponsePacket::opcode);
  }

  void writeResponse(std::ostream &os)
  {
    os << RESPONSE;
  } 
};


TEST_F(ResponsePacketTest, ReadsPacket)
{
  NetworkTypeHandlerMock<std::uint8_t> opcodeMock;
  NetworkTypeHandlerMockProxy<std::uint8_t>::mock = &opcodeMock;

  NetworkTypeHandlerMock<std::string_view> responseMock;
  NetworkTypeHandlerMockProxy<std::string_view>::mock = &responseMock;

  NetworkTypeHandlerMock<std::int64_t> sizeMock;
  NetworkTypeHandlerMockProxy<std::int64_t>::mock = &sizeMock;

  EXPECT_CALL(opcodeMock, write(_, ResponsePacket::opcode)).WillOnce(Invoke([&] (std::ostream &os, std::uint8_t) {writeOpcode(os);}));
  EXPECT_CALL(responseMock, write(_, RESPONSE)).WillOnce(Invoke([&] (std::ostream &os, std::string_view) {writeResponse(os);}));
  EXPECT_CALL(sizeMock, write(_, sizeof(ResponsePacket::opcode) + RESPONSE.size()));


  ResponsePacket packet{RESPONSE};
  operator<< <NetworkTypeHandlerMockProxy<std::uint8_t>,
              NetworkTypeHandlerMockProxy<std::string_view>,
              NetworkTypeHandlerMockProxy<std::streamsize>>
  (stream, packet);
}