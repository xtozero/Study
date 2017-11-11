#include <iostream>
#include "Holder.h"

class Something
{
public:
	void perform( ) { std::cout << "perform" << std::endl; }
	Something( ) { std::cout << "created" << std::endl; }
	~Something( ) { std::cout << "deleted" << std::endl; }
};

class MyClass
{
};

Holder<Something> creator( )
{
	Holder<Something> h( new Something );
	MyClass x;
	return std::move( h );
}

int main( )
{
	creator( );
}