template <typename X>
class Base
{
public:
	int basefield;
	typedef int T;
};

class D1 : public Base<Base<void>> // 이 클래스는 템플릿이 아니다.
{
public:
	void f( ) { basefield = 3; }
};

template <typename T>
class D2 : public Base<double>	// 종속되지 않은 기본 클래스
{
public:
	void f( ) { basefield = 7; }	// 일반적으로 상속받은 멤버로 접근
	T strange;						// T는 Base<double>::T 이지 템플릿 파라미터가 아님
};

void g( D2<int*>& d2, int* p )
{
	d2.strange = p;					// error
}

int main( )
{

}