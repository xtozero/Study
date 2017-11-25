#include "../Util/StopWatch.h"

#include <emmintrin.h>
#include <iostream>

int GetSumValueC( const int* pIntArray, const int nSize )
{
	int SumValue = 0;
	for ( int i = 0; i < nSize; ++i )
	{
		SumValue += pIntArray[i];
	}
	return SumValue;
}

int GetSumValueSIMD( const int* pIntArray, const int nSize )
{
	const int* pInt = pIntArray; // 함수 안에서 __asm을 사용할 때 포인터는 스택 변수로 변환시켜야 한다.
	int nLoopCount = static_cast<int>( nSize * 0.25 ) * 16; // 한번에 4개씩 연산하므로 4로 나누고 16byte씩 포인트 이동을 하므로 16을 곱한다.
	int nRemain = nSize % 4;
	int nSumValue = 0; // 결과값
	int SumValueArray[4] = { 0 }; // 중간 결과값

	__asm
	{
		pushad
		mov eax, pInt
		mov esi, 0
		mov ecx, nLoopCount

		pxor xmm0, xmm0	// 0으로 초기화

		SUMLP :
		movdqu xmm1, [eax + esi]
			paddd xmm0, xmm1
			add esi, 16
			cmp ecx, esi
			jnz SUMLP

			movdqu SumValueArray, xmm0

			popad
	}

	for ( int elem : SumValueArray )
	{
		nSumValue += elem;
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		nSumValue += pInt[i];
	}

	return nSumValue;
}

int GetSumValueIntrinsics( const int* pIntArray, const int nSize )
{
	int nRemain = nSize % 4;
	int nLoop = nSize - nRemain;

	int nSumValue = 0;
	int ResultArray[4] = { 0 };

	__m128i XMMCurrentValue;
	__m128i XMMSumValue = _mm_setzero_si128( );

	for ( int i = 0; i < nLoop; i += 4 )
	{
		XMMCurrentValue = _mm_loadu_si128( reinterpret_cast<const __m128i*>( pIntArray + i ) );

		XMMSumValue = _mm_add_epi32( XMMSumValue, XMMCurrentValue );
	}

	_mm_storeu_si128( reinterpret_cast<__m128i*>( ResultArray ), XMMSumValue );

	for ( int i = 0; i < 4; ++i )
	{
		nSumValue += ResultArray[i];
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		nSumValue += pIntArray[i];
	}

	return nSumValue;
}

int main( )
{
	CStopWatch StopWatch;
	constexpr int MAX_SIZE = 100000003;

	int* pIntArray = new int[MAX_SIZE];
	memset( pIntArray, 0, MAX_SIZE * sizeof( int ) );

	for ( int i = 0; i < MAX_SIZE; ++i )
	{
		pIntArray[i] = 1;
	}

	int nResult = 0;

	StopWatch.Start( );
	nResult = GetSumValueC( pIntArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "C Get Value : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	nResult = GetSumValueSIMD( pIntArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "SIMD Get Value : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	nResult = GetSumValueIntrinsics( pIntArray, MAX_SIZE );
	StopWatch.End( );

	std::cout << "Intrinsics Get Value : " << nResult << ", Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	delete[] pIntArray;

	return 0;
}