#include <iostream>
#include <utility>

#include "../Util/StopWatch.h"

int FindPositionC( const short* pShortArray, const short nFindValue, const int nSize )
{
	for ( int i = 0; i < nSize; ++i )
	{
		if ( pShortArray[i] == nFindValue )
		{
			return i;
		}
	}

	return nSize;
}

int FindPositionSTL( const short* pShortArray, const short nFindValue, const int nSize )
{
	const short* pPosition = std::find( pShortArray, pShortArray + nSize, nFindValue );
	return pPosition - pShortArray;
}

int FindPositionSIMD( const short* pShortArray, const short nFindValue, const int nSize )
{
	const short* pShort = pShortArray;
	int nLoopCount = static_cast<int>( nSize * 0.125 ) * 16;
	int nRemain = nSize % 8;

	short pFIndMask[8] = { nFindValue, nFindValue, nFindValue, nFindValue, nFindValue, nFindValue, nFindValue, nFindValue };

	int nFindCount = 0;
	int nPosition = nSize;

	__asm
	{
		pushad
		movdqu xmm0, pFIndMask

		mov eax, pShort
		mov ecx, nLoopCount
		mov esi, 0

		FINDLP:
		movdqu xmm1, [eax+esi]
		pcmpeqw xmm1, xmm0 
		pmovmskb ebx, xmm1

		cmp ebx, 0
		je NOTFOUND
		{
			pextrw ebx, xmm1, 0
			cmp ebx, 0
			je NOTFOUND0
			mov edx, 0
			jp FINDEND
		NOTFOUND0:
			pextrw ebx, xmm1, 1
			cmp ebx, 0
			je NOTFOUND1
			mov edx, 1
			jp FINDEND
		NOTFOUND1:
			pextrw ebx, xmm1, 2
			cmp ebx, 0
			je NOTFOUND2
			mov edx, 2
			jp FINDEND
		NOTFOUND2:
			pextrw ebx, xmm1, 3
			cmp ebx, 0
			je NOTFOUND3
			mov edx, 3
			jp FINDEND
		NOTFOUND3:
			pextrw ebx, xmm1, 4
			cmp ebx, 0
			je NOTFOUND4
			mov edx, 4
			jp FINDEND
		NOTFOUND4:
			pextrw ebx, xmm1, 5
			cmp ebx, 0
			je NOTFOUND5
			mov edx, 5
			jp FINDEND
		NOTFOUND5:
			pextrw ebx, xmm1, 6
			cmp ebx, 0
			je NOTFOUND6
			mov edx, 6
			jp FINDEND
		NOTFOUND6:
			pextrw ebx, xmm1, 7
			cmp ebx, 0
			je NOTFOUND
			mov edx, 7
			jp FINDEND
		}

		NOTFOUND:
		add esi, 16
		cmp esi, ecx
		jne FINDLP
		FINDEND:
		mov eax, esi
		shr eax, 1
		add eax, edx
		mov nPosition, eax

		popad
	}

	if ( nPosition == nSize )
	{
		for ( int i = nSize - nRemain; i < nSize; ++i )
		{
			if ( pShortArray[i] == nFindValue )
			{
				return i;
			}
		}
	}

	return nPosition;
}

int main( )
{
	CStopWatch StopWatch;
	const int MAX_SIZE = 100000000;

	short* pShortArray = new short[MAX_SIZE];
	memset( pShortArray, 0, MAX_SIZE * sizeof( short ) );

	pShortArray[9000004] = 100;

	int nResult = 0;

	// C ver
	StopWatch.Start( );
	nResult = FindPositionC( pShortArray, 100, MAX_SIZE );
	StopWatch.End( );

	std::cout << "C Find Count : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	// STL ver
	StopWatch.Start( );
	nResult = FindPositionSTL( pShortArray, 100, MAX_SIZE );
	StopWatch.End( );

	std::cout << "STL Find Count : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	// SIMD ver
	StopWatch.Start( );
	nResult = FindPositionSIMD( pShortArray, 100, MAX_SIZE );
	StopWatch.End( );

	std::cout << "SIMD Find Count : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	delete[] pShortArray;
	return 0;
}