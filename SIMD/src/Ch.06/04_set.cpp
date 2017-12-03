/*--------------
_m128d r = _mm_set_pd( double w, double x )

_m128d r = _mm_set1_pd( double w )

_m128d r = _mm_setr_pd( double w, double x )

_m128d r = _mm_setzero_pd(void)

intrinsic 함수		SIMD 명령어		연산 방식
_mm_set_sd			없음				하위 32bit 값을 입력하고, 나머지는 0으로 초기화
_mm_set1_pd			없음				32bit 실수형 데이터 1개를 입력받아 4개로 대입
_mm_set_pd			없음				32bit 실수형 데이터 4개를 입력받아 대입
_mm_setr_pd			없음				32bit 실수형 데이터 4개를 입력받아 역순으로 대입
_mm_setzero_pd		XORPD			모두 0으로 초기화
_mm_move_sd			MOVSD			하위 64bit에 double형 실숫값을 넣고 상위는 a의 인자 전달
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) double R[2] = { 0 };

	__m128d xmmR = _mm_set_pd( 2.0, 1.0 );

	_mm_store_pd( R, xmmR );

	std::cout << std::fixed;
	std::cout << "Set : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_set1_pd( 3.0 );

	_mm_store_pd( R, xmmR );

	std::cout << "Set1 : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_setr_pd( 5.0, 4.0 );

	_mm_store_pd( R, xmmR );

	std::cout << "Setr : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_setzero_pd( );

	_mm_store_pd( R, xmmR );

	std::cout << "Set Zero : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}