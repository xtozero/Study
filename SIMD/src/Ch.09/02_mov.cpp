/*--------------
AVX 어셈블리 명령어는 정수형, 실수형 모두 3항 연산으로 변화하였고, 실수형에 대해 256bit ymm 레지스터를 사용할 수 있다.

기존 SSE 명령어에 v 접두사가 추가되어 일관되게 AVX 명령어를 사용할 수 있다.

명령어					SSE							AVX							변경점
실수형 데이터 이동		movups xmm0, [eax+esi]		vmovups ymm0, [eax+esi]		256bit 레지스터
실수형 덧셈				addps xmm0, xmm1			vaddps ymm2, ymm1, ymm0		256bit 레지스터
실수형 곱셈				mulps xmm0, xmm1			vmulps ymm2, ymm1, ymm0		256bit 레지스터
정수 데이터 이동			movdqu xmm0, [eax+esi]		vmovdqu xmm0, [eax+esi]		
정수형 곱셈				pmullw xmm0, xmm1			vpmullw xmm2, xmm0, xmm1	3항 연산
정수형 뺄셈				psubw xmm2, xmm0			vpsubw xmm2, xmm0, xmm1		3항 연산
정수형 덧셈				paddw xmm2, xmm1			vpaddw xmm2, xmm0, xmm1		3항 연산

실수형 package의 데이터 읽고 쓰기
256bit의 vector 연산을 하기 위해서 연속된 float형 데이터를 ymm 레지스터에 대입하고 연산완료 후에는 256bit의 데이터를 메모리로 출력해야 한다.
이를 위해 사용하는 명령어가 vmovaps와 vmovups이다.

사용 문법					pack 사이즈			연산 기능
vmovaps ymm1, ymm2/m256		32bit float			32bit 형 실수 8개를 읽고 쓴다. 메모리는 정렬되어 있어야 한다.
vmovapd ymm1, ymm2/m256		64bit double		64bit 형 실수 4개를 읽고 쓴다. 메모리는 정렬되어 있어야 한다.
vmovups ymm1, ymm2/m256		32bit float			32bit 형 실수 8개를 읽고 쓴다. 메모리는 정렬되어 있지 않아도 된다.
vmovupd ymm1, ymm2/m256		64bit double		64bit 형 실수 4개를 읽고 쓴다. 메모리는 정렬되어 있지 않아도 된다.
--------------*/

#include <iostream>

int main( )
{
	float SrcUnalign[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float DestUnalign[8] = { 0.f };

	__asm
	{
		vmovups ymm0, SrcUnalign
		vmovups DestUnalign, ymm0
	}

	for ( float elem : DestUnalign )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	alignas( 32 ) float SrcAlign[8] = { 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f };
	alignas( 32 ) float DestAlign[8] = { 0.f };

	__asm
	{
		vmovaps ymm0, SrcAlign
		vmovaps DestAlign, ymm0 
	}

	for ( float elem : DestAlign )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}