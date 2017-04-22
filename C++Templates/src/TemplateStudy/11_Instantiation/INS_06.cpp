#include <iostream>

template <typename T>
void f( T ) throw ( T )
{
}

template void f<int>( int ) throw( int );
template void f<>( float ) throw( float );
template void f( long ) throw( long );
template void f( char );					// gcc에서는 성공하지만 vs 2015 community 에서는 실패한다.

template <typename T>
class S
{
public:
	void f( )
	{

	}
};

template void S<int>::f( );

template class S<void>;

template <typename T>
void toast( const T& x )
{
	std::cout << "function template" << std::endl;
}

template void toast( const float& x );

template <>
void toast( const float& x )
{
	std::cout << "explicit specialization" << std::endl;
}

int main( )
{
	float a;
	toast( a );
}