/*--------------
SSE 논리 연산과 마찬가지로 수행되며 한 번에 8개의 package를 연산한다.
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f };
	float SrcB[8] = { 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f };

	float DstAnd[8] = { 0 };
	float DstOr[8] = { 0 };
	float DstXor[8] = { 0 };
	float DstAndN[8] = { 0 };

	__m256 mSrcA = _mm256_loadu_ps( SrcA );
	__m256 mSrcB = _mm256_loadu_ps( SrcB );

	__m256 mDst = _mm256_and_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( DstAnd, mDst );

	mDst = _mm256_or_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( DstOr, mDst );

	mDst = _mm256_xor_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( DstXor, mDst );

	mDst = _mm256_andnot_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( DstAndN, mDst );

	std::cout << "And : ";
	for ( double elem : DstAnd )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Or : ";
	for ( double elem : DstOr )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Xor : ";
	for ( double elem : DstXor )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "And not : ";
	for ( double elem : DstAndN )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}