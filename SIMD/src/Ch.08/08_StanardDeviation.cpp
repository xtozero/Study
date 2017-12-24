#include <fvec.h>
#include <iostream>

#include "../Util/StopWatch.h"

float GetStdevVector( float* Array, int Size )
{
	int LoopSize = ( Size / 4 ) * 4;

	float Sum = 0;

	F32vec4 xmmSum( 0.f );
	F32vec4 xmmCur( 0.f );
	F32vec4 xmmResult( 0.f );

	for ( int i = 0; i < LoopSize; i += 4 )
	{
		loadu( xmmCur, Array + i );
		xmmSum += xmmCur;
	}

	xmmResult = _mm_shuffle_ps( xmmSum, xmmResult, 0b00001110 );
	xmmSum += xmmResult;
	xmmResult = _mm_shuffle_ps( xmmSum, xmmResult, 0b00000001 );
	xmmSum += xmmResult;
	_mm_store_ss( &Sum, xmmSum );

	for ( int i = LoopSize; i < Size; ++i )
	{
		Sum += Array[i];
	}

	float Average = Sum / Size;

	F32vec4 xmmAVG( Average );

	F32vec4 xmmDistribution( 0.f );
	F32vec4 xmmSumDist( 0.f );

	for ( int i = 0; i < LoopSize; i += 4 )
	{
		loadu( xmmCur, Array + i );
		xmmDistribution = xmmCur - xmmAVG;
		xmmDistribution *= xmmDistribution;

		xmmSumDist += xmmDistribution;
	}

	xmmResult = F32vec4( 0.f );
	xmmResult = _mm_shuffle_ps( xmmSumDist, xmmResult, 0b00001110 );
	xmmSumDist += xmmResult;
	xmmResult = _mm_shuffle_ps( xmmSumDist, xmmResult, 0b00000001 );
	xmmSumDist += xmmResult;
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
	Result = GetStdevVector( Array, ARRAYSIZE );
	StopWatch.End( );

	std::cout << "Vector Stdev Result : " << Result << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}