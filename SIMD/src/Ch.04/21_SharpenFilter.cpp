#define _SCL_SECURE_NO_WARNINGS

#include "../Lib/bitmap_image.hpp"
#include "../Util/StopWatch.h"

#include <emmintrin.h>
#include <iostream>

void Convolution3x3Intrinsic( unsigned char* pSrc, unsigned char* pDest, unsigned int nImageWidth, unsigned int nImageHeight, unsigned int* ROIPoint, short* pKernel )
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

	__m128i Kernel[9];
	__m128i ImageLow[9];
	__m128i ImageHigh[9];
	
	__m128i ZeroData = _mm_setzero_si128( );
	__m128i ResultHigh;
	__m128i ResultLow;

	for ( int i = 0; i < 9; ++i )
	{
		Kernel[i] = _mm_set1_epi16( pKernel[i] );
	}

	constexpr int BYTE_PER_PIXEL = 3;

	nStartX *= BYTE_PER_PIXEL;
	nEndX *= BYTE_PER_PIXEL;

	for ( int y = nStartY; y < nEndY; ++y )
	{
		for ( int x = nStartX; x < nEndX; x += 15 )
		{
			unsigned int ImagePitch = nImageWidth * BYTE_PER_PIXEL;
			unsigned char* pIterSrc = pSrc + y * ImagePitch + x;
			unsigned char* pIterDest = pDest + y * ImagePitch + x;;

			// ( x - 1, y - 1 )
			ImageLow[0] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - ImagePitch - BYTE_PER_PIXEL ) );

			// ( x, y - 1 )
			ImageLow[1] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - ImagePitch ) );

			// ( x + 1, y - 1 )
			ImageLow[2] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - ImagePitch + BYTE_PER_PIXEL ) );

			// ( x - 1, y )
			ImageLow[3] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - BYTE_PER_PIXEL ) );

			// ( x, y )
			ImageLow[4] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc ) );

			// ( x + 1, y )
			ImageLow[5] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + BYTE_PER_PIXEL ) );

			// ( x - 1, y + 1 )
			ImageLow[6] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + ImagePitch - BYTE_PER_PIXEL ) );

			// ( x, y + 1 )
			ImageLow[7] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + ImagePitch ) );

			// ( x + 1, y + 1 )
			ImageLow[8] = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + ImagePitch + BYTE_PER_PIXEL ) );

			ResultHigh = _mm_setzero_si128( );
			ResultLow = _mm_setzero_si128( );
			for ( int i = 0; i < 9; ++i )
			{
				ImageHigh[i] = _mm_unpackhi_epi8( ImageLow[i], ZeroData );
				ImageLow[i] = _mm_unpacklo_epi8( ImageLow[i], ZeroData );

				ImageHigh[i] = _mm_mullo_epi16( ImageHigh[i], Kernel[i] );
				ImageLow[i] = _mm_mullo_epi16( ImageLow[i], Kernel[i] );

				ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh[i] );
				ResultLow = _mm_add_epi16( ResultLow, ImageLow[i] );
			}

			ResultLow = _mm_packus_epi16( ResultLow, ResultHigh );

			ResultLow.m128i_i8[15] = *( pIterSrc + 15 );

			_mm_storeu_si128( reinterpret_cast<__m128i*>( pIterDest ), ResultLow );
		}
	}
}

void Convolution3x3Intrinsic2( unsigned char* pSrc, unsigned char* pDest, unsigned int nImageWidth, unsigned int nImageHeight, unsigned int* ROIPoint, short* pKernel )
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

	__m128i Kernel[9];
	__m128i ImageLow;
	__m128i ImageHigh;

	__m128i ZeroData = _mm_setzero_si128( );
	__m128i ResultHigh;
	__m128i ResultLow;

	for ( int i = 0; i < 9; ++i )
	{
		Kernel[i] = _mm_set1_epi16( pKernel[i] );
	}

	constexpr int BYTE_PER_PIXEL = 3;

	nStartX *= BYTE_PER_PIXEL;
	nEndX *= BYTE_PER_PIXEL;

	for ( int y = nStartY; y < nEndY; ++y )
	{
		for ( int x = nStartX; x < nEndX; x += 15 )
		{
			unsigned int ImagePitch = nImageWidth * BYTE_PER_PIXEL;
			unsigned char* pIterSrc = pSrc + y * ImagePitch + x;
			unsigned char* pIterDest = pDest + y * ImagePitch + x;;

			ResultHigh = _mm_setzero_si128( );
			ResultLow = _mm_setzero_si128( );

			// ( x - 1, y - 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - ImagePitch - BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[0] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[0] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x, y - 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - ImagePitch ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[1] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[1] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x + 1, y - 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - ImagePitch + BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[2] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[2] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x - 1, y )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc - BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[3] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[3] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x, y )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[4] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[4] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x + 1, y )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[5] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[5] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x - 1, y + 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + ImagePitch - BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[6] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[6] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x, y + 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + ImagePitch ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[7] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[7] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			// ( x + 1, y + 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( pIterSrc + ImagePitch + BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageLow = _mm_mullo_epi16( ImageLow, Kernel[8] );
			ImageHigh = _mm_mullo_epi16( ImageHigh, Kernel[8] );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_adds_epi16( ResultLow, ImageLow );

			ResultLow = _mm_packus_epi16( ResultLow, ResultHigh );

			ResultLow.m128i_u8[15] = *( pIterSrc + 15 );

			_mm_storeu_si128( reinterpret_cast<__m128i*>( pIterDest ), ResultLow );
		}
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
	unsigned int BYTE_PER_PIXEL = lenna.bytes_per_pixel( );
	unsigned int IMAGE_SIZE = WIDTH * HEIGHT * BYTE_PER_PIXEL;

	unsigned char* pLenna = new unsigned char[IMAGE_SIZE];
	unsigned char* pDest = new unsigned char[IMAGE_SIZE];

	memcpy_s( pLenna, IMAGE_SIZE, lenna.data( ), IMAGE_SIZE );
	memcpy_s( pDest, IMAGE_SIZE, lenna.data( ), IMAGE_SIZE );

	bitmap_image result( WIDTH, HEIGHT );
	CStopWatch StopWatch;

	unsigned int ROI[4] = { 0, 0, WIDTH, HEIGHT };
	short kernel[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };

	StopWatch.Start( );
	Convolution3x3Intrinsic( pLenna, pDest, WIDTH, HEIGHT, ROI, kernel );
	StopWatch.End( );

	std::cout << "Intrinsic Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << " msec" << std::endl;

	memcpy_s( result.data( ), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/SharpenFilter/SharpenByIntrinsic.bmp" );

	StopWatch.Start( );
	Convolution3x3Intrinsic2( pLenna, pDest, WIDTH, HEIGHT, ROI, kernel );
	StopWatch.End( );

	std::cout << "Intrinsic2 Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << " msec" << std::endl;

	memcpy_s( result.data( ), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/SharpenFilter/SharpenByIntrinsic2.bmp" );

	delete[] pLenna;
	delete[] pDest;

	return 0;
}