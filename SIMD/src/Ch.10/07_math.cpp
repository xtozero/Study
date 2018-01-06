/*--------------
intrinsic 수학 함수는 복잡한 수학 연산을 사용할 수 있도록 도와주며 하드웨어 계산 방식을 지원하기 때문에 빠르다.

R = _mm256_rcp_ps( A );
R = _mm256_sqrt_ps( A );
R = _mm256_rsqrt_ps( A );
R = _mm256_hadd_ps( A, B );
R = _mm256_hsub_ps( A, B );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float DstRCP[8] = { 0 };
	float DstRsqrt[8] = { 0 };
	float DstSqrt[8] = { 0 };
	float DstHadd[8] = { 0 };
	float DstHsub[8] = { 0 };

	__m256 mSrcA = _mm256_loadu_ps( SrcA );
	__m256 mSrcB = _mm256_loadu_ps( SrcB );

	__m256 mDst = _mm256_rcp_ps( mSrcA );
	_mm256_storeu_ps( DstRCP, mDst );

	mDst = _mm256_rsqrt_ps( mSrcA );
	_mm256_storeu_ps( DstRsqrt, mDst );

	mDst = _mm256_sqrt_ps( mSrcA );
	_mm256_storeu_ps( DstSqrt, mDst );

	mDst = _mm256_hadd_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( DstHadd, mDst );

	mDst = _mm256_hsub_ps( mSrcA, mSrcB );
	_mm256_storeu_ps( DstHsub, mDst );

	std::cout << "RCP : ";
	for ( double elem : DstRCP )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Rsqrt : ";
	for ( double elem : DstRsqrt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Sqrt : ";
	for ( double elem : DstSqrt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Hadd : ";
	for ( double elem : DstHadd )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Hsub : ";
	for ( double elem : DstHsub )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}