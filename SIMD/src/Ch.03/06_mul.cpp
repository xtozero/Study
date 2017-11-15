#include <iostream>

/*--------------
Multiply Packed
32bit float형 실수 4개 혹은 64bit double형 실수 2개를 동시에 곱한다.

사용문법					pack size				연산 기능
mulps					32bit float				32bit float형 실수 4개를 동시에 곱한다.
mulpd					64bit double			64bit double형 실수 2개를 동시에 곱한다.

Multiply Scalar
첫번째 pack의 32bit float형 실수 혹은 64bit double형 실수를 곱한다.

사용문법					pack size				연산 기능
mulss					32bit float				첫 번째 32bit float형 실수 1개를 곱한다.
mulsd					64bit double			첫 번째 64bit double형 실수 1개를 곱한다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	alignas( 16 ) float SrcB[4] = { 4.4f, 3.3f, 2.2f, 1.1f };

	alignas( 16 ) float MulPSResult[4] = { 0.f };
	alignas( 16 ) float MulSSResult[4] = { 0.f };

	__asm
	{
		pushad

		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		mulps xmm0, xmm2	// xmm0 *= xmm2
		mulss xmm1, xmm2	// xmm1 *= xmm2

		movaps MulPSResult, xmm0
		movaps MulSSResult, xmm1

		popad
	}

	std::cout << "MULPS : ";
	for ( float elem : MulPSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "MULSS : ";
	for ( float elem : MulSSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}