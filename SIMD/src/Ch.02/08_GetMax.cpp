#include "../Util/StopWatch.h"

#include <iostream>

short GetMaxValueC( const short* pShortArray, const int nSize )
{
	short MaxValue = 0;
	for ( int i = 0; i < nSize; ++i )
	{
		if ( pShortArray[i] > MaxValue )
		{
			MaxValue = pShortArray[i];
		}
	}

	return MaxValue;
}

short GetMaxValueSIMD( const short* pShortArray, const int nSize )
{
	const short* pShort = pShortArray;

	int nLoopCount = static_cast<int>( nSize * 0.125 ) * 16;
	int nRemain = nSize % 8;

	short nMaxValue = 0;

	short MaxValueArray[8] = { 0 };

	__asm
	{
		pushad
		mov eax, pShort
		mov ecx, nLoopCount
		mov esi, 0
		
		movdqu xmm1, [eax+esi]
		pxor xmm0, xmm0
		
		MAXLP:
		pmaxsw xmm0, xmm1
		add esi, 16
		cmp ecx, esi
		jnz MAXLP

		movdqu MaxValueArray, xmm0

		popad
	}

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
			nMaxValue = pShortArray[i];
		}
	}

	return nMaxValue;
}

int main( )
{
	CStopWatch StopWatch;
	const int MAX_SIZE = 100000000;

	short* pShortArray = new short[MAX_SIZE];
	memset( pShortArray, 0, MAX_SIZE * sizeof( short ) );

	pShortArray[9000003] = 100;
	pShortArray[0] = 101;

	int nResult = 0;

	StopWatch.Start( );
	nResult = GetMaxValueC( pShortArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "C Get Value : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	nResult = GetMaxValueSIMD( pShortArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "SIMD Get Value : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	delete[] pShortArray;
	
	return 0;
}