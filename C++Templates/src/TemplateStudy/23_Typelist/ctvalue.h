#pragma once

#include "Typelist.h"

template <typename T, T Value>
struct CTValue
{
	static constexpr T value = Value;
};

template <typename T, typename U>
struct MultiplyT;

template <typename T, T Value1, T Value2>
struct MultiplyT<CTValue<T, Value1>, CTValue<T, Value2>>
{
public:
	using Type = CTValue<T, Value1 * Value2>;
};

template <typename T, typename U>
using Multiply = typename MultiplyT<T, U>::Type;

template <typename T, T... Values>
using CTTypelist = Typelist<CTValue<T, Values>...>;

template <typename T, typename U>
struct GreaterThanT;

template <typename T, T First, T Second>
struct GreaterThanT<CTValue<T, First>, CTValue<T, Second>>
{
	static constexpr bool value = First > Second;
};