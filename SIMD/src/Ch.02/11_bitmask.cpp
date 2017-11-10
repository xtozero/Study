#include <iostream>

/*--------------
XMM 레지스터의 값을 1Byte씩 읽어서 범용 레지스터에 최상위 첫번째 bit만을 기록한다.
     
	 1byte        11byte   12byte   13byte   14byte   15byte   16byte
xmm0 00000000 ... 00000000 00000000 11111111 00000000 11111111 11111111
     ^            ^                 ^        ^        ^        ^
eax 0000000000001011

PMOVMSKB( Move Byte Mask )
사용문법
pmovmskb r32, xmm
--------------*/

int main( )
{
	char CharArray[16] = { 0xff, 0xff, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	int mask = 0;

	__asm
	{
		pushad
		movdqu xmm0, CharArray
		pmovmskb eax, xmm0
		mov mask, eax
		popad
	}

	std::cout << "mask = " << mask << std::endl;

	return 0;
}