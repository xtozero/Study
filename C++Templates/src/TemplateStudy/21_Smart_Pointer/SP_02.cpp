#include <iostream>
#include "Holder.h"

class Something
{
public:
	void perform( ) { std::cout << "perform" << std::endl; }
	~Something( ) { std::cout << "deleted" << std::endl; }
};

void read_something( Something* ) {}

Something* load_something( )
{
	Something* result = new Something;

	read_something( result );

	return result;
}

Something* load_something_ver_holder( )
{
	Holder<Something> result( new Something );

	read_something( result.get() );

	Something* ret = result.get( );
	result.release( );

	return ret;
}

int main( )
{

}