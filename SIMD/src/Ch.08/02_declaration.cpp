/*--------------
객체 생성법은 일반적인 클래스 생성과 같다.

F64vec2 A;
F32vec4 B;
F32vec1 C;

실수 Vector 클래스는 내부적으로 __m128, __m128d 변수를 내포하고 있다.

class F64vec2
{
protected:
__m128d vec;
public:
	멤버 함수...
};

class F32vec4
{
protected:
__m128 vec;
public:
	멤버 함수...
};

__m128, __m128d 데이터를 이용해 객체를 초기화할 수도 있고 각각에 맞는 데이터형으로 초기화할 수도 있다.
F64vec4(__m256d m);
F64vec4( double _D3, double _D2, double _D1, double _D0 );
--------------*/
