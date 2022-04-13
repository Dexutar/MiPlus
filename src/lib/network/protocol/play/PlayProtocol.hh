#pragma once

#include <boost/system/error_code.hpp>
#include <istream>

#include "Session_forwarding.hh"

namespace miplus
{
namespace network
{

class PlayProtocol
{
 public:
  PlayProtocol(Session *session);
  PlayProtocol &operator=(const PlayProtocol &) = default;

  void inbound(std::istream &is);
  void on_error(const boost::system::error_code &error);

 private:
  Session *session;
};

}  // namespace network
}  // namespace miplus