#include <iostream>

/*--------------
SIMD 명령어 명명법
p <SIMD_op> <suffix> => p packed를 의미, <SIMD_op> 실제 연산을 수행할 내용, <suffix> 연산을 수행할 pack의 사이즈를 의미하는 접미사
pack 사이즈 접미사
s,	signed 
u,	unsigned
b,	byte
w,	word
d,	double word
q,	quad word
--------------*/

int main( )
{
	// MOVDQU : Move Double Quard word Unaligned
	{
		short ShortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		short ShortArrayB[8] = { 0 };

		__asm
		{
			pushad
			movdqu xmm0, ShortArrayA	// xmm0 = ShortArrayA
			movdqu ShortArrayB, xmm0	// ShortArrayB = xmm0
			popad
		}

		std::cout << "ShortArrayB : ";
		for ( short elem : ShortArrayB )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// MOVDQA : Move Double Quard word Align
	{
		alignas(16) short ShortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		alignas(16) short ShortArrayB[8] = { 0 };

		__asm
		{
			pushad
			movdqa xmm0, ShortArrayA	// xmm0 = ShortArrayA
			movdqa ShortArrayB, xmm0	// ShortArrayB = xmm0
			popad
		}

		std::cout << "ShortArrayB : ";
		for ( short elem : ShortArrayB )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
	

	return 0;
}