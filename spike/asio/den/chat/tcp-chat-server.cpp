#include <boost/asio.hpp>
#include <optional>
#include <queue>
#include <unordered_set>

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

using message_handler = std::function<void (std::string)>;
using error_handler = std::function<void ()>;

class session : public std::enable_shared_from_this<session>
{
public:

  using pointer = std::shared_ptr<session>;

  session (tcp::socket &&socket) : socket(std::move(socket))
  {}

  void start (message_handler &&on_message, error_handler &&on_error)
  {
    this->on_message = std::move(on_message);
    this->on_error = std::move(on_error);
    async_read();
  }

  void post (std::string const &message)
  {
    bool idle = outgoing.empty();
    outgoing.push(message);

    if (idle) async_write();
  }

private:

  void async_read ()
  {
    io::async_read_until(socket, streambuf, "\n", [self = shared_from_this()] (auto error, std::size_t bytes_transferred)
    {
      self->on_read(error, bytes_transferred);
    });
  }

  void on_read (error_code &error, std::size_t bytes_transferred)
  {
    if (not error)
    {
      std::stringstream message;
      message << socket.remote_endpoint(error) << ": " << std::istream(&streambuf).rdbuf();
      streambuf.consume(bytes_transferred);
      on_message(message.str());
      async_read();
    }
    else
    {
      socket.close(error);
      on_error();
    }
  }

  void async_write ()
  {
    io::async_write(socket, io::buffer(outgoing.front()), [self = shared_from_this()] (auto error, std::size_t bytes_transferred)
    {
      self->on_write(error, bytes_transferred);
    });
  }

  void on_write (error_code &error, std::size_t bytes_transferred)
  {
    if (not error)
    {
      outgoing.pop();
      if (not outgoing.empty()) async_write();
    }
    else
    {
      socket.close(error);
      on_error();
    }
  }


  tcp::socket socket;
  io::streambuf streambuf;
  std::queue<std::string> outgoing;
  message_handler on_message;
  error_handler on_error;
};

class server
{
public:

  server (io::io_context &io_context, std::uint16_t port) : io_context(io_context), acceptor(io_context, tcp::endpoint(tcp::v4(), port))
  {}

  void async_accept ()
  {
    socket.emplace(io_context);

    acceptor.async_accept(*socket, [&] (auto error)
    {
      auto client = std::make_shared<session>(std::move(*socket));
      client->post("Welcome to chat\n\r");
      post("We have a newcomer\n\r");

      clients.insert(client);

      client->start(std::bind(&server::post, this, std::placeholders::_1), [&, client]
      {
        if (clients.erase(client))
          post("We are one less\n\r");
      });
    });
  }

  void post (std::string const &message)
  {
    for (auto &client : clients)
      client->post(message);
  }

private:

  io::io_context &io_context;
  tcp::acceptor acceptor;
  std::optional<tcp::socket> socket;
  std::unordered_set<session::pointer> clients;
};

int main ()
{
  io::io_context io_context;
  server srv(io_context, 15001);
  srv.async_accept();
  io_context.run();
  return 0;
}