/*--------------
__m128i r = _mm_shuffle_epi32( __m128i a, int imm )

intrinsic				SIMD 연산자		Operation
_mm_shuffle_epi32		PSHUFD			선택 조합
_mm_shufflehi_epi16		PSHUFHW			선택 조합
_mm_shufflelo_epi16		PSHUFLW			선택 조합
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) int A[4] = { 1, 2, 3, 4 };
	alignas( 16 ) int B[4] = { 0 };

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );

	__m128i xmmR = _mm_shuffle_epi32( xmmA, 0b10011101 );

	_mm_store_si128( reinterpret_cast<__m128i*>( B ), xmmR );

	std::cout << "Shuffle : ";
	for ( int elem : B )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}