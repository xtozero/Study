#include <iostream>

/*--------------
왼쪽 방향 shift
shl reg, imm8	imm8은 int형 상수를 의미
shl m32, imm8
오른쪽 방향 shift
shr reg, imm8
shr m32, imm8
--------------*/

int main( )
{
	int nValue = 8;
	__asm
	{
		pushad
		mov eax, nValue
		shl eax, 1			// eax << 1; 8 * 2 = 16
		mov nValue, eax
		popad
	}

	std::cout << "SHL Result : " << nValue << std::endl;

	__asm
	{
		pushad
		mov eax, nValue
		shr eax, 2			// eax >> 2; 16 / 4 = 4
		mov nValue, eax
		popad
	}

	std::cout << "SHR Result : " << nValue << std::endl;
	return 0;
}