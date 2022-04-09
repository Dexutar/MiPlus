#pragma once

#include <concepts>
#include <iterator>

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

template<typename T, typename iterator, typename Value>
concept NetworkTypeIteratorReader = std::input_iterator<iterator> and requires(iterator begin, iterator end)
{
  {
    T::template read<Value>(begin, end)
  } -> std::same_as<Value>;
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