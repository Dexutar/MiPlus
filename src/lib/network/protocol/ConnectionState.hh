#pragma once

namespace miplus
{
namespace network
{

enum class ConnectionState : std::int8_t
{
  Handshake = -1,
  Play      = 0,
  Status    = 1,
  Login     = 2
};

}  // namespace network
}  // namespace miplus