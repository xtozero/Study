#pragma once

#include "indexList.h"
#include "TupleTypelist.h"
#include "../23_Typelist/ctvalue.h"

template <typename... Types, typename V>
PushFront<Tuple<Types...>, V> pushFront( const Tuple<Types...>& tuple, const V& value )
{
	return PushFront<Tuple<Types...>, V>( value, tuple );
}

template <typename V>
Tuple<V> pushBack( const Tuple<>&, const V& value )
{
	return Tuple<V>( value );
}

template <typename Head, typename... Tail, typename V>
Tuple<Head, Tail..., V> pushBack( const Tuple<Head, Tail...>& tuple, const V& value )
{
	return Tuple<Head, Tail..., V>( tuple.getHead( ), pushBack( tuple.getTail( ), value ) );
}

template <typename... Types>
PopFront<Tuple<Types...>> popFront( const Tuple<Types...>& tuple )
{
	return tuple.getTail( );
}

//Tuple<> reverse( const Tuple<>& t )
//{
//	return t;
//}
//
//template <typename Head, typename... Tail>
//Reverse<Tuple<Head, Tail...>> reverse( const Tuple<Head, Tail...>& t )
//{
//	return pushBack( reverse( t.getTail( ) ), t.getHead( ) );
//}

template <typename... Types>
PopBack<Tuple<Types...>> popBack( const Tuple<Types...>& t )
{
	return reverse( popFront( reverse( t ) ) );
}

template <typename... Elements, unsigned... Indices>
auto reverseImpl( const Tuple<Elements...>& t, Valuelist<unsigned, Indices...> )
{
	return makeTuple( get<Indices>( t )... );
}

template <typename... Elements>
auto reverse( const Tuple<Elements...>& t )
{
	return reverseImpl( t, Reverse<MakeIndexList<sizeof...( Elements )>>( ) );
}

template <typename... Elements, unsigned... Indices>
auto select( const Tuple<Elements...>& t, Valuelist<unsigned, Indices...> )
{
	return makeTuple( get<Indices>( t )... );
}

template <unsigned I, unsigned N, typename IndexList = Valuelist<unsigned>>
class ReplicatedIndexListT;

template <unsigned I, unsigned N, unsigned... Indices>
class ReplicatedIndexListT<I, N, Valuelist<unsigned, Indices...>> 
	: public ReplicatedIndexListT<I, N - 1, Valuelist<unsigned, Indices..., I>> 
{};

template <unsigned I, unsigned... Indices>
class ReplicatedIndexListT<I, 0, Valuelist<unsigned, Indices...>>
{
public:
	using Type = Valuelist<unsigned, Indices...>;
};

template <unsigned I, unsigned N>
using ReplicatedIndexList = typename ReplicatedIndexListT<I, N>::Type;

template <unsigned I, unsigned N, typename... Elements>
auto splat( const Tuple<Elements...>& t )
{
	return select( t, ReplicatedIndexList<I, N>( ) );
}

template <typename List, template <typename T, typename U> class F>
class MetafunOfNthElementT
{
public:
	template <typename T, typename U> class Apply;

	template <unsigned N, unsigned M>
	class Apply<CTValue<unsigned, M>, CTValue<unsigned, N>> : public F<NthElement<List, M>, NthElement<List, N>>{ };
};

template <template <typename T, typename U> class Compare, typename... Elements>
auto sort( const Tuple<Elements...>& t )
{
	return select( t, InsertionSort<MakeIndexList<sizeof...( Elements )>, MetafunOfNthElementT<Tuple<Elements...>, Compare>::template Apply>( ) );
}

template <typename F, typename... Elements, unsigned... Indices>
auto applyImpl( F f, const Tuple<Elements...>& t, Valuelist<unsigned, Indices...> )
-> decltype( f( get<Indices>( t )... ) )
{
	return f( get<Indices>( t )... );
}

template <typename F, typename... Elements, unsigned N = sizeof...( Elements )>
auto apply( F f, const Tuple<Elements...>& t ) -> decltype(applyImpl(f, t, MakeIndexList<N>()))
{
	return applyImpl( f, t, MakeIndexList<N>( ) );
}