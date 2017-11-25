#include <emmintrin.h>
#include <iostream>

#include "../Util/StopWatch.h"

void SelectC( short* pSrc, short CmpValue, int nSize )
{
	for ( int i = 0; i < nSize; ++i )
	{
		if ( pSrc[i] < CmpValue )
		{
			pSrc[i] = 0;
		}
	}
}

void SelectIntrinsic( short* pSrc, short CmpValue, int nSize )
{
	int nRemain = nSize % 8;

	__m128i XMMCurrentValue;
	__m128i XMMCmpValue = _mm_set1_epi16( CmpValue );
	__m128i XMMCmpResult;

	for ( int i = 0; i < nSize; i += 8 )
	{
		XMMCurrentValue = _mm_loadu_si128( reinterpret_cast<__m128i*>( pSrc + i ) );
		
		XMMCmpResult = _mm_cmpgt_epi16( XMMCurrentValue, XMMCmpValue );

		XMMCurrentValue = _mm_and_si128( XMMCurrentValue, XMMCmpResult );

		_mm_storeu_si128( reinterpret_cast<__m128i*>( pSrc + i ), XMMCurrentValue );
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		if ( pSrc[i] < CmpValue )
		{
			pSrc[i] = 0;
		}
	}
}

int main( )
{
	constexpr int MAXSIZE = 10000;

	short Array[MAXSIZE] = { 0 };

	for ( int i = 0; i < MAXSIZE; ++i )
	{
		if ( i % 2 == 0 )
		{
			Array[i] = i;
		}
		else
		{
			Array[i] = -1 * i;
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
			Array[i] = -1 * i;
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
	std::cout << " intrinsic TIme : " << StopWatch.GetDuration<duration<float, std::milli>>() << std::endl;

	return 0;
}