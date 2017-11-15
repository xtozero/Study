#include <iostream>

/*--------------
두 개의 레지스터를 조합해서 pack사이즈를 byte -> word, word -> double word, double word -> quad word로 변환시켜 준다. 

Unpack High Packed Data
High Packed Data는 128bit 레지스터 2개를 합치면 256bit가 되므로 128bit 레지스터의 상위 위치 64bit 두개를 더해서 128bit로 만든다는 의미이다.

		상위 위치						하위 위치 버림
xmm0	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|
xmm1	|	0	|	0	|	0	|	0	|	1	|	1	|	1	|	1	|
xmm0	|	0	|	8	|	0	|	7	|	0	|	6	|	0	|	5	|

사용문법
punpckhbw xmm, xmm/m128
punpckhwd xmm, xmm/m128
punpckhdq xmm, xmm/m128
punpckhqdq xmm, xmm/m128

Unpack Low Packed Data
Low Packed Data는 반대로 하위 64bit만 연산하여 조합하는 명령어이다.

		상위 위치 버림					하위 위치
xmm0	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|
xmm1	|	1	|	1	|	1	|	1	|	0	|	0	|	0	|	0	|
xmm0	|	0	|	4	|	0	|	3	|	0	|	2	|	0	|	1	|

사용문법
punpcklbw xmm, xmm/m128
punpcklwd xmm, xmm/m128
punpckldq xmm, xmm/m128
punpcklqdq xmm, xmm/m128

Packed with signed Saturation
두 개의 레지스터에 담긴 pack 데이터를 word -> byte, double word -> word로 변환시켜 준다. 축소되는 형의 값을 넘어서는 데이터는 사라진다.

xmm0	|		4		|		3		|		2		|		1		|
xmm1	|		8		|		7		|		6		|		5		|
xmm0	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|

사용문법					pack size				연산 기능
packsswb				16bit signed short		16bit short형 정수 8개를 가진 레지스터 2개를 조합하여 8bit 정수형 pack 16개를 가진 레지스터를 조합한다.
packssdw				32bit signed integer	32bit integer형 정수 4개를 가진 레지스터 2개를 조합하여 16bit 정수형 pack 8개를 가진 레지스터를 조합한다.

Packed with unsigned Saturation
Packed with signed Saturation 의 unsiged 버전이다.

사용문법					pack size				연산 기능
packuswb				16bit signed short		16bit short형 정수 8개를 가진 레지스터 2개를 조합하여 8bit 정수형 pack 16개를 가진 레지스터를 조합한다.
packusdw				32bit signed integer	32bit integer형 정수 4개를 가진 레지스터 2개를 조합하여 16bit 정수형 pack 8개를 가진 레지스터를 조합한다.	
--------------*/

int main( )
{
	// Unpack High Packed Data
	{
		alignas( 16 ) short shortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		alignas( 16 ) short shortArrayB[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		alignas( 16 ) short shortResult[8] = { 0 };
		alignas( 16 ) int Result[4] = { 0 };

		__asm
		{
			pushad
			movdqa xmm0, shortArrayA
			movdqa xmm1, shortArrayB
			punpckhwd xmm0, xmm1
			movdqa shortResult, xmm0
			movdqa Result, xmm0
			popad
		}

		std::cout << "short Result : ";
		for ( const short& elem : shortResult )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;

		std::cout << "Int Result : ";
		for ( const int& elem : Result )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// Unpack Low Packed Data
	{
		alignas( 16 ) short shortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		alignas( 16 ) short shortArrayB[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		alignas( 16 ) short shortResult[8] = { 0 };
		alignas( 16 ) int Result[4] = { 0 };

		__asm
		{
			pushad
			movdqa xmm0, shortArrayA
			movdqa xmm1, shortArrayB
			punpcklwd xmm0, xmm1
			movdqa shortResult, xmm0
			movdqa Result, xmm0
			popad
		}

		std::cout << "short Result : ";
		for ( const short& elem : shortResult )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;

		std::cout << "Int Result : ";
		for ( const int& elem : Result )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// Pack wiht signed Saturation
	{
		alignas( 16 ) int intArrayA[4] = { 1, 2, 3, 4 };
		alignas( 16 ) int intArrayB[4] = { 5, 6, 7, 8 };

		alignas( 16 ) short shortResult[8] = { 0 };

		__asm
		{
			pushad
			movdqa xmm0, intArrayA
			movdqa xmm1, intArrayB
			packssdw xmm0, xmm1
			movdqa shortResult, xmm0;
			popad
		}

		std::cout << "short Result : ";
		for ( const short& elem : shortResult )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
}