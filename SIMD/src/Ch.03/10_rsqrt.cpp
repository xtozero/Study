#include <iostream>

/*--------------
Reciprocals of Square Root

32bit float형 실수 4개 또는 1개에 대한 제곱의 역수 값을 계산한다.
목적 레지스터에 있던 값은 무시하거나 그대로 전달한다.

사용문법						pack size				연산 기능
rsqrtps xmm1, xmm2/m128		32bit float			32bit float형 실수 4개에 대한 제곱근의 역수 값을 구한다.
rsqrtss xmm1, xmm2/m128		32bit float			32bit float형 실수 4개에 대한 제곱근의 역수 값을 구한다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.f, 2.f, 3.f, 4.f };
	alignas( 16 ) float SrcB[4] = { 4.f, 3.f, 2.f, 1.f };
	alignas( 16 ) float RsqrtpsResult[4] = { 0 };
	alignas( 16 ) float RsqrtssResult[4] = { 0 };

	__asm
	{
		pushad

		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		rsqrtps xmm0, xmm2	// xmm0 = 1 / root( xmm2 ) Packed
		rsqrtss xmm1, xmm2	// xmm1 = 1 / root( xmm1 ) Scalar

		movaps RsqrtpsResult, xmm0
		movaps RsqrtssResult, xmm1

		popad
	}

	std::cout << "RSQRTPS : ";
	for ( float elem : RsqrtpsResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "RSQRTSS : ";
	for ( float elem : RsqrtssResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}