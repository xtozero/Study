#include "Tuple.h"

#include <string>
#include <iostream>

int main( )
{
	auto t = makeTuple( 0, '1', 2.2f, std::string( "hello" ) );

	auto a = t[CTValue<unsigned, 2>{}];
	auto b = t[CTValue<unsigned, 3>{}];

	std::cout << a << ' ' << b << std::endl;

	/* C++14 지원 컴파일러에서 사용가능
	auto t = makeTuple( 0, ’1’, 2.2f, std::string{ "hello" } );
	auto c = t[2_c];
	auto d = t[3_c];
	*/
}