#include <cassert>

#include "SArray.h"

template <typename T, typename Rep = SArray<T>>
class Array
{
private:
	Rep expr_rep;

public:
	explicit Array( size_t s ) : expr_rep( s ) {}

	Array( const Rep& rb ) : expr_rep( rb ) {}

	Array& operator= ( const Array& b )
	{
		assert( size( ) == b.size( ) );
		for ( size_t idx = 0; idx < b.size( ); ++idx )
		{
			expr_rep[idx] = b[idx];
		}
		return *this;
	}

	template <typename T2, typename Rep2>
	Array& operator= ( const Array<T2, Rep2>& b )
	{
		assert( size( ) == b.size( ) );
		for ( size_t idx = 0; idx < b.size( ); ++idx )
		{
			expr_rep[idx] = b[idx];
		}
		return *this;
	}

	size_t size( ) const
	{
		return expr_rep.size( );
	}

	T operator[] ( size_t idx ) const
	{
		assert( idx < size( ) );
		return expr_rep[idx];
	}

	T& operator[] ( size_t idx )
	{
		assert( idx < size( ) );
		return expr_rep[idx];
	}

	const Rep& rep( ) const
	{
		return expr_rep;
	}

	Rep& rep( )
	{
		return expr_rep;
	}
};