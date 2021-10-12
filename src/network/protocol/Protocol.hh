#pragma once

#include <boost/system/error_code.hpp>
#include <iostream>

class Session;

class Protocol
{
 public:
  Protocol(Session &session) : session{session} {}

  virtual void inbound(std::istream &is) = 0;
  virtual void on_error(const boost::system::error_code &error);

 protected:
  Session &session;
};