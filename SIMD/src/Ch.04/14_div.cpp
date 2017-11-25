#include <emmintrin.h>
#include <iostream>

int main( )
{
	short nA = 149;
	short nB = 9;
	short nR = nA / nB;

	std::cout << "C Div : " << nA << " / " << nB << " = " << nR << std::endl;

	alignas( 16 ) short A[8] = { 149, 149, 149, 149, 149, 149, 149, 149 };
	alignas( 16 ) short R[8] = { 0 };

	__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( A ) );
	__m128i xmmB = _mm_set1_epi16( 256 / 9 );
	
	xmmA = _mm_mullo_epi16( xmmA, xmmB );
	
	__m128i xmmR = _mm_srli_epi16( xmmA, 8 );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), xmmR );

	std::cout << "Intrinsic Div : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}