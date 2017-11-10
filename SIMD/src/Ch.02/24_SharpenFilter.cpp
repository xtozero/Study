#define _SCL_SECURE_NO_WARNINGS

#include <iostream>

#include "../Lib/bitmap_image.hpp"
#include "../Util/StopWatch.h"

void Convolution3x3C( unsigned char* pSrc, unsigned char* pDest,
					unsigned int nImageWidth, unsigned int nImageHeight,
					unsigned int* ROIPoint, short* pKernel )
{
	unsigned int nStartX = ROIPoint[0];
	unsigned int nStartY = ROIPoint[1];
	unsigned int nEndX = ROIPoint[2];
	unsigned int nEndY = ROIPoint[3];

	if ( nStartX == 0 )
	{
		nStartX = 1;
	}

	if ( nStartY == 0 )
	{
		nStartY = 1;
	}

	if ( nEndX == nImageWidth )
	{
		nEndX = nImageWidth - 1;
	}

	if ( nEndY == nImageHeight )
	{
		nEndY = nImageHeight - 1;
	}

	constexpr int BYTE_PER_PIXEL = 3;

	nStartX *= BYTE_PER_PIXEL;
	nEndX *= BYTE_PER_PIXEL;

	short total = 0;
	short value[9] = { 0 };

	unsigned widthOffset = nImageWidth * BYTE_PER_PIXEL;

	for ( unsigned int j = nStartY; j < nEndY; ++j )
	{
		for ( unsigned int i = nStartX; i < nEndX; ++i )
		{
			total = 0;
			value[0] = pSrc[i + j * widthOffset - widthOffset - BYTE_PER_PIXEL];
			total += pKernel[0] * value[0];

			value[1] = pSrc[i + j * widthOffset - widthOffset];
			total += pKernel[1] * value[1];

			value[2] = pSrc[i + j * widthOffset - widthOffset + BYTE_PER_PIXEL];
			total += pKernel[2] * value[2];

			value[3] = pSrc[i + j * widthOffset - BYTE_PER_PIXEL];
			total += pKernel[3] * value[3];

			value[4] = pSrc[i + j * widthOffset];
			total += pKernel[4] * value[4];

			value[5] = pSrc[i + j * widthOffset + BYTE_PER_PIXEL];
			total += pKernel[5] * value[5];

			value[6] = pSrc[i + j * widthOffset + widthOffset - BYTE_PER_PIXEL];
			total += pKernel[6] * value[6];

			value[7] = pSrc[i + j * widthOffset + widthOffset];
			total += pKernel[7] * value[7];

			value[8] = pSrc[i + j * widthOffset + widthOffset + BYTE_PER_PIXEL];
			total += pKernel[8] * value[8];

			if ( total < 0 )
			{
				total = 0;
			}
			else if ( total > 255 )
			{
				total = 255;
			}

			pDest[i + j * widthOffset] = static_cast<unsigned char>( total );
		}
	}
}

void Convolution3x3SIMD( unsigned char* pSrc, unsigned char* pDest,
	unsigned int nImageWidth, unsigned int nImageHeight,
	unsigned int* ROIPoint, short* pKernel )
{
	unsigned int nStartX = ROIPoint[0];
	unsigned int nStartY = ROIPoint[1];
	unsigned int nEndX = ROIPoint[2];
	unsigned int nEndY = ROIPoint[3];

	if ( nStartX == 0 )
	{
		nStartX = 1;
	}

	if ( nStartY == 0 )
	{
		nStartY = 1;
	}

	if ( nEndX == nImageWidth )
	{
		nEndX = nImageWidth - 1;
	}

	if ( nEndY == nImageHeight )
	{
		nEndY = nImageHeight - 1;
	}

	constexpr int BYTE_PER_PIXEL = 3;

	nStartX *= BYTE_PER_PIXEL;
	nEndX *= BYTE_PER_PIXEL;

	unsigned widthOffset = nImageWidth * BYTE_PER_PIXEL;

	alignas( 16 ) short Mask0[8], Mask1[8], Mask2[8], Mask3[8];
	alignas( 16 ) short Mask4[8], Mask5[8], Mask6[8], Mask7[8], Mask8[8];

	for ( int i = 0; i < 8; ++i )
	{
		Mask0[i] = pKernel[0];	// Kernel[m-1][n-1]
		Mask1[i] = pKernel[1];	// Kernel[m][n-1]
		Mask2[i] = pKernel[2];	// Kernel[m+1][n-1]
		Mask3[i] = pKernel[3];	// Kernel[m-1][n]
		Mask4[i] = pKernel[4];	// Kernel[m][n]
		Mask5[i] = pKernel[5];	// Kernel[m+1][n]
		Mask6[i] = pKernel[6];	// Kernel[m-1][n+1]
		Mask7[i] = pKernel[7];	// Kernel[m][n+1]
		Mask8[i] = pKernel[8];	// Kernel[m+1][n+1]
	}

	unsigned int nProcessLength = nEndX - nStartX;
	int HLoopCount = nProcessLength / 15;	// 15 byte 씩 진행 ( = rgb 채널 * 5 픽셀씩 처리 )
	unsigned int VLoopCount = nEndY - nStartY;
	unsigned int nRemain = ( nProcessLength % 15 );
	unsigned int nNextStartLength = widthOffset - nProcessLength + 15;

	unsigned char* pStartSrc = pSrc + nStartX + nStartY * widthOffset;
	unsigned char* pDestSrc = pDest + nStartX + nStartY * widthOffset;
	unsigned test = 0;
	unsigned int width = widthOffset;

	__asm
	{
		pushad
		mov eax, pStartSrc
		mov edx, pDestSrc
		mov esi, nNextStartLength
		mov ebx, VLoopCount
		mov ecx, HLoopCount
		mov edi, width

		movdqa xmm3, Mask8
		pxor xmm4, xmm4
	VLP:
	HLP:
		// 0번 위치
		pxor xmm7, xmm7			// 하위 short형 합 결과 값
		pxor xmm6, xmm6			// 상위 short형 합 결과 값

		sub eax, edi			// [x][y-1] 위치
		movdqa xmm5, Mask0
		movdqu xmm0, [eax-3]	// [x-1][y-1] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 1번 위치
		movdqa xmm5, Mask1
		movdqu xmm0, [eax]		// [x][y-1] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 2번 위치
		movdqa xmm5, Mask2
		movdqu xmm0, [eax+3]	// [x+1][y-1] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 3번 위치
		add eax, edi
		movdqa xmm5, Mask3
		movdqu xmm0, [eax - 3]	// [x-1][y] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 4번 위치
		movdqa xmm5, Mask4
		movdqu xmm0, [eax]	// [x][y] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 5번 위치
		movdqa xmm5, Mask5
		movdqu xmm0, [eax + 3]	// [x+1][y] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 6번 위치
		add eax, edi
		movdqa xmm5, Mask6
		movdqu xmm0, [eax - 3]	// [x-1][y+1] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 7번 위치
		movdqa xmm5, Mask7
		movdqu xmm0, [eax]	// [x][y+1] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		// 8번 위치
		movdqa xmm5, Mask8
		movdqu xmm0, [eax + 3]	// [x+1][y+1] 위치
		movdqa xmm1, xmm0

		punpcklbw xmm0, xmm4
		punpckhbw xmm1, xmm4

		pmullw xmm0, xmm5
		pmullw xmm1, xmm5

		paddw xmm7, xmm0
		paddw xmm6, xmm1

		packuswb xmm7, xmm6
		sub eax, edi
		pinsrb xmm7, [eax + 15], 15	// 마지막 16비트는 쓰레기 값이나 다름 없으므로 원래 값으로 대체
		movdqu[edx], xmm7

		dec ecx
		cmp ecx, 0
		jg ADD15
		je ADDREMAIN
		jl HLPEND
	ADD15:
		add eax, 15
		add edx, 15
		jmp HLP
	ADDREMAIN:	// 마지막 15단위 처리 후 나머지 부분 처리
		add eax, nRemain
		add edx, nRemain
		jmp HLP
	HLPEND:
		add eax, esi
		add edx, esi
		mov ecx, HLoopCount

		dec ebx
		cmp ebx, 0
		jz LPEND
		jmp VLP
	LPEND:
		popad
	}
}

int main( )
{
	bitmap_image lenna( "../Resource/SharpenFilter/Lenna.bmp" );

	if ( !lenna )
	{
		std::cout << "Failed to open Lenna.bmp" << std::endl;
	}
	
	unsigned int WIDTH = lenna.width( );
	unsigned int HEIGHT = lenna.height( );
	constexpr unsigned int BYTE_PER_PIXEL = 3;

	unsigned int IMAGE_SIZE = WIDTH * HEIGHT * BYTE_PER_PIXEL;

	unsigned char* pLenna = new unsigned char[IMAGE_SIZE];
	unsigned char* pDest = new unsigned char[IMAGE_SIZE];

	memcpy_s( pLenna, IMAGE_SIZE, lenna.data( ), IMAGE_SIZE );
	memcpy_s( pDest, IMAGE_SIZE, lenna.data( ), IMAGE_SIZE );

	unsigned int ROI[4] = { 0, 0, WIDTH, HEIGHT };
	short kernel[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };

	CStopWatch StopWatch;

	StopWatch.Start( );
	Convolution3x3C( pLenna, pDest, WIDTH, HEIGHT, ROI, kernel );
	StopWatch.End( );

	std::cout << "C Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << " msec" << std::endl;

	bitmap_image result( WIDTH, HEIGHT );

	memcpy_s( result.data(), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/SharpenFilter/SharpenByC.bmp" );

	StopWatch.Start( );
	Convolution3x3SIMD( pLenna, pDest, WIDTH, HEIGHT, ROI, kernel );
	StopWatch.End( );

	std::cout << "SIMD Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << " msec" << std::endl;

	memcpy_s( result.data( ), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/SharpenFilter/SharpenBySIMD.bmp" );
}