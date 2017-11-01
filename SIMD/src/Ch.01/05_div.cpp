#include <iostream>

//--------------
// �������� eax, �ٸ� �������Ϳ� �޸� ���� ������ ���. �ᱣ���� ���� eax, �������� edx�� ��.
// div reg
// div mem
//--------------

int main( )
{
	int A = 5;
	int B = 0;
	int C = 0;

	__asm
	{
		pushad
		mov eax, 17
		cdq				// 32bit�� 64bit�� Ȯ�� convert dobule word to quad word �� ����
		mov ebx, A
		div ebx			// eax /= ebx
		mov B, eax
		// edx = eax % ebx
		mov C, edx
		popad
	}

	std::cout << "17/5 DIV Result : " << B << ", " << C << std::endl;
}