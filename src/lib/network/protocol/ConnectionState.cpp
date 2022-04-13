#include "ConnectionState.hh"

namespace miplus
{
namespace network
{

ConnectionState get_state_from_id(int32_t id)
{
  if (id < ConnectionState::Handshake or id > ConnectionState::Login) 
    return ConnectionState::INVALID;

  return static_cast<ConnectionState>(id);
}

}  // namespace network
}  // namespace miplus