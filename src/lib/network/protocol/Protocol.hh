#pragma once

#include <variant>

#include "HandshakeProtocol.hh"
#include "LoginProtocol.hh"
#include "PlayProtocol.hh"
#include "StatusProtocol.hh"

namespace miplus
{
namespace network
{

using Protocol = std::variant<HandshakeProtocol, LoginProtocol, PlayProtocol, StatusProtocol>;

}  // namespace network
}  // namespace miplus