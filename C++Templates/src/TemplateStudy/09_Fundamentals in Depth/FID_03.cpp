int C;

class C; // ok Ŭ���� �̸��� Ŭ������ �ƴ� �̸��� �ٸ� ������ ����.

int X;

template <typename T>
class X; // error : ���� X �� �浹

struct S;

template <typename T>
class S; // error : struct S�� �浹

extern "C++" template <typename T>
void normal( ) {} // �̰��� �⺻

extern "C" template <typename T>
void invalid( ) {} // error ���ø��� C ��ũ�� ���� �� ����

int main( )
{

}