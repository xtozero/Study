#include <emmintrin.h>
#include <iostream>

#include "../Util/StopWatch.h"

void SelectC( float* pSrc, float CmpValue, int nSize )
{
	for ( int i = 0; i < nSize; ++i )
	{
		if ( pSrc[i] < CmpValue )
		{
			pSrc[i] = 0.f;
		}
	}
}

void SelectIntrinsic( float* pSrc, float CmpValue, int nSize )
{
	int nRemain = nSize % 8;

	__m128 XMMCurrentValue;
	__m128 XMMCmpValue = _mm_set1_ps( CmpValue );
	__m128 XMMCmpResult;

	for ( int i = 0; i < nSize; i += 4 )
	{
		XMMCurrentValue = _mm_loadu_ps( pSrc + i );

		XMMCmpResult = _mm_cmpgt_ps( XMMCurrentValue, XMMCmpValue );

		XMMCurrentValue = _mm_and_ps( XMMCurrentValue, XMMCmpResult );

		_mm_storeu_ps( pSrc + i, XMMCurrentValue );
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		if ( pSrc[i] < CmpValue )
		{
			pSrc[i] = 0.f;
		}
	}
}

int main( )
{
	constexpr int MAXSIZE = 10000;

	float Array[MAXSIZE] = { 0 };

	for ( int i = 0; i < MAXSIZE; ++i )
	{
		if ( i % 2 == 0 )
		{
			Array[i] = i;
		}
		else
		{
			Array[i] = -1.f * i;
		}
	}

	CStopWatch StopWatch;

	std::cout << "Source Data : ";
	for ( int i = 0; i < 8; ++i )
	{
		std::cout << Array[i] << " ";
	}
	std::cout << std::endl;

	StopWatch.Start( );
	SelectC( Array, 0, MAXSIZE );
	StopWatch.End( );

	std::cout << "Result Data : ";
	for ( int i = 0; i < 8; ++i )
	{
		std::cout << Array[i] << " ";
	}
	std::cout << " C TIme : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	for ( int i = 0; i < MAXSIZE; ++i )
	{
		if ( i % 2 == 0 )
		{
			Array[i] = i;
		}
		else
		{
			Array[i] = -1.f * i;
		}
	}

	StopWatch.Start( );
	SelectIntrinsic( Array, 0, MAXSIZE );
	StopWatch.End( );

	std::cout << "Result Data : ";
	for ( int i = 0; i < 8; ++i )
	{
		std::cout << Array[i] << " ";
	}
	std::cout << " intrinsic TIme : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}