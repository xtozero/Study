#include "ODR_19.h"

namespace
{
	void paint( Color c )
	{
		std::cout << "paint - main : " << c << std::endl;
	}
}

int main( )
{
	init( );
	highlight( red );
}