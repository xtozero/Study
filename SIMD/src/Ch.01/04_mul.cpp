#include <iostream>

/*--------------
피승수는 eax, 승수는 다른 메모리 혹은 레지스터 사용. 결과는 eax에 저장.
mul reg
mul mem
--------------*/

int main( )
{
	int A = 5;
	int C = 0;

	__asm
	{
		pushad
		mov ebx, 15
		mov eax, A
		mul ebx		// eax *= ebx
		mov C, eax
		popad
	}

	std::cout << "15 * 5 MUL Result : " << C << std::endl;
}