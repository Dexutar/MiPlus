#include "VarInt.hh"

std::pair<VarInt::iterator,std::uint32_t> VarInt::readVarInt (iterator begin, iterator end)
{
  std::uint32_t result = 0;
  std::uint8_t indx = 0;
  std::uint8_t read = 0;

  iterator it = begin;

  do
  {
    if (it == end)
      return {end,0};
    read = *(it++);
    result |=  (read & 0x7F) << (indx++ * 7);
    if (indx > 5) throw std::overflow_error("VarInt is too big");
  }
  while (read & 0x80);
  
  return {--it, result};
}