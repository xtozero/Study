/*--------------
SIMD 명령어를 이용한 구현은 어셈블리 언어 구조이므로 루프 문에 대한 구현, 레지스터 개수 제한, 디버깅의 어려움 등의 단점이 있다.
인텔에서는 이런 점을 보안하기 위해 intrinsic 함수를 제공한다. 
intrinsic 함수를 사용하면 C/C++환경에 익숙한 루프와, 조건문, 코드의 가독성, 보다 나은 디버깅 환경을 얻을 수 있다.

명명법
_mm_<intrin_op>_<suffix>

_mm_ : SIMD의 intrinsic 함수를 의미한다.
<intrin_op> : 실제로 동작할 연산자를 의미한다.
<suffix> : 사용하게 될 인자의 데이터 타입과 사이즈, packed 혹은 scalar와 같은 정보가 들어가게 된다.
두 개의 문자가 포함되는데 첫 번째는 p(packed), ep(extended packed), s(scalar)가 들어간다.
두 번째 들어갈 문자는 데이터형의 크기로 결정되며 들어가는 문자는 다음과 같다.

문자			데이터 타입
s			32 bit 실수형 ( single-precision floating point )
d			64 bit 실수형 ( double-precision floating point )	
i128		128bit signed 정수 ( signed 128-bit integer )
i64			64bit signed 정수 ( signed 64-bit integer )
u64			64bit unsigned 정수 ( unsigned 64-bit integer )
i32			32bit signed 정수 ( signed 32-bit integer )
u32			32bit unsigned 정수 ( unsigned 32-bit integer )
i16			16bit signed 정수 ( signed 16-bit integer )
u16			16bit unsigned 정수 ( unsigned 16-bit integer )
i8			8bit signed 정수 ( signed 8-bit integer )
u8			8bit unsigned 정수 ( unsigned 8-bit integer )

128bit 정수형 데이터 타입

명명법
__m128i

__m : intrinsic 데이터 타입임을 나타낸다.
128 : 데이터형의 사이즈이다.
i : 정수형을 의미한다.

intrinsic 함수를 사용하기 위해서는 다음과 같은 헤더 파일을 포함해야 한다.
SSE2 : emmintrin.h
SSE3 : pmmintrin.h
SSE4 : smmintrin.h, nmmintrin.h
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	__m128i _128_int_type;
	/*
	typedef union __declspec(intrin_type) __declspec(align(16)) __m128i {
	__int8              m128i_i8[16];
	__int16             m128i_i16[8];
	__int32             m128i_i32[4];
	__int64             m128i_i64[2];
	unsigned __int8     m128i_u8[16];
	unsigned __int16    m128i_u16[8];
	unsigned __int32    m128i_u32[4];
	unsigned __int64    m128i_u64[2];
	} __m128i;
	*/

	__m128  _128_bit_type;
	/*
	typedef union __declspec( intrin_type ) __declspec( align( 16 ) ) __m128 {
		float               m128_f32[4];
		unsigned __int64    m128_u64[2];
		__int8              m128_i8[16];
		__int16             m128_i16[8];
		__int32             m128_i32[4];
		__int64             m128_i64[2];
		unsigned __int8     m128_u8[16];
		unsigned __int16    m128_u16[8];
		unsigned __int32    m128_u32[4];
	} __m128;
	*/

	return 0;
}