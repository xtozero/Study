#include <iostream>

/*--------------
피제수가 eax, 다른 레지스터와 메모리 값을 제수로 사용. 결괏값의 목은 eax, 나머지는 edx에 들어감.
div reg
div mem
--------------*/

int main( )
{
	int A = 5;
	int B = 0;
	int C = 0;

	__asm
	{
		pushad
		mov eax, 17
		cdq				// 32bit를 64bit로 확장 convert dobule word to quad word 의 약자
		mov ebx, A
		div ebx			// eax /= ebx
		mov B, eax
		// edx = eax % ebx
		mov C, edx
		popad
	}

	std::cout << "17/5 DIV Result : " << B << ", " << C << std::endl;
}