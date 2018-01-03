#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float DstGt[8] = { 0 };

	__asm
	{
		vmovups ymm0, SrcA
		vmovups ymm1, SrcB

		vcmpgtps ymm2, ymm0, ymm1
		vandps ymm2, ymm2, ymm0
		vmovups DstGt, ymm2
	}

	std::cout << "select gt : ";
	for ( float elem : DstGt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}