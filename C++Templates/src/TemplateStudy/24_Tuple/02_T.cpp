#include "TupleTypelist.h"

#include <string>

int main( )
{
	Tuple<int, double, std::string> t1( 17, 3.14, "Hello World!" );
	using T2 = PopFront<PushBack<decltype( t1 ), bool>>;
	T2 t2( get<1>( t1 ), get<2>( t1 ), true );
	std::cout << t2;
}