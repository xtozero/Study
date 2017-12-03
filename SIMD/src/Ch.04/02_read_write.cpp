/*--------------
메모리에서 데이터 읽기
byte, short, integer, __int64로 이뤄진 정수형 메모리 배열에서 __m128i 데이터형으로 값을 가져온다.

__m128i r = _mm_load_si128( __m128i const* p )
__m128i r = _mm_loadu_si128( __m128i const* p )

intrinsic 함수		연산 방식			SIMD 명령어
_mm_load_si128		읽기					MOVDQU
_mm_loadu_si128		읽기					MOVDQA
_mm_loadl_epi64		하위 64bit 읽기		MOVQ

메모리에 데이터 쓰기
__m128i 데이터형에 있는 데이터를 byte, short, integer, __int64로 이뤄진 정수형 메모리 배열에 쓴다.

void _mm_store_si128( __m128i *p, __m128 b )
void _mm_storeu_si128( __m128i *p, __m128 b )

intrinsic 함수			SIMD 명령어		연산 방식
_mm_stream_si128		MOVNTDQ			저장하기				
_mm_stream_si32			MOVNTI			저장하기				
_mm_store_si128			MOVDQU			저장하기				
_mm_storeu_si128		MOVDQA			저장하기				
_mm_maskmoveu_si128		MASKMOVDQU		상태 저장			
_mm_storel_epi64		MOVQ			하위 64bit 저장		
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	// 정렬된 메모리 사용
	{
		alignas( 16 ) short Source[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		alignas( 16 ) short Dest[8] = { 0 };

		__m128i xmmA = _mm_load_si128( reinterpret_cast<__m128i*>( Source ) );
		__m128i xmmB = xmmA;
		_mm_store_si128( reinterpret_cast<__m128i*>( Dest ), xmmB );

		std::cout << "Dest : ";
		for ( short elem : Dest )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	// 정렬되지 않은 메모리 사용
	{
		short Source[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		short Dest[8] = { 0 };

		__m128i xmmA = _mm_loadu_si128( reinterpret_cast<__m128i*>( Source ) );
		__m128i xmmB = xmmA;
		_mm_storeu_si128( reinterpret_cast<__m128i*>( Dest ), xmmB );

		std::cout << "Dest : ";
		for ( short elem : Dest )
		{
			std::cout << elem << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}