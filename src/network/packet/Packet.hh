#pragma once

#include <ostream>

#include "NetworkTypeHandlers.hh"
#include "VarNumbersHandler.hh"

class Packet
{
 public:
  static constexpr std::size_t max_packet_length = 2097152;

 protected:
  template<NetworkTypeWriter<std::streamsize> SizeWriter = VarNumbersHandler>
  std::ostream &write_header(std::ostream &os, std::ostream &data) const
  {
    SizeWriter::write(os, static_cast<std::streamsize>(data.tellp()));
    return os << data.rdbuf();
  }
};