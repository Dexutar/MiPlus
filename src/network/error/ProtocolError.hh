#pragma once

#include <string>
#include <boost/system/error_code.hpp> 

enum class protocol_error
{
  timeout = 1,
  packet_length_overflow,
  unexpected_opcode
};

namespace boost
{
  namespace system
  {
    template <> struct is_error_code_enum<protocol_error> : std::true_type
    {
    };
  }
}


namespace detail
{
  class protocol_error_category : public boost::system::error_category
  {
  public:
    virtual const char *name() const noexcept override final 
    { 
      return "Protocol Error"; 
    }

    virtual std::string message (int c) const override final
    {
      switch (static_cast<protocol_error>(c))
      {
        case protocol_error::timeout:
          return "Connection timed out";
        case protocol_error::packet_length_overflow:
          return "Received packet with length wider than 21-bit";
        default:
          return "Unknown";
      }
    }
  };
}

extern inline const detail::protocol_error_category& protocol_error_category()
{
  static detail::protocol_error_category category;
  return category;
}

inline boost::system::error_code make_error_code (protocol_error error)
{
  return {static_cast<int>(error), protocol_error_category()};
}