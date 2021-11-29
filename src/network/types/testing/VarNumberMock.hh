#pragma once

#include <gmock/gmock.h>

#include <concepts>

template <std::integral number>
class VarNumberMock
{
 public:
  MOCK_METHOD(number, read, (std::istream & is));

  MOCK_METHOD(void, write, (std::ostream & os, number value));
};

template <std::integral number>
struct VarNumberMockProxy
{
  inline static VarNumberMock<number> *mock;

  template <std::integral>
  static number read(std::istream &is) { return mock->read(is); }

  static void write(std::ostream &os, number value) { mock->write(os, value); }
};