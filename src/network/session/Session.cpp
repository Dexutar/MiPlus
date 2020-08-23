#include "Session.hh"


namespace io = boost::asio;
using tcp = io::ip::tcp;

Session::Session (tcp::socket &&socket, io::io_context &io_context) : channel{std::move(socket),io_context,std::move(ProtocolFactory::create(Protocols::Handshake,*this))}
{}

std::string Session::getID () const
{
  return channel.getRemoteAddress();
}

void Session::setProtocol (Protocols protocol)
{
  channel.setProtocol(std::move(ProtocolFactory::create(protocol,*this)));
}

void Session::send (const Message &message)
{
  channel.send(message);
}