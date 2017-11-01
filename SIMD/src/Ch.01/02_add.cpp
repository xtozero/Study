#include <iostream>

//--------------
// add reg, reg
// add reg, mem
// add mem, reg
// add reg, imm
// add mem, imm
//--------------

int main( )
{
	int A = 5;
	int B = 7;
	int C = 0;

	__asm
	{
		pushad			// 사용하고 있던 레지스터의 값을 스택에 push로 저장
		mov eax, A
		mov ebx, B
		add eax, ebx	// eax += ebx
		mov C, eax
		popad			// 스택에 저장했던 레지스터 값을 pop하여 복구
	}

	std::cout << "5 + 7 ADD Result : " << C << std::endl;

	return 0;
}