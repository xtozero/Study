/*--------------
__m128i r = _mm_avg_epu16( __m128i a, __m128i b )
16bit 정수 8개를 가진 128bit 데이터 타입 a, b를 평균하여 반올림한 뒤 r 값에 리턴한다.
unsigned 형만 지원한다.

intrinsic			SIMD 연산자		Operation										데이터 타입
_mm_avg_epu8		PAVGB			8bit 16개 packed 평균값							unsigned
_mm_avg_epu16		PAVGW			16bit 8개 packed 평균값							unsigned
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short A[8] = { 2, 4, 6, 8, 10, 8, 6, 4 };
	alignas( 16 ) short B[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short R[8] = { 0 };

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
	__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );
	__m128i xmmR = _mm_avg_epu16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Avg : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}