#pragma once

#include <boost/system/error_code.hpp>
#include <string>

namespace miplus
{
namespace network
{

enum class protocol_error
{
  timeout = 1,
  packet_length_overflow,
  unexpected_opcode
};

}  // namespace network
}  // namespace miplus

namespace boost
{
namespace system
{
template <>
struct is_error_code_enum<miplus::network::protocol_error> : std::true_type
{
};

}  // namespace system
}  // namespace boost

namespace miplus
{
namespace network
{

class protocol_error_category : public boost::system::error_category
{
 public:
  static const protocol_error_category& instance()
  {
    static protocol_error_category category;
    return category;
  }

  virtual const char* name() const noexcept override final
  {
    return "Protocol Error";
  }

  virtual std::string message(int c) const override final
  {
    switch (static_cast<miplus::network::protocol_error>(c))
    {
      case miplus::network::protocol_error::timeout:
        return "Connection timed out";
      case miplus::network::protocol_error::packet_length_overflow:
        return "Received packet with length wider than 21-bit";
      default:
        return "Unknown";
    }
  }
};

inline boost::system::error_code make_error_code(protocol_error error)
{
  return {static_cast<int>(error), protocol_error_category::instance()};
}

}  // namespace network
}  // namespace miplus