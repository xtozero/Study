#include "Duo_Final.h"

#include <iostream>

int main( )
{
	Duo<int, Duo<char, Duo<bool, double>>> q4;

	q4.v2( ).v2( ).v1( );
	
	DuoT<3, Duo<int, Duo<char, Duo<bool, double>>>>::ResultT type;

	// �ܼ��� duo�� �����ϰ� ���
	Duo<bool, int> d;
	std::cout << d.v1( ) << std::endl;
	std::cout << val<1>( d ) << std::endl;

	// triple�� �����ϰ� ���
	Duo<bool, Duo<int, float>> t;

	val<1>( t ) = true;
	val<2>( t ) = 42;
	val<3>( t ) = 0.2f;

	std::cout << val<1>(t) << std::endl;
	std::cout << val<2>(t) << std::endl;
	std::cout << val<3>(t) << std::endl;
}