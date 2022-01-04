#pragma once

#include <string>

#include "NetworkTypeHandlerConcepts.hh"
#include "VarNumberHandler.hh"

struct VarStringHandler
{
  template <typename, NetworkTypeReader<std::int32_t> SizeReader = VarNumberHandler>
  static std::string read(std::istream &is);

  template <NetworkTypeWriter<std::int32_t> SizeWriter = VarNumberHandler>
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