#include <iostream>

/*--------------
비교 구문은 sub연산을 기본으로 비트 플래그에 두 값이 같은지, 더 큰지 작은지를 기록
부호 없는 정수의 경우 ZF(zero flag), CF(carry falg)
왼쪽 값을 VL, 오른쪽 값을 VR이라 하면
두 값이 같으면 ZF 1, CF 0 ( VL - VR = 0 )
VR 이 더 클경우 ZF 0, CF 1 ( VL - VR < 0 )
VL 이 더 클경우 ZF 0, CF 0
부호 있는 정수의 경우 ZF, SF(sign flag), OF(overflow flag)
두 값이 같으면 ZF 0
VL - VR 결과가 음수인 경우 SF 1 => VL 이 더 클경우 OF 1, VR 이 더 클경우 OF 0
VL - VR 결과가 양수인 경우 SF 0 => VL 이 더 클경우 OF 0, VR 이 더 클경우 OF 1
cmp reg, reg
cmp reg, mem
cmp mem, reg
--------------*/

int main( )
{
	__asm
	{
		mov eax, 5;
		cmp eax, 8
	}
}