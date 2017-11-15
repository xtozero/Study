#include <iostream>

/*--------------
두 XMM 레지스터의 pack에 있는 값이 같은지를 비교한다. ( Packed Compare Equal )

사용문법							pack size			연산 기능
pcmpeqb xmm1, xmm2/m128			8bit byte			8bit byte형 정수 16개를 비교하여 값이 같으면 Pack의 모든 비트를 1로 세팅
pcmpeqw xmm1, xmm2/m128			16bit short			16bit short형 정수 8개를 비교하여 값이 같으면 Pack의 모든 비트를 1로 세팅
pcmpeqd xmm1, xmm2/m128			32bit integer		32bit int형 정수 4개를 비교하여 값이 같으면 Pack의 모든 비트를 1로 세팅

xmm0 8	7	6	5		4	3	2	1
xmm1 2	3	4	5		6	7	8	9
xmm0 0	0	0	ffff	0	0	0	0

두 XMM 레지스터의 pack중 어느 것이 더 큰지를 비교한다. ( Packed Compare Greater Than )
사용문법							pack size			연산 기능
pcmpgtb xmm1, xmm2/m128			8bit byte			8bit byte형 정수 16개를 비교하여 값이 크면 Pack의 모든 비트를 1로 세팅
pcmpgtw xmm1, xmm2/m128			16bit short			16bit short형 정수 8개를 비교하여 값이 크면 Pack의 모든 비트를 1로 세팅
pcmpgtd xmm1, xmm2/m128			32bit integer		32bit int형 정수 4개를 비교하여 값이 크면 Pack의 모든 비트를 1로 세팅

Dest가 Source보다 크면 모든 bit에 1을 적는다.
xmm0 8		7		6		5	4	3	2	1
xmm1 2		3		4		5	6	7	8	9
xmm0 ffff	ffff	ffff	0	0	0	0	0
--------------*/

int main( )
{
	short ShortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	short ShortArrayB[8] = { 9, 8, 7, 6, 5, 4, 3, 2 };
	short MinResult[8] = { 0 };
	short MaxResult[8] = { 0 };

	__asm
	{
		pushad
		movdqu xmm0, ShortArrayA
		movdqu xmm1, xmm0
		movdqu xmm2, ShortArrayB

		pcmpeqw xmm0, xmm2
		pcmpgtw xmm1, xmm2

		movdqu MinResult, xmm0
		movdqu MaxResult, xmm1
		popad
	}

	std::cout << "Equality Result : " << std::hex;
	for ( short elem : MinResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;


	std::cout << "Greater than : " << std::hex;
	for ( short elem : MaxResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}