#pragma once

#include <optional>

#include <boost/asio.hpp>

#include "EventLoop.hh"
#include "Session.hh"

class Bootstrap
{
public:

  Bootstrap (std::uint16_t port, std::function<void (Session &&session)> &&onAccept);

  void shutdown ();
  void join ();

private:

  EventLoop boss;
  EventLoop worker;

  boost::asio::ip::tcp::acceptor acceptor;

  std::optional<boost::asio::ip::tcp::socket> socket;

  std::function<void (Session &&session)> onAccept;

  void accept ();
};