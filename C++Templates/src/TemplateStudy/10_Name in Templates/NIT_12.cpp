#include <iostream>

namespace N
{
	class X
	{

	};

	template <int N> void select( X* ) { std::cout << "select<int N>" << std::endl; };
	template <typename T> void select( T* ) { std::cout << "select<T>" << std::endl; }
}

void g( N::X* xp )
{
	select<3>( xp );
	select( xp );
}

int main( )
{
	g( nullptr );
}