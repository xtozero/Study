/*--------------
__m128i r = _mm_sub_epi16( __m128i a, __m128i b )

intrinsic			SIMD 연산자		Operation					데이터 타입
_mm_sub_epi8		PSUBB			8bit 16개 packed 뺄셈		signed, unsigned
_mm_sub_epi16		PSUBW			16bit 8개 packed 뺄셈		signed, unsigned
_mm_sub_epi32		PSUBD			32bit 4개 packed 뺄셈		signed, unsigned
_mm_sub_si64		PSUBQ			64bit 1개 scalar 뺄셈		signed, unsigned
_mm_sub_epi64		PSUBQ			64bit 2개 packed 뺄셈		signed, unsigned
_mm_subs_epi8		PSUBSB			8bit 16개 packed 뺄셈		signed
_mm_subs_epi16		PSUBSW			16bit 8개 packed 뺄셈		signed
_mm_subs_epu8		PSUBUSB			8bit 16개 packed 뺄셈		unsigned
_mm_subs_epu16		PSUBUSW			16bit 8개 packed 뺄셈		unsigned
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
	__m128i xmmR = _mm_sub_epi16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Sub : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}