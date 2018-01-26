#include "../Util/StopWatch.h"

#include <iostream>

int FindValueCountC( const int* pIntArray, const int nFindValue, const int nSize )
{
	int nFindCount = 0;

	for ( int i = 0; i < nSize; ++i )
	{
		if ( pIntArray[i] == nFindValue )
		{
			++nFindCount;
		}
	}

	return nFindCount;
}

// 아래 코드는 4개의 pack중 2개 이상이 같은 값을 가지면 오동작 한다.
// 몇가지 명령어를 더 알아보고 FindInt2 버전을 만들어 이 문제를 해결한다.
int FindValueCountSIMD( const int* pIntArray, const int nFindValue, const int nSize )
{
	const int* pInt = pIntArray;
	int nLoopCount = static_cast<int>( nSize * 0.25 ) * 16;
	int nRemain = nSize % 4;
	int pFindMask[4] = { nFindValue, nFindValue, nFindValue, nFindValue };
	int nFindCount = 0;

	__asm
	{
		pushad
		mov eax, pInt		// pInt
		mov ebx, 0			// middle result
		mov ecx, 0			// count
		mov edx, nLoopCount // loop
		mov esi, 0			// index

		movdqu xmm1, pFindMask

		COUNT:
		movdqu xmm0, [eax + esi]

		pcmpeqd xmm0, xmm1
		pmovmskb ebx, xmm0
		cmp ebx, 0
		je NOTCOUNT
		{
			pextrd ebx, xmm0, 0
			cmp ebx, 0
			je NOTCOUNT0
			inc ecx
		NOTCOUNT0:
			pextrd ebx, xmm0, 1
			cmp ebx, 0
			je NOTCOUNT1
			inc ecx
		NOTCOUNT1:
			pextrd ebx, xmm0, 2
			cmp ebx, 0
			je NOTCOUNT2
			inc ecx
		NOTCOUNT2:
			pextrd ebx, xmm0, 3
			cmp ebx, 0
			je NOTCOUNT
			inc ecx
		}
		NOTCOUNT:
		add esi, 16
		cmp esi, edx
		jnz COUNT

		mov nFindCount, ecx
		popad
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		if ( pIntArray[i] == nFindValue )
		{
			++nFindCount;
		}
	}

	return nFindCount;
}

int main( )
{
	CStopWatch StopWatch;
	const int MAX_SIZE = 10000000;

	int* pIntArray = new int[MAX_SIZE];
	memset( pIntArray, 0, MAX_SIZE * sizeof( short ) );

	for ( int i = 0; i < 10; ++i )
	{
		pIntArray[i] = 100;
	}

	int nResult = 0;

	StopWatch.Start( );
	nResult = FindValueCountC( pIntArray, 100, MAX_SIZE );
	StopWatch.End( );

	std::cout << "C Find Count : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	nResult = FindValueCountSIMD( pIntArray, 100, MAX_SIZE );
	StopWatch.End( );

	std::cout << "SIMD Find Count : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	delete[] pIntArray;

	return 0;
}