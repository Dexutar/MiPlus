#pragma once

#include <boost/system/error_code.hpp>
#include <istream>

#include "PingPacket.hh"
#include "Session_forwarding.hh"

namespace miplus
{
namespace network
{

class StatusProtocol
{
 public:
  StatusProtocol(Session *session);
  StatusProtocol &operator=(const StatusProtocol &) = default;

  void inbound(std::istream &is);
  void on_error(const boost::system::error_code &error);

 private:
  void handle();
  void handle(const PingPacket &packet) const;

  Session *session;
  bool handled;
};

}  // namespace network
}  // namespace miplus