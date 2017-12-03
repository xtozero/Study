/*--------------
__m128d r = _mm_and_pd( __m128d a, __m128d b )

__m128d r = _mm_or_pd( __m128d a, __m128d b )

__m128d r = _mm_xor_pd( __m128d a, __m128d b )

__m128d r = _mm_andnot_pd( __m128d a, __m128d b )

intrinsic 함수		SIMD 명령어		연산 방식
_mm_and_pd			ANDPS			And 연산
_mm_andnot_pd		ANDNPS			And Not 연산
_mm_or_pd			ORPS			OR 연산
_mm_xor_pd			XORPS			XOR 연산
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) double A[2] = { 0.0, 1.0 };
	alignas( 16 ) double B[2] = { 1.0, 0.0 };

	alignas( 16 ) double R[2] = { 0 };

	__m128d xmmA = _mm_load_pd( A );
	__m128d xmmB = _mm_load_pd( B );

	__m128d xmmR = _mm_and_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "AND Result : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_or_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "OR Result : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_xor_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "XOR Result : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_andnot_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "ANDNOT Result : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}