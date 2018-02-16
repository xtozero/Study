#pragma once

#include "ctvalue.h"

template <typename T, T... Values>
struct Valuelist
{
};

template <typename T, T... Values>
struct IsEmpty<Valuelist<T, Values...>>
{
	static constexpr bool value = sizeof...( Values ) == 0;
};

template <typename T, T Head, T... Tail>
struct FrontT<Valuelist<T, Head, Tail...>>
{
	using Type = CTValue<T, Head>;
	static constexpr T value = Head;
};

template <typename T, T Head, T... Tail>
struct PopFrontT<Valuelist<T, Head, Tail...>>
{
	using Type = Valuelist<T, Tail...>;
};

template <typename T, T... Values, T New>
struct PushFrontT<Valuelist<T, Values...>, CTValue<T, New>>
{
	using Type = Valuelist<T, New, Values...>;
};

template <typename T, T... Values, T New>
struct PushBackT<Valuelist<T, Values...>, CTValue<T, New>>
{
	using Type = Valuelist<T, Values..., New>;
};

template <typename Types, typename Indices>
class SelectT;

template <typename Types, unsigned... Indices>
class SelectT<Types, Valuelist<unsigned, Indices...>>
{
public:
	using Type = Typelist<NthElement<Types, Indices>...>;
};

template <typename Types, typename Indices>
using Select = typename SelectT<Types, Indices>::Type;