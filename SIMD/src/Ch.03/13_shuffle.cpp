#include <iostream>

/*--------------
Source에 있는 값과 Dest에 있는 값을 선택하여 가져올 수 있도록 조합해 준다.
Source에 있는 Pack중 2개를 선택해서 앞의 2개의 Pack에 넣고 Dest에 있는 Pack중 2개를 선택해서 뒤의 2개의 Pack에 넣는다.

위치bit 11		10		01		00
xmm0 |	4	|	3	|	2	|	1	|
		^						^

xmm1 |	8	|	7	|	6	|	5	|
				^		^

imm8				| 1001b | 1100b |

xmm0 |	7	|	6	|	4	|	1	|

사용문법							pack size			연산 기능
shufps xmm1, xmm2/m128, imm8	32bit float			2개 128bit 레지스터에서 각각 2개의 pack을 가져와서 조합한다.
shufpd xmm1, xmm2/m128, imm8	64bit double		2개 128bit 레지스터에서 각각 1개의 pack을 가져와서 조합한다.
--------------*/

int main( )
{
	float SrcA[4] = { 1.f, 2.f, 3.f, 4.f };
	float SrcB[4] = { 5.f, 6.f, 7.f, 8.f };
	float Result[4] = { 0 };

	__asm
	{
		pushad
		movups xmm0, SrcA
		movups xmm1, SrcB

		shufps xmm0, xmm1, 10011100b

		movups Result, xmm0		// 1 4 6 7
		popad
	}

	std::cout << "SHUFPS : ";
	for ( float elem : Result )
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}