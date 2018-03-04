#pragma once

#include <utility>
#include <type_traits>

template <typename... Types>
class Tuple;

template <unsigned Height, typename T, bool = std::is_class<T>::value && !std::is_final<T>::value>
class TupleElt;

template <unsigned Height, typename T>
class TupleElt<Height, T, false>
{
	T value;

public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : value( std::forward<U>( other ) ) {}

	T& get( ) { return value; }
	const T& get( ) const { return value; }
};

template <unsigned Height, typename T>
class TupleElt<Height, T, true> : private T
{
public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : T( std::forward<U>( other ) ) {}

	T& get( ) { return *this; }
	const T& get( ) const { return *this; }
};


template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<sizeof...( Tail ), Head>, private Tuple<Tail...>
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

	template<unsigned I, typename... Elements> friend auto get( Tuple<Elements...>& t );
};

template <>
class Tuple<>
{
};

template <unsigned H, typename T>
T& getHeight( TupleElt<H, T>& te )
{
	return te.get( );
}

template <unsigned I, typename... Elements>
auto get( Tuple<Elements...>& t )
{
	return getHeight<sizeof...(Elements)-I - 1>( t );
}