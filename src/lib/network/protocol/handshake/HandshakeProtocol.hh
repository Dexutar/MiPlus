#pragma once

#include <boost/system/error_code.hpp>
#include <istream>

#include "HandshakePacket.hh"
#include "Session_forwarding.hh"

namespace miplus
{
namespace network
{

class HandshakeProtocol
{
 public:
  HandshakeProtocol(Session *session);
  HandshakeProtocol &operator=(const HandshakeProtocol &) = default;

  void inbound(std::istream &is);
  void on_error(const boost::system::error_code &error);

 private:
  void handle(const HandshakePacket &packet);

  Session *session;
};

}  // namespace network
}  // namespace miplus