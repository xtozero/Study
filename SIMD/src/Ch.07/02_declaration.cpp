/*--------------
일반 클래스와 같이 데이터형을 명시하고 이름을 선언하면 객체가 생성된다.

Is16vec8 A;

정수 Vector 클래스는 내부적으로 __m128i 데이터를 내포하고 있다.
class M128	// M128을 상속받는다.
{
protected:
__m128i vec;

public:
	멤버 함수...
};

__m128i 데이터를 이용해서 객체를 초기화할 수도 있고 각각에 맞는 데이터형으로 초기화할 수도 있다.
I16vec8(__m128i _Mm);
I16vec8(short _S7, short _S6, short _S5, short _S4, short _S3, short _S2, short _S1, short _S0);

임시 객체를 생성하여 사용할 수도 있다.
Is32vec4 R = Is32vec4( 3, 2, 1, 0 ) + Is32vec4( 0, 1, 2, 3 );

정수형 Vector간에는 어떤 형태도 서로 대입 연산할 수 있다.
Is16vec4 A;
Is8vec8 B;
I64vec1 C;

A = B;
B = C;
B = A & C;
--------------*/
