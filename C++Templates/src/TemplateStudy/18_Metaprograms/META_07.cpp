#include <iostream>

template <typename T>
inline T dot_product( int dim, T* a, T* b )
{
	T result = T( );
	for ( int i = 0; i < dim; ++i )
	{
		result += a[i] * b[i];
	}
	return result;
}

// Unroll loop version

template <int DIM, typename T>
class DotProduct
{
public:
	static T result( T* a, T* b )
	{
		return *a * *b + DotProduct<DIM - 1, T>::result( a + 1, b + 1 );
	}
};

template <typename T>
class DotProduct<1, T>
{
public:
	static T result( T* a, T* b )
	{
		return *a * *b;
	}
};

template <int DIM, typename T>
inline T Dot( T* a, T* b )
{
	return DotProduct<DIM, T>::result( a, b );
}

int main( )
{
	int a[3] = { 1, 2, 3 };
	int b[3] = { 5, 6, 7 };

	std::cout << "dot_product( 3, a, b ) = " << dot_product( 3, a, b ) << std::endl;
	std::cout << "dot_product( 3, a, a ) = " << dot_product( 3, a, a ) << std::endl;

	std::cout << "Dot<3>( a, b ) = " << Dot<3>( a, b ) << std::endl;
	std::cout << "Dot<3>( a, a ) = " << Dot<3>( a, a ) << std::endl;
}