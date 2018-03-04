#include "Tuple.h"

#include <string>
#include <tuple>

int main( )
{
	Tuple<int, double, std::string> t( 17, 3.14, "Hello, World!" );

	Tuple<long int, long double, std::string> t2( t );

	auto t3 = makeTuple( 17, 3.14, "Hello, World!" );
	auto t4 = makeTuple( 1, 2, 3, 4, 5, 6, 7, 8 );

	auto t5 = makeTuple( 1, 2, 3, 4 );
	auto t6 = makeTuple( 5, 6, 7, 8 );

	bool isLess = t5 < t6;

	std::cout << makeTuple( 1, 2.5, std::string( "Hello" ) ) << std::endl;
}