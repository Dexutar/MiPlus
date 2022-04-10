#pragma once

#include <boost/asio.hpp>

#include <iterator>

#include "NetworkTypeHandlerConcepts.hh"
#include "VarNumberHandler.hh"
#include "Packet.hh"

namespace miplus
{
namespace network
{

template <std::input_iterator Iterator = boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type>>
struct PacketLengthReader
{
  PacketLengthReader(std::size_t &packet_length) : packet_length{packet_length} {}
  PacketLengthReader(const PacketLengthReader &packet_length_reader) : packet_length{packet_length_reader.packet_length} {}

  template <NetworkTypeIteratorReader<Iterator, std::int32_t> PacketLengthReader = VarNumberHandler>
  std::pair<Iterator, bool> operator()(Iterator begin, Iterator end)
  {
    try
    {
      auto [valid, it, value] = PacketLengthReader::template read<Iterator, std::int32_t>(begin, end);
      packet_length = value;
      return {it, valid};
    }
    catch(const std::overflow_error& error)
    {
      packet_length = Packet::max_packet_length + 1;
      return {end, true};
    }
  }

  std::size_t &packet_length;
};

}  // namespace network
}  // namespace miplus

namespace boost::asio
{

template <>
struct is_match_condition<miplus::network::PacketLengthReader<>> : public boost::true_type
{
};

}  // namespace boost::asio