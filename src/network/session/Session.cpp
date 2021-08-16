#include "Session.hh"


namespace io = boost::asio;
using tcp = io::ip::tcp;

Session::Session (tcp::socket &&socket, io::io_context &io_context) : channel{std::move(socket),io_context,std::move(ProtocolFactory::create(ConnectionState::Handshake,*this))}
{}

std::string Session::getID () const
{
  return channel.getRemoteAddress();
}

void Session::setState (ConnectionState state)
{
  channel.setProtocol(std::move(ProtocolFactory::create(state,*this)));
}

void Session::send (const Packet &packet)
{
  channel.send(packet);
}