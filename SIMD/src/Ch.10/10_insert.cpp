/*--------------
AVX에서 기존의 Insert 함수에 insertf128이 추가되었다.
insertf128은 __m256 데이터형의 원하는 위치에서 __m128 데이터를 넣는다.
위치 지정은 함수의 2번째 인수에 0을 넣으면 하위 128bit, 1을 넣으면 상위 128bit 위치에 데이터를 넣는다.

R = _mm256_extractf128_ps( A, 1 );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	int nSrc[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
	float fSrc[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

	int DstIA[8] = { 0 };
	int DstIB[8] = { 0 };
	float DstPSA[8] = { 0 };
	float DstPSB[8] = { 0 };

	__m256 m256Src = _mm256_setzero_ps( );
	__m128 m128Src = _mm_loadu_ps( fSrc );

	m256Src = _mm256_insertf128_ps( m256Src, m128Src, 0 );

	_mm256_storeu_ps( DstPSA, m256Src );

	m128Src = _mm_loadu_ps( fSrc + 4 );
	m256Src = _mm256_insertf128_ps( _mm256_setzero_ps( ), m128Src, 1 );

	_mm256_storeu_ps( DstPSB, m256Src );

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

	__m256i m256iSrc = _mm256_setzero_si256( );
	__m128i m128iSrc = _mm_loadu_si128( reinterpret_cast<__m128i*>( nSrc ) );

	m256iSrc = _mm256_insertf128_si256( m256iSrc, m128iSrc, 0 );

	_mm256_storeu_si256( reinterpret_cast<__m256i*>( DstIA ), m256iSrc );

	m128iSrc = _mm_loadu_si128( reinterpret_cast<__m128i*>( nSrc + 4 ) );
	m256iSrc = _mm256_insertf128_si256( _mm256_setzero_si256( ), m128iSrc, 1 );

	_mm256_storeu_si256( reinterpret_cast<__m256i*>( DstIB ), m256iSrc );

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