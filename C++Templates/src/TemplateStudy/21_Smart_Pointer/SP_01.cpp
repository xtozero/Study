#include <iostream>
#include "Holder.h"

class Something
{
public:
	void perform( ) { std::cout << "perform" << std::endl; }
	~Something( ) { std::cout << "deleted" << std::endl; }
};

void do_something( )
{
	Holder<Something> first( new Something );

	first->perform( );
}

int main( )
{
	do_something( );
}