/*--------------
메모리에서 데이터 읽어오기

__m128 r = _mm_load_ps( float* p )
__m128 r = _mm_loadu_ps( float* p )

intrinsic 함수		SIMD 명령어			연산 방식
_mm_loadh_pi		MOVHPS reg, mem		64bit 값을 상위 64bit 위치에 대입한다.
_mm_loadl_pi		MOVLPS reg, mem		64bit 값을 하위 64bit 위치에 대입한다.
_mm_load_ss			MOVSS				32bit 실수를 하위 32bit에 대입하고, 상위 96bit는 0으로 초기화 한다.
_mm_load1_ps		MOVSS + Shuffling	32bit 실수를 4개의 pack에 모두 대입한다.
_mm_load_ps			MOVAPS				align 된 32bit 실수 4개를 읽어서 대입한다.
_mm_loadu_ps		MOVUPS				align 되지 않은 32bit 실수 4개를 읽어서 대입한다.
_mm_loadr_ps		MOVAPS + Shuffling	align 된 32bit 실수 4개를 읽어서 역순으로 대입한다.

메모리에 데이터 쓰기

void _mm_store_ps( float* p, __m128 a )
void _mm_store_ss( float* p, __m128 a )

intrinsic 함수		SIMD 명령어			연산 방식
_mm_storeh_pi		MOVHPS reg, mem		상위 64bit 값을 저장한다.
_mm_storel_pi		MOVLPS reg, mem		하위 64bit 값을 저장한다.
_mm_store_ss		MOVSS				하위 32bit 값을 저장한다.
_mm_store1_ps		MOVSS + Shuffling	하위 32bit 값 1개를 가져와서 4개로 복사하여 저장한다.
_mm_store_ps		MOVAPS				32bit 값 4개를 정렬된 메모리에 저장한다.
_mm_storeu_ps		MOVUPS				32bit 값 4개를 정렬되지 않은 메모리에 저장한다.
_mm_storer_ps		MOVAPS + Shuffling	32bit 값 4개를 역순으로 저장한다.
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float A[4] = { 1.0, 2.0, 3.0, 4.0 };
	alignas( 16 ) float R[4] = { 0 };

	__m128 xmmA = _mm_load_ps( A );
	__m128 xmmR = xmmA;
	_mm_stream_ps( R, xmmR );

	std::cout << std::fixed;
	std::cout << "align Store : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	float B[4] = { 5.0, 6.0, 7.0, 8.0 };
	float R2[4] = { 0 };

	__m128 xmmB = _mm_loadu_ps( B );
	xmmR = xmmB;
	_mm_storeu_ps( R2, xmmR );

	std::cout << "Unalign Store : ";
	for ( float elem : R2 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}