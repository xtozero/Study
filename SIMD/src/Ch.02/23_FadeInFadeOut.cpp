#define _SCL_SECURE_NO_WARNINGS

#include <iostream>

#include "../Lib/bitmap_image.hpp"
#include "../Util/StopWatch.h"

int ImageSumC( const unsigned char* ImageA, const unsigned char* ImageB, unsigned char* ResultImage, const unsigned char nFrame, const int nImageSize )
{
	if ( nFrame == 0 || nFrame == 8 )
	{
		return -1; // 0프레임과 8프레임은 A, B이미지를 사용하면 되므로 계산하지 않는다.
	}

	unsigned short RatioA = nFrame;
	unsigned short RatioB = 8 - nFrame;

	unsigned short AValue = 0;
	unsigned short BValue = 0;

	for ( int nIndex = 0; nIndex < nImageSize; ++nIndex )
	{
		AValue = ImageA[nIndex];
		BValue = ImageB[nIndex];
		ResultImage[nIndex] = static_cast<unsigned char>( ( RatioA * AValue + RatioB * BValue ) / 8 );
	}

	return 1;
}

int ImageSumSIMD( const unsigned char* ImageA, const unsigned char* ImageB, unsigned char* ResultImage, const unsigned char nFrame, const int nImageSize )
{
	if ( nFrame == 0 || nFrame == 8 )
	{
		return -1; // 0프레임과 8프레임은 A, B이미지를 사용하면 되므로 계산하지 않는다.
	}

	const unsigned char* pImageA = ImageA;
	const unsigned char* pImageB = ImageB;
	unsigned char* pResult = ResultImage;
	unsigned short RatioA[8] = { nFrame, nFrame, nFrame, nFrame, nFrame, nFrame, nFrame, nFrame };
	unsigned short RatioB[8] = { 8 - nFrame, 8 - nFrame, 8 - nFrame, 8 - nFrame, 8 - nFrame, 8 - nFrame, 8 - nFrame, 8 - nFrame };
	
	unsigned int nLoop = static_cast<int>( nImageSize / 16 ) * 16;

	__asm
	{
		pushad

		mov eax, pImageA
		mov ebx, pImageB
		mov edi, pResult
		mov esi, 0
		mov ecx, nLoop

		pxor xmm4, xmm4 // tmp
		movdqu xmm5, RatioA
		movdqu xmm6, RatioB

		SIMDLP:
		movdqu xmm0, [eax+esi]
		movdqu xmm1, xmm0

		movdqu xmm2, [ebx+esi]
		movdqu xmm3, xmm2

		punpcklbw xmm0, xmm4
		punpcklbw xmm2, xmm4

		pmullw xmm0, xmm5
		pmullw xmm2, xmm6

		paddw xmm0, xmm2
		psrlw xmm0, 3

		punpckhbw xmm1, xmm4
		punpckhbw xmm3, xmm4

		pmullw xmm1, xmm5
		pmullw xmm3, xmm6

		paddw xmm1, xmm3
		psrlw xmm1, 3

		packuswb xmm0, xmm1

		movdqu [edi+esi], xmm0

		add esi, 16
		cmp esi, ecx
		jne SIMDLP

		popad
	}

	{
		unsigned short RatioA = nFrame;
		unsigned short RatioB = 8 - nFrame;
		unsigned short AValue = 0;
		unsigned short BValue = 0;

		for ( int i = nLoop; i < nImageSize; ++i )
		{
			AValue = ImageA[i];
			BValue = ImageB[i];
			ResultImage[i] = static_cast<unsigned char>( ( RatioA * AValue + RatioB * BValue ) / 8 );
		}
	}
}

int main( )
{
	{
		bitmap_image imageA( "../Resource/FadeInFadeOut/A.bmp" );
		if ( !imageA )
		{
			std::cout << "Failed to open A.bmp" << std::endl;
		}

		bitmap_image imageB( "../Resource/FadeInFadeOut/B.bmp" );
		if ( !imageB )
		{
			std::cout << "Failed to open B.bmp" << std::endl;
		}

		unsigned int WIDTH = imageA.width( );
		unsigned int HEIGHT = imageA.height( );
		unsigned int IMAGE_SIZE = WIDTH * HEIGHT * 3;

		unsigned char* pSrcA = new unsigned char[IMAGE_SIZE];
		unsigned char* pSrcB = new unsigned char[IMAGE_SIZE];
		unsigned char* pResult = new unsigned char[IMAGE_SIZE];

		memcpy_s( pSrcA, IMAGE_SIZE, imageA.data( ), IMAGE_SIZE );
		memcpy_s( pSrcB, IMAGE_SIZE, imageB.data( ), IMAGE_SIZE );

		bitmap_image resultImage( WIDTH, HEIGHT );

		for ( int i = 1; i < 8; ++i )
		{
			ImageSumSIMD( pSrcA, pSrcB, pResult, i, IMAGE_SIZE );

			memcpy_s( resultImage.data( ), IMAGE_SIZE, pResult, IMAGE_SIZE );

			char filePath[256];
			sprintf_s( filePath, "../Resource/FadeInFadeOut/Result%d.bmp", i );
			resultImage.save_image( filePath );
		}

		delete[] pSrcA;
		delete[] pSrcB;
		delete[] pResult;
	}

	// performance test
	{
		CStopWatch StopWatch;
		unsigned char* pData1 = new unsigned char[1024 * 1024];
		unsigned char* pData2 = new unsigned char[1024 * 1024];
		unsigned char* pData3 = new unsigned char[1024 * 1024];

		StopWatch.Start( );
		ImageSumC( pData1, pData2, pData3, 1, 1024 * 1024 );
		StopWatch.End( );

		std::cout << "C Time : " << StopWatch.GetDuration<duration<float, std::milli>>() << std::endl;

		StopWatch.Start( );
		ImageSumSIMD( pData1, pData2, pData3, 1, 1024 * 1024 );
		StopWatch.End( );

		std::cout << "SIMD Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

		delete[] pData1;
		delete[] pData2;
		delete[] pData3;
	}

	return 0;
}