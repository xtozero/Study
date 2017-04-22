#include <iostream>

template <typename T> void f( )
{
	std::cout << "f()" << std::endl;
}

template void f<int>( );

void g( );

int main( )
{
	g( );
}