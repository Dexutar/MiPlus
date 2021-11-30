#pragma once

#include <string>

#include "NetworkTypes.hh"
#include "VarNumber.hh"

class VarString
{
 public:
  template <typename, NetworkTypeReader<std::int32_t> SizeReader = VarNumber>
  static std::string read(std::istream &is);

  template <NetworkTypeWriter<std::int32_t> SizeWriter = VarNumber>
  static void write(std::ostream &os, std::string_view string);
};

template <typename, NetworkTypeReader<std::int32_t> SizeReader>
std::string VarString::read(std::istream &is)
{
  std::string res;
  int size = SizeReader::template read<std::int32_t>(is);
  std::copy_n(std::istream_iterator<char>(is), size, std::back_inserter(res));
  return res;
}

template <NetworkTypeWriter<std::int32_t> SizeWriter>
void VarString::write(std::ostream &os, std::string_view string)
{
  SizeWriter::write(os, string.size());
  os << string;
}