#include <iostream>

#include "../Util/StopWatch.h"

/*--------------
prefetch
명령어 뒤에 메모리 주소를 두면 직전 메모리 주소부터 해당 주소 번지까지 미리 캐시에 읽어 들여 메모리 로딩 시간을 단축한다.

사용문법					연산 기능
prefetch0 m8			모든 캐시 level에 임시 데이터를 미리 읽도록 한다.
prefetch1 m8			L1 캐시 level에 임시 데이터를 미리 읽도록 한다.
prefetch2 m8			L2 캐시 level에 임시 데이터를 미리 읽도록 한다.
prefetchnta m8			모든 캐시 level에 데이터를 미리 읽도록 한다.

lfence
prefetch 명령은 멀티 스레딩, 멀티코어에서 작동이 보장되지 않는다. 따라서 멀티 스레딩, 멀티코어로 프로그램 작성 시에는 prefetch 명령어를 사용한 후 lfence를 적어준다.

movnts ( MOVE NONTEMPORAL HINT )
prefetch와 반대로 레지스터의 내용을 메모리에 쓸 때 캐시를 거치지 않게 한다.
'다시 사용할 내용'이 아니라면 캐시에 적지 않고 바로 메모리에 쓰는 것이 빠르다.

사용문법					연산 기능
movntdqa xmm, m128		Align된 메모리에 캐시를 거치지 않고 128bit 데이터를 쓴다.
movntdq m128, xmm		메모리에 캐시를 거치지 않고 128bit 데이터를 쓴다.
movntpd m128, xmm		64bit double형 실수 2 개를 가진 데이터를 캐시를 거치지 않고 메모리에 쓴다.
movntps m128, xmm		32bit float형 실수 4 개를 가진 데이터를 캐시를 거치지 않고 메모리에 쓴다.

sfence
movnts 명령어는 멀티 스레딩, 멀티코어에서 작동이 보장되지 않는다. 따라서 멀티 스레딩, 멀티코어로 프로그램 작성 시에는 movnts 명령어를 사용한 후 sfence를 적어준다.
--------------*/

// SIMD를 이용한 간단한 Memcpy함수. 128의 배수 크기만 정상적으로 처리가 가능.
void MemcpySIMD( char* pSrc, char* pDest, int Size )
{
	int loopSize = Size / 128;

	__asm
	{
		pushad
		mov ecx, loopSize
		mov eax, pSrc
		mov edx, pDest
		mov esi, 0

	MEMLP:
		movdqa xmm0, [eax + esi]
		movdqa xmm1, [eax + esi + 16]
		movdqa xmm2, [eax + esi + 32]
		movdqa xmm3, [eax + esi + 48]
		movdqa xmm4, [eax + esi + 64]
		movdqa xmm5, [eax + esi + 80]
		movdqa xmm6, [eax + esi + 96]
		movdqa xmm7, [eax + esi + 112]

		movdqa [edx + esi], xmm0
		movdqa [edx + esi + 16], xmm1
		movdqa [edx + esi + 32], xmm2
		movdqa [edx + esi + 48], xmm3
		movdqa [edx + esi + 64], xmm4
		movdqa [edx + esi + 80], xmm5
		movdqa [edx + esi + 96], xmm6
		movdqa [edx + esi + 112], xmm7

		add esi, 128
		dec ecx
		jnz MEMLP

		popad
	}
}

// MemcpySIMD1에서 인덱싱 방법만 약간 변경
void MemcpySIMD2( char* pSrc, char* pDest, int Size )
{
	int loopSize = Size / 128;

	__asm
	{
		pushad
		mov ecx, loopSize
		mov eax, pSrc
		mov edx, pDest

	MEMLP:
		movdqa xmm0, [eax]
		movdqa xmm1, [eax + 16]
		movdqa xmm2, [eax + 32]
		movdqa xmm3, [eax + 48]
		movdqa xmm4, [eax + 64]
		movdqa xmm5, [eax + 80]
		movdqa xmm6, [eax + 96]
		movdqa xmm7, [eax + 112]

		movdqa [edx], xmm0
		movdqa [edx + 16], xmm1
		movdqa [edx + 32], xmm2
		movdqa [edx + 48], xmm3
		movdqa [edx + 64], xmm4
		movdqa [edx + 80], xmm5
		movdqa [edx + 96], xmm6
		movdqa [edx + 112], xmm7

		add eax, 128
		add edx, 128
		dec ecx
		jnz MEMLP

		popad
	}
}

// movntdq 를 통해서 캐시를 거치지 않고 메모리에 기록하는 버전
void MemcpySIMD3( char* pSrc, char* pDest, int Size )
{
	int loopSize = Size / 128;

	__asm
	{
		pushad
		mov ecx, loopSize
		mov eax, pSrc
		mov edx, pDest

	MEMLP :
		movdqa xmm0, [eax]
		movdqa xmm1, [eax + 16]
		movdqa xmm2, [eax + 32]
		movdqa xmm3, [eax + 48]
		movdqa xmm4, [eax + 64]
		movdqa xmm5, [eax + 80]
		movdqa xmm6, [eax + 96]
		movdqa xmm7, [eax + 112]

		movntdq [edx], xmm0
		movntdq [edx + 16], xmm1
		movntdq [edx + 32], xmm2
		movntdq [edx + 48], xmm3
		movntdq [edx + 64], xmm4
		movntdq [edx + 80], xmm5
		movntdq [edx + 96], xmm6
		movntdq [edx + 112], xmm7

		add eax, 128
		add edx, 128
		dec ecx
		jnz MEMLP
		sfence

		popad
	}
}

int main( )
{
	constexpr int BuffSize = 100000000;
	char* pChar = new char[BuffSize];
	char* pChar2 = new char[BuffSize];

	for ( int i = 0; i < BuffSize; ++i )
	{
		pChar[i] = 5;
	}

	CStopWatch StopWatch;

	StopWatch.Start( );
	MemcpySIMD( pChar, pChar2, BuffSize );
	StopWatch.End( );
	std::cout << "movdqa : " << StopWatch.GetDuration<duration<float, std::milli>>() << std::endl;

	StopWatch.Start( );
	MemcpySIMD2( pChar, pChar2, BuffSize );
	StopWatch.End( );
	std::cout << "movdqa : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	// memcpy가 캐시 처리되어 동작하여 SIMD를 사용하였을 때 성능향상을 볼 수 없었다.
	StopWatch.Start( );
	memcpy( pChar, pChar2, BuffSize );
	StopWatch.End( );
	std::cout << "memcpy : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	StopWatch.Start( );
	MemcpySIMD3( pChar, pChar2, BuffSize );
	StopWatch.End( );
	std::cout << "movnts : " << StopWatch.GetDuration<duration<float, std::milli>>( ) << std::endl;

	delete[] pChar;
	delete[] pChar2;

	return 0;
}