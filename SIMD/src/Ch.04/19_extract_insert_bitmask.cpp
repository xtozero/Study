/*--------------
__m128i r = _mm_insert_epi16( __m128i a, int b, int imm )
int r = _mm_extract_epi16( __m128i a, int imm )
int r = _mm_movemask( _128i a )

intrinsic 함수			SIMD 명령어		연산 방식
_mm_extract_epi16		PEXTRW			pack에 있는 1개 값 가져오기
_mm_insert_epi16		PINSRW			pack에 있는 1개 값 입력하기
_mm_movemask_epi8		PMOVMSKB		bitmask 생성
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short A[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short R[8] = { 0 };
	
	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
	__m128i xmmR = _mm_insert_epi16( xmmA, 10, 3 );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Result : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	int r = _mm_extract_epi16( xmmA, 6 );

	std::cout << "Extract Result : " << r << std::endl;

	alignas( 16 ) char B[16] = { 0xFF, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );

	int mask = _mm_movemask_epi8( xmmB );

	std::cout << "Mask : " << mask << std::endl;

	return 0;
}