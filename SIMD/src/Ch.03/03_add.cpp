#include <iostream>

/*--------------
Add Packed
32bit float형 실수 4개 혹은 64bit double형 실수 2개를 동시에 더한다.

사용문법					pack size				연산 기능
addps					32bit float				32bit float형 실수 4개를 동시에 더한다.
addpd					64bit double			64bit double형 실수 2개를 동시에 더한다.

Add Scalar
접미사 S는 Scalar연산을 의미한다.
첫번째 pack의 32bit float형 실수 혹은 64bit double형 실수를 더한다.

사용문법					pack size				연산 기능
addss					32bit float				첫 번째 32bit float형 실수 1개를 더한다.
addsd					64bit double			첫 번째 64bit double형 실수 1개를 더한다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	alignas( 16 ) float SrcB[4] = { 4.4f, 3.3f, 2.2f, 1.1f };

	alignas( 16 ) float AddPSResult[4] = { 0.f };
	alignas( 16 ) float AddSSResult[4] = { 0.f };

	__asm
	{
		pushad

		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		addps xmm0, xmm2	// xmm0 += xmm2
		addss xmm1, xmm2	// xmm1 += xmm2

		movaps AddPSResult, xmm0
		movaps AddSSResult, xmm1

		popad
	}

	std::cout << "ADDPS : ";
	for ( float elem : AddPSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "ADDSS : ";
	for ( float elem : AddSSResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}
