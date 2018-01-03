/*--------------
기존에 사용하던 andps, orps, xorps, andnps 에 v 접두사를 붙이고 ymm 레지스터를 사용하면 논리 연산을 사용할 수 있다.
--------------*/

#include <iostream>

int main( )
{
	alignas( 32 ) float SrcA[8] = { 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f };
	alignas( 32 ) float SrcB[8] = { 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f };
	alignas( 32 ) float DstAnd[8] = { 0.f };
	alignas( 32 ) float DstOr[8] = { 0.f };
	alignas( 32 ) float DstXor[8] = { 0.f };
	alignas( 32 ) float DstAndn[8] = { 0.f };

	__asm
	{
		vmovaps ymm0, SrcA
		vmovaps ymm1, SrcB

		vandps ymm2, ymm0, ymm1
		vmovaps DstAnd, ymm2

		vorps ymm2, ymm0, ymm1
		vmovaps DstOr, ymm2

		vxorps ymm2, ymm0, ymm1
		vmovaps DstXor, ymm2

		vandnps ymm2, ymm0, ymm1
		vmovaps DstAndn, ymm2
	}

	std::cout << "And : ";
	for ( float elem : DstAnd )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Or : ";
	for ( float elem : DstOr )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Xor : ";
	for ( float elem : DstXor )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Andn : ";
	for ( float elem : DstAndn )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}