#include <boost/asio.hpp>

class Channel
{
public:

  Channel (boost::asio::io_context &io_context) : socket{io_context}, read{io_context}, write{io_context}
  {}


private:

  boost::asio::ip::tcp::socket socket;
  boost::asio::io_context::strand read;
  boost::asio::io_context::strand write;
};