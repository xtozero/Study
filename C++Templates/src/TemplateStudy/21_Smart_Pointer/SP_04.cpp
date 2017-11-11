#include "CounthingPtr.h"

#include <iostream>

class MyClass
{
public:
	MyClass( ) { std::cout << "MyClass( )" << std::endl; }
	~MyClass( ) { std::cout << "~MyClass( )" << std::endl; }
};

int main( )
{
	CountingPtr<MyClass> ptr1( new MyClass );

	{
		CountingPtr<MyClass> ptr2( ptr1 );
	}
}