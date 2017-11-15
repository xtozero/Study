#include <iostream>

/*--------------
32bit float�� �Ǽ� 4�� �Ǵ� 1���� ���� �������� ����Ѵ�.
������ ���������� ���� �����ϰų� �״�� �����Ѵ�.

Sqare root

��빮��					pack size				���� ���
sqrtps					32bit float				32bit float�� �Ǽ� 4���� ���� �������� ���Ѵ�.
sqrtss					32bit float				32bit float�� �Ǽ� 1���� ���� �������� ���Ѵ�.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.f, 2.f, 3.f, 4.f };
	alignas( 16 ) float SrcB[4] = { 4.f, 3.f, 2.f, 1.f };

	alignas( 16 ) float SqrtpsResult[4] = { 0.f };
	alignas( 16 ) float SqrtssResult[4] = { 0.f };

	__asm
	{
		movaps xmm0, SrcA
		movaps xmm1, xmm0
		movaps xmm2, SrcB

		sqrtps xmm0, xmm2	// xmm0 = sqrt( xmm2 ) Packed
		sqrtss xmm1, xmm2	// xmm1 = sqrt( xmm2 ) Scalar

		movaps RcppsResult, xmm0
		movaps RcpssResult, xmm1
	}

	std::cout << "SQRTPS : ";
	for ( float elem : SqrtpsResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "SQRTSS : ";
	for ( float elem : SqrtssResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}