#include <vector>
#include <thread>

#include <boost/asio.hpp>

class EventLoop
{
public:

  EventLoop (unsigned int thread_count);

  ~EventLoop ();

  boost::asio::io_context& getContext (); 

private:

  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard;

  std::vector<std::thread> threads;
};