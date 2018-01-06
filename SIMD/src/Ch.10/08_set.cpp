/*--------------
set 함수를 사용해서 __m256 데이터형에 원하는 값을 채워 넣을 수 있다.

R = _mm256_set_ps( A, B, C, D, E, F, G, H );
R = _mm256_set_zero();
R = _mm256_setr_ps( A, B, C, D, E, F, G, H );
R = _mm256_set1_ps( A );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float DstSet[8] = { 0 };
	float DstZero[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };
	float DstSetR[8] = { 0 };
	float DstSet1[8] = { 0 };

	__m256 mSrcA = _mm256_loadu_ps( SrcA );
	__m256 mSrcB = _mm256_loadu_ps( SrcB );

	__m256 mDst = _mm256_set_ps( 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f );
	_mm256_storeu_ps( DstSet, mDst );

	mDst = _mm256_setzero_ps( );
	_mm256_storeu_ps( DstZero, mDst );

	mDst = _mm256_setr_ps( 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f );
	_mm256_storeu_ps( DstSetR, mDst );

	mDst = _mm256_set1_ps( 9.f );
	_mm256_storeu_ps( DstSet1, mDst );

	std::cout << "Set : ";
	for ( float elem : DstSet )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Set Zero : ";
	for ( float elem : DstZero )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "SetR : ";
	for ( double elem : DstSetR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Set1 : ";
	for ( double elem : DstSet1 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}