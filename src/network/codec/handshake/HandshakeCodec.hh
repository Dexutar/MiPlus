#pragma once

class HandshakeCodec
{
public:
  
  void decode () {}
  void encode () {}

  int getOpcode () { return opcode; }

private:
  const int opcode = 0;
};