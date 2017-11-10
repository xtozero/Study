#include <iostream>
#include <utility>

#include "../Util/StopWatch.h"

// FIndPosition.cpp에서 pextrw 명령어에 상수만 사용할 수 있는 문제로 인한 긴 코드의 나열을 쉬프트 명령을 사용해서 간결하게 작성하였다. 

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
		mov edx, -1
		mov esi, 0

		FINDLP:
		movdqu xmm1, [eax + esi]
		pcmpeqw xmm1, xmm0
		pmovmskb ebx, xmm1

		cmp ebx, 0
		je NOTFOUND
		{
			FINDNEXT:
			inc edx
			pextrw ebx, xmm1, 0
			psrldq xmm1, 2
			cmp ebx, 0
			je FINDNEXT
			jne FINDEND
		}

		NOTFOUND:
		add esi, 16
		cmp esi, ecx
		jne FINDLP
		FINDEND :
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