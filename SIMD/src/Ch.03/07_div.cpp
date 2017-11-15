#include <iostream>

/*--------------
실수형 계산에서는 나눗셈 연산이 추가되었다.

Divide Packed
32bit float형 실수 4개 혹은 64bit double형 실수 2개를 동시에 나눈다.

사용문법					pack size				연산 기능
divps					32bit float				32bit float형 실수 4개를 동시에 나눈다.
divpd					64bit double			64bit double형 실수 2개를 동시에 나눈다.

Divide Scalar
첫번째 pack의 32bit float형 실수 혹은 64bit double형 실수를 나눈다.

사용문법					pack size				연산 기능
divss					32bit float				첫 번째 32bit float형 실수 1개를 나눈다.
divsd					64bit double			첫 번째 64bit double형 실수 1개를 나눈다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	alignas( 16 ) float SrcB[4] = { 4.4f, 3.3f, 2.2f, 1.1f };

	alignas( 16 ) float DivPSResult[4] = { 0.f };
	alignas( 16 ) float DivSSResult[4] = { 0.f };

	__asm
	{
		pushad

		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		divps xmm0, xmm2	// xmm0 /= xmm2
		divss xmm1, xmm2	// xmm1 /= xmm2

		movaps DivPSResult, xmm0
		movaps DivSSResult, xmm1

		popad
	}

	std::cout << "DIVPS : ";
	for ( float elem : DivPSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "DIVSS : ";
	for ( float elem : DivSSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}