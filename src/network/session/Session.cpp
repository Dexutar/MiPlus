#include "Session.hh"
#include "ProtocolFactory.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;

Session::Session (tcp::socket &&socket, io::io_context &io_context) : channel{std::move(socket),io_context,std::move(ProtocolFactory::create(Protocols::Handshake))}
{}

std::string Session::getID () const
{
  return channel.getRemoteAddress();
}