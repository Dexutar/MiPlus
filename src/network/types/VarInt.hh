#pragma once

#include <optional>

#include <boost/asio.hpp>

class VarInt
{
public:

  using iterator = boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type>;

  static std::pair<iterator,std::uint32_t> readVarInt (iterator begin, iterator end);
};