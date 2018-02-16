#include "Duo.h"

#include <iostream>

Duo<bool, int> foo( )
{
	Duo<bool, int> result;
	result.v1 = true;
	result.v2 = 42;
	return result;

	// or 

	return make_duo( true, 42 );
}

int main( )
{
	Duo<bool, int> result = foo( );
	if ( result.v1 )
	{
		std::cout << result.v2 << std::endl;
	}
	else
	{
		std::cout << "Error occurred" << std::endl;
	}
}