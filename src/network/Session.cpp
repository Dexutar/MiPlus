#include "Session.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;

Session::Session (tcp::socket &&socket, io::io_context &io_context) : channel{std::make_unique<Channel>(std::move(socket),io_context,std::move(ProtocolFactory::create(Protocols::Handshake)))}
{}

bool Session::operator== (const Session &session) const
{
  return *(this->channel) == *(session.channel);
}

size_t std::hash<Session>::operator() (const Session &session) const
{
  return std::hash<Channel>{}(*session.channel);
}