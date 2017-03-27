template <typename T, T nontype_param>
class C
{
};

C<int, 33>* cl;			// 정수형

int a;
C<int*, &a> c2;			// 외부 변수의 주소

void f( );
void f( int );
C<void( *)(int), f> c3;	// 함수의 이름 : 오버로딩 해석에 의해 f( int )를 선택

class X
{
public:
	int n;
	static bool b;
};

C<bool&, X::b>* c4;		// 정적 클래스 멤버는 수용가능

C<int X::*, &X::n>* c5;	// 멤버 접근 포인터 상수의 예

template<typename T>
void templ_func( );

C<void(*)( ), &templ_func<double>>* c6; // 함수 템플릿 인스턴스도 함수임

constexpr float fv = 10.f;
C<float, fv>* c7; // error 부동소수점 숫자는 안됨

const char* stringLiteral = "Hello Template";
C<char*, stringLiteral> c8; // error 문자열 리터럴도 안됨

// 상수 문자열로 초기화하려면 아래와 같은 방법으로 해야한다.
extern const char hello[] = "Hello World!"; // extern 빼면 const 배열 변수가 내부 링크를 가질 수 있으므로 주의
C<const char*, hello> c9;

class Base
{
public:
	int i;
} base;

class Derived : public Base
{

} derived_obj;

C<Base*, &derived_obj> err1; // error 부모 클래스로의 변환은 고려되지 않는다.

C<int&, base.i> err2; // error 클래스 변수의 멤버변수는 변수로 간주되지 않음.

int a[10];
C<int*, &a[0]> err3; // error 배열 내 개별 주소 역시 마찬가지

int main( )
{
}