#pragma once

#include <ostream>

#include "NetworkTypes.hh"
#include "VarNumber.hh"

class Packet
{
 public:
  static constexpr std::size_t max_packet_length = 2097152;

 protected:
  template<NetworkTypeWriter<std::streamsize> SizeWriter = VarNumber>
  std::ostream &write_header(std::ostream &os, std::ostream &data) const
  {
    SizeWriter::write(os, static_cast<std::streamsize>(data.tellp()));
    return os << data.rdbuf();
  }
};