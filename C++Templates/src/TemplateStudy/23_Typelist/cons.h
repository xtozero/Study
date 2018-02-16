#pragma once

#include <type_traits>

class Nil {};

template <typename HeadT, typename TailT = Nil>
class Cons
{
public:
	using Head = HeadT;
	using Tail = TailT;
};

template <typename List>
class FrontT
{
public:
	using Type = typename List::Head;
};

template <typename List>
using Front = typename FrontT<List>::Type;

template <typename List, typename Element>
class PushFrontT
{
public:
	using Type = Cons<Element, List>;
};

template <typename List, typename Element>
using PushFront = typename PushFrontT<List, Element>::Type;

template <typename List>
class PopFrontT
{
public:
	using Type = typename List::Tail;
};

template <typename List>
using PopFront = typename PopFrontT<List>::Type;

template <typename List>
class IsEmpty
{
public:
	static constexpr bool value = false;
};

template <>
class IsEmpty<Nil>
{
public:
	static constexpr bool value = true;
};

// from Typelist.h
template <typename List, typename Element, template <typename T, typename U> class Compare, bool = IsEmpty<List>::value>
class InsertionSortedT;

template <typename List, typename Element, template <typename T, typename U> class Compare>
class InsertionSortedT<List, Element, Compare, false>
{
private:
	using NewHead = typename std::conditional<Compare<Element, Front<List>>::value, Element, Front<List>>::type;
	using NewTail = typename std::conditional<Compare<Element, Front<List>>::value, List, typename InsertionSortedT<PopFront<List>, Element, Compare>::Type>::type;
public:
	using Type = PushFront<NewTail, NewHead>;
};

template <typename List, typename Element, template <typename T, typename U> class Compare>
class InsertionSortedT<List, Element, Compare, true> : public PushFrontT<List, Element> {};

template <typename List, template <typename T, typename U> class Compare, bool = IsEmpty<List>::value>
class InsertionSortT;

template <typename List, template <typename T, typename U> class Compare>
class InsertionSortT<List, Compare, false> : public InsertionSortedT<typename InsertionSortT<PopFront<List>, Compare>::Type, Front<List>, Compare>
{};

template <typename List, template <typename T, typename U> class Compare>
class InsertionSortT<List, Compare, true>
{
public:
	using Type = List;
};

template <typename List, template <typename T, typename U> class Compare>
using InsertionSort = typename InsertionSortT<List, Compare>::Type;