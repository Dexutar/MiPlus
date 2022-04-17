#pragma once

#include <cstdint>

namespace miplus
{
namespace network
{

enum ConnectionState : std::int8_t
{
  Handshake = -1,
  Play      = 0,
  Status    = 1,
  Login     = 2,
  INVALID
};

}  // namespace network
}  // namespace miplus