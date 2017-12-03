/*--------------
메모리에서 데이터 읽어오기

__m128d r = _mm_load_pd( double const* dp )
__m128d r = _mm_loadu_pd( double const* dp )

intrinsic 함수		SIMD 명령어			연산 방식
_mm_load_pd			MOVAPD				정렬된 2개의 double형 실수를 읽어온다.
_mm_load1_pd		MOVESD + shuffling	1개의 double형 실수를 읽어서 2개로 복사 대입한다.
_mm_loadr_pd		MOVEAPD + shuffling	2개의 double형 실수를 읽어 역순으로 대입한다.
_mm_loadu_pd		MOVUPD				정렬되지 않은 2개의 double형 실수를 읽어온다.
_mm_load_sd			MOVSD				1개의 double형 실수를 읽어서 하위에 대입하고, 상위는 0으로 초기화
_mm_loadh_pd		MOVHPD				1개의 double형 실수를 읽어서 상위에 대입하고, 하위는 a를 전달
_mm_loadl_pd		MOVLPD				1개의 double형 실수를 읽어서 하위에 대입하고, 상위는 a를 전달


메모리에 데이터 쓰기

void _mm_store_pd( double* dp, __m128d a )
void _mm_storeu_pd( double* dp, __m128d a )

intrinsic 함수		SIMD 명령어			연산 방식
_mm_stream_pd		MOVNTPD				cache 없이 저장하기
_mm_store_sd		MOVSD				하위 64bit 위치 저장
_mm_store1_pd		MOVAPD + shuffling	하위 64bit 값 1개를 2개로 복사후 저장
_mm_store_pd		MOVAPD				align 된 double 형 실수 2개 저장
_mm_storeu_pd		MOVUPD				align 되지 않은 double 형 실수 2개 저장
_mm_storer_pd		MOVAPD + shuffling	align 된 double형 실수 2개를 역순으로 저장
_mm_storeh_pd		MOVHPD				상위 위치 double형 실수 한 개 저장
_mm_storel_pd		MOVLPD				하위 위치 double형 실수 한 개 저장
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) double A[2] = { 1.0, 2.0 };
	alignas( 16 ) double R[2] = { 0.0 };

	__m128d xmmA = _mm_load_pd( A );
	__m128d xmmR = xmmA;
	_mm_store_pd( R, xmmR );

	std::cout << std::fixed;
	std::cout << "Aligned Memory : ";
	for ( double elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	double B[2] = { 3.0, 4.0 };
	double uR[2] = { 0 };

	__m128d xmmB = _mm_loadu_pd( B );
	xmmR = xmmB;
	_mm_storeu_pd( uR, xmmR );

	std::cout << "Unaligned Memory : ";
	for ( double elem : uR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}