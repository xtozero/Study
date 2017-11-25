/*--------------
__m128i r = _mm_cmpeq_epi16( __m128i a, __m128i b )
__m128i r = _mm_cmpgt_epi16( __m128i a, __m128i b )
__m128i r = _mm_cmplt_epi16( __m128i a, __m128i b )

intrinsic			SIMD 연산자		Operation
_mm_cmpeq_epi8		PCMPEQB			==
_mm_cmpeq_epi16		PCMPEQW			==
_mm_cmpeq_epi32		PCMPEQD			==
_mm_cmpgt_epi8		PCMPGTB			>
_mm_cmpgt_epi16		PCMPGTW			>
_mm_cmpgt_epi32		PCMPGTD			>
_mm_cmplt_epi8		PCMPGTB			<
_mm_cmplt_epi16		PCMPGTW			<
_mm_cmplt_epi32		PCMPGTD			<

_mm_cmplt_epi8, _mm_cmplt_epi16, _mm_cmplt_epi32 는 PCMPGT 명령셋 인수 위치를 바뀌 연산한다.
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short A[8] = { 1, 0, 1, 0, 1, 0, 1, 0 };
	alignas( 16 ) short B[8] = { 1, 1, 2, 1, 0, 0, 0, -1 };
	alignas( 16 ) short R[8] = { 0 };

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
	__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );
	__m128i xmmR = _mm_cmpeq_epi16( xmmA, xmmB );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << std::hex;
	std::cout << "Equality : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_cmpgt_epi16( xmmA, xmmB );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Greater Than : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_cmplt_epi16( xmmA, xmmB );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Less Than : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}