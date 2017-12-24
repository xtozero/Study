#include "../Util/StopWatch.h"

#include <fvec.h>
#include <iostream>

void Matrix4x4Vector2( float* MatrixA, F32vec4* MatrixB, float* MatrixDest )
{
	int indexA = 0;
	int indexB = 0;

	F32vec4 xmmR;

	for ( int i = 0; i < 4; ++i )
	{
		indexB = 0;

		xmmR = F32vec4( MatrixA[indexA++] ) * MatrixB[indexB++]
			+ F32vec4( MatrixA[indexA++] ) * MatrixB[indexB++]
			+ F32vec4( MatrixA[indexA++] ) * MatrixB[indexB++]
			+ F32vec4( MatrixA[indexA++] ) * MatrixB[indexB++];

		storeu( MatrixDest + ( i * 4 ), xmmR);
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
		Matrix4x4Vector2( MatrixA, reinterpret_cast<F32vec4*>( MatrixB ), MatrixDest );
	}
	StopWatch.End( );
	std::cout << "4x4 Vector2 SIMD Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;
	for ( int i = 0; i < 16; ++i )
	{
		std::cout << MatrixDest[i] << ' ';
		if ( i % 4 == 3 )
		{
			std::cout << std::endl;
		}
	}

	return 0;
}