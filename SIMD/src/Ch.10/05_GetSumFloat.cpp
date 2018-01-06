#include "immintrin.h"
#include "../Util/StopWatch.h"

#include <iostream>

float GetSumFloatAVX( float* pData, int size )
{
	int i = 0;
	float sum = 0;
	float* pFloatA = pData;

	__m256 avxSum = _mm256_setzero_ps( );
	__m256 avxCurValue = _mm256_setzero_ps( );

	for ( int i = 0; i < size; i += 8 )
	{
		avxCurValue = _mm256_loadu_ps( pFloatA + i );
		avxSum = _mm256_add_ps( avxSum, avxCurValue );
	}

	for ( int i = 0; i < 8; ++i )
	{
		sum += *( (float*)( &avxSum ) + i );
	}

	return sum;
}

int main( )
{
	constexpr int SIZE = 8000;
	alignas( 32 ) float FloatDataArray[SIZE];

	float FloatSum = 0;
	int IntergerSum = 0;

	for ( int i = 0; i < SIZE; ++i )
	{
		FloatDataArray[i] = static_cast<float>( i );
		IntergerSum += i;
	}

	std::cout << "Integer Sum Result : " << IntergerSum << std::endl;

	CStopWatch StopWatch;
	StopWatch.Start( );
	float SIMDResult = GetSumFloatAVX( FloatDataArray, SIZE );
	StopWatch.End( );

	std::cout << "AVX Sum Result : " << SIMDResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}