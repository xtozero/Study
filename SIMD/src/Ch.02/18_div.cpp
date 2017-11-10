#include <iostream>

/*--------------
순수하게 Shift만 사용하면 2, 4, 8, 16 단위의 나눗셈만 가능하다. 149/9 과 같은 나눗셈을 구현하기 위해서는 일정한 값을 곱하고 shift연산을 수행한다.
나눗셈을 구하는 과정은 다음과 같다.
1. 오버플로가 발생하지 않는 범위의 shift 단위를 정한다.
	> 256을 shift 단위로 정한다.
2. shift 단위를 재수로 나눈다.
	> 256 / 9 = 28
3. 구한값을 피제수에 곱한다.
	> 149 * 28 = 4172
4. 피제수를 오른쪽 shift한다.
	> 4172 >> 8 = 16
--------------*/

int main( )
{
	short A = 149;
	short B = 9;
	short R = A / B;

	std::cout << "C Div : " << A << " / " << B << " = " << R << std::endl;

	short ShortArrayA[8] = { 149, 149, 149, 149, 149, 149, 149, 149 };
	short ShortArrayB[8] = { 0 };
	short ShortResult[8] = { 0 };

	int multipier = 256 / 9;
	for ( auto& elem : ShortArrayB )
	{
		elem = multipier;
	}

	__asm
	{
		pushad
		movdqu xmm0, ShortArrayA
		movdqu xmm1, ShortArrayB
		pmullw xmm0, xmm1
		psraw xmm0, 8
		movdqu ShortResult, xmm0
		popad
	}

	std::cout << "DivResult : ";
	for ( const short& elem : ShortResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}
