#include <iostream>

#include "Enum.h"

void printTrueOrFalse( bool arg )
{
	std::cout << ( arg ? "True" : "False" ) << std::endl;
}

enum SomeEnum
{
};

int main( )
{
	printTrueOrFalse( IsEnumT<int>::value );

	printTrueOrFalse( IsEnumT<SomeEnum>::value );
}