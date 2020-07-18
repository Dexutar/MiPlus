#pragma once

#include <optional>
#include <iostream>

#include <boost/asio.hpp>

class VarNumber
{
public:

  template <typename iterator>
  static std::tuple<bool,iterator,std::int32_t> readVarInt (iterator begin, iterator end)
  {
    std::int32_t result = 0;
    std::uint8_t indx = 0;
    std::uint8_t read = 0;

    iterator it = begin;

    do
    {
      if (it == end)
        return {false,end,0};
      read = *(it++);
      result |=  (read & 0x7F) << (indx++ * 7);
      if (indx > 5) throw std::overflow_error("VarInt is too big");
    }
    while (read & 0x80);
    
    return {true,it,result};
  }

  template <typename iterator>
  static std::tuple<bool,iterator,std::int64_t> readVarLong (iterator begin, iterator end)
  {
    std::int64_t result = 0;
    std::uint8_t indx = 0;
    std::uint8_t read = 0;

    iterator it = begin;

    do
    {
      if (it == end)
        return {false,end,0};
      read = *(it++);
      result |=  (read & 0x7F) << (indx++ * 7);
      if (indx > 10) throw std::overflow_error("VarLong is too big");
    }
    while (read & 0x80);
    
    return {true,it,result};
  }

  static std::int32_t readVarInt (std::istream &is);
  static std::int64_t readVarLong (std::istream &is);
};