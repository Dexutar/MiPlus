#include "HandshakePacket.hh"

ConnectionState HandshakePacket::getRequestedState() const { return requested_state; }
