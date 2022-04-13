#pragma once

#include <mutex>
#include <unordered_map>

#include "Session.hh"

namespace miplus
{
namespace network
{

class SessionRegistry
{
 public:
  bool add(boost::asio::ip::tcp::socket socket, boost::asio::io_context &io_context)
  {
    std::lock_guard<std::mutex> lock(sessions_mutex);
    return sessions
        .emplace(std::piecewise_construct, 
                 std::forward_as_tuple(global_register_count),
                 std::forward_as_tuple(global_register_count++, std::move(socket), io_context, *this))
        .second;
  }

  void erase(std::size_t id);

 private:
  std::mutex sessions_mutex;
  std::size_t global_register_count = 0;
  std::unordered_map<std::size_t, Session> sessions;
};

}  // namespace network
}  // namespace miplus