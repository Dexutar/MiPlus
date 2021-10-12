#include "VarNumber.hh"

std::int32_t VarNumber::readVarInt(std::istream &is)
{
  auto begin = std::istreambuf_iterator<char>(is);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, res] = VarNumber::readVarInt(begin, end);
  return res;
}

std::int64_t VarNumber::readVarLong(std::istream &is)
{
  auto begin = std::istreambuf_iterator<char>(is);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, res] = VarNumber::readVarLong(begin, end);
  return res;
}