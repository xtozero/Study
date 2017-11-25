/*--------------
intrinsic			SIMD 연산자		Operation										데이터 타입
_mm_madd_epi16		PMADDWD			16bit 8개 packed 곱 합 계산						signed, unsigned
_mm_sad_epu8		PSADBW			8bit 16개 편차를 구해서 총합을 구한다.			unsigned

PMADDWD
xmm0	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|
xmm1	|	1	|	2	|	3	|	4	|	5	|	6	|	7	|	8	|
xmm0	|		22		|		38		|		38		|		22		|

r0 := (a0 * b0) + (a1 * b1)
r1 := (a2 * b2) + (a3 * b3)
r2 := (a4 * b4) + (a5 * b5)
r3 := (a6 * b6) + (a7 * b7)

PSADBW
xmm0	|	16	|	15	|	14	|	13	|	12	|	11	|	10	|	9	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|
xmm1	|	1	|	2	|	3	|	4	|	5	|	6	|	7	|	8	|	9	|	10	|	11	|	12	|	13	|	14	|	15	|	16	|
xmm0	|		0		|		0		|		0		|		64		|		0		|		0		|		0		|		64		|

r0 := abs(a0 - b0) + abs(a1 - b1) +...+ abs(a7 - b7)
r1 := 0x0 ; r2 := 0x0 ; r3 := 0x0
r4 := abs(a8 - b8) + abs(a9 - b9) +...+ abs(a15 - b15)
r5 := 0x0 ; r6 := 0x0 ; r7 := 0x0
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short shortA[8] = { 2, 4, 6, 8, 10, 8, 6, 4 };
	alignas( 16 ) short shortB[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) int intResult[4] = { 0 };

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( shortA ) );
	__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( shortB ) );
	__m128i xmmR = _mm_madd_epi16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( intResult ), xmmR );

	std::cout << "Multiply Add : ";
	for ( int elem : intResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
	
	alignas( 16 ) char charA[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	alignas( 16 ) char charB[16] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	alignas( 16 ) short shortResult[8] = { 0 };
	xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( charA ) );
	xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( charB ) );
	
	// 결과는 첫 번째 pack 다섯 번째 pack에 담기게 된다.
	xmmR = _mm_sad_epu8( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( shortResult ), xmmR );

	std::cout << "Min : ";
	for ( short elem : shortResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}