#include "VarNumber.hh"

std::int32_t VarNumber::readVarInt (std::istream &is)
{
  auto [valid, it, res] = VarNumber::readVarInt(std::istream_iterator<char>(is),std::istream_iterator<char>());
  return res;
}

std::int64_t VarNumber::readVarLong (std::istream &is)
{
  auto [valid, it, res] = VarNumber::readVarLong(std::istream_iterator<char>(is),std::istream_iterator<char>());
  return res;
}