#include <iostream>

#include "Compound.h"

void printTrueOrFalse( bool arg )
{
	std::cout << ( arg ? "True" : "False" ) << std::endl;
}

class SomeClass {};

int main( )
{
	printTrueOrFalse( IsPointerT<char>::value );
	printTrueOrFalse( IsPointerT<char*>::value );

	printTrueOrFalse( IsLValueReferenceT<int&>::value );
	printTrueOrFalse( IsLValueReferenceT<int>::value );

	printTrueOrFalse( IsRValueReferenceT<int&&>::value );
	printTrueOrFalse( IsRValueReferenceT<int&>::value );

	printTrueOrFalse( IsArrayT<int[]>::value );
	printTrueOrFalse( IsArrayT<float[4]>::value );
	printTrueOrFalse( IsArrayT<long>::value );

	printTrueOrFalse( IsPointerToMemberT<int SomeClass::*>::value );
	printTrueOrFalse( IsPointerToMemberT<long>::value );
}