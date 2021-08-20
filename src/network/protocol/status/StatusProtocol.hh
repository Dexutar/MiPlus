#pragma once

#include "Protocol.hh"

#include "PingPacket.hh"

class StatusProtocol : public Protocol
{
public:
  
  StatusProtocol (Session &session) : Protocol {session}, handled{false} {}

  void inbound (std::istream &is) override;

private:

  void handle ();
  void handle (const PingPacket &packet) const;

  bool handled;
};