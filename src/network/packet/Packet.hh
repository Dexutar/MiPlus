#pragma once

#include <ostream>

#include "VarNumber.hh"

class Packet
{
public:
  
  friend std::ostream& operator<< (std::ostream &os, const Packet &packet)
  {
    return packet.write(os);
  }

protected:

  std::ostream& write_header (std::ostream &os, std::ostream &data) const
  {
    VarNumber::writeVarNumber(os, static_cast<std::streamsize>(data.tellp())); 
    return os << data.rdbuf();
  }

private:

  virtual std::ostream& write (std::ostream &os) const = 0;
};