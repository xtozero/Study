#include "immintrin.h"
#include "../Util/StopWatch.h"

#include <iostream>

float GetSumFloatC( float* pData, int size )
{
	float result = 0;

	for ( int i = 0; i < size; ++i )
	{
		result += pData[i];
	}

	return result;
}

float GetSumFloatSSE( float* pData, const int nSize )
{
	int nRemain = nSize % 4;
	int nLoop = nSize - nRemain;

	float sum = 0;
	float* pFloatA = pData;

	__m128 XMMSumValue = _mm_setzero_ps( );
	__m128 XMMCurrentValue = _mm_setzero_ps( );

	for ( int i = 0; i < nLoop; i += 4 )
	{
		XMMCurrentValue = _mm_loadu_ps( pFloatA + i );
		XMMSumValue = _mm_add_ps( XMMSumValue, XMMCurrentValue );
	}

	for ( int i = 0; i < 4; ++i )
	{
		sum += *( (float*)( &XMMSumValue ) + i );
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		sum += pData[i];
	}

	return sum;
}

float GetSumFloatAVX( float* pData, int size )
{
	int nRemain = size % 8;
	int nLoop = size - nRemain;

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

	for ( int i = size - nRemain; i < size; ++i )
	{
		sum += pData[i];
	}

	return sum;
}

int main( )
{
	constexpr int SIZE = 260000;
	float* FloatDataArray = new float[SIZE];

	float FloatSum = 0;
	int IntergerSum = 0;

	for ( int i = 0; i < SIZE; ++i )
	{
		FloatDataArray[i] = 1.f;
		IntergerSum += 1;
	}

	std::cout << "Integer Sum Result : " << IntergerSum << std::endl;

	CStopWatch StopWatch;
	StopWatch.Start( );
	float CResult = GetSumFloatC( FloatDataArray, SIZE );
	StopWatch.End( );

	std::cout << "C Sum Result : " << CResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	float SSEResult = GetSumFloatSSE( FloatDataArray, SIZE );
	StopWatch.End( );

	std::cout << "SSE Sum Result : " << SSEResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	float AVXResult = GetSumFloatAVX( FloatDataArray, SIZE );
	StopWatch.End( );

	std::cout << "AVX Sum Result : " << AVXResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	delete[] FloatDataArray;

	return 0;
}