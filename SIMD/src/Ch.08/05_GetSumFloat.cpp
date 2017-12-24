#include <fvec.h>
#include <iostream>

#include "../Util/StopWatch.h"

float GetSumFloatC( float* array, int size )
{
	float result = 0;

	for ( int i = 0; i < size; ++i )
	{
		result += array[i];
	}

	return result;
}

float GetSumFloatVector( F32vec4* array, int size )
{
	float result = 0;
	F32vec4 vec0, vec1;

	int loopSize = size / 4;
	int remain = size % 4;

	vec0 = _mm_setzero_ps( );

	for ( int i = 0; i < loopSize; ++i )
	{
		vec0 += array[i];
	}

	vec1 = _mm_shuffle_ps( vec0, vec0, 0x0E );
	vec0 += vec1;
	vec1 = _mm_shuffle_ps( vec0, vec0, 0x01 );
	vec0 += vec1;
	_mm_store_ss( &result, vec0 );

	/* 책에 있던 방식의 코드
	vec0 = _mm_load_ps( (float*)array );

	for ( int i = 0; i < loopSize; ++i )
	{
		vec0 += array[i];
	}

	vec1 = _mm_shuffle_ps( vec1, vec0, 0x40 );
	vec0 += vec1;
	vec1 = _mm_shuffle_ps( vec1, vec0, 0x30 );
	vec0 += vec1;
	vec0 = _mm_shuffle_ps( vec0, vec0, 2 );
	_mm_store_ss( &result, vec0 );*/

	for ( int i = size - remain; i < size; ++i )
	{
		result += reinterpret_cast<float*>(array)[i];
	}

	return result;
}

int main( )
{
	constexpr int SIZE = 5000;

	alignas( 16 ) float FloatDataArray[SIZE];

	float FloatSum = 0;

	int IntergerSum = 0;

	for ( int i = 0; i < SIZE; ++i )
	{
		FloatDataArray[i] = static_cast<float>( i );
		IntergerSum += i;
	}

	CStopWatch StopWatch;
	StopWatch.Start( );
	float SIMDResult = GetSumFloatVector( reinterpret_cast<F32vec4*>( FloatDataArray ), SIZE );
	StopWatch.End( );

	std::cout << "Vector Sum Result : " << SIMDResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>() << std::endl;

	StopWatch.Start( );
	float CResult = GetSumFloatC( FloatDataArray, SIZE );
	StopWatch.End( );

	std::cout << "C Float Sum Result : " << CResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}