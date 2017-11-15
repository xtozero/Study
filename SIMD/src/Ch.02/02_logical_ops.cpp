#include <iostream>

/*--------------
128bit XMM 레지스터의 모든 값에 대해 bit 연산을 수행한다.

PAND (Bitwise Logical And)
pand xmm1, xmm2/m128
POR (Bitwise Logical OR)
por xmm1, xmm2/m128
PXOR (Bitwise Logical Exclusive OR)
pxor xmm2, xmm2/m128
PANDN (Bitwise Logical And Not)
pandn xmm1, xmm2/m128
--------------*/

int main( )
{
	alignas( 16 ) int IntArrayA[4] = { 1, 1, 0, 0 };
	alignas( 16 ) int IntArrayB[4] = { 1, 0, 1, 0 };
	alignas( 16 ) int ANDResult[4] = { 0 };
	alignas( 16 ) int ORResult[4] = { 0 };
	alignas( 16 ) int XORResult[4] = { 0 };
	alignas( 16 ) int ANDNOTResult[4] = { 0 };

	__asm
	{
		pushad

		movdqa xmm0, IntArrayA
		movdqa xmm1, xmm0
		movdqa xmm2, xmm0
		movdqa xmm3, xmm0
		movdqa xmm4, IntArrayB
		
		pand xmm0, xmm4
		por xmm1, xmm4
		pxor xmm2, xmm4
		pandn xmm3, xmm4

		movdqa ANDResult, xmm0
		movdqa ORResult, xmm1
		movdqa XORResult, xmm2
		movdqa ANDNOTResult, xmm3

		popad
	}

	std::cout << "AND Result : ";
	for ( int elem : ANDResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "OR Result : ";
	for ( int elem : ORResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "XOR Result : ";
	for ( int elem : XORResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "ANDNOT Result : ";
	for ( int elem : ANDNOTResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}