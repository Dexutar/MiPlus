#pragma once

enum class ConnectionState : std::int8_t 
{ 
  Handshake = -1,  
  Play, 
  Status, 
  Login
};