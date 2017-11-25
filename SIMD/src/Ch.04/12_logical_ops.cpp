/*--------------
입력받은 128bit 값에 대해서 bit 단위 연산을 수행한다.
정수형 128bit 논리 연산은 pack에 상관없이 동일하다.
따라서 정수형 intrinsic 함수에서 논리 연산 함수는 모두 동일하다.

__m128i r = _mm_and_si128( __m128i a, __m128i b )

__m128i r = _mm_or_si128( __m128i a, __m128i b )

__m128i r = _mm_xor_si128(  __m128i a, __m128i b )

__m128i r = _mm_andnot_si128(  __m128i a, __m128i b )

intrinsic			SIMD 연산자		Operation
_mm_and_si128		PAND			AND 연산
_mm_andnot_si128	PANDN			AND NOT 연산
_mm_or_si128		POR				OR 연산
_mm_xor_si128		PXOR			XOR 연산
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short A[8] = { 1, 0, 1, 0, 1, 0, 1, 0 };
	alignas( 16 ) short B[8] = { 1, 1, 1, 1, 0, 0, 0, 0 };
	alignas( 16 ) short R[8] = { 0 };

	std::cout << "Source A : ";
	for ( short elem : A )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Source B : ";
	for ( short elem : B )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
	__m128i xmmB = _mm_load_si128( reinterpret_cast<__m128i*>( B ) );
	__m128i xmmR = _mm_and_si128( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "AND : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_or_si128( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "OR : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_xor_si128( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "XOR : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_andnot_si128( xmmA, xmmB );
	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "AND NOT : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}