#pragma once

#include <string>

#include "NetworkTypeHandlers.hh"
#include "VarNumbersHandler.hh"

class VarStringHandler
{
 public:
  template <typename, NetworkTypeReader<std::int32_t> SizeReader = VarNumbersHandler>
  static std::string read(std::istream &is);

  template <NetworkTypeWriter<std::int32_t> SizeWriter = VarNumbersHandler>
  static void write(std::ostream &os, std::string_view string);
};

template <typename, NetworkTypeReader<std::int32_t> SizeReader>
std::string VarStringHandler::read(std::istream &is)
{
  std::string res;
  int size = SizeReader::template read<std::int32_t>(is);
  std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
  return res;
}

template <NetworkTypeWriter<std::int32_t> SizeWriter>
void VarStringHandler::write(std::ostream &os, std::string_view string)
{
  SizeWriter::write(os, string.size());
  os << string;
}