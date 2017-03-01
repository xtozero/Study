#include "ODR_15.h"

static int counter = 0;

inline void increase_counter( )
{
	++counter;
	std::cout << counter << std::endl;
	std::cout << &counter << std::endl;
}

inline void increase_counter1( )
{
	++counter;
	std::cout << counter << std::endl;
	std::cout << &counter << std::endl;
}

void count1( )
{
	increase_counter1( );
}

void count_error1( )
{
	increase_counter( );
}