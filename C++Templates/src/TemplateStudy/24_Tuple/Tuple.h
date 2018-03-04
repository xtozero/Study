#pragma once
#include <utility>
#include <iostream>
#include "../23_Typelist/ctvalue.h"

template <typename... Types>
class Tuple;

template <unsigned N, typename... Types>
const auto& get( const Tuple<Types...>& t );

template <typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
private:
	Head head;
	Tuple<Tail...> tail;
public:
	Tuple( ) {}
	Tuple( const Head& head, const Tuple<Tail...>& tail ) : head( head ), tail( tail ) {}
	template <typename VHead, typename... VTail, typename = typename std::enable_if<sizeof...(VTail) == sizeof...(Tail)>::type>
	Tuple( VHead&& vhead, VTail&&... vtail ) : head( std::forward<VHead>( vhead ) ), tail( std::forward<VTail>( vtail )... ) {}

	template <typename VHead, typename... VTail, typename = typename std::enable_if<sizeof...( VTail ) == sizeof...( Tail )>::type>
	Tuple( const Tuple<VHead, VTail...>& other ) : head( other.getHead( ) ), tail( other.getTail( ) ) { }

	Head& getHead( ) { return head; }
	const Head& getHead( ) const { return head; }
	Tuple<Tail...>& getTail( ) { return tail; }
	const Tuple<Tail...>& getTail( ) const { return tail; }
	
	template <typename T, T Index>
	auto& operator[]( CTValue<T, Index> )
	{
		return get<Index>( *this );
	}
};

template <>
class Tuple<>
{
};

template <unsigned N>
struct TupleGet 
{
	template <typename Head, typename... Tail>
	static const auto& apply( const Tuple<Head, Tail...>& t )
	{
		return TupleGet<N - 1>::apply( t.getTail( ) );
	}
};

template <>
struct TupleGet<0>
{
	template <typename Head, typename... Tail>
	static const Head& apply( const Tuple<Head, Tail...>& t )
	{
		return t.getHead( );
	}
};

template <unsigned N, typename... Types>
const auto& get( const Tuple<Types...>& t )
{
	return TupleGet<N>::apply( t );
}

template <typename... Types>
auto makeTuple( Types&&... elems )
{
	return Tuple<std::decay_t<Types>...>( std::forward<Types>( elems )... );
}

bool operator==( const Tuple<>&, const Tuple<>& )
{
	return true;
}

template <typename Head1, typename... Tail1,
		typename Head2, typename... Tail2,
		typename = std::enable_if_t<sizeof...( Tail1 ) == sizeof...( Tail2 )>>
	bool operator==( const Tuple<Head1, Tail1...>& lhs, const Tuple<Head2, Tail2...>& rhs )
{
	return lhs.getHead( ) == rhs.getHead( ) && lhs.getTail( ) == rhs.getTail( );
}

bool operator<( const Tuple<>&, const Tuple<>& )
{
	return false;
}

template <typename Head1, typename... Tail1,
	typename Head2, typename... Tail2,
	typename = std::enable_if_t<sizeof...( Tail1 ) == sizeof...( Tail2 )>>
	bool operator<( const Tuple<Head1, Tail1...>& lhs, const Tuple<Head2, Tail2...>& rhs )
{
	return lhs.getHead( ) < rhs.getHead( ) || 
		( !( rhs.getHead( ) < lhs.getHead( ) ) && lhs.getTail( ) < rhs.getTail( ) );
}

void printTuple( std::ostream& strm, const Tuple<>&, bool isFirst = true )
{
	strm << ( isFirst ? '(' : ')' );
}

template <typename Head, typename... Tail>
void printTuple( std::ostream& strm, const Tuple<Head, Tail...>& t, bool isFirst = true )
{
	strm << ( isFirst ? "(" : ", " );
	strm << t.getHead( );
	printTuple( strm, t.getTail( ), false );
}

template <typename... Types>
std::ostream& operator<<( std::ostream& strm, const Tuple<Types...>& t )
{
	printTuple( strm, t );
	return strm;
}