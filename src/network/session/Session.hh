#pragma once

#include <boost/asio.hpp>

#include "Channel.hh"

class Session;


class Session
{
public:
  Session (boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &io_context);

  std::string getID () const;

private:
  Channel channel;
};
