#include <dvec.h>
#include <iostream>

#include "../Util/StopWatch.h"

short GetMaxValueVector( const short* pShortArray, const int nSize )
{
	const short* pShort = pShortArray;

	int nRemain = nSize % 8;

	short nMaxValue = 0;

	short MaxValueArray[8] = { 0 };

	Is16vec8* XMMCurrentValue;
	Is16vec8 XMMMaxValue;

	for ( int i = 0; i < nSize; i += 8 )
	{
		XMMCurrentValue = (Is16vec8*)( pShortArray + i );
		XMMMaxValue = simd_max( XMMMaxValue, *XMMCurrentValue );
	}

	_mm_storeu_si128( reinterpret_cast<__m128i*>( MaxValueArray ), XMMMaxValue );

	for ( int i = 0; i < 8; ++i )
	{
		if ( nMaxValue < MaxValueArray[i] )
		{
			nMaxValue = MaxValueArray[i];
		}
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		if ( nMaxValue < pShortArray[i] )
		{
			nMaxValue = pShort[i];
		}
	}

	return nMaxValue;
}

int main( )
{
	CStopWatch StopWatch;
	constexpr int MAX_SIZE = 100000002;

	short* pShortArray = new short[MAX_SIZE];

	for ( int i = 0; i < MAX_SIZE; ++i )
	{
		pShortArray[i] = i % 10000;
	}

	int nResult = 0;

	StopWatch.Start( );
	nResult = GetMaxValueVector( pShortArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "Vector Get Value : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}