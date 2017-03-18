#include <typeinfo>
#include <iostream>

template <typename T>
void ref( const T& x )
{
	std::cout << "void ref( const T& x ): " << typeid(x).name( ) << '\n' << std::endl;
}


template <typename T>
void nonref( const T x )
{
	std::cout << "void nonref( const T x ): " << typeid(x).name( ) << '\n' << std::endl;
}

int main( )
{
	ref( "hello" ); //  char[6]
	nonref( "hello" ); // char*
}