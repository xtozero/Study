#include <iostream>

#include "Class.h"

void printTrueOrFalse( bool arg )
{
	std::cout << ( arg ? "True" : "False" ) << std::endl;
}

class SomeClass {};
struct SomeStruct {};
union SomeUnion {};

int main( )
{
	printTrueOrFalse( IsClassT<int>::value );

	printTrueOrFalse( IsClassT<SomeClass>::value );
	printTrueOrFalse( IsClassT<SomeStruct>::value );
	printTrueOrFalse( IsClassT<SomeUnion>::value );
}