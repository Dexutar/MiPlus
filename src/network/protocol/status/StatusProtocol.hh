#pragma once

#include "PingPacket.hh"
#include "Protocol.hh"

namespace miplus
{
namespace network
{

class StatusProtocol : public Protocol
{
 public:
  StatusProtocol(Session &session) : Protocol{session}, handled{false} {}

  void inbound(std::istream &is) override;

 private:
  void handle();
  void handle(const PingPacket &packet) const;

  bool handled;
};

}  // namespace network
}  // namespace miplus