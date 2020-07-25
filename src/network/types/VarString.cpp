#include "VarString.hh"
#include "VarNumber.hh"

std::string VarString::readVarString (std::istream &is)
{
  std::string res;
  int size = VarNumber::readVarInt(is);
  std::copy_n(std::istream_iterator<char>(is),size,std::back_inserter(res));
  return res;
}