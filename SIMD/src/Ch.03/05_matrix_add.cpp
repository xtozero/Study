#include <iostream>

void AddMatrix4x4C( const float* MatrixA, const float* MatrixB, float* MatrixDest )
{
	for ( int i = 0; i < 16; ++i )
	{
		MatrixDest[i] = MatrixA[i] + MatrixB[i];
	}
}

void AddMatrix4x4SIMD( float* MatrixA, float* MatrixB, float* MatrixDest )
{
	__asm
	{
		pushad
		mov eax, MatrixA
		mov ebx, MatrixB
		mov edx, MatrixDest

		movups xmm0, [eax]
		movups xmm1, [eax + 16]
		movups xmm2, [eax + 32]
		movups xmm3, [eax + 48]

		movups xmm4, [ebx]
		movups xmm5, [ebx + 16]
		movups xmm6, [ebx + 32]
		movups xmm7, [ebx + 48]

		addps xmm0, xmm4
		addps xmm1, xmm5
		addps xmm2, xmm6
		addps xmm3, xmm7

		movups [edx], xmm0
		movups [edx + 16], xmm1
		movups [edx + 32], xmm2
		movups [edx + 48], xmm3
		popad
	}
}

int main( )
{
	float MatrixA[16] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f, 11.11f, 12.12f, 13.13f, 14.14f, 15.15f, 16.16f };
	float MatrixB[16] = { 16.16f, 15.15f, 14.14f, 13.13f, 12.12f, 11.11f, 10.10f, 9.9f, 8.8f, 7.7f, 6.6f, 5.5f, 4.4f, 3.3f, 2.2f, 1.1f };
	float MatrixDestByC[16] = { 0.f };

	AddMatrix4x4C( MatrixA, MatrixB, MatrixDestByC );

	float MatrixDestBySIMD[16] = { 0 };

	AddMatrix4x4SIMD( MatrixA, MatrixB, MatrixDestBySIMD );

	std::cout << "AddMatrix4x4C : ";
	for ( float elem : MatrixDestByC )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "AddMatrix4x4SIMD : ";
	for ( float elem : MatrixDestBySIMD )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}