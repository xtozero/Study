#include <iostream>

/*--------------
사용문법						pack size			연산 기능
paddb xmm1, xmm2/m128			char				8bit Byte 형 정수 16개를 더한다.
paddw xmm1, xmm2/m128			short				16bit Byte 형 정수 8개를 더한다.
paadd xmm1, xmm2/m128			interger			32bit Byte 형 정수 4개를 더한다.
paadq xmm1, xmm2/m128			__int64				64bit Byte 형 정수 2개를 더한다.
paddsb xmm1, xmm2/m128			signed char			8bit signed Byte형 덧셈, 오버플로 시 +- 부호 유지
paddsw xmm1, xmm2/m128			signed short		16bit signed Byte형 덧셈, 오버플로 시 +- 부호 유지
paddusb xmm1, xmm2/m128			unsigned char		8bit usigned Byte형 덧셈, 오버플로 시 + 부호 유지
paddusw xmm1, xmm2/m128			unsigned short		16bit usigned Byte형 덧셈, 오버플로 시 + 부호 유지
--------------*/

int main( )
{
	int IntArrayA[4] = { 1, 2, 3, 4 };
	int IntArrayB[4] = { 5, 6, 7, 8 };

	int IntResult[4] = { 0 };

	__asm
	{
		pushad
		movdqu xmm0, IntArrayA
		movdqu xmm1, IntArrayB
		paddd xmm0, xmm1		// xmm0 += xmm1
		movdqu IntResult, xmm0
		popad
	}

	std::cout << "AddResult : ";
	for ( int elem : IntResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}