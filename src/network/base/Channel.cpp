#include "Channel.hh"

#include <iostream>

namespace io = boost::asio;

Channel::Channel (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, Protocol &&protocol) 
  : socket{std::move(socket)}, read{io_context}, write{io_context}, protocol{std::move(protocol)},
    remoteAddress{this->socket.remote_endpoint().address().to_string() + ":" + std::to_string(this->socket.remote_endpoint().port())}, localAddress{this->socket.local_endpoint().address().to_string() + ":" + std::to_string(this->socket.local_endpoint().port())}
{
  std::cout << "New session with remote endpoint: " << remoteAddress << std::endl;
}

bool Channel::operator== (const Channel &channel) const
{
  return this->remoteAddress == channel.remoteAddress;
}