#include <iostream>

#include "Fundamental.h"

template <typename T>
void test( const T& )
{
	if ( IsFundaT<T>::value )
	{
		std::cout << "T is a fundamental type" << std::endl;
	}
	else
	{
		std::cout << "T is not a fundamental type" << std::endl;
	}
}

int main( )
{
	test( 7 );
	test( "hello" );
}