#pragma once

namespace miplus
{
namespace network
{

enum class ConnectionState : std::int8_t
{
  Handshake = -1,
  Play,
  Status,
  Login
};

}  // namespace network
}  // namespace miplus