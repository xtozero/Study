#pragma once

#include <type_traits>

template <typename T, typename = std::void_t<>>
class IsClassT : public std::false_type {};

template <typename T>
class IsClassT<T, std::void_t<int T::*>> : public std::true_type {};