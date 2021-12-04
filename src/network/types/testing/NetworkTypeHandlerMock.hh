#pragma once

#include <gmock/gmock.h>

#include <concepts>

template <typename Value>
class NetworkTypeHandlerMock
{
 public:
  MOCK_METHOD(Value, read, (std::istream & is));

  MOCK_METHOD(void, write, (std::ostream & os, Value value));
};

template <typename Value>
struct NetworkTypeHandlerMockProxy
{
  inline static NetworkTypeHandlerMock<Value> *mock;

  template <typename>
  static Value read(std::istream &is) { return mock->read(is); }

  static void write(std::ostream &os, Value value) { mock->write(os, value); }
};