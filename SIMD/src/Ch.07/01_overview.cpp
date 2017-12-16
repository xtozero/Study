/*--------------
Vector 클래스는 intrinsic 함수를 개선하기 위해 제공되는 라이브러리이다.
intrinsic 함수가 어셈블리 언어의 SIMD 명령어 세트 보다는 사용하기 편리하지만 데이터 형식에 맞는 함수를 찾아야 하고
코드가 길어지는 단점이 있다. 이것을 개선하기 위해 제공된 것이 인텔 SIMD Vector 클래스이다.
덧셈 구현 방법을 통해 SIMD 명령어, intrinsic 함수, Vector 클래스를 비교하면 다음과 같다.

SIMD 명령어
----------
_asm
{
	movdqu xmm0, a
	movdqu xmm1, b
	paddsw xmm0, xmm1
	movdqu c, xmm0
}
----------

intrinsic 함수
----------
#include <emmintrin.h>

__m128i xmmA = _mm_loadu_si128( reinterpret_cast<__m128i*>( a ) )
__m128i xmmB = _mm_loadu_si128(	reinterpret_cast<__m128i*>( b ) )
xmmA = _mm_add_epi16( xmmA, xmmB );
_mm_storeu_si128( reinterpret_cast<__m128i*>( c ), xmmA );
----------

Vector 클래스
----------
#include <dvec.h>
Is16vec8 A, B, C
C = A + B
----------

명명법
Vector 클래스 이름은 다음과 같이 이루어진다.
<type><signedness><bits>vec<elements>
{ F | I } { s | u } { 64 | 32 | 16 | 8 } vec { 8 | 4 | 2 | 1 }

<type> : 해당 클래스가 어떤 변수 형을 지원하는지를 나타낸다.
F : 실수형 변수를 나타내게 된다.
I : 정수형 변수를 나타내게 된다.

<signedness> : 해당 클래스가 어떤 부호형을 지원하는지를 나타낸다.
s : signed
u : unsigned

<bits> : 해당 클래스가 포함하고 있는 pack의 크기를 나타낸다.
64 : 64bit 로 double 또는 __int64 형을 나타낸다.
32 : 32bit 로 float 또는 int 형을 나타낸다.
16 : 16bit 로 short 형을 나타낸다.
8 : 8bit 로 byte 형을 나타낸다.

<elements> : 내포하고 있는 pack의 개수를 나타낸다.
8, 4, 2 ,1의 개수를 나타내면 pack 사이즈와 곱하여 128bit를 넘을 수 없다.

정수형 pack을 담을 수 있는 Vector 클래스의 목록은 다음과 같다.
class			부호				pack 데이터 타입			pack 사이즈		pack 개수		헤더 파일
I128vec1		unspecified		__128i					128				1				dvec.h
I64vec2			unspecified		__int64					64				2				dvec.h	
Is64vec2		signed			__int64					64				2				dvec.h
Iu64vec2		unsigned		__int64					64				2				dvec.h
I32vec4			unspecified		int						32				4				dvec.h
Is32vec4		signed			int						32				4				dvec.h
Iu32vec4		unsigned		int						32				4				dvec.h
I16vec8			unspecified		short					16				8				dvec.h	
Is16vec8		signed			short					16				8				dvec.h
Iu16vec8		unsigned		short					16				8				dvec.h
I8vec16			unspecified		char					8				16				dvec.h
Is8vec16		signed			char					8				16				dvec.h
Iu8vec16		unsigned		char					8				16				dvec.h
--------------*/
