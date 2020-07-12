#pragma once

class Protocol
{
public:
  virtual void inbound (int opcode) = 0;
  virtual void outbound (int opcode) = 0;
};