#pragma once

#include <ostream>

#include "NetworkTypeHandlerConcepts.hh"
#include "VarNumberHandler.hh"

namespace miplus
{
namespace network
{

class Packet
{
 public:
  static constexpr std::size_t max_packet_length = 2097152;

 protected:
  template <NetworkTypeWriter<std::streamsize> SizeWriter = VarNumberHandler>
  std::ostream &write_header(std::ostream &os, std::ostream &data) const
  {
    SizeWriter::write(os, static_cast<std::streamsize>(data.tellp()));
    return os << data.rdbuf();
  }
};

}  // namespace network
}  // namespace miplus