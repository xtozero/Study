template <typename T> class C;	// 선언만

C<int>* p = 0;					// ok 정의가 필요하진 않음.

template <typename T>
class C
{
public:
	C( int );
	void f( );					// 멤버 선언
};								// 템플릿 정의

void g( C<int>& c )				// 클래스 템플릿 선언만 사용됨.
{
	// c.f( );						// 클래스 템플릿 멤버 함수의 정의가 사용됨.
}

void candidate( const C<double>& );	// #1
void candidate( int ) {}			// #2

int main( )
{
	// C<void>* cVoid = new C<void>;
	candidate( 42 );
}