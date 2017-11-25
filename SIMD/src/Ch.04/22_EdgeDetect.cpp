#define _SCL_SECURE_NO_WARNINGS

#include "../Lib/bitmap_image.hpp"
#include "../Util/StopWatch.h"

#include <emmintrin.h>
#include <iostream>

void EdgeDetect3x3C( unsigned char* pSrc, unsigned char* pDest, unsigned int nImageWidth, unsigned int nImageHeight, unsigned int* ROIPoint )
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
	short value;

	int nImagePitch = nImageWidth * BYTE_PER_PIXEL;

	for ( int y = nStartY; y < nEndY; ++y )
	{
		for ( int x = nStartX; x < nEndX; ++x )
		{
			int nCur = y * nImagePitch + x;

			total = 0;

			// ( x - 1, y - 1 )
			value = pSrc[nCur - nImagePitch - BYTE_PER_PIXEL];
			total += value / 8;

			// ( x, y - 1 )
			value = pSrc[nCur - nImagePitch];
			total += value / 8;

			// ( x + 1, y - 1 )
			value = pSrc[nCur - nImagePitch + BYTE_PER_PIXEL];
			total += value / 8;

			// ( x - 1, y )
			value = pSrc[nCur - BYTE_PER_PIXEL];
			total += value / 8;

			// ( x, y )
			value = pSrc[nCur];
			total -= value;

			// ( x + 1, y )
			value = pSrc[nCur + BYTE_PER_PIXEL];
			total += value / 8;

			// ( x - 1, y + 1 )
			value = pSrc[nCur + nImagePitch - BYTE_PER_PIXEL];
			total += value / 8;

			// ( x, y + 1 )
			value = pSrc[nCur + nImagePitch];
			total += value / 8;

			// ( x + 1, y + 1 )
			value = pSrc[nCur + nImagePitch + BYTE_PER_PIXEL];
			total += value / 8;

			total = total > 0 ? 255 : 0;

			pDest[nCur] = static_cast<unsigned short>( total );
		}
	}
}

void EdgeDetect3x3Intrinsic( unsigned char* pSrc, unsigned char* pDest, unsigned int nImageWidth, unsigned int nImageHeight, unsigned int* ROIPoint )
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

	unsigned char* iterSrc;
	unsigned char* iterDest;

	int nImagePitch = nImageWidth * BYTE_PER_PIXEL;

	__m128i ZeroData = _mm_setzero_si128( );

	__m128i ImageHigh;
	__m128i ImageLow;

	__m128i ResultHigh;
	__m128i ResultLow;

	for ( int y = nStartY; y < nEndY; ++y )
	{
		for ( int x = nStartX; x < nEndX; x += 16 )
		{
			iterSrc = pSrc + nImagePitch * y + x;
			iterDest = pDest + nImagePitch * y + x;

			ResultHigh = _mm_setzero_si128( );
			ResultLow = _mm_setzero_si128( );

			// ( x - 1, y - 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - nImagePitch - BYTE_PER_PIXEL ) );
			
			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );
			

			// ( x, y - 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - nImagePitch ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			// ( x + 1, y - 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - nImagePitch + BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			// ( x - 1, y )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			// ( x, y )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ResultHigh = _mm_sub_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_sub_epi16( ResultLow, ImageLow );

			// ( x + 1, y )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + BYTE_PER_PIXEL ) );
			
			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			// ( x - 1, y + 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + nImagePitch - BYTE_PER_PIXEL ) );
			
			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			// ( x, y + 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + nImagePitch ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			// ( x + 1, y + 1 )
			ImageLow = _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + nImagePitch + BYTE_PER_PIXEL ) );

			ImageHigh = _mm_unpackhi_epi8( ImageLow, ZeroData );
			ImageLow = _mm_unpacklo_epi8( ImageLow, ZeroData );

			ImageHigh = _mm_srli_epi16( ImageHigh, 3 );
			ImageLow = _mm_srli_epi16( ImageLow, 3 );

			ResultHigh = _mm_add_epi16( ResultHigh, ImageHigh );
			ResultLow = _mm_add_epi16( ResultLow, ImageLow );

			ResultLow = _mm_packs_epi16( ResultLow, ResultHigh );
			ResultLow = _mm_cmpgt_epi8( ResultLow, ZeroData );

			_mm_storeu_si128( reinterpret_cast<__m128i*>( pDest ), ResultLow );
		}
	}
}

int main( )
{
	bitmap_image lenna( "../Resource/EdgeDetect/Lenna.bmp" );

	if ( !lenna )
	{
		std::cout << "Failed to open Lenna.bmp" << std::endl;
	}

	const unsigned int WIDTH = lenna.width( );
	const unsigned int HEIGHT = lenna.height( );
	const unsigned int BYTE_PER_PIXEL = lenna.bytes_per_pixel( );
	const unsigned int IMAGE_SIZE = WIDTH * HEIGHT * BYTE_PER_PIXEL;

	unsigned char* pLenna = new unsigned char[IMAGE_SIZE];
	unsigned char* pDest = new unsigned char[IMAGE_SIZE];

	unsigned int ROI[4] = { 0, 0, WIDTH, HEIGHT };

	memcpy_s( pLenna, IMAGE_SIZE, lenna.data( ), IMAGE_SIZE );
	memcpy_s( pDest, IMAGE_SIZE, lenna.data( ), IMAGE_SIZE );

	CStopWatch StopWatch;
	StopWatch.Start( );
	EdgeDetect3x3C( pLenna, pDest, WIDTH, HEIGHT, ROI );
	StopWatch.End( );

	std::cout << "C Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	bitmap_image result( WIDTH, HEIGHT );

	memcpy_s( result.data( ), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/EdgeDetect/EdgeDetectByC.bmp" );

	StopWatch.Start( );
	EdgeDetect3x3Intrinsic( pLenna, pDest, WIDTH, HEIGHT, ROI );
	StopWatch.End( );

	std::cout << "Intrinsic Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	memcpy_s( result.data( ), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/EdgeDetect/EdgeDetectByIntrinsic.bmp" );

	delete[] pLenna;
	delete[] pDest;

	return 0;
}