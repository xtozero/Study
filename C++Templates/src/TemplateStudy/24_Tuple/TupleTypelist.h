#pragma once
#include "Tuple.h"
#include "../23_Typelist/Typelist.h"

template <>
struct IsEmpty<Tuple<>>
{
	static constexpr bool value = true;
};

template <typename Head, typename... Tail>
class FrontT<Tuple<Head, Tail...>>
{
public:
	using Type = Head;
};

template <typename Head, typename... Tail>
class PopFrontT<Tuple<Head, Tail...>>
{
public:
	using Type = Tuple<Tail...>;
};

template <typename... Types, typename Element>
class PushFrontT<Tuple<Types...>, Element>
{
public:
	using Type = Tuple<Element, Types...>;
};

template <typename... Types, typename Element>
class PushBackT<Tuple<Types...>, Element>
{
public:
	using Type = Tuple<Types..., Element>;
};
