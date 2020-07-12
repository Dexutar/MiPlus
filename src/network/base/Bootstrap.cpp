#include "Bootstrap.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

Bootstrap::Bootstrap (std::uint16_t port,std::function<void (Session &&session)> &&onAccept) : boss{2}, worker{4}, acceptor{boss.getContext(),tcp::endpoint{tcp::v4(),port}}
{
  this->onAccept = std::move(onAccept);
  accept();
}

void Bootstrap::shutdown ()
{
  boss.shutdown();
  worker.shutdown();
}

void Bootstrap::join ()
{
  boss.join();
  worker.join();
}

void Bootstrap::accept ()
{
  socket.emplace(worker.getContext());
  
  acceptor.async_accept(*socket, [&] (const auto &error)
  {
    if (not error)
    {
      Session session{std::move(*socket), worker.getContext()};
      onAccept(std::move(session));
    }
    accept();
  });
}