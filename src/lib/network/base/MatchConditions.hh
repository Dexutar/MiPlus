#pragma once

#include <boost/asio.hpp>

#include <iterator>
#include <stdexcept>

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
    std::uint8_t index = 0;
    Iterator it = begin;

    while (it != end) 
    {
      if (index < 3)
      {
        std::int8_t read = *(it++);
      
        if (read > 0)
        {
          auto [consumed, value] = PacketLengthReader::template read<Iterator, std::int32_t>(begin, it);
          
          packet_length = value;
          return {consumed, true};
        }
      }
      else
        throw std::length_error("Packet with length wider than 21-bit");
      
      ++index;
    }

    return {begin, false};
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