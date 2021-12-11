#include "Bootstrap.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

Bootstrap::Bootstrap(std::uint16_t port, SessionRegistry &sessions)
    : boss{2},
      worker{4},
      acceptor{boss.get_context(), tcp::endpoint{tcp::v4(), port}},
      sessions{sessions}
{
  accept();
}

void Bootstrap::shutdown()
{
  boss.shutdown();
  worker.shutdown();
}

void Bootstrap::join()
{
  boss.join();
  worker.join();
}

void Bootstrap::accept()
{
  socket.emplace(worker.get_context());

  acceptor.async_accept(*socket, [&](const auto &error)
  {
    if (not error)
    {
      std::string id = socket->remote_endpoint().address().to_string() + ":" + std::to_string(socket->remote_endpoint().port());
      sessions.emplace(std::move(id), std::move(*socket), worker.get_context());
    }
    accept();
  });
}