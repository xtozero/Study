/*--------------
AVX에서 기존의 Extract 함수에 extractf128이 추가되었다.
extractf128은 __m256 데이터형의 원하는 위치에서 __m128 데이터를 가져온다.
위치 지정은 함수의 2번째 인수에 0을 넣으면 하위 128bit, 1을 넣으면 상위 128bit 위치의 데이터를 가져온다.

R = _mm256_extractf128_ps( A, 1 );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	int nSrc[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
	float fSrc[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

	int DstIA[4] = { 0 };
	int DstIB[4] = { 0 };
	float DstPSA[4] = { 0 };
	float DstPSB[4] = { 0 };

	__m256 m256Src = _mm256_loadu_ps( fSrc );
	__m128 m128Src = _mm256_extractf128_ps( m256Src, 0 );

	_mm_storeu_ps( DstPSA, m128Src );

	m128Src = _mm256_extractf128_ps( m256Src, 1 );

	_mm_storeu_ps( DstPSB, m128Src );

	std::cout << "DstPSA : ";
	for ( float elem : DstPSA )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "DstPSB : ";
	for ( float elem : DstPSB )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m256i m256iSrc = _mm256_loadu_si256( reinterpret_cast<__m256i*>( nSrc ) );
	__m128i m128iSrc = _mm256_extractf128_si256( m256iSrc, 0 );

	_mm_storeu_si128( reinterpret_cast<__m128i*>( DstIA ), m128iSrc );

	m128iSrc = _mm256_extractf128_si256( m256iSrc, 1 );

	_mm_storeu_si128( reinterpret_cast<__m128i*>( DstIB ), m128iSrc );

	std::cout << "DstIA : ";
	for ( int elem : DstIA )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "DstIB : ";
	for ( int elem : DstIB )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}