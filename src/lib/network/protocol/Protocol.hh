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

using Protocol = std::variant<HandshakeProtocol, PlayProtocol, StatusProtocol, LoginProtocol>;

}  // namespace network
}  // namespace miplus