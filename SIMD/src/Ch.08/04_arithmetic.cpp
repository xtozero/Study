#include <fvec.h>
#include <iostream>

int main( )
{
	float pA[4] = { 1.1, 2.2, 3.3, 4.4 };
	float pB[4] = { 4.4, 3.3, 2.2, 1.1 };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 B;
	F32vec4 R;

	loadu( A, pA );
	loadu( B, pB );

	R = A + B;

	storeu( pR, R );
	std::cout << "Add : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = A - B;

	storeu( pR, R );
	std::cout << "Sub : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = A * B;

	storeu( pR, R );
	std::cout << "Mul : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = A / B;

	storeu( pR, R );
	std::cout << "Div : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}