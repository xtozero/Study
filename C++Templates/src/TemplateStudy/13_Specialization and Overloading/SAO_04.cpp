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

int main( )
{
	std::cout << f<int*>( (int*)0 ) << std::endl;
	std::cout << f<int>( (int*)0 ) << std::endl;
}