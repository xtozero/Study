#include <cassert>
#include <iostream>

#include "ExprOps.h"

int main( )
{
	auto a = A_Add<float, A_Scalar<float>, A_Scalar<float>>(A_Scalar<float>( 12.f ), A_Scalar<float>( 8.f ))[0];
	std::cout << a << std::endl;
}