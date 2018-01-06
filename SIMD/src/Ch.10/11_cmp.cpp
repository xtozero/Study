/*--------------
AVX intrinsic 비교 함수는 명령어 세트와 다르게 gt, lt, eq와 같은 접미사를 사용하지 않는다.
대신 cmp 비교 함수의 세번째 인자로 비교 처리 방법을 설정하는 인수를 전달한다.

R = _mm256_cmp_ps( A, B, CMP_EQ_OS );
R = _mm256_cmp_ps( A, B, CMP_LT_OQ );
R = _mm256_cmp_ps( A, B, CMP_GT_OQ );

비교 처리 방법의 접미사는 다음과 같은 의미를 같는다.

OS : ordered signaling
OQ : ordered non-signaling
US : unordered signaling
UQ : unordered non-signaling

ordered : 피연산자가 NaN이 있으면 false, 없으면 true
unordered : 피연산자에 NaN이 있으면 true, 없으면 false
signaling : 피연산자가 NaN 이면 예외 발생.
non-signaling : 피연산자가 NaN이여도 예외를 발생하지 않음.
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float DstEq[8] = { 0 };
	float DstLt[8] = { 0 };
	float DstLe[8] = { 0 };
	float DstGt[8] = { 0 };
	float DstGe[8] = { 0 };

	__m256 mSrcA = _mm256_loadu_ps( SrcA );
	__m256 mSrcB = _mm256_loadu_ps( SrcB );
	__m256 mDst = _mm256_cmp_ps( mSrcA, mSrcB, _CMP_EQ_OS );
	_mm256_storeu_ps( DstEq, mDst );

	mDst = _mm256_cmp_ps( mSrcA, mSrcB, _CMP_LT_OQ );
	_mm256_storeu_ps( DstLt, mDst );

	mDst = _mm256_cmp_ps( mSrcA, mSrcB, _CMP_LE_OQ );
	_mm256_storeu_ps( DstLe, mDst );

	mDst = _mm256_cmp_ps( mSrcA, mSrcB, _CMP_GT_OQ );
	_mm256_storeu_ps( DstGt, mDst );

	mDst = _mm256_cmp_ps( mSrcA, mSrcB, _CMP_GE_OQ );
	_mm256_storeu_ps( DstGe, mDst );

	std::cout << "Equal : ";
	for ( float elem : DstEq )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Less Than : ";
	for ( float elem : DstLt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Less Equal : ";
	for ( float elem : DstLe )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Greater than : ";
	for ( float elem : DstGt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Greater Equal : ";
	for ( float elem : DstGe )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}