#include "INS_07_TR1.h"

#include <iostream>

template <typename T> void f( )
{
	std::cout << "f<int>() called" << std::endl;
}

template void f<int>( );

int main( )
{
	g( );
}