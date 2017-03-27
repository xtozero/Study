int C;

class C; // ok 클래스 이름과 클래스가 아닌 이름은 다른 공간에 있음.

int X;

template <typename T>
class X; // error : 변수 X 와 충돌

struct S;

template <typename T>
class S; // error : struct S와 충돌

extern "C++" template <typename T>
void normal( ) {} // 이것이 기본

extern "C" template <typename T>
void invalid( ) {} // error 템플릿은 C 링크를 가질 수 없음

int main( )
{

}