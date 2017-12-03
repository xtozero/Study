/*--------------
_m128 r = _mm_set_ps( float z, float y, float x, float w )
|	z	|	y	|	x	|	w	|

_m128 r = _mm_set1_ps( float w )

_m128 r = _mm_setzero_ps(void)

_m128 r = _mm_setr_ps( float z, float y, float x, float w )
|	w	|	x	|	y	|	z	|

intrinsic 함수		SIMD 명령어		연산 방식
_mm_set_ss			없음				하위 32bit 값을 입력하고, 나머지는 0으로 초기화
_mm_set1_ps			없음				32bit 실수형 데이터 1개를 입력받아 4개로 대입
_mm_set_ps			없음				32bit 실수형 데이터 4개를 입력받아 대입
_mm_setr_ps			없음				32bit 실수형 데이터 4개를 입력받아 역순으로 대입
_mm_setzero_ps		XORPS			모두 0으로 초기화
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float R[4] = { 0 };

	__m128 xmmR = _mm_set_ps( 4.0, 3.0, 2.0, 1.0 );

	_mm_store_ps( R, xmmR );

	std::cout << std::fixed;
	std::cout << "Set : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_set1_ps( 5.0 );

	_mm_store_ps( R, xmmR );

	std::cout << "Set1 : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_setr_ps( 9.0, 8.0, 7.0, 6.0 );

	_mm_store_ps( R, xmmR );

	std::cout << "Setr : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_setzero_ps( );

	_mm_store_ps( R, xmmR );

	std::cout << "Set Zero : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
	
	return 0;
}