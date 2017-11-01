#include <iostream>

//--------------
// jp Ȥ�� jmp (jump)			������ ����
// je	(jump equal)			�� ���� ������ ����
// jne	(jump not equal)		�� ���� �ٸ��� ����
// jz	(jump zero)				���� 0�̸� ����
// jnz	(jump not zero)			���� 0�� �ƴϸ� ����
// jg	(jump greater)			���� �� ũ�� ����
// jge	(jump greater equal)	���� ũ�ų� ������ ����
// jl	(jump less)				���� �� ������ ����
// jle	(jump less equal)		���� �۰ų� ������ ����
//--------------

int main( )
{
	/*
	int nValue = 0;
	for ( int eax = 0; eax < 1000; eax++ )
		nValue = eax;
	*/
	int nValue = 0;
	__asm
	{
		pushad
		mov eax, nValue		// eax = nValue
SIMDLOOP:
		inc eax				// eax++
		cmp eax, 1000		// if ( eax != 1000 )
		jne SIMDLOOP		// goto LOOP
		mov nValue, eax		// nValue = eax
		popad
	}

	std::cout << "Result : " << nValue << std::endl;

	// Do while�� ����� ������ �ۼ��ϴ� ����
	nValue = 1000;
	__asm
	{
		pushad
		mov eax, nValue
WHILE:
		// �ݺ� ���� �ڵ� �ۼ�
		dec eax			// eax-- => dec ����� eax ���� 0�� �Ǵ� ���� ZF�� 1�� ����
		jnz WHILE	// if ( eax != 0 ) goto WHILE
		mov nValue, eax
		popad
	}

	std::cout << "Result : " << nValue << std::endl;

	return 0;
}