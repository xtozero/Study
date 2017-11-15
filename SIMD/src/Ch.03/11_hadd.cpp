#include <iostream>

/*--------------
2���� 128bit xmm�������͸� �Է¹޾� �¿쿡 �ִ� ���� ���Ͽ� ����� ���´�.
������ ���� ���� �������� ���� ���ϴ� �Ϳ��� ����������� ���� ���� �� �ֵ��� �ϴ� ��ɾ��̴�.

ù ��° ���������� 1,2 pack�� ���� dest�� ù ��° pack�� �ְ� ù ��° ���������� 3, 4�� pack�� ���ļ� dest�� 2��° pack�� �ִ´�.
�� ��° ���������� 1,2 pack�� ���� dest�� �� ��° pack�� �ְ� �� ��° ���������� 3, 4�� pack�� ���ļ� dest�� 4��° pack�� �ִ´�.

Packed Horizontal Add

��빮��					pack size				���� ���
haddps					32bit float				32bit float�� �Ǽ� 8���� ���� ���� ���� ���� ���Ѵ�.
haddpd					64bit double			64bit double�� �Ǽ� 4���� ���� ���� ���� ���� ���Ѵ�.
--------------*/

int main( )
{
	float SrcA[4] = { 1.f, 2.f, 3.f, 4.f };
	float SrcB[4] = { 5.f, 6.f, 7.f, 8.f };

	float Result[4] = { 0.f };

	__asm
	{
		movups xmm0, SrcA
		movups xmm1, SrcB

		haddps xmm0, xmm1	// 8 + 7, 6 + 5, 4 + 3, 2 + 1

		movups Result, xmm0
	}

	std::cout << "HADDPS : ";
	for ( float elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}