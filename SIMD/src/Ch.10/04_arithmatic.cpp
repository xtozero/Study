/*--------------
instinsic 함수는 AVX 명령어 세트를 인라인으로 구현했기 때문에 성능과 동작은 어셈블리와 같다.
따라서 사칙 연산의 동작도 명령어 세트와 마찬가지로 사용하면 된다.

R = _mm256_add_ps( A, B );
R = _mm256_sub_ps( A, B );
R = _mm256_mul_ps( A, B );
R = _mm256_div_ps( A, B );
--------------*/

#include "immintrin.h"

#include <iostream>

int main( )
{
	alignas( 32 ) float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	alignas( 32 ) float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };
	alignas( 32 ) float DstAdd[8] = { 0 };
	alignas( 32 ) float DstSub[8] = { 0 };
	alignas( 32 ) float DstMul[8] = { 0 };
	alignas( 32 ) float DstDiv[8] = { 0 };

	__m256 mmSrcA = _mm256_setzero_ps( );
	__m256 mmSrcB = _mm256_setzero_ps( );
	__m256 mmDst = _mm256_setzero_ps( );

	mmSrcA = _mm256_load_ps( SrcA );
	mmSrcB = _mm256_load_ps( SrcB );

	mmDst = _mm256_add_ps( mmSrcA, mmSrcB );
	_mm256_store_ps( DstAdd, mmDst );

	mmDst = _mm256_sub_ps( mmSrcA, mmSrcB );
	_mm256_store_ps( DstSub, mmDst );

	mmDst = _mm256_mul_ps( mmSrcA, mmSrcB );
	_mm256_store_ps( DstMul, mmDst );

	mmDst = _mm256_div_ps( mmSrcA, mmSrcB );
	_mm256_store_ps( DstDiv, mmDst );

	std::cout << "Add : ";
	for ( double elem : DstAdd )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Sub : ";
	for ( double elem : DstSub )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Mul : ";
	for ( double elem : DstMul )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Div : ";
	for ( double elem : DstDiv )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}