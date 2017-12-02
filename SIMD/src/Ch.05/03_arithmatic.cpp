/*--------------
__m128 r = _mm_add_ps( __m128 a, __m128 b )

__m128 r = _mm_sub_ps( __m128 a, __m128 b )

__m128 r = _mm_mul_ps( __m128 a, __m128 b )

__m128 r = _mm_div_ps( __m128 a, __m128 b )

__m128 r = _mm_max_ps( __m128 a, __m128 b )

__m128 r = _mm_min_ps( __m128 a, __m128 b )

intrinsic 함수		연산 방식			SIMD 명령어
_mm_add_ss			ADDSS				Scalar 덧셈
_mm_add_ps			ADDPS				병렬 덧셈
_mm_sub_ss			SUBSS				Scalar 뺄셈
_mm_sub_ps			SUBPS				병렬 뺄셈
_mm_mul_ss			MULSS				Scalar 곱셈
_mm_mul_ps			MULPS				병렬 곱셈
_mm_div_ss			DIVSS				Scalar 나눗셈
_mm_div_ps			DIVPS				병렬 나눗셈
_mm_sqrt_ss			SQRTSS				Scalar 제곱근
_mm_sqrt_ps			SQRTPS				병렬 제곱근
_mm_rcp_ss			RCPSS				Scalar 역수
_mm_rcp_ps			RCPPS				병렬 역수
_mm_rsqrt_ss		RSQRTSS				Scalar 제곱근 역수
_mm_rsqrt_ps		RSQRTPS				병렬 제곱근 역수
_mm_min_ss			MINSS				Scalar MIN 값
_mm_min_ps			MINPS				병렬 MIN 값
_mm_max_ss			MAXSS				Scalar MAX 값
_mm_max_ps			MAXPS				병렬 MAX 값
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float A[4] = { 1.0, 2.0, 3.0, 4.0 };
	alignas( 16 ) float B[4] = { 4.0, 3.0, 2.0, 1.0 };
	alignas( 16 ) float R[4] = { 0 };

	__m128 xmmA = _mm_load_ps( A );
	__m128 xmmB = _mm_load_ps( B );

	__m128 xmmR = _mm_add_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << std::fixed;
	std::cout << "Add : " << std::endl;
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_sub_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << "Sub : " << std::endl;
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_mul_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << "Mul : " << std::endl;
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_div_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << "Div : " << std::endl;
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_max_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << "Max : " << std::endl;
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_min_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << "Min : " << std::endl;
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}