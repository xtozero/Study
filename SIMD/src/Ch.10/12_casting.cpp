/*--------------
정밀도를 높여서 처리하거나 연산 완료 후 정밀도를 다시 낮추는 일이 빈번하다. 형변환 함수는 이 경우 유용하게 사용된다.

R = _mm256_cvtepi32_ps( A );
R =	_mm256_cvtepi32_pd( A );
R =	_mm256_cvtps_epi32( A );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	{
		int nSrc[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
		float fSrc[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

		int DstPStoI[8] = { 0 };
		float DstItoPS[8] = { 0 };
		double DstItoPD[4] = { 0 };

		__m256i m256iSrc = _mm256_loadu_si256( reinterpret_cast<__m256i*>( nSrc ) );
		__m256 mDstPS = _mm256_cvtepi32_ps( m256iSrc );

		_mm256_storeu_ps( DstItoPS, mDstPS );

		__m128i m128iSrc = _mm_loadu_si128( reinterpret_cast<__m128i*>( nSrc ) );
		__m256d mDstPD = _mm256_cvtepi32_pd( m128iSrc );

		_mm256_storeu_pd( DstItoPD, mDstPD );

		__m256 mSrc = _mm256_loadu_ps( fSrc );
		__m256i m256iDst = _mm256_cvtps_epi32( mSrc );

		_mm256_storeu_si256( reinterpret_cast<__m256i*>( DstPStoI ), m256iDst );

		std::cout << "convert i to ps : ";
		for ( float elem : DstItoPS )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;

		std::cout << "convert i to pd : ";
		for ( double elem : DstItoPD )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;

		std::cout << "convert ps to i : ";
		for ( int elem : DstPStoI )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// char -> float 변환
	{
		char nSrc[20] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		float fSrc[8] = { 10.f, 20.f, 30.f, 40.f, 50.f, 60.f, 70.f, 80.f };

		float DstPS[8] = { 0 };

		__m128i m128isrcA = _mm_loadu_si128( reinterpret_cast<__m128i*>( nSrc ) );
		__m128i m128isrcB = _mm_loadu_si128( reinterpret_cast<__m128i*>( nSrc + 4 ) );

		m128isrcA = _mm_cvtepu8_epi32( m128isrcA );
		m128isrcB = _mm_cvtepu8_epi32( m128isrcB );

		__m256i m256iSrc = _mm256_insertf128_si256( _mm256_setzero_si256( ), m128isrcA, 0 );
		m256iSrc = _mm256_insertf128_si256( m256iSrc, m128isrcB, 1 );

		__m256 mDstPS = _mm256_cvtepi32_ps( m256iSrc );

		_mm256_storeu_ps( DstPS, mDstPS );

		std::cout << std::fixed << "DstPS : ";
		for ( float elem : DstPS )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}
