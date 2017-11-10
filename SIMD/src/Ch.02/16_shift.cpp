#include <iostream>

/*--------------
논리적 왼쪽 shift 연산 - 2배수를 곱한 효과가 있다.
논리적 오른쪽 shift 연산 - 2배수로 나눈 효과가 있다. 음의 정수에 사용하면 2로 나눈 결과가 양수로 바뀌게 되는데 최상위 비트를 값에 상관없이 0으로 넣기 때문이다.
산술적 오른쪽 shift 연산 - 부호를 유지하고 2배수로 나눈 효과가 있다.

논리적 왼쪽 shift 연산 ( Packed Shift Left Logical )
사용문법						pack size			연산 기능
psllw xmm1, imm8				16bit short			16bit short형 정수 8개를 논리적 왼쪽 쉬프트한다.
pslld xmm1, imm8				32bit integer		32bit integer형 정수 4개를 논리적 왼쪽 쉬프트한다.
psllq xmm1, imm8				64bit __int64		64bit __int64 정수 2개를 논리적 왼쪽 쉬프트한다.

논리적 오른쪽 shift 연산 ( Packed Shift Right Logical )
사용문법						pack size			연산 기능
psrlw xmm1, imm8				16bit short			16bit short형 정수 8개를 논리적 오른쪽 쉬프트한다.
psrld xmm1, imm8				32bit integer		32bit integer형 정수 4개를 논리적 오른쪽 쉬프트한다.
psrlq xmm1, imm8				64bit __int64		64bit __int64 정수 2개를 논리적 오른쪽 쉬프트한다.

산술적 오늘쪽 shift 연산 ( Packed Shift Right Arithmetic )
사용문법						pack size			연산 기능
psraw xmm1, imm8				16bit short			16bit short형 정수 8개를 산술적 오른쪽 쉬프트한다.
psrad xmm1, imm8				32bit integer		32bit integer형 정수 4개를 산술적 오른쪽 쉬프트한다.
psraq xmm1, imm8				64bit __int64		64bit __int64 정수 2개를 산술적 오른쪽 쉬프트한다.

XMM 레지스터 전체 왼쪽 shift
사용문법						pack size			연산 기능
pslldq xmm1, imm8				128bit double quad	왼쪽으로 1Byte씩 쉬프트한다.

XMM 레지스터 전체 오른쪽 shift
사용문법						pack size			연산 기능
psrldq xmm1, imm8				128bit double quad	오른쪽으로 1Byte씩 쉬프트한다.
--------------*/

int main( )
{
	// Packed Shift Left Logical
	{
		short Value[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		short ResultA[8] = { 0 };

		__asm
		{
			pushad
			movdqu xmm0, Value
			psllw xmm0, 2
			movdqu ResultA, xmm0
			popad
		}

		std::cout << "Bit Left shift Result : ";
		for ( const short& elem : ResultA )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// Packed Shift Right Logical
	{
		short Value[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		short ResultA[8] = { 0 };

		__asm
		{
			pushad
			movdqu xmm0, Value
			psrlw xmm0, 1
			movdqu ResultA, xmm0 
			popad
		}

		std::cout << "Bit Right shift Result : ";
		for ( const short& elem : ResultA )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// Packed Shift Right Arithmetic
	{
		alignas(16) int intArrayA[4] = { -100, -200, -300, -400 };
		alignas(16) int intResult[4] = { 0 };

		__asm
		{
			pushad
			movdqa xmm0, intArrayA
			psrad xmm0, 2
			movdqa intResult, xmm0
			popad
		}

		std::cout << "Bit Right shift Arithmetic Result : ";
		for ( const int& elem : intResult )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// Byte Shift Logical
	{
		alignas(16) char byteArrayA[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		alignas(16) char LeftResult[16] = { 0 };
		alignas(16) char RightResult[16] = { 0 };

		__asm
		{
			pushad
			movdqa xmm0, byteArrayA
			movdqa xmm1, xmm0
			pslldq xmm0, 2
			psrldq xmm1, 2
			movdqa LeftResult, xmm0
			movdqa RightResult, xmm1
			popad
		}

		std::cout << "Shift Double Quadword Left Logical : ";
		for ( const short& elem : LeftResult )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;

		std::cout << "Shift Double Quadword Right Logical : ";
		for ( const short& elem : RightResult )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
}