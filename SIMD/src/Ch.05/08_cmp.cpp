/*--------------
__m128 r = _mm_cmpeq_ps( __m128 a, __m128 b )

__m128 r = _mm_cmpgt_ps( __m128 a, __m128 b )

__m128 r = _mm_cmplt_ps( __m128 a, __m128 b )

intrinsic			SIMD 연산자		Operation
_mm_cmpeq_ss		CMPEQSS			==
_mm_cmpeq_ps		CMPEQPS			==
_mm_cmplt_ss		CMPLTSS			<
_mm_cmplt_ps		CMPLTPS			<
_mm_cmple_ss		CMPLESS			<=
_mm_cmple_ps		CMPLEPS			<=
_mm_cmpgt_ss		CMPGTSS			>
_mm_cmpgt_ps		CMPGTPS			>
_mm_cmpge_ss		CMPGESS			>=
_mm_cmpge_ps		CMPGEPS			>=
_mm_cmpneq_ss		CMPNEQSS		!=
_mm_cmpneq_ps		CMPNEQPS		!=
_mm_cmpnlt_ss		CMPNLTSS		!( a < b )
_mm_cmpnlt_ps		CMPNLTPS		!( a < b )
_mm_cmpnle_ss		CMPNLESS		!( a <= b )
_mm_cmpnle_ps		CMPNLEPS		!( a <= b )
_mm_cmpngt_ss		CMPNGTSS		!( a > b )
_mm_cmpngt_ps		CMPNGTPS		!( a > b )
_mm_cmpnge_ss		CMPNGESS		!( a >= b )
_mm_cmpnge_ps		CMPNGEPS		!( a >= b )
_mm_cmpord_ss		CMPORDSS		정렬
_mm_cmpord_ps		CMPORDPS		정렬
_mm_cmpunord_ss		CMPUNORDSS		역순 정렬
_mm_cmpunord_ps		CMPUNORDPS		역순 정렬
_mm_comieq_ss		COMISS			==
_mm_comilt_ss		COMISS			<
_mm_comile_ss		COMISS			<=
_mm_comigt_ss		COMISS			>
_mm_comige_ss		COMISS			>=
_mm_comineq_ss		UCOMISS			!=
_mm_ucomieq_ss		UCOMISS			==
_mm_ucomilt_ss		UCOMISS			<
_mm_ucomile_ss		UCOMISS			<=
_mm_ucomigt_ss		UCOMISS			>
_mm_ucomige_ss		UCOMISS			>=
_mm_ucomineq_ss		UCOMISS			!=
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float A[4] = { 1.f, 2.f, 3.f, 4.f };
	alignas( 16 ) float B[4] = { 2.f, 2.f, 2.f, 2.f };
	alignas( 16 ) float R[4] = { 0 };

	__m128 xmmA = _mm_load_ps( A );
	__m128 xmmB = _mm_load_ps( B );

	__m128 xmmR = _mm_cmpeq_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );

	std::cout << "equality : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_cmpgt_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );
	std::cout << "grater than : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_cmplt_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );
	std::cout << "less than : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}