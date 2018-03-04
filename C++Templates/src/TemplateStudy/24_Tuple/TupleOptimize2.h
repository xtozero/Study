#pragma once

#include <utility>

template <typename... Types>
class Tuple;

template <typename T>
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
class Tuple<Head, Tail...> : private TupleElt<Head>, private Tuple<Tail...>
{
public:
	Head& getHead( ) 
	{ 
		return static_cast<TupleElt<Head*>>(this)->get(); 
	}
	const Head& getHead( ) const
	{ 
		return static_cast<TupleElt<const Head*>>( this )->get( );
	}
	Tuple<Tail...>& getTail( ) { return *this; }
	const Tuple<Tail...>& getTail( ) const { return *this; }
};

template <>
class Tuple<>
{
};