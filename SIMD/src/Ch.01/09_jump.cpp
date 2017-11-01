#include <iostream>

//--------------
// jp 혹은 jmp (jump)			무조건 점프
// je	(jump equal)			두 값이 같으면 점프
// jne	(jump not equal)		두 값이 다르면 점프
// jz	(jump zero)				값이 0이면 점프
// jnz	(jump not zero)			값이 0이 아니면 점프
// jg	(jump greater)			값이 더 크면 점프
// jge	(jump greater equal)	값이 크거나 같으면 점프
// jl	(jump less)				값이 더 작으면 점프
// jle	(jump less equal)		값이 작거나 같으면 점프
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

	// Do while과 비슷한 구조로 작성하는 예제
	nValue = 1000;
	__asm
	{
		pushad
		mov eax, nValue
WHILE:
		// 반복 연산 코드 작성
		dec eax			// eax-- => dec 수행시 eax 값이 0이 되는 순간 ZF가 1로 세팅
		jnz WHILE	// if ( eax != 0 ) goto WHILE
		mov nValue, eax
		popad
	}

	std::cout << "Result : " << nValue << std::endl;

	return 0;
}