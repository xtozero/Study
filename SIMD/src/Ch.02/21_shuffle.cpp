#include <iostream>

/*--------------
Packed Shuffle Byte
1개의 xmm레지스터는 조합하고자 하는 source 값, 다른 xmm 레지스터는 조합하기를 원하는 위치 값을 지정한다.
위치 값은 0 ~ 15 까지이며 해당 값을 넘어서게 되면 0을 세팅하게 된다.

사용문법
pshufb xmm1, xmm2/m128

Shuffle Packed High Words
XMM 레지스터 하위 64bit값은 그대로 전달하고 상위 64bit값은 주어진 위치 상수 imm8의 값에 따라 조합한다.

사용문법
pshufhw xmm1, xmm2/m128, imm8

xmm1 |	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
		11		10		01		00

imm8 00111011b

xmm0 |	4	|	7	|	6	|	7	|	3	|	2	|	1	|	0	|
		00		11		01		11

Shuffle Packed Low Words
XMM 레지스터 상위 64bit값은 그대로 전달하고 상위 64bit값은 주어진 위치 상수 imm8의 값에 따라 조합한다.

사용문법
pshuflw xmm1, xmm2/m128, imm8

xmm1 |	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
										11		10		01		00

imm8 10001100b

xmm0 |	7	|	6	|	5	|	4	|	2	|	0	|	3	|	0	|
										10		00		11		00

Shuffle Packed Double Words
32bit integer형 pack 4개를 담고 있는 레지스터를 조합한다. 위치 상수 imm8의 값에 따라 원하는 조합을 만들 수 있다.

사용문법
pshufd xmm1, xmm2/m128, imm8

xmm1 |	3	|	2	|	1	|	0	|

imm8 00111011b

xmm0 |	0	|	3	|	2	|	3	|
--------------*/

int main( )
{
	short ShortValue[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	short HighResult[8] = { 0 };
	short LowResult[8] = { 0 };

	int IntValue[4] = { 0, 1, 2, 3 };
	int Result[4] = { 0 };

	__asm
	{
		pushad
		movdqu xmm1, ShortValue

		pshufhw xmm0, xmm1, 00111011b

		movdqu HighResult, xmm0

		pshuflw xmm0, xmm1, 10001100b

		movdqu LowResult, xmm0

		movdqu xmm1, IntValue

		pshufd xmm0, xmm1, 00111011b

		movdqu Result, xmm0

		popad
	}

	std::cout << "Shuffle High Result : ";
	for ( short elem : HighResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Shuffle Low Result : ";
	for ( short elem : LowResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Shuffle Result : ";
	for ( int elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}