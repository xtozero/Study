#include <iostream>

#include "Functional.h"

void printTrueOrFalse( bool arg )
{
	std::cout << ( arg ? "True" : "False" ) << std::endl;
}

int main( )
{
	printTrueOrFalse( IsFunctionT<int (int)>::value );
	printTrueOrFalse( IsFunctionT<char*>::value );

	printTrueOrFalse( IsFunctionT<int( int ) &>::value );
	printTrueOrFalse( IsFunctionT<int( ... ) &>::value );
}