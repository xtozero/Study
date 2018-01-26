#include "../Util/StopWatch.h"

#include <emmintrin.h>
#include <iostream>

float GetStdev( float* Array, int Size )
{
	float Sum = 0;

	for ( int i = 0; i < Size; ++i )
	{
		Sum += Array[i];
	}

	float Average = Sum / Size;

	float DistValue = 0;
	float SumDist = 0;

	for ( int i = 0; i < Size; ++i )
	{
		DistValue = Average - Array[i];
		SumDist += DistValue * DistValue;
	}

	return sqrt( SumDist / Size );
}

float GetStdevIntrinsic( float* Array, int Size )
{
	int LoopSize = ( Size / 4 ) * 4;

	float Sum = 0;

	__m128 xmmSum = _mm_setzero_ps( );
	__m128 xmmCur = _mm_setzero_ps( );
	__m128 xmmResult = _mm_setzero_ps( );

	for ( int i = 0; i < LoopSize; i += 4 )
	{
		xmmCur = _mm_loadu_ps( Array + i );
		xmmSum = _mm_add_ps( xmmSum, xmmCur );
	}

	xmmResult = _mm_shuffle_ps( xmmResult, xmmSum, 0b10000000 );
	xmmSum = _mm_add_ps( xmmSum, xmmResult );
	xmmResult = _mm_shuffle_ps( xmmResult, xmmSum, 0b10000000 );
	xmmSum = _mm_add_ps( xmmSum, xmmResult );
	xmmSum = _mm_shuffle_ps( xmmSum, xmmSum, 0b00000011 );
	_mm_store_ss( &Sum, xmmSum );

	for ( int i = LoopSize; i < Size; ++i )
	{
		Sum += Array[i];
	}

	float Average = Sum / Size;

	__m128 xmmAVG = _mm_set1_ps( Average );

	__m128 xmmDistribution = _mm_setzero_ps( );
	__m128 xmmSumDist = _mm_setzero_ps( );

	for ( int i = 0; i < LoopSize; i += 4 )
	{
		xmmCur = _mm_loadu_ps( Array + i );
		xmmDistribution = _mm_sub_ps( xmmCur, xmmAVG );
		xmmDistribution = _mm_mul_ps( xmmDistribution, xmmDistribution );

		xmmSumDist = _mm_add_ps( xmmSumDist, xmmDistribution );
	}

	xmmResult = _mm_setzero_ps( );
	xmmResult = _mm_shuffle_ps( xmmResult, xmmSumDist, 0b10000000 );
	xmmSumDist = _mm_add_ps( xmmSumDist, xmmResult );
	xmmResult = _mm_shuffle_ps( xmmResult, xmmSumDist, 0b10000000 );
	xmmSumDist = _mm_add_ps( xmmSumDist, xmmResult );
	xmmSumDist = _mm_shuffle_ps( xmmSumDist, xmmSumDist, 0b00000011 );
	_mm_store_ss( &Sum, xmmSumDist );

	for ( int i = LoopSize; i < Size; ++i )
	{
		Sum += ( Average - Array[i] ) * ( Average - Array[i] );
	}

	return sqrt( Sum / Size );
}

int main( )
{
	CStopWatch StopWatch;

	constexpr int ARRAYSIZE = 10003;
	float Array[ARRAYSIZE] = { 0 };

	for ( int i = 0; i < ARRAYSIZE; ++i )
	{
		Array[i] = i;
	}

	float Result = 0;

	StopWatch.Start( );
	Result = GetStdev( Array, ARRAYSIZE );
	StopWatch.End( );

	std::cout << "C Stdev Result : " << Result << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	Result = GetStdevIntrinsic( Array, ARRAYSIZE );
	StopWatch.End( );

	std::cout << "Intrinsic Stdev Result : " << Result << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}