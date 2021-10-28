#pragma once

#include <gmock/gmock.h>

#include <concepts>

template <std::integral number>
class VarNumberMock
{
 public:
  MOCK_METHOD(std::int32_t, readVarInt, (std::istream & is));
  MOCK_METHOD(std::int64_t, readVarLong, (std::istream & is));

  MOCK_METHOD(void, writeVarNumber, (std::ostream & os, number value));
};

template <std::integral number>
struct VarNumberMockProxy
{
  inline static VarNumberMock<std::size_t> *mock;

  static std::int32_t readVarInt(std::istream &is) { return mock->readVarInt(is); }
  static std::int64_t readVarLong(std::istream &is) { return mock->readVarLong(is); }

  static void writeVarNumber(std::ostream &os, number value) { mock->writeVarNumber(os, value); }
};