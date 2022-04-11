#pragma once

#include "HandshakePacket.hh"
#include "Protocol.hh"

namespace miplus
{
namespace network
{

class HandshakeProtocol : public Protocol
{
 public:
  HandshakeProtocol(Session &session) : Protocol{session} {}

  void inbound(std::istream &is) override;

 private:
  void handle(const HandshakePacket &packet);
};

}  // namespace network
}  // namespace miplus