#include "VarNumber.hh"

template<>
std::int32_t VarNumber::read(std::istream &is)
{
  auto begin = std::istreambuf_iterator<char>(is);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, res] = VarNumber::read<decltype(begin), std::int32_t>(begin, end);
  return res;
}

template<>
std::int64_t VarNumber::read(std::istream &is)
{
  auto begin = std::istreambuf_iterator<char>(is);
  auto end = std::istreambuf_iterator<char>();

  auto [valid, it, res] = VarNumber::read<decltype(begin), std::int64_t>(begin, end);
  return res;
}