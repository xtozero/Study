/*--------------
__m128i r = _mm_slli_epi16( __m128i a, int count );
__m128i r = _mm_sll_epi16( __m128i a, __m128i count );
__m128i r = _mm_srai_epi16( __m128i a, int count );
__m128i r = _mm_sra_epi16( __m128i a, __m128i count );
__m128i r = _mm_srli_epi16( __m128i a, int count );
__m128i r = _mm_srl_epi16( __m128i a, __m128i count );

intrinsic			SIMD 연산자		Operation			쉬프트 형식
_mm_slli_si128		PSLLDQ			왼쪽 쉬프트			논리적 쉬프트
_mm_slli_epi16		PSLLW			왼쪽 쉬프트			논리적 쉬프트
_mm_sll_epi16		PSLLW			왼쪽 쉬프트			논리적 쉬프트
_mm_slli_epi32		PSLLD			왼쪽 쉬프트			논리적 쉬프트
_mm_sll_epi32		PSLLD			왼쪽 쉬프트			논리적 쉬프트
_mm_slli_epi64		PSLLQ			왼쪽 쉬프트			논리적 쉬프트
_mm_sll_epi64		PSLLQ			왼쪽 쉬프트			논리적 쉬프트
_mm_srai_epi16		PSRAW			오른쪽 쉬프트			산술적 쉬프트
_mm_sra_epi16		PSRAW			오른쪽 쉬프트			산술적 쉬프트
_mm_srai_epi32		PSRAD			오른쪽 쉬프트			산술적 쉬프트
_mm_sra_epi32		PSRAD			오른쪽 쉬프트			산술적 쉬프트
_mm_srli_si128		PSRLDQ			오른쪽 쉬프트			논리적 쉬프트
_mm_srli_epi16		PSRLW			오른쪽 쉬프트			논리적 쉬프트
_mm_srl_epi16		PSRLW			오른쪽 쉬프트			논리적 쉬프트
_mm_srli_epi32		PSRLD			오른쪽 쉬프트			논리적 쉬프트
_mm_srl_epi32		PSRLD			오른쪽 쉬프트			논리적 쉬프트
_mm_srli_epi64		PSRLQ			오른쪽 쉬프트			논리적 쉬프트
_mm_srl_epi64		PSRLQ			오른쪽 쉬프트			논리적 쉬프트
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short A[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short B[8] = { -1, -2, -3, -4, -5, -6, -7, -8 };
	alignas( 16 ) short R[8] = { 0 };

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
	__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );

	__m128i xmmR = _mm_slli_epi16( xmmA, 1 );		// 양수 왼쪽 shift

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Left Shift : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_slli_epi16( xmmB, 1 );		// 음수 왼쪽 shift

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Left Shift : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_srai_epi16( xmmA, 1 );		// 양수 산술적 오른쪽 shift

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Arithmetic Right Shift : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_srli_epi16( xmmA, 1 );		// 양수 논리적 오른쪽 shift

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Logical Right Shift : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_srai_epi16( xmmB, 1 );		// 음수 산술적 오른쪽 shift

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Arithmetic Right Shift : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_srli_epi16( xmmB, 1 );		// 음수 논리적 오른쪽 shift

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );
	std::cout << "Logical Right Shift : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}