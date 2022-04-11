#include "StatusProtocol.hh"

#include "PongPacket.hh"
#include "ProtocolError.hh"
#include "RequestPacket.hh"
#include "ResponsePacket.hh"
#include "Session.hh"

namespace miplus
{
namespace network
{

void StatusProtocol::inbound(std::istream &is)
{
  int32_t opcode = VarNumberHandler::read<std::int32_t>(is);

  if (opcode == RequestPacket::opcode)
  {
    if (not handled)
      handle();
    else
      session.terminate();
  }
  else if (opcode == PingPacket::opcode)
  {
    PingPacket packet;
    is >> packet;
    handle(packet);
  }
  else
  {
    std::cerr << "Unexpected opcode:  " << opcode << std::endl;
    on_error(protocol_error::unexpected_opcode);
  }
}

void StatusProtocol::handle()
{
  handled = true;

  ResponsePacket response{
      "{\"version\":{\"protocol\":340,\"name\":\"1.12.2\"},\"description\":{\"text\":\"OwO\"},"
      "\"players\":{\"max\":0,\"online\":0}}"};
  session.send(response);
}

void StatusProtocol::handle(const PingPacket &packet) const
{
  PongPacket pong{packet.get_payload()};
  session.send(pong);
  session.terminate();
}

}  // namespace network
}  // namespace miplus