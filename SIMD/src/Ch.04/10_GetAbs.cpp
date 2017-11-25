#include "../Util/StopWatch.h"

#include <emmintrin.h>
#include <iostream>

void ABSC( short* pSrc, int nSize )
{
	for ( int i = 0; i < nSize; ++i )
	{
		if ( pSrc[i] < 0 )					// 0 보다 작으면 -1 곱하여 양수로 변환
		{
			pSrc[i] *= -1;
		}
	}
}

void ABSIntrinsic( short* pSrc, int nSize )
{
	int nRemain = nSize % 8;

	__m128i XMMCurrentValue;
	__m128i XMMZeroValue;

	for ( int i = 0; i < nSize; i += 8 )
	{
		XMMZeroValue = _mm_setzero_si128( );
		XMMCurrentValue = _mm_loadu_si128( reinterpret_cast<__m128i*>( pSrc + i ) );

		// ZeroValue = 0 - CurrentValue, 양수는 음수 변환, 음수는 양수 변환
		XMMZeroValue = _mm_sub_epi16( XMMZeroValue, XMMCurrentValue );

		// 두 값을 비교하여 큰 값을 가져온다.
		XMMZeroValue = _mm_max_epi16( XMMZeroValue, XMMCurrentValue );

		_mm_storeu_si128( reinterpret_cast<__m128i*>( pSrc + i ), XMMZeroValue );
	}

	for ( int i = nSize - nRemain; i < nSize; ++i )
	{
		if ( pSrc[i] < 0 )					// 0 보다 작으면 -1 곱하여 양수로 변환
		{
			pSrc[i] *= -1;
		}
	}
}

int main( )
{
	constexpr int MAXSIZE = 10000;

	short Array[MAXSIZE] = { 0 };

	int i = 0;

	// 홀수는 음수, 짝수는 양수로 세팅
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
		std::cout << Array[i] << ' ';
	}
	std::cout << std::endl;

	StopWatch.Start( );
	ABSC( Array, MAXSIZE );
	StopWatch.End( );

	std::cout << "Result Data : ";
	for ( int i = 0; i < 8; ++i )
	{
		std::cout << Array[i] << ' ';
	}
	std::cout << "C Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	// 홀수는 음수, 짝수는 양수로 세팅
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
	ABSIntrinsic( Array, MAXSIZE );
	StopWatch.End( );

	std::cout << "Result Data : ";
	for ( int i = 0; i < 8; ++i )
	{
		std::cout << Array[i] << ' ';
	}
	std::cout << "intrinsic Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	return 0;
}