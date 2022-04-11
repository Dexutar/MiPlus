#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <vector>

namespace miplus
{
namespace network
{

class EventLoop
{
 public:
  EventLoop(unsigned int thread_count);

  void shutdown();
  void join();

  boost::asio::io_context& get_context();

 private:
  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard;

  std::vector<std::thread> threads;
};

}  // namespace network
}  // namespace miplus