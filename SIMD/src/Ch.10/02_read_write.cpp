/*--------------
_mm256 데이터에 값을 넣고 가져오는 함수는 기존의 load, store 함수에 256bit를 의미하는 수치가 붙어 확장되었다.

__m256 R = _mm256_loadu_ps( float* S );
_mm256_store_ps( float* R, __m256 S );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	float SrcUnalign[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float DstUnalign[8] = { 0 };
	__m256 AvxData = _mm256_setzero_ps( );

	AvxData = _mm256_loadu_ps( SrcUnalign );
	_mm256_storeu_ps( DstUnalign, AvxData );

	for ( float elem : DstUnalign )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	alignas( 32 ) float SrcAlign[8] = { 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	alignas( 32 ) float DstAlign[8] = { 0 };

	AvxData = _mm256_setzero_ps( );
	
	AvxData = _mm256_load_ps( SrcAlign );
	_mm256_store_ps( DstAlign, AvxData );

	for ( float elem : DstAlign )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}