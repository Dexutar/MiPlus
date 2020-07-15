#include "Channel.hh"
#include "VarInt.hh"

#include <iostream>

namespace io = boost::asio;

Channel::Channel (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context, std::unique_ptr<Protocol> &&protocol) 
  : socket{std::move(socket)}, read_strand{io_context}, write_strand{io_context}, protocol{std::move(protocol)},
    remoteAddress{this->socket.remote_endpoint().address().to_string() + ":" + std::to_string(this->socket.remote_endpoint().port())}
{
  read_header();
}

void Channel::read_header ()
{
  io::async_read_until(socket, in_buffer, match_condition, io::bind_executor(read_strand, [&,packet_length = match_condition.packet_length] (const auto &error, std::size_t bytes_transferred)
  {
    if (not error)
    {
      in_buffer.consume(bytes_transferred);
      read_packet();
    }
    else if (error == io::error::eof)
    {
      std::cout << "Client closed connection" << std::endl;
    }
    else std::cout << "read_header failed: " << error.message() << std::endl;
  }));
}

void Channel::read_packet ()
{
  std::size_t to_read = *(match_condition.packet_length) - std::min(in_buffer.size(),*(match_condition.packet_length));
  io::async_read(socket, in_buffer, boost::asio::transfer_at_least(to_read), io::bind_executor(read_strand, [&] (const auto &error, std::size_t bytes_transferred)
  {
    if (not error)
    {
      in_buffer.consume(*(match_condition.packet_length));
      read_header();
    }
    else if (error == io::error::eof)
    {
      std::cout << "Client closed connection" << std::endl;
    }
    else std::cout << "read_packet failed: " << error.message() << std::endl;
  }));
}

bool Channel::operator== (const Channel &channel) const
{
  return this->remoteAddress == channel.remoteAddress;
}

std::pair<Channel::MatchCondition::iterator, bool> Channel::MatchCondition::operator() (iterator begin, iterator end)
{
  iterator it;
  std::tie(it, *packet_length) = VarInt::readVarInt(begin,end);
  if (it == end)
    return {end, false};
  
  return {++it, true};
}