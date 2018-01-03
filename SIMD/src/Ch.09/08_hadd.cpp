/*--------------
사용 문법						pack 사이즈			연산 기능
vhaddps ymm2, ymm1, ymm0		32bit float			32bit float형 실수 8개에 대한 수평 덧셈값을 구한다.
vhsubps ymm2, ymm1, ymm0		32bit float			32bit float형 실수 8개에 대한 수평 뺠샘값을 구한다.

VHADDPS
DEST[31:0] ← SRC1[63:32] + SRC1[31:0]
DEST[63:32] ← SRC1[127:96] + SRC1[95:64]
DEST[95:64] ← SRC2[63:32] + SRC2[31:0]
DEST[127:96] ← SRC2[127:96] + SRC2[95:64]
DEST[159:128] ← SRC1[191:160] + SRC1[159:128]
DEST[191:160] ← SRC1[255:224] + SRC1[223:192]
DEST[223:192] ← SRC2[191:160] + SRC2[159:128]
DEST[255:224] ← SRC2[255:224] + SRC2[223:192]

VHSUBPS
DEST[31:0] ← SRC1[31:0] - SRC1[63:32]
DEST[63:32] ← SRC1[95:64] - SRC1[127:96]
DEST[95:64] ← SRC2[31:0] - SRC2[63:32]
DEST[127:96] ← SRC2[95:64] - SRC2[127:96]
DEST[159:128] ← SRC1[159:128] - SRC1[191:160]
DEST[191:160] ← SRC1[223:192] - SRC1[255:224]
DEST[223:192] ← SRC2[159:128] - SRC2[191:160]
DEST[255:224] ← SRC2[223:192] - SRC2[255:224]
--------------*/

#include <iostream>

int main( )
{
	alignas( 32 ) float fSrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	alignas( 32 ) float fSrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	alignas( 32 ) float HaddPS[8] = { 0.f };
	alignas( 32 ) float HsubPS[8] = { 0.f };

	alignas( 32 ) double dSrcA[4] = { 1.0, 2.0, 3.0, 4.0 };
	alignas( 32 ) double dSrcB[4] = { 2.0, 2.0, 2.0, 2.0 };

	alignas( 32 ) double HaddPD[4] = { 0.f };
	alignas( 32 ) double HsubPD[4] = { 0.f };

	__asm
	{
		vmovaps ymm0, fSrcA
		vmovaps ymm1, fSrcB

		vhaddps ymm2, ymm1, ymm0
		vmovaps HaddPS, ymm2

		vhsubps ymm2, ymm1, ymm0
		vmovaps HsubPS, ymm2

		vmovapd ymm0, dSrcA
		vmovapd ymm1, dSrcB

		vhaddpd ymm2, ymm1, ymm0
		vmovapd HaddPD, ymm2

		vhsubpd ymm2, ymm1, ymm0
		vmovapd HsubPD, ymm2
	}

	std::cout << "HaddPS : ";
	for ( float elem : HaddPS )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "HSubPS : ";
	for ( float elem : HsubPS )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "HaddPD : ";
	for ( double elem : HaddPD )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "HSubPD : ";
	for ( double elem : HsubPD )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}