#include <iostream>

//--------------
// mov ���� ��������, ���� ��������	->		mov reg, reg
// mov ���� ��������, �޸�(����)	->		mov reg, mem
// mov �޸�(����), ���� ��������	->		mov mem, reg
// mov ���� ��������, ���			->		mov reg, imm
// mov �޸�(����), ���				->		mov mem, imm
//--------------

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