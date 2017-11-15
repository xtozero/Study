#include <iostream>

/*--------------
MMX가 처음 나왔을 때는 64bit 정수형 데이터 연산밖에 지원되지 않았다.
SEE로 발전하면서 실수 연산도 지원되고 데이터형도 128bit로 증가하였다.

실수 SIMD 명령어 명명법
<SIMD_op> p <suffix> => p packed를 의미
<SIMD_op> s <suffix> => s scalar를 의미

정수형 SIMD 명령어와 구분하기 위해서 실수형 SIMD의 연산자는 p가 뒤로 옮겨졌다.
<SIMD_op> 실제 연산을 수행할 내용
<suffix> 연산을 수행할 pack의 사이즈를 의미하는 접미사
pack 사이즈 접미사
ps, 32bit 형 float 실수 4개의 pack 연산
ss, 32bit 형 float 실수 1개의 연산
pd, 64bit 형 double 실수 2개의 pack 연산
sd, 64bit 형 double 실수 1개의 연산

대입 명령어
Move aligned packed values

사용문법					pack size				연산 기능
movaps					32bit float				32bit float형 실수 4개를 읽고 쓴다. 메모리가 정렬되어 있어야 한다.
movapd					64bit double			64bit double형 실수 2개를 읽고 쓴다. 메모리가 정렬되어 있어야 한다.

Move Unaligned packed values

사용문법					pack size				연산 기능
movups					32bit float				32bit float형 실수 4개를 읽고 쓴다. 메모리가 정렬되어 있지 않아도 된다.
movupd					64bit double			64bit double형 실수 2개를 읽고 쓴다. 메모리가 정렬되어 있지 않아도 된다.
--------------*/

int main( )
{
	alignas( 16 ) float SrcA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	alignas( 16 ) float ResultA[4] = { 0.f };

	float SrcB[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	float ResultB[4] = { 0.f };

	__asm
	{
		pushad
		movaps xmm0, SrcA		// xmm0 = SrcA
		movaps ResultA, xmm0	// ResultA = xmm0

		movups xmm0, SrcB
		movups ResultB, xmm0
		popad
	}

	std::cout << "align Result : ";
	for ( float elem : ResultA )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Unalign Result : ";
	for ( float elem : ResultB )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}