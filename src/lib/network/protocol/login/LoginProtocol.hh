#pragma once

#include <boost/system/error_code.hpp>
#include <istream>

#include "Session_forwarding.hh"

namespace miplus
{
namespace network
{

class LoginProtocol
{
 public:
  LoginProtocol(Session *session);
  LoginProtocol& operator=(const LoginProtocol&) = default;

  void inbound(std::istream &is);
  void on_error(const boost::system::error_code &error);

 private:
  Session *session;
};

}  // namespace network
}  // namespace miplus