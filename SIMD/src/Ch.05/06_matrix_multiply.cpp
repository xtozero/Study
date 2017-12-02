#include <emmintrin.h>
#include <iostream>

#include "../Util/StopWatch.h"

void Matrix4x4Intrinsic( float* MatrixA, float* MatrixB, float* MatrixDest )
{
	int indexA = 0;
	int indexB = 0;

	__m128 xmmB[4];

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

void MatrixMul4x4C( float* MatrixA, float* MatrixB, float* MatrixDest )
{
	MatrixDest[0] = MatrixA[0] * MatrixB[0] + MatrixA[1] * MatrixB[4] + MatrixA[2] * MatrixB[8] + MatrixA[3] * MatrixB[12];
	MatrixDest[1] = MatrixA[0] * MatrixB[1] + MatrixA[1] * MatrixB[5] + MatrixA[2] * MatrixB[9] + MatrixA[3] * MatrixB[13];
	MatrixDest[2] = MatrixA[0] * MatrixB[2] + MatrixA[1] * MatrixB[6] + MatrixA[2] * MatrixB[10] + MatrixA[3] * MatrixB[14];
	MatrixDest[3] = MatrixA[0] * MatrixB[3] + MatrixA[1] * MatrixB[7] + MatrixA[2] * MatrixB[11] + MatrixA[3] * MatrixB[15];
	MatrixDest[4] = MatrixA[4] * MatrixB[0] + MatrixA[5] * MatrixB[4] + MatrixA[6] * MatrixB[8] + MatrixA[7] * MatrixB[12];
	MatrixDest[5] = MatrixA[4] * MatrixB[1] + MatrixA[5] * MatrixB[5] + MatrixA[6] * MatrixB[9] + MatrixA[7] * MatrixB[13];
	MatrixDest[6] = MatrixA[4] * MatrixB[2] + MatrixA[5] * MatrixB[6] + MatrixA[6] * MatrixB[10] + MatrixA[7] * MatrixB[14];
	MatrixDest[7] = MatrixA[4] * MatrixB[3] + MatrixA[5] * MatrixB[7] + MatrixA[6] * MatrixB[11] + MatrixA[7] * MatrixB[15];
	MatrixDest[8] = MatrixA[8] * MatrixB[0] + MatrixA[9] * MatrixB[4] + MatrixA[10] * MatrixB[8] + MatrixA[11] * MatrixB[12];
	MatrixDest[9] = MatrixA[8] * MatrixB[1] + MatrixA[9] * MatrixB[5] + MatrixA[10] * MatrixB[9] + MatrixA[11] * MatrixB[13];
	MatrixDest[10] = MatrixA[8] * MatrixB[2] + MatrixA[9] * MatrixB[6] + MatrixA[10] * MatrixB[10] + MatrixA[11] * MatrixB[14];
	MatrixDest[11] = MatrixA[8] * MatrixB[3] + MatrixA[9] * MatrixB[7] + MatrixA[10] * MatrixB[11] + MatrixA[11] * MatrixB[15];
	MatrixDest[12] = MatrixA[12] * MatrixB[0] + MatrixA[13] * MatrixB[4] + MatrixA[14] * MatrixB[8] + MatrixA[15] * MatrixB[12];
	MatrixDest[13] = MatrixA[12] * MatrixB[1] + MatrixA[13] * MatrixB[5] + MatrixA[14] * MatrixB[9] + MatrixA[15] * MatrixB[13];
	MatrixDest[14] = MatrixA[12] * MatrixB[2] + MatrixA[13] * MatrixB[6] + MatrixA[14] * MatrixB[10] + MatrixA[15] * MatrixB[14];
	MatrixDest[15] = MatrixA[12] * MatrixB[3] + MatrixA[13] * MatrixB[7] + MatrixA[14] * MatrixB[11] + MatrixA[15] * MatrixB[15];
}

void MatrixMul4x4SIMD( float* MatrixA, float* MatrixB, float* MatrixDest )
{
	__asm
	{
		pushad

		mov eax, MatrixA
		mov ebx, MatrixB
		mov edx, MatrixDest
		mov esi, 0

		movups xmm0, [ebx]
		movups xmm1, [ebx + 16]
		movups xmm2, [ebx + 32]
		movups xmm3, [ebx + 48]

		MULLP:
		movups xmm7, [eax + esi]
		movups xmm4, xmm7
		movups xmm5, xmm7
		movups xmm6, xmm7

		shufps xmm4, xmm7, 00000000b
		shufps xmm5, xmm7, 01010101b
		shufps xmm6, xmm7, 10101010b
		shufps xmm7, xmm7, 11111111b

		mulps xmm4, xmm0
		mulps xmm5, xmm1
		mulps xmm6, xmm2
		mulps xmm7, xmm3

		addps xmm5, xmm4
		addps xmm6, xmm5
		addps xmm7, xmm6

		movups[edx + esi], xmm7

		add ecx, 16
		cmp ecx, 64
		jne MULLP

		popad
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
		MatrixMul4x4C( MatrixA, MatrixB, MatrixDest );
	}
	StopWatch.End( );
	std::cout << "4x4 C Result Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;
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
		MatrixMul4x4SIMD( MatrixA, MatrixB, MatrixDest );
	}
	StopWatch.End( );
	std::cout << "4x4 SIMD Result Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;
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
}