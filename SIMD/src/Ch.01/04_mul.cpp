#include <iostream>

//--------------
// �ǽ¼��� eax, �¼��� �ٸ� �޸� Ȥ�� �������� ���. ����� eax�� ����.
// mul reg
// mul mem
//--------------

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