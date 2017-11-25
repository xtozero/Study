/*--------------
__m128i r = _mm_mullo_epi16( __m128i a, __m128i b )

intrinsic			SIMD 연산자		Operation										데이터 타입
_mm_mulhi_epi16		PMULHW			16bit 8개 packed 곱셈의 상위 17 ~ 32bit 값		signed, unsigned
_mm_mulhi_epu16		PMULHUW			16bit 8개 packed 곱셈의 상위 17 ~ 32bit 값		unsigned
_mm_mullo_epi16		PMULLW			16bit 8개 packed 곱셈							signed, unsigned
_mm_mul_epu32		PMULUDQ			32bit 4개 packed 곱셈							unsigned
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
	__m128i xmmR = _mm_mullo_epi16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Mul : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}