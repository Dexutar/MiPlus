#pragma once

#include <ostream>

#include "VarNumber.hh"

class Packet
{
 public:
  static constexpr std::size_t max_packet_length = 2097152;

 protected:
  std::ostream &write_header(std::ostream &os, std::ostream &data) const
  {
    VarNumber::write(os, static_cast<std::streamsize>(data.tellp()));
    return os << data.rdbuf();
  }
};