/*--------------
AND, OR, XOR 연산이 구현되어 있다.
ANDNOT(andnot()) 연산은 F64vec2, F64vec4, F32vec8에만 구현되어 있다.
F64vec2, F32vec1 클래스도 지원한다.
--------------*/

#include <fvec.h>
#include <dvec.h>
#include <iostream>

int main( )
{
	float pA[4] = { 1.f, 0.f, 1.f, 0.f };
	float pB[4] = { 1.f, 1.f, 0.f, 0.f };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 B;
	F32vec4 R;

	loadu( A, pA );
	loadu( B, pB );

	R = A & B;

	storeu( pR, R );
	std::cout << "AND : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = A | B;

	storeu( pR, R );
	std::cout << "OR : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = A ^ B;

	storeu( pR, R );
	std::cout << "XOR : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}