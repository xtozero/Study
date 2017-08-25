#include <iostream>

template <typename T>
void apply( T& arg, void ( *func )( T ) )
{
	func( arg );
}

void incr( int& a )
{
	++a;
}

void print( int a )
{
	std::cout << a << std::endl;
}

int main( )
{
	int x = 7;
	apply( x, print );
	apply( x, incr );
}