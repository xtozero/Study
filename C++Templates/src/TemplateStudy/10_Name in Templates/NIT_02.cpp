#include <iostream>
#include <vector>

class BigInt
{
public:
	// 2. operator-function-id
	BigInt& operator=( const BigInt& );

	// 3. conversion-function-id
	operator int( );
};

template <typename T>
class Stack 
{
public:
	typedef T Type;

	std::vector element;
};

int x;

class _Idenfitier1 {};

// class 1Idenfitier {};

int main( )
{
	// 1. identifier
	_Idenfitier1 valid;	// identifier
	// Idenfitier invalid;	// error
	int reserved;		// reserved

	// 4. template-id and unqualified-id
	Stack<int> intStack;

	// 6. qualified-id
	Stack<float>::Type floatStackType;

	// 7. qualified name
	intStack.element;

	// 10. dependent name
	Stack<float> floatStack;
}