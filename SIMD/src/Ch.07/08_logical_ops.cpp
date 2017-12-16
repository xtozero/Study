/*--------------
Is16vec8 클래스는 16bit short 형 정수 pack 8개에 각각 bit 논리 연산을 수행한다.
&, |, ^, andnot의 경우 이항 연산을 수행하고 &=, |=, ^= 은 단항 연산을 수행한다.
--------------*/

#include <dvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short pA[8] = { 1, 0, 1, 0, -1, 0, -1, 2 };
	alignas( 16 ) short pB[8] = { 1, 1, 0, 0, 1, 1, 0, 0 };
	alignas( 16 ) short pR[8] = { 0 };

	Is16vec8* pVA = (Is16vec8*)pA;
	Is16vec8* pVB = (Is16vec8*)pB;
	Is16vec8* pVR = (Is16vec8*)pR;

	*pVR = *pVA & *pVB;

	std::cout << "AND : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = *pVA | *pVB;

	std::cout << "OR : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = *pVA ^ *pVB;

	std::cout << "XOR : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = andnot( *pVA, *pVB );

	std::cout << "ANDNOT : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}