#include <iostream>

//--------------
// ���� ������ ++
// inc reg
// inc mem
// ���� ������ --
// dec reg
// dec mem
//--------------

int main( )
{
	int A = 1;
	int B = 3;

	__asm
	{
		pushad
		mov eax, A
		inc eax			// eax++
		mov A, eax
		dec B			// B--
		popad
	}

	std::cout << "INC Result : " << A << " / DEC Result : " << B << std::endl;
	return 0;
}