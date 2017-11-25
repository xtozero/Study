/*--------------
__m128i r = _mm_unpackhi_epi32( __m128i a, __m128i b )
__m128i r = _mm_unpacklo_epi32( __m128i a, __m128i b )

intrinsic				SIMD 연산자		Operation
_mm_unpackhi_epi8		PUNPCKHBW		상위 8개 pack 조합			
_mm_unpackhi_epi16		PUNPCKHWD		상위 4개 pack 조합	
_mm_unpackhi_epi32		PUNPCKHDQ		상위 2개 pack 조합	
_mm_unpackhi_epi64		PUNPCKHQDQ		상위 1개 pack 조합	
_mm_unpacklo_epi8		PUNPCKLBW		하위 8개 pack 조합	
_mm_unpacklo_epi16		PUNPCKLWD		하위 4개 pack 조합	
_mm_unpacklo_epi32		PUNPCKLDQ		하위 2개 pack 조합	
_mm_unpacklo_epi64		PUNPCKLQDQ		하위 1개 pack 조합	

__m128i r = _mm_packs_epi32( __m128i a, __m128i b )

intrinsic				SIMD 연산자		Operation
_mm_packs_epi16			PACKSSWB		형 변환 조립
_mm_packs_epi32			PACKSSDW		형 변환 조립
_mm_packus_epi16		PACKUSWB		형 변환 조립
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	// Unpack
	{
		alignas( 16 ) short A[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		alignas( 16 ) short B[8] = { 0 };
		alignas( 16 ) int R[4] = { 0 };

		__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
		__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );

		__m128i xmmR = _mm_unpackhi_epi16( xmmA, xmmB );

		_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
		std::cout << "Unpack High : ";
		for ( int elem : R )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;

		xmmR = _mm_unpacklo_epi16( xmmA, xmmB );

		_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
		std::cout << "Unpack Low : ";
		for ( int elem : R )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}
	
	// Pack
	{
		alignas( 16 ) int A[4] = { 1, 2, 3, 4 };
		alignas( 16 ) int B[4] = { 5, 6, 7, 8 };
		alignas( 16 ) short R[8] = { 0 };

		__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
		__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );

		__m128i xmmR = _mm_packs_epi32( xmmA, xmmB );

		_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
		std::cout << "Pack : ";
		for ( short elem : R )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}