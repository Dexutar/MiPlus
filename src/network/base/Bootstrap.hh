#pragma once

#include <boost/asio.hpp>
#include <optional>

#include "EventLoop.hh"
#include "Session.hh"
#include "SessionRegistry.hh"

class Bootstrap
{
 public:
  Bootstrap(std::uint16_t port, SessionRegistry &sessions);

  void shutdown();
  void join();

 private:
  void accept();

  EventLoop boss;
  EventLoop worker;

  boost::asio::ip::tcp::acceptor acceptor;

  std::optional<boost::asio::ip::tcp::socket> socket;

  SessionRegistry &sessions;
};