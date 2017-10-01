#include <cassert>
#include <iostream>

#include "ExprOps.h"
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

template <typename T, typename R1, typename R2>
Array<T, A_Add<T, R1, R2>> operator+( const Array<T, R1>& lhs, const Array<T, R2>& rhs )
{
	return Array<T, A_Add<T, R1, R2>>( A_Add<T, R1, R2>( lhs.rep( ), rhs.rep( ) ) );
}

template <typename T, typename R1, typename R2>
Array<T, A_Mult<T, R1, R2>> operator*( const Array<T, R1>& lhs, const Array<T, R2>& rhs )
{
	return Array<T, A_Mult<T, R1, R2>>( A_Mult<T, R1, R2>( lhs.rep( ), rhs.rep( ) ) );
}

template <typename T, typename R2>
Array<T, A_Mult<T, A_Scalar<T>, R2>> operator*( const T& lhs, const Array<T, R2>& rhs )
{
	return Array<T, A_Mult<T, A_Scalar<T>, R2>>( A_Mult<T, A_Scalar<T>, R2>( A_Scalar<T>(lhs), rhs.rep( ) ) );
}

int main( )
{
	Array<double> x( 1000 ), y( 1000 );

	for ( int i = 0; i < 1000; ++i )
	{
		x[i] = y[i] = i;
	}

	x = 1.2 * x + x * y;

	int input;

	while ( std::cin >> input )
	{
		std::cout << x[input] << std::endl;
	}
} 