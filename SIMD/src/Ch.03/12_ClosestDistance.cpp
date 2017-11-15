#include <iostream>

#include "../Util/StopWatch.h"

struct Point
{
	float m_x;
	float m_y;
};

float MinLengthC( Point* pRect1, Point* pRect2 )
{
	float MinValue = FLT_MAX;
	float xValue = 0;
	float yValue = 0;
	float Sum = 0;

	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 4; ++j )
		{
			xValue = pRect1[i].m_x - pRect2[j].m_x;
			yValue = pRect1[i].m_y - pRect2[j].m_y;

			xValue *= xValue;
			yValue *= yValue;

			Sum = xValue + yValue;

			if ( MinValue > Sum )
			{
				MinValue = Sum;
			}
		}
	}

	return sqrtf( MinValue );
}

float MinLengthSIMD( Point* pRect1, Point* pRect2 )
{
	float Result[4];

	__asm
	{
		pushad
		mov eax, pRect1
		mov ebx, pRect2

		movups xmm0, [eax]	// 1번째 사각형 좌표 로드
		movups xmm3, xmm0

		movups xmm5, [ebx] // 2번째 사각형 좌표 로드
		movups xmm6, [ebx + 16]

		movups xmm1, xmm0

		unpcklpd xmm0, xmm1	// R1.x1, R1.y1, R1.x1, R1.y1 으로 생성
		movups xmm1, xmm0	// 재사용을 위해 복사

		subps xmm0, xmm5 // R1.x1 - R2.x1, R1.y1 - R2.y1, R1.x1 - R2.x2, R1.y1 - R2.y2
		mulps xmm0, xmm0 // x*x, y*y
		haddps xmm0, xmm0 // x*x+y*y

		movups xmm7, xmm0 // 결과 저장

		subps xmm1, xmm6 // R1.x1 - R2.x3, R1.y1 - R2.y3, R1.x1 - R2.x4, R1.y1 - R2.y4
		mulps xmm1, xmm1 // x*x, y*y
		haddps xmm1, xmm1 // x*x+y*y

		minps xmm7, xmm1 // 최솟값 저장

		movups xmm0, xmm3
		movups xmm1, xmm0

		unpckhpd xmm0, xmm1 // R1.x2, R1.y2, R1.x2, R1.y2 으로 생성
		
		movups xmm1, xmm0 // xmm1에 복사

		subps xmm0, xmm5 // R1.x2 - R2.x1, R1.y2 - R2.y1, R1.x2 - R2.x2, R1.y2 - R2.y2
		mulps xmm0, xmm0 // x*x, y*y
		haddps xmm0, xmm0 // x*x+y*y

		minps xmm7, xmm0

		subps xmm1, xmm6 // R1.x2 - R2.x3, R1.y2 - R2.y3, R1.x2 - R2.x4, R1.y2 - R2.y4
		mulps xmm1, xmm1 // x*x, y*y
		haddps xmm1, xmm1 // x*x+y*y

		minps xmm7, xmm1

		// 나머지 2 정점에 대한 처리

		movups xmm0, [eax + 16]
		movups xmm3, xmm0

		movups xmm1, xmm0

		unpcklpd xmm0, xmm1
		movups xmm1, xmm0

		subps xmm0, xmm5
		mulps xmm0, xmm0
		haddps xmm0, xmm0

		minps xmm7, xmm0

		subps xmm1, xmm6
		mulps xmm1, xmm1
		haddps xmm1, xmm1

		minps xmm7, xmm1

		movups xmm0, xmm3
		movups xmm1, xmm0

		unpckhpd xmm0, xmm1

		movups xmm1, xmm0

		subps xmm0, xmm5
		mulps xmm0, xmm0
		haddps xmm0, xmm0

		minps xmm7, xmm0

		subps xmm1, xmm6
		mulps xmm1, xmm1
		haddps xmm1, xmm1

		minps xmm7, xmm1

		movups xmm6, xmm7
		psrldq xmm6, 4

		minps xmm7, xmm6

		sqrtps xmm7, xmm7

		movups Result, xmm7

		popad
	}

	return Result[0];
}

int main( )
{
	Point RectPoint[4];
	RectPoint[0].m_x = 5.5; RectPoint[0].m_y = 6.5;
	RectPoint[1].m_x = 5.5; RectPoint[1].m_y = 16.5;
	RectPoint[2].m_x = 8.5; RectPoint[2].m_y = 9.5;
	RectPoint[3].m_x = 11.5; RectPoint[3].m_y = 15.5;

	Point RectPoint2[4];
	RectPoint2[0].m_x = 15.5; RectPoint2[0].m_y = 26.5;
	RectPoint2[1].m_x = 22.5; RectPoint2[1].m_y = 6.5;
	RectPoint2[2].m_x = 18.5; RectPoint2[2].m_y = 19.5;
	RectPoint2[3].m_x = 1.5; RectPoint2[3].m_y = 15.5;

	CStopWatch StopWatch;

	float Result[10000];
	int i = 0;

	StopWatch.Start( );
	for ( int i = 0; i < 10000; ++i )
	{
		Result[i] = MinLengthC( RectPoint, RectPoint2 );
	}
	StopWatch.End( );

	std::cout << "C Calc " << Result[0] << ", " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	for ( int i = 0; i < 10000; ++i )
	{
		Result[i] = MinLengthSIMD( RectPoint, RectPoint2 );
	}
	StopWatch.End( );

	std::cout << "SIMD Calc " << Result[0] << ", " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;
}