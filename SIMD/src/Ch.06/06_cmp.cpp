/*--------------
__m128d r = _mm_cmpeq_pd( __m128d a, __m128d b )

__m128d r = _mm_cmpgt_pd( __m128d a, __m128d b )

__m128d r = _mm_cmplt_pd( __m128d a, __m128d b )

intrinsic 함수		SIMD 명령어		연산 방식		데이터형
_mm_cmpeq_pd		CMPEQPD			==				packed
_mm_cmplt_pd		CMPLTPD			<				packed
_mm_cmple_pd		CMPLEPD			<=				packed
_mm_cmpgt_pd		CMPGTPD			>				packed
_mm_cmpge_pd		CMPGEPD			>=				packed
_mm_cmpneq_pd		CMPNEQPD		!=				packed
_mm_cmpnlt_pd		CMPNLTPD		!( a < b )		packed
_mm_cmpnle_pd		CMPNLEPD		!( a <= b )		packed
_mm_cmpngt_pd		CMPNGTPD		!( a > b )		packed
_mm_cmpnge_pd		CMPNGEPD		!( a >= b )		packed
_mm_cmpord_pd		CMPORDPD		정렬				packed
_mm_cmpunord_pd		CMPUNORDPD		역순 정렬		packed
_mm_cmpeq_sd		CMPEQSD			==				scalar
_mm_cmplt_sd		CMPLTSD			<				scalar
_mm_cmple_sd		CMPLESD			<=				scalar
_mm_cmpgt_sd		CMPGTSD			>				scalar
_mm_cmpge_sd		CMPGESD			>=				scalar
_mm_cmpneq_sd		CMPNEQSD		!=				scalar
_mm_cmpnlt_sd		CMPNLTSD		!( a < b )		scalar
_mm_cmpnle_sd		CMPNLESD		!( a <= b )		scalar
_mm_cmpngt_sd		CMPNGTSD		!( a > b )		scalar
_mm_cmpnge_sd		CMPNGESD		!( a >= b )		scalar
_mm_cmpord_sd		CMPORDSD		정렬				scalar
_mm_cmpunord_sd		CMPUNORDSD		역순 정렬		scalar
_mm_comieq_sd		COMISD			==				scalar
_mm_comilt_sd		COMISD			<				scalar
_mm_comile_sd		COMISD			<=				scalar
_mm_comigt_sd		COMISD			>				scalar
_mm_comige_sd		COMISD			>=				scalar
_mm_comineq_sd		UCOMISDdd			!=				scalar
_mm_ucomieq_sd		UCOMISDdd			==				scalar
_mm_ucomilt_sd		UCOMISDdd			<				scalar
_mm_ucomile_sd		UCOMISDdd			<=				scalar
_mm_ucomigt_sd		UCOMISDdd			>				scalar
_mm_ucomige_sd		UCOMISDdd			>=				scalar
_mm_ucomineq_sd		UCOMISDdd			!=				scalar
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) double A[2] = { 1.0, 2.0 };
	alignas( 16 ) double B[2] = { 1.0, 1.0 };
	alignas( 16 ) double C[2] = { 1.0, 3.0 };
	alignas( 16 ) double R[2] = { 0 };

	__m128d xmmA = _mm_load_pd( A );
	__m128d xmmB = _mm_load_pd( B );
	__m128d xmmC = _mm_load_pd( C );

	__m128d xmmR = _mm_cmpeq_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );

	std::cout << "equality : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_cmpgt_pd( xmmA, xmmB );

	_mm_store_pd( R, xmmR );
	std::cout << "grater than : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_cmplt_pd( xmmA, xmmC );

	_mm_store_pd( R, xmmR );
	std::cout << "less than : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}