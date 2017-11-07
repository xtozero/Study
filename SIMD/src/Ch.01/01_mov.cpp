#include <iostream>

/*--------------
mov 범용 레지스터, 범용 레지스터	->		mov reg, reg
mov 범용 레지스터, 메모리(변수)	->		mov reg, mem
mov 메모리(변수), 범용 레지스터	->		mov mem, reg
mov 범용 레지스터, 상수			->		mov reg, imm
mov 메모리(변수), 상수			->		mov mem, imm
--------------*/

int main( )
{
	int a = 1;
	int nValue;

	__asm
	{
		mov eax, 1		// eax = 1
		mov nValue, 2	// nValue = 2
	}

	std::cout << "nValue : " << nValue << std::endl;
	return 0;
}