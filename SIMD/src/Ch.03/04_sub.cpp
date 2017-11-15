#include <iostream>

/*--------------
Subtract Packed
32bit float형 실수 4개 혹은 64bit double형 실수 2개를 동시에 뺀다.

사용문법					pack size				연산 기능
subps					32bit float				32bit float형 실수 4개를 동시에 뺀다.
subpd					64bit double			64bit double형 실수 2개를 동시에 뺀다.

Subtract Scalar
첫번째 pack의 32bit float형 실수 혹은 64bit double형 실수를 뺀다.

사용문법					pack size				연산 기능
subss					32bit float				첫 번째 32bit float형 실수 1개를 뺀다.
subsd					64bit double			첫 번째 64bit double형 실수 1개를 뺀다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	alignas( 16 ) float SrcB[4] = { 4.4f, 3.3f, 2.2f, 1.1f };

	alignas( 16 ) float SubPSResult[4] = { 0.f };
	alignas( 16 ) float SubSSResult[4] = { 0.f };

	__asm
	{
		pushad
		
		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		subps xmm0, xmm2	// xmm0 -= xmm2
		subss xmm1, xmm2	// xmm1 -= xmm2

		movaps SubPSResult, xmm0
		movaps SubSSResult, xmm1

		popad
	}

	std::cout << "SUBPS : ";
	for ( float elem : SubPSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "SUBSS : ";
	for ( float elem : SubSSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}