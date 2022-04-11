#include "Protocol.hh"

#include "Session.hh"

namespace miplus
{
namespace network
{

void Protocol::on_error(const boost::system::error_code& error)
{
  session.terminate();
}

}  // namespace network
}  // namespace miplus