#include "TupleAlgorithm.h"

#include <string>

void print( )
{}

template<typename T, typename... Types>
void print( T firstArg, Types... args )
{
	std::cout << firstArg << ' ';
	print( args... );
}

int main( )
{
	Tuple<std::string, char const*, int, char> t( "Pi", "is roughly", 3, '\n' );
	apply( print<std::string, char const*, int, char>, t );

	return 0;
}