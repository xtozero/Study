#pragma once

#include <type_traits>

template <typename... Elements>
class Typelist
{
};

template <typename List>
class FrontT;

template <typename Head, typename... Tail>
class FrontT<Typelist<Head, Tail...>>
{
public:
	using Type = Head;
};

template <typename List>
using Front = typename FrontT<List>::Type;

template <typename List>
class PopFrontT;

template <typename Head, typename... Tail>
class PopFrontT<Typelist<Head, Tail...>>
{
public:
	using Type = Typelist<Tail...>;
};

template <typename List>
using PopFront = typename PopFrontT<List>::Type;

template <typename List, typename NewElement>
class PushFrontT;

template <typename... Elements, typename NewElement>
class PushFrontT<Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist<NewElement, Elements...>;
};

template <typename List, typename NewElements>
using PushFront = typename PushFrontT<List, NewElements>::Type;

template <typename List, unsigned int N>
class NthElementT : public NthElementT<PopFront<List>, N - 1>
{
};

template <typename List>
class NthElementT<List, 0> : public FrontT<List>
{
};

template <typename List, unsigned int N>
using NthElement = typename NthElementT<List, N>::Type;

/*
template <typename List>
class LargestTypeT;

template <typename List>
class LargestTypeT
{
private:
	using First = Front<List>;
	using Rest = typename LargestTypeT<PopFront<List>>::Type;

public:
	using Type = typename std::conditional<sizeof( First ) >= sizeof( Rest ), First, Rest>::type;
};

template <>
class LargestTypeT<Typelist<>>
{
public:
	using Type = char;
};

template <typename List>
using LargestType = typename LargestTypeT<List>::Type;
*/

template <typename List>
class IsEmpty
{
public:
	static constexpr bool value = false;
};

template <>
class IsEmpty<Typelist<>>
{
public:
	static constexpr bool value = true;
};

template <typename List, bool Empty = IsEmpty<List>::value>
class LargestTypeT;

template <typename List>
class LargestTypeT<List, false>
{
private:
	using Contender = Front<List>;
	using Best = typename LargestTypeT<PopFront<List>>::Type;
public:
	using Type = typename std::conditional<sizeof( Contender ) >= sizeof( Best ), Contender, Best>::type;
};

template <typename List>
class LargestTypeT<List, true>
{
public:
	using Type = char;
};

template <typename List>
using LargestType = typename LargestTypeT<List>::Type;

template <typename List, typename NewElement>
class PushBackT;

template <typename... Elements, typename NewElement>
class PushBackT<Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist<Elements..., NewElement>;
};

//template <typename List, typename NewElement>
//using PushBack = typename PushBackT<List, NewElement>::Type;

template <typename List, typename NewElement, bool = IsEmpty<List>::value>
class PushBackRecT;

template <typename List, typename NewElement>
class PushBackRecT<List, NewElement, false>
{
private:
	using Head = Front<List>;
	using Tail = PopFront<List>;
	using NewTail = typename PushBackRecT<Tail, NewElement>::Type;

public:
	using Type = PushFront<NewTail, Head>;
};

template <typename List, typename NewElement>
class PushBackRecT<List, NewElement, true>
{
public:
	using Type = PushFront<List, NewElement>;
};

template <typename List, typename NewElement>
class PushBackT : public PushBackRecT<List, NewElement> {};

template <typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;

template <typename List, bool = IsEmpty<List>::value>
class ReverseT;

template <typename List>
using Reverse = typename ReverseT<List>::Type;

template <typename List>
class ReverseT<List, false> : public PushBackT<Reverse<PopFront<List>>, Front<List>> { };

template <typename List>
class ReverseT<List, true>
{
public:
	using Type = List;
};

template <typename List>
class PopBackT
{
public:
	using Type = Reverse<PopFront<Reverse<List>>>;
};

template <typename List>
using PopBack = typename PopBackT<List>::Type;

template <typename List, template <typename T> class MetaFun, bool = IsEmpty<List>::value>
class TransformT;

template <typename List, template <typename T> class MetaFun>
class TransformT<List, MetaFun, false> : public PushFrontT<typename TransformT<PopFront<List>, MetaFun>::Type, 
										typename MetaFun<Front<List>>::Type> { };

template <typename List, template <typename T> class MetaFun>
class TransformT<List, MetaFun, true>
{
public:
	using Type = List;
};

template <typename List, template <typename T> class MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;

template <typename List, template <typename X, typename Y> class F, typename I, bool = IsEmpty<List>::value>
class AccumulateT;

template <typename List, template <typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, false> : public AccumulateT<PopFront<List>, F, typename F<I, Front<List>>::Type>
{};

template <typename List, template <typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, true>
{
public:
	using Type = I;
};

template <typename List, template <typename X, typename Y> class F, typename I>
using Accumulate = typename AccumulateT<List, F, I>::Type;

template <typename T, typename U>
class LargerTypeT 
{
public:
	using Type = typename std::conditional<sizeof( T ) >= sizeof( U ), T, U>::type;
};

/*
template <typename TypeList>
class LargestTypeAccT : public AccumulateT<PopFront<TypeList>, LargerTypeT, Front<TypeList>> {};

template <typename TypeList>
using LargesetTypeAcc = typename LargestTypeAccT<TypeList>::Type;
*/

template <typename TypeList, bool = IsEmpty<TypeList>::value>
class LargestTypeAccT;

template <typename TypeList>
class LargestTypeAccT<TypeList, false> : public AccumulateT<PopFront<TypeList>, LargerTypeT, Front<TypeList>> {};

template <typename TypeList>
class LargestTypeAccT<TypeList, true> {};

template <typename TypeList>
using LargesetTypeAcc = typename LargestTypeAccT<TypeList>::Type;

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

template <typename... Elements, template<typename T> class MetaFun>
class TransformT<Typelist<Elements...>, MetaFun, false>
{
public:
	using Type = Typelist<typename MetaFun<Elements>::Type...>;
};
