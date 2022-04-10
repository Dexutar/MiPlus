#pragma once

#include <gmock/gmock.h>

#include <iterator>
#include <utility>

namespace miplus
{
namespace testing
{
namespace network
{

template <std::input_iterator Iterator, typename Value>
struct NetworkTypeIteratorReaderMock
{
  MOCK_METHOD((std::pair<Iterator, Value>), read, (Iterator begin, Iterator end));
};

template <std::input_iterator Iterator, typename Value>
struct NetworkTypeIteratorReaderMockProxy
{
  inline static NetworkTypeIteratorReaderMock<Iterator, Value> *mock;

  template<typename,typename>
  static std::pair<Iterator, Value> read(Iterator begin, Iterator end)
  {
    return mock->read(begin, end);
  }
};

}  // namespace network
}  // namespace testing
}  // namespace miplus