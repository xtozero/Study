/*--------------
__m128 r = _mm_and_ps( __m128 a, __m128 b )

__m128 r = _mm_or_ps( __m128 a, __m128 b )

__m128 r = _mm_xor_ps( __m128 a, __m128 b )

__m128 r = _mm_andnot_ps( __m128 a, __m128 b )

intrinsic			SIMD 연산자		Operation
_mm_and_ps			ANDPS			And 연산
_mm_andnot_ps		ANDNPS			And Not 연산
_mm_or_ps			ORPS			OR 연산
_mm_xor_ps			XORPS			XOR 연산
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float A[4] = { 1, 1, 0, 0 };
	alignas( 16 ) float B[4] = { 1, 0, 1, 0 };

	alignas( 16 ) float Result[4] = { 0 };

	std::cout << "SourceA : ";
	for ( float elem : A )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "SourceB : ";
	for ( float elem : B )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m128 xmmA = _mm_load_ps( A );
	__m128 xmmB = _mm_load_ps( B );

	__m128 xmmR = _mm_and_ps( xmmA, xmmB );

	_mm_store_ps( Result, xmmR );

	std::cout << "AND Result : ";
	for ( float elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_andnot_ps( xmmA, xmmB );

	_mm_store_ps( Result, xmmR );

	std::cout << "ANDNOT Result : ";
	for ( float elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_or_ps( xmmA, xmmB );

	_mm_store_ps( Result, xmmR );

	std::cout << "OR Result : ";
	for ( float elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_xor_ps( xmmA, xmmB );

	_mm_store_ps( Result, xmmR );

	std::cout << "XOR Result : ";
	for ( float elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}