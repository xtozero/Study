#include "../Util/StopWatch.h"

#include <emmintrin.h>
#include <iostream>

double FactorialC( int input )
{
	double Result = 1;
	for ( int i = 1; i <= input; ++i )
	{
		Result *= i;
	}
	return Result;
}

double FactorialIntrinsic( int input )
{
	alignas( 16 ) double Result[2] = { 0 };
	__m128d SumValue = _mm_set1_pd( 1 );
	int LoopLimit = static_cast<int>( input / 2 ) * 2;

	for ( int i = 1; i <= LoopLimit; i += 2 )
	{
		SumValue = _mm_mul_pd( _mm_set_pd( i, i + 1 ), SumValue );
	}

	_mm_store_pd( Result, SumValue );

	if ( input % 2 != 0 )
	{
		Result[0] *= input;
	}

	return Result[0] * Result[1];
}

int main( )
{
	CStopWatch StopWatch;
	
	int input = 51;
	double R = 0;

	StopWatch.Start( );
	R = FactorialC( input );
	StopWatch.End( );

	std::cout << "Result : " << R << ", C Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	R = FactorialIntrinsic( input );
	StopWatch.End( );

	std::cout << "Result : " << R << ", Intrinsic Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}