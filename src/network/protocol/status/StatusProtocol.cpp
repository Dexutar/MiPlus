#include "StatusProtocol.hh"

#include "Session.hh"

#include "RequestPacket.hh"

#include "ResponsePacket.hh"
#include "PongPacket.hh"

void StatusProtocol::inbound (std::istream &is)
{
  int32_t opcode = VarNumber::readVarInt(is);

  if (opcode == RequestPacket::opcode)
  {
    if (not handled) handle();
  }
  else if (opcode == PingPacket::opcode)
  {
    PingPacket packet; is >> packet;
    handle(packet);
  }
}

void StatusProtocol::handle ()
{
  handled = true;

  ResponsePacket response{"{\"version\":{\"protocol\":340,\"name\":\"1.12.2\"},\"description\":{\"text\":\"OwO\"},\"players\":{\"max\":0,\"online\":0}}"};
  session.send(response);
}

void StatusProtocol::handle (const PingPacket &packet) const
{
  PongPacket pong{packet.getPayload()};
  session.send(pong);
}