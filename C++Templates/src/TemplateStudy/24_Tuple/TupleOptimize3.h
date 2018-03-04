#pragma once

#include <utility>

template <typename... Types>
class Tuple;

template <unsigned Height, typename T>
class TupleElt
{
	T value;

public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : value( std::forward<U>( other ) ) {}

	T& get( ) { return value; }
	const T& get( ) const { return value; }
};

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<sizeof...(Tail), Head>, private Tuple<Tail...>
{
public:
	using HeadElt = TupleElt<sizeof...( Tail ), Head>;
	Head& getHead( )
	{
		return static_cast<HeadElt*>( this )->get( );
	}
	const Head& getHead( ) const
	{
		return static_cast<const HeadElt*>( this )->get( );
	}
	Tuple<Tail...>& getTail( ) { return *this; }
	const Tuple<Tail...>& getTail( ) const { return *this; }
};

template <>
class Tuple<>
{
};