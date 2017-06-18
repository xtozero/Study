#include <iostream>

template <typename T>
int f( T )
{
	return 1;
}

template <typename T>
int f( T* )
{
	return 2;
}

template <typename T>
void t( T*, const T* = 0, ... ) {}

template <typename T>
void t( const T*, T*, T* = 0 ) {}

void example( int* p )
{
	t( p, p );
}

int main( )
{
	std::cout << f( 0 ) << std::endl;
	std::cout << f( (int*)0 ) << std::endl;
}