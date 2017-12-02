/*--------------
MMX 에서는 64bit 정수형 package 연산만 가능하였으나 SSE에서는 128bit package에 32bit float 실수 자료형에 대한 병렬 연산이 가능하다.

__m128 : 32bit float 형 실수 데이터 4개를 담을 수 있는 128bit 데이터형을 의미한다.
xmmintrin.h 파일 안에 __m128 데이터형은 다음과 같이 정의되어 있다.

typedef union __declspec(intrin_type) __declspec(align(16)) __m128 {
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

명명법
_mm_<intrin_op>_<suffix>

_mm_ : intrinsic 함수임
<intrin_op> : 실제로 수행할 연산
<suffix> : ps( packed single-precision floating point ), ss( scalar single-precision floating point )을 의미
--------------*/
