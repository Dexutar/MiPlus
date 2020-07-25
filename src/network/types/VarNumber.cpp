#include "VarNumber.hh"

std::int32_t VarNumber::readVarInt (std::istream &is)
{
  auto [valid, it, res] = VarNumber::readVarInt(std::istreambuf_iterator<char>(is),std::istreambuf_iterator<char>());
  return res;
}

std::int64_t VarNumber::readVarLong (std::istream &is)
{
  auto [valid, it, res] = VarNumber::readVarLong(std::istreambuf_iterator<char>(is),std::istreambuf_iterator<char>());
  return res;
}