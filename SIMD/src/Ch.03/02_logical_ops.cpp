#include <iostream>

/*--------------
각 pack의 실수값에 대해 Bitwase 논리연산을 수행한다.
AND, OR, XOR, AND NOT을 지원한다.

사용문법					pack size				연산 기능
andps					32bit float				32bit float형 실수 4개를 AND 연산
andpd					64bit double			64bit double형 실수 2개를 AND 연산
orps					32bit float				32bit float형 실수 4개를 OR 연산
orpd					64bit double			64bit double형 실수 2개를 OR 연산
xorps					32bit float				32bit float형 실수 4개를 XOR 연산
xorpd					64bit double			64bit double형 실수 2개를 XOR 연산
andnps					32bit float				32bit float형 실수 4개를 AND NOT 연산
andnpd					64bit double			64bit double형 실수 2개를 AND NOT 연산
--------------*/

int main( )
{
	alignas( 16 ) float SourceA[4] = { 1.f, 0.f, 1.f, 0.f };
	alignas( 16 ) float SourceB[4] = { 1.f, 1.f, 0.f, 0.f };

	alignas( 16 ) float ANDResult[4] = { 0.f };
	alignas( 16 ) float ORResult[4] = { 0.f };
	alignas( 16 ) float XORResult[4] = { 0.f };
	alignas( 16 ) float ANDNOTResult[4] = { 0.f };

	__asm
	{
		pushad

		movaps xmm0, SourceA
		movaps xmm1, xmm0
		movaps xmm2, xmm0
		movaps xmm3, xmm0
		movaps xmm4, SourceB

		andps xmm0, xmm4
		orps xmm1, xmm4
		xorps xmm2, xmm4
		andnps xmm3, xmm4

		movaps ANDResult, xmm0
		movaps ORResult, xmm1
		movaps XORResult, xmm2
		movaps ANDNOTResult, xmm3

		popad
	}

	std::cout << "AND : ";
	for ( float elem : ANDResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "OR : ";
	for ( float elem : ORResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "XOR : ";
	for ( float elem : XORResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "ANDNOT : ";
	for ( float elem : ANDNOTResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}