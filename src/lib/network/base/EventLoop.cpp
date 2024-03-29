#include "EventLoop.hh"

namespace miplus
{
namespace network
{

EventLoop::EventLoop(unsigned int thread_count) : work_guard(io_context.get_executor())
{
  for (unsigned int i = 0; i < thread_count; ++i) threads.emplace_back([&]() { io_context.run(); });
}

void EventLoop::shutdown()
{
  work_guard.reset();
}

void EventLoop::join()
{
  for (auto& thread : threads)
  {
    if (thread.joinable()) thread.join();
  }
}

boost::asio::io_context& EventLoop::get_context()
{
  return io_context;
}

}  // namespace network
}  // namespace miplus