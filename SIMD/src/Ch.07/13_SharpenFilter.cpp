#include "../Lib/bitmap_image.hpp"
#include "../Util/StopWatch.h"

#include <dvec.h>

void Convolution3x3Vector( unsigned char* pSrc, unsigned char* pDest, unsigned int nImageWidth, unsigned int nImageHeight,
	unsigned int* ROIPoint, short *pKernel )
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

	Is16vec8 Kernel[9];

	for ( int i = 0; i < 9; ++i )
	{
		Kernel[i] = Is16vec8( _mm_set1_epi16( pKernel[i] ) );
	}

	Is16vec8 ImageLow;
	Is16vec8 ImageHigh;

	Is8vec16 srcImage;
	Is8vec16 destImage;

	Is8vec16 zeroVector = Is8vec16( _mm_setzero_si128( ) );

	Is16vec8 resultHigh;
	Is16vec8 resultLow;

	unsigned char* iterSrc;
	unsigned char* iterDest;

	constexpr int BYTE_PER_PIXEL = 3;

	nStartX *= BYTE_PER_PIXEL;
	nEndX *= BYTE_PER_PIXEL;

	for ( int y = nStartY; y < nEndY; ++y )
	{
		for ( int x = nStartX; x < nEndX; x += 15 )
		{
			unsigned int ImagePitch = nImageWidth * BYTE_PER_PIXEL;
			iterSrc = pSrc + y * ImagePitch + x;
			iterDest = pDest + y * ImagePitch + x;

			resultHigh = zeroVector;
			resultLow = zeroVector;

			// ( x - 1, y - 1 )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - ImagePitch - BYTE_PER_PIXEL ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[0];
			ImageLow *= Kernel[0];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x, y - 1 )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - ImagePitch ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[1];
			ImageLow *= Kernel[1];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x + 1, y - 1 )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - ImagePitch + BYTE_PER_PIXEL ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[2];
			ImageLow *= Kernel[2];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x - 1, y )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc - BYTE_PER_PIXEL ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[3];
			ImageLow *= Kernel[3];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x, y )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[4];
			ImageLow *= Kernel[4];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x + 1, y )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + BYTE_PER_PIXEL ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[5];
			ImageLow *= Kernel[5];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x - 1, y + 1 )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + ImagePitch - BYTE_PER_PIXEL ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[6];
			ImageLow *= Kernel[6];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x, y + 1 )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + ImagePitch ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[7];
			ImageLow *= Kernel[7];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			// ( x + 1, y + 1 )
			srcImage = Is8vec16( _mm_loadu_si128( reinterpret_cast<__m128i*>( iterSrc + ImagePitch + BYTE_PER_PIXEL ) ) );

			ImageHigh = unpack_high( srcImage, zeroVector );
			ImageLow = unpack_low( srcImage, zeroVector );

			ImageHigh *= Kernel[8];
			ImageLow *= Kernel[8];

			resultHigh += ImageHigh;
			resultLow += ImageLow;

			destImage = packu_sat( resultLow, resultHigh );
			destImage[15] = srcImage[15];

			_mm_storeu_si128( reinterpret_cast<__m128i*>( iterDest ), destImage );
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
	Convolution3x3Vector( pLenna, pDest, WIDTH, HEIGHT, ROI, kernel );
	StopWatch.End( );

	std::cout << "Intrinsic Time : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << " msec" << std::endl;

	memcpy_s( result.data( ), IMAGE_SIZE, pDest, IMAGE_SIZE );

	result.save_image( "../Resource/SharpenFilter/SharpenByVector.bmp" );

	delete[] pLenna;
	delete[] pDest;

	return 0;
}