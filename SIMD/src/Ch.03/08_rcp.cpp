#include <iostream>

/*--------------
32bit float형 실수 4개 또는 1개에 대한 역수 값을 계산한다.
목적지 레지스터의 값은 무시하거나 그대로 전달한다.

Reciprocals

사용문법					pack size				연산 기능
rcpps					32bit float				32bit float형 실수 4개에 대한 역수 값을 구한다.
rcpss					32bit float				32bit float형 실수 1개에 대한 역수 값을 구한다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	alignas( 16 ) float SrcB[4] = { 4.4f, 3.3f, 2.2f, 1.1f };

	alignas( 16 ) float RcppsResult[4] = { 0.f };
	alignas( 16 ) float RcpssResult[4] = { 0.f };

	__asm
	{
		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		rcpps xmm0, xmm2	// xmm0 = 1 / xmm2 Packed
		rcpss xmm1, xmm2	// xmm1 = 1 / xmm2 Scalar

		movaps RcppsResult, xmm0
		movaps RcpssResult, xmm1
	}

	std::cout << "RCPPS : ";
	for ( float elem : RcppsResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "RCPSS : ";
	for ( float elem : RcpssResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}