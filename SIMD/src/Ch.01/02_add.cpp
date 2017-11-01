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
		pushad			// ����ϰ� �ִ� ���������� ���� ���ÿ� push�� ����
		mov eax, A
		mov ebx, B
		add eax, ebx	// eax += ebx
		mov C, eax
		popad			// ���ÿ� �����ߴ� �������� ���� pop�Ͽ� ����
	}

	std::cout << "5 + 7 ADD Result : " << C << std::endl;

	return 0;
}