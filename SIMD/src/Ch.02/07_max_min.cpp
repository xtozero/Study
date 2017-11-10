#include <iostream>

/*--------------
2개의 128bit XMM 레지스터 안에 있는 pack 값을 비교하여 최대값을 구한다.

사용문법						pack size			연산 기능
pmaxsb xmm1, xmm2/m128			signed char			8bit signed Byte 16개 계산
pmaxsw xmm1, xmm2/m128			signed short		16bit signed short 8개 계산
pmaxsd xmm1, xmm2/m128			signed integer		32it signed integer 4개 계산
pmaxub xmm1, xmm2/m128			unsigned char		8bit unsigned Byte 16개 계산
pmaxuw xmm1, xmm2/m128			unsigned short		16bit unsigned short 8개 계산
pmaxud xmm1, xmm2/m128			unsigend integer	32bit unsigned integer 4개 계산

2개의 128bit XMM 레지스터 안에 있는 pack 값을 비교하여 최소값을 구한다.
사용문법						pack size			연산 기능
pminsb xmm1, xmm2/m128			signed char			8bit signed Byte 16개 계산
pminsw xmm1, xmm2/m128			signed short		16bit signed short 8개 계산
pminsd xmm1, xmm2/m128			signed integer		32it signed integer 4개 계산
pminub xmm1, xmm2/m128			unsigned char		8bit unsigned Byte 16개 계산
pminuw xmm1, xmm2/m128			unsigned short		16bit unsigned short 8개 계산
pminud xmm1, xmm2/m128			unsigend integer	32bit unsigned integer 4개 계산
--------------*/

int main( )
{
	short ShortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	short ShortArrayB[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	short MinResult[8] = { 0 };
	short MaxResult[8] = { 0 };

	__asm
	{
		pushad
		movdqu xmm0, ShortArrayA
		movdqu xmm1, xmm0
		movdqu xmm2, ShortArrayB
		
		pminsw xmm0, xmm2
		pmaxsw xmm1, xmm2

		movdqu MinResult, xmm0
		movdqu MaxResult, xmm1

		popad
	}

	std::cout << "MinResult : ";
	for ( short elem : MinResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;


	std::cout << "MaxResult : ";
	for ( short elem : MaxResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}