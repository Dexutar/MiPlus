#pragma once

#include <boost/asio.hpp>

namespace miplus
{
namespace network
{

template <std::input_iterator Iterator = boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type>>
struct ValidFrameCondition
{
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
          return {it, true};
      }
      else
        return {++it, true};
      
      ++index;
    }

    return {begin, false};
  }
};

}  // namespace network
}  // namespace miplus

namespace boost::asio
{

template <>
struct is_match_condition<miplus::network::ValidFrameCondition<>> : public boost::true_type
{
};

}  // namespace boost::asio