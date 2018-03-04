// #include "TupleOptimize3.h"
#include "TupleOptimizeFinal.h"

#include <iostream>

struct A
{
	A( )
	{
		std::cout << "A()" << std::endl;
	}
};

struct B
{
	B( )
	{
		std::cout << "B()" << std::endl;
	}
};

int main( )
{
	Tuple<A, char, A, char, B> t1;
	std::cout << sizeof( t1 ) << " bytes" << std::endl; // vs 2015 에서 6, g++ 에서 5

	std::cout << get<1>( t1 ) << std::endl;;
}