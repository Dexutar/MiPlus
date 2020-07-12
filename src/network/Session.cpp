#include "Session.hh"

namespace io = boost::asio;
using tcp = io::ip::tcp;

Session::Session (tcp::socket &&socket, io::io_context &io_context) : channel{std::move(socket),io_context,Protocol()}
{}

bool Session::operator== (const Session &session) const
{
  return this->channel == session.channel;
}

size_t std::hash<Session>::operator() (const Session &session) const
{
  return std::hash<Channel>{}(session.channel);
}