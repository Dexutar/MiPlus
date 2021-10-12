#include "Protocol.hh"

#include "Session.hh"

void Protocol::on_error(const boost::system::error_code& error) { session.terminate(); }