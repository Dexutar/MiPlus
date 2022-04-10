#pragma once

#include <concepts>
#include <iterator>
#include <tuple>

namespace miplus
{
namespace network
{

template<typename T, typename Value>
concept NetworkTypeReader = requires(std::istream &is)
{
  {
    T::template read<Value>(is)
  } -> std::same_as<Value>;
};

template<typename T, typename Iterator, typename Value>
concept NetworkTypeIteratorReader = std::input_iterator<Iterator> and requires(Iterator begin, Iterator end)
{
  {
    T::template read<Iterator, Value>(begin, end)
  } -> std::same_as<std::tuple<bool, Iterator, Value>>;
};

template<typename T, typename Value>
concept NetworkTypeWriter = requires(std::ostream &os, Value value)
{
  {
    T::write(os, value)
  } -> std::same_as<void>;
};

}  // namespace network
}  // namespace miplus