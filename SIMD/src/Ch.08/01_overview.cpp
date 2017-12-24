/*--------------
MMX에서 SEE로 발전하면서 128bit 실수형 병렬 연산이 가능해졌다.
SSE2 기술로 발전하면서 128bit 데이터형에 64bit double형 실수 2개를 담아 계산하는 기능도 추가되었다.
실수 Vector 클래스는 32bit SIMD 연산과 64bit SIMD 연산을 담당하는 클래스로 나누어져 있다.
내부적으로는 32bit intrinsic 함수와 64bit intrinsic 함수를 포함하는 래핑 클래스이다.

명명법
F32vec4
F63vec2

F : 실수형을 가진 Vector 클래스임을 나타낸다.
32 : pack에 있는 데이터의 사이즈를 나타낸다.
vec : Vector 클래스를 뜻한다.
4 : 32bit pack이 4개 들어 있음을 나타낸다.

실수형 vector 클래스의 종류는 다음과 같다.
class			pack 데이터 타입			pack 사이즈		pack 개수		헤더 파일
F64vec2			double					64				2				dvec.h
F32vec4			float					32				4				fvec.h
F32vec1			float					32				1				fvec.h
--------------*/
