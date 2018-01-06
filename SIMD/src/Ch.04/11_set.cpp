/*--------------
모두 0으로 초기화 한다.
__m128i r = _mm_setzero_si128()

16bit short 값 8개를 입력받아 128bit 값에 세트한다.
__m128i r = _mm_set_epi16( short w7, short w6, short w5, short w4, short w3, short w2, short w1, short w0 )
|	w7	|	w6	|	w5	|	w4	|	w3	|	w2	|	w1	|	w0	|

16bit short 값 1개를 입력받아 128bit 값에 세트한다.
__m128i r = _mm_set1_epi16( short w )

16bit short 값 8개를 입력받아 반대 순서로 128bit 값에 세트한다.
__m128i r = _mm_setr_epi16( short w7, short w6, short w5, short w4, short w3, short w2, short w1, short w0 )
|	w0	|	w1	|	w2	|	w3	|	w4	|	w5	|	w6	|	w7	|


intrinsic 함수		SIMD 명령어			연산 방식
_mm_set_epi64		없음					64bit 정수 2개 입력
_mm_set_epi32		없음					32bit 정수  4개 입력
_mm_set_epi16		없음					16bit 정수 8개 입력
_mm_set_epi8		없음					8bit 정수 16개 입력
_mm_set1_epi64		없음					64bit 정수 1개를 입력받아 모두 같은 값으로 입력
_mm_set1_epi32		없음					32bit 정수  1개를 입력받아 모두 같은 값으로 입력
_mm_set1_epi16		없음					16bit 정수 1개를 입력받아 모두 같은 값으로 입력
_mm_set1_epi8		없음					8bit 정수 1개를 입력받아 모두 같은 값으로 입력
_mm_setr_epi64		없음					64bit 정수 2개를 반대 순서로 입력
_mm_setr_epi32		없음					32bit 정수  4개를 반대 순서로 입력
_mm_setr_epi16		없음					16bit 정수 8개를 반대 순서로 입력
_mm_setr_epi8		없음					8bit 정수 16개를 반대 순서로 입력
_mm_setzero_si128	없음					모두 0으로 입력
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short R[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };

	// 0으로 초기화
	__m128i xmmR = _mm_setzero_si128( );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Result : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	// 순서대로 입력
	xmmR = _mm_set_epi16( 8, 7, 6, 5, 4, 3, 2, 1 );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Result : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	// 1개 값으로 모두 입력
	xmmR = _mm_set1_epi16( 9 );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Result : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	// 역순으로 입력
	xmmR = _mm_setr_epi16( 8, 7, 6, 5, 4, 3, 2, 1 );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Result : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}