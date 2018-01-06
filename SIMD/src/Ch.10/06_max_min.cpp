/*--------------
R = _mm256_max_ps( A, B );
R = _mm256_min_ps( A, B );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float fDstMin[8] = { 0 };
	float fDstMax[8] = { 0 };

	__m256 mSrcA = _mm256_loadu_ps( SrcA );
	__m256 mSrcB = _mm256_loadu_ps( SrcB );
	__m256 mDst = _mm256_min_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( fDstMin, mDst );

	mDst = _mm256_max_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( fDstMax, mDst );

	std::cout << "float Min : ";
	for ( double elem : fDstMin )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "float Max : ";
	for ( double elem : fDstMax )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}