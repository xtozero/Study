#include <iostream>

#include "../Util/StopWatch.h"

__int64 GetSumValueC( const int* pIntArray, const int nSize )
{
	__int64 SumValue = 0;
	for ( int i = 0; i < nSize; ++i )
	{
		SumValue += pIntArray[i];
	}

	return SumValue;
}

__int64 GetSumValueSIMD( const int* pIntArray, const int nSize )
{
	const int* pInt = pIntArray;
	int nLoopCount = static_cast<int>( nSize * 0.25 ) * 16;
	int nRemain = nSize % 4;

	__int64 nSumValue = 0;
	
	__int64 SumValueArray[2] = { 0 };
	int fordebug[4] = { 0 };

	__asm
	{
		pushad
		mov eax, pIntArray
		mov esi, 0
		mov ecx, nLoopCount
		pxor xmm6, xmm6		// pack 확장시 사용할 temp 항상 0으로 둔다.
		pxor xmm7, xmm7

		SUMLP:
		movdqu xmm0, [eax+esi]
		movdqu xmm1, xmm0

		punpckhdq xmm1, xmm6
		paddq xmm7, xmm1

		punpckldq xmm0, xmm6
		paddq xmm7, xmm0

		add esi, 16
		cmp ecx, esi
		jne SUMLP

		movdqu SumValueArray, xmm7

		popad
	}

	for ( const __int64 elem : SumValueArray )
	{
		nSumValue += elem;
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		nSumValue += pInt[i];
	}

	return nSumValue;
}

int main( )
{
	CStopWatch StopWatch;
	constexpr int MAX_SIZE = 10000000;

	int* pIntArray = new int[MAX_SIZE];
	memset( pIntArray, 0, MAX_SIZE * sizeof( int ) );

	for ( int i = 0; i < MAX_SIZE; ++i )
	{
		pIntArray[i] = 1;
	}

	__int64 nResultC = 0;

	StopWatch.Start( );
	nResultC = GetSumValueC( pIntArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "C Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	__int64 nResultSIMD = 0;

	StopWatch.Start( );
	nResultSIMD = GetSumValueSIMD( pIntArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "SIMD Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	if ( nResultC == nResultSIMD )
	{
		std::cout << "Result OK" << std::endl;
	}

	delete[] pIntArray;

	return 0;
}