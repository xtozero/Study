#include <iostream>

/*--------------
다음 명령어는 SSE 4.1부터 지원한다.

Extract 명령어는 128bit 레지스터에 있는 pack 값을 꺼내오는 기능을 한다.
imm8이 지정하는 위치에 있는 pack 값을 꺼내서 범용 레지스터나 메모리 변수에 넣는다.
imm8은 상수만 넣을 수 있다.
사용문법						pack size			연산 기능
pextrb r32/m8, xmm, imm8		8bit byte			imm8 상수가 지정하는 8bit pack의 값을 꺼내온다.
pextrw r32/m16, xmm, imm8		16bit short			imm8 상수가 지정하는 16bit pack의 값을 꺼내온다.
pextrd r32/m32, xmm, imm8		32bit interger		imm8 상수가 지정하는 32bit pack의 값을 꺼내온다.
pextrq r64/m64, xmm, imm8		64bit __int64		imm8 상수가 지정하는 64bit pack의 값을 꺼내온다.

Insert 명령어는 범용 레지스터나 메모리 변수의 값을 imm8이 지정하는 위치에 있는 pack에 입력한다.
imm8에는 상수만 넣을 수 있다.
사용문법						pack size			연산 기능
pinsrb xmm, r32/m8, imm8		8bit byte			imm8 상수가 지정하는 위치에 8bit pack의 값을 입력한다.
pinsrw xmm, r32/m16, imm8		16bit short			imm8 상수가 지정하는 위치에 16bit pack의 값을 입력한다.
pinsrd xmm, r32/m32, imm8		32bit interger		imm8 상수가 지정하는 위치에 32bit pack의 값을 입력한다.
pinsrq xmm, r64/m64, imm8		64bit __int64		imm8 상수가 지정하는 위치에 64bit pack의 값을 입력한다.
--------------*/

int main( )
{
	short SourceA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	short SourceB[8] = { 0 };

	short Result[8] = { 0 };

	int Value = 0;

	__asm
	{
		pushad
		movdqu xmm0, SourceA
		pextrw eax, xmm0, 2
		mov Value, eax

		mov eax, 8
		movdqu xmm0, SourceB
		pinsrw xmm0, eax, 4
		movdqu Result, xmm0
		popad
	}

	std::cout << "Pextrw : " << Value << std::endl;
	std::cout << "Pinsrw : ";
	for ( short elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}