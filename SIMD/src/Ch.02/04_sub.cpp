#include <iostream>

/*--------------
사용문법						pack size			연산 기능
psubb xmm1, xmm2/m128			char				8bit Byte 형 정수 16개를 더한다.
psubw xmm1, xmm2/m128			short				16bit Byte 형 정수 8개를 더한다.
psubd xmm1, xmm2/m128			interger			32bit Byte 형 정수 4개를 더한다.
psubq xmm1, xmm2/m128			__int64				64bit Byte 형 정수 2개를 더한다.
psubsb xmm1, xmm2/m128			signed char			8bit signed Byte형 덧셈, 오버플로 시 +- 부호 유지
psubsw xmm1, xmm2/m128			signed short		16bit signed Byte형 덧셈, 오버플로 시 +- 부호 유지
psubusb xmm1, xmm2/m128			unsigned char		8bit usigned Byte형 덧셈, 오버플로 시 + 부호 유지
psubusw xmm1, xmm2/m128			unsigned short		16bit usigned Byte형 덧셈, 오버플로 시 + 부호 유지
--------------*/

int main( )
{
	char ByteArrayA[16] = { 0 };
	char ByteArrayB[16] = { 0 };

	for ( int i = 0; i < 16; ++i )
	{
		ByteArrayA[i] = i + 1;
		ByteArrayB[i] = i;
	}

	char ByteResult[16] = { 0 };

	__asm
	{
		pushad
		movdqu xmm0, ByteArrayA
		movdqu xmm1, ByteArrayB
		psubb xmm0, xmm1			// xmm0 -= xmm1
		movdqu ByteResult, xmm0
		popad
	}

	std::cout << "subResult : ";
	for ( char elem : ByteResult )
	{
		std::cout << static_cast<int>( elem ) << ' ';
	}
	std::cout << std::endl;
}