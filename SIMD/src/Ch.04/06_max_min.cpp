/*--------------
__m128i r = _mm_max_epi16( __m128i a, __m128i b )
__m128i r = _mm_min_epi16( __m128i a, __m128i b )

intrinsic			SIMD 연산자		Operation										데이터 타입
_mm_max_epi16		PMAXSW			16bit 8개 packed Max 값							signed
_mm_max_epu8		PMAXUB			8bit 16개 packed Max 값							unsigned
_mm_min_epi16		PMINSW			16bit 8개 packed Min 값							signed
_mm_min_epu8		PMINUB			8bit 16개 packed Min 값							unsigned
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
	__m128i xmmR = _mm_max_epi16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Max : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_min_epi16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Min : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}