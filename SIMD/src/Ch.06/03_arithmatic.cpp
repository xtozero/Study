/*--------------
__m128d r = _mm_add_pd( __m128d a, __m128d b )

__m128d r = _mm_sub_pd( __m128d a, __m128d b )

__m128d r = _mm_mul_pd( __m128d a, __m128d b )

__m128d r = _mm_div_pd( __m128d a, __m128d b )

__m128d r = _mm_max_pd( __m128d a, __m128d b )

__m128d r = _mm_min_pd( __m128d a, __m128d b )

__m128d r = _mm_sqrt_pd( __m128d a )

intrinsic 함수		SIMD 명령어			연산 방식
_mm_add_sd			ADDSD				Scalar 덧셈
_mm_add_pd			ADDPD				병렬 덧셈
_mm_sub_sd			SUBSD				Scalar 뺄셈
_mm_sub_pd			SUBPD				병렬 뺄셈
_mm_mul_sd			MULSD				Scalar 곱셈
_mm_mul_pd			MULPD				병렬 곱셈
_mm_div_sd			DIVSD				Scalar 나눗셈
_mm_div_pd			DIVPD				병렬 나눗셈
_mm_sqrt_sd			SQRTSD				Scalar 제곱근
_mm_sqrt_pd			SQRTPD				병렬 제곱근
_mm_min_sd			MINSD				Scalar MIN 값
_mm_min_pd			MINPD				병렬 MIN 값
_mm_max_sd			MAXSD				Scalar MAX 값
_mm_max_pd			MAXPD				병렬 MAX 값
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) double A[2] = { 1.0, 2.0 };
	alignas( 16 ) double B[2] = { 3.0, 4.0 };
	alignas( 16 ) double R[2] = { 0 };

	__m128d xmmA = _mm_load_pd( A );
	__m128d xmmB = _mm_load_pd( B );

	__m128d xmmR = _mm_add_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << std::fixed;
	std::cout << "Add : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_sub_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "Sub : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_mul_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "Mul : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_div_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "Div : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_max_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "Max : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_min_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "Min : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_sqrt_pd( xmmA );

	_mm_store_pd( R, xmmR );

	std::cout << "Sqrt : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}