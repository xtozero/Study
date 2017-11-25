/*--------------
intrinsic 함수의 연산 결과는 레지스터에 존재하게 된다.
연산을 반복하면 SIMD 명령어 사용과 동일한 성능을 보인다.

__m128i r = _mm_add_epi16( __m128i a, __m128i b )

intrinsic			SIMD 연산자		Operation					데이터 타입
_mm_add_epi8		PADDB			8bit 16개 packed 덧셈		signed, unsigned
_mm_add_epi16		PADDW			16bit 8개 packed 덧셈		signed, unsigned
_mm_add_epi32		PADDD			32bit 4개 packed 덧셈		signed, unsigned
_mm_add_si64		PADDQ			64bit 1개 scalar 덧셈		signed, unsigned
_mm_add_epi64		PADDQ			64bit 2개 packed 덧셈		signed, unsigned
_mm_adds_epi8		PADDSB			8bit 16개 packed 덧셈		signed
_mm_adds_epi16		PADDSW			16bit 8개 packed 덧셈		signed
_mm_adds_epu8		PADDUSB			8bit 16개 packed 덧셈		unsigned
_mm_adds_epu16		PADDUSW			16bit 8개 packed 덧셈		unsigned
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
	__m128i xmmR = _mm_add_epi16( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Add : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}