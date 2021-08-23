#pragma once

#include <ostream>

#include "VarNumber.hh"

class Packet
{
public:
  
  static constexpr std::size_t max_packet_length = 2097152;

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