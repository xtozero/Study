#include <emmintrin.h>
#include <iostream>

#include "../Util/StopWatch.h"

void Matrix4x4Intrinsic( float* MatrixA, float* MatrixB, float* MatrixDest )
{
	int indexA = 0;
	int indexB = 0;

	__m128 xmmB[4];

	/*
	__m128 의 구조 정의는 다음과 같이 되어 있다.

	typedef union __declspec(intrin_type) __declspec(align(16)) __m128 {
	float               m128_f32[4];
	unsigned __int64    m128_u64[2];
	__int8              m128_i8[16];
	__int16             m128_i16[8];
	__int32             m128_i32[4];
	__int64             m128_i64[2];
	unsigned __int8     m128_u8[16];
	unsigned __int16    m128_u16[8];
	unsigned __int32    m128_u32[4];
	} __m128;

	아래 for문을 해석하면 다음과 같은 코드가 되어 불필요한 복사가 일어난다.

	m128_f32[4][4] := MatrixB;
	*/
	for ( int i = 0; i < 4; ++i )
	{
		xmmB[i] = _mm_loadu_ps( MatrixB + i * 4 );
	}

	__m128 xmmR;

	for ( int i = 0; i < 4; ++i )
	{
		indexB = 0;

		xmmR = _mm_add_ps( _mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), xmmB[indexB++] ),
				_mm_add_ps( _mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), xmmB[indexB++] ),
				_mm_add_ps( _mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), xmmB[indexB++] ),
				_mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), xmmB[indexB++] ) ) ) );

		_mm_store_ps( MatrixDest + i * 4, xmmR );
	}
}

// 불필요한 복사를 방지하기 위해 __m128 형을 인자로 입력 받도록 한다.
void Matrix4x4Intrinsic2( float* MatrixA, __m128* MatrixB, float* MatrixDest )
{
	int indexA = 0;
	int indexB = 0;

	__m128 xmmR;

	for ( int i = 0; i < 4; ++i )
	{
		indexB = 0;

		xmmR = _mm_add_ps( _mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), MatrixB[indexB++] ),
				_mm_add_ps( _mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), MatrixB[indexB++] ),
				_mm_add_ps( _mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), MatrixB[indexB++] ),
				_mm_mul_ps( _mm_set1_ps( MatrixA[indexA++] ), MatrixB[indexB++] ) ) ) );

		_mm_store_ps( MatrixDest + i * 4, xmmR );
	}
}

int main( )
{
	float MatrixA[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	float MatrixB[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	float MatrixDest[16] = { 0 };

	CStopWatch StopWatch;
	int i = 0;

	StopWatch.Start( );
	for ( int i = 0; i < 10000; ++i )
	{
		Matrix4x4Intrinsic( MatrixA, MatrixB, MatrixDest );
	}
	StopWatch.End( );
	std::cout << "4x4 Intrinsic SIMD Result Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;
	for ( int i = 0; i < 16; ++i )
	{
		std::cout << MatrixDest[i] << ' ';
		if ( i % 4 == 3 )
		{
			std::cout << std::endl;
		}
	}

	StopWatch.Start( );
	for ( int i = 0; i < 10000; ++i )
	{
		Matrix4x4Intrinsic2( MatrixA, reinterpret_cast<__m128*>( MatrixB ), MatrixDest );
	}
	StopWatch.End( );
	std::cout << "4x4 Intrinsic2 SIMD Result Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;
	for ( int i = 0; i < 16; ++i )
	{
		std::cout << MatrixDest[i] << ' ';
		if ( i % 4 == 3 )
		{
			std::cout << std::endl;
		}
	}
}