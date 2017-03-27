template <typename T, T nontype_param>
class C
{
};

C<int, 33>* cl;			// ������

int a;
C<int*, &a> c2;			// �ܺ� ������ �ּ�

void f( );
void f( int );
C<void( *)(int), f> c3;	// �Լ��� �̸� : �����ε� �ؼ��� ���� f( int )�� ����

class X
{
public:
	int n;
	static bool b;
};

C<bool&, X::b>* c4;		// ���� Ŭ���� ����� ���밡��

C<int X::*, &X::n>* c5;	// ��� ���� ������ ����� ��

template<typename T>
void templ_func( );

C<void(*)( ), &templ_func<double>>* c6; // �Լ� ���ø� �ν��Ͻ��� �Լ���

constexpr float fv = 10.f;
C<float, fv>* c7; // error �ε��Ҽ��� ���ڴ� �ȵ�

const char* stringLiteral = "Hello Template";
C<char*, stringLiteral> c8; // error ���ڿ� ���ͷ��� �ȵ�

// ��� ���ڿ��� �ʱ�ȭ�Ϸ��� �Ʒ��� ���� ������� �ؾ��Ѵ�.
extern const char hello[] = "Hello World!"; // extern ���� const �迭 ������ ���� ��ũ�� ���� �� �����Ƿ� ����
C<const char*, hello> c9;

class Base
{
public:
	int i;
} base;

class Derived : public Base
{

} derived_obj;

C<Base*, &derived_obj> err1; // error �θ� Ŭ�������� ��ȯ�� ������� �ʴ´�.

C<int&, base.i> err2; // error Ŭ���� ������ ��������� ������ ���ֵ��� ����.

int a[10];
C<int*, &a[0]> err3; // error �迭 �� ���� �ּ� ���� ��������

int main( )
{
}