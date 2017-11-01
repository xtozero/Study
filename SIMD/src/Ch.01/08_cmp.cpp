#include <iostream>

//--------------
// �� ������ sub������ �⺻���� ��Ʈ �÷��׿� �� ���� ������, �� ū�� �������� ���
// ��ȣ ���� ������ ��� ZF(zero flag), CF(carry falg)
// ���� ���� VL, ������ ���� VR�̶� �ϸ�
// �� ���� ������ ZF 1, CF 0 ( VL - VR = 0 )
// VR �� �� Ŭ��� ZF 0, CF 1 ( VL - VR < 0 )
// VL �� �� Ŭ��� ZF 0, CF 0
// ��ȣ �ִ� ������ ��� ZF, SF(sign flag), OF(overflow flag)
// �� ���� ������ ZF 0
// VL - VR ����� ������ ��� SF 1 => VL �� �� Ŭ��� OF 1, VR �� �� Ŭ��� OF 0
// VL - VR ����� ����� ��� SF 0 => VL �� �� Ŭ��� OF 0, VR �� �� Ŭ��� OF 1
// cmp reg, reg
// cmp reg, mem
// cmp mem, reg
//--------------

int main( )
{
	__asm
	{
		mov eax, 5;
		cmp eax, 8
	}
}