/*--------------
double형 실수에 대한 intrinsic 데이터형은 128bit 크기이므로 2개의 double형 변수를 담을 수 있다.

__m128d : 64bit double 형 실수 데이터 2개를 담을 수 있는 128bit 데이터형을 의미한다.
emmintrin.h 파일 안에 __m128 데이터형은 다음과 같이 정의되어 있다.

typedef struct __declspec(intrin_type) __declspec(align(16)) __m128d {
double              m128d_f64[2];
} __m128d;


명명법
_mm_<intrin_op>_<suffix>

_mm_ : intrinsic 함수임
<intrin_op> : 실제로 수행할 연산
<suffix> : pd( packed double-precision floating point ), sd( scalar double-precision floating point )을 의미
--------------*/
