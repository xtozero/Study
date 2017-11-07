#include <iostream>

/*--------------
sub reg, reg
sub reg, mem
sub mem, reg
sub reg, imm
sub mem, imm
--------------*/

int main( )
{
	int A = 5;
	int B = 7;
	int C = 0;

	__asm
	{
		pushad
		mov eax, A
		mov ebx, B
		sub eax, ebx	// eax -= ebx
		mov C, eax
		popad
	}

	std::cout << "5 - 7 SUB Result : " << C << std::endl;
	return 0;
}