template <typename X>
class Base
{
public:
	int basefield;
	typedef int T;
};

class D1 : public Base<Base<void>> // �� Ŭ������ ���ø��� �ƴϴ�.
{
public:
	void f( ) { basefield = 3; }
};

template <typename T>
class D2 : public Base<double>	// ���ӵ��� ���� �⺻ Ŭ����
{
public:
	void f( ) { basefield = 7; }	// �Ϲ������� ��ӹ��� ����� ����
	T strange;						// T�� Base<double>::T ���� ���ø� �Ķ���Ͱ� �ƴ�
};

void g( D2<int*>& d2, int* p )
{
	d2.strange = p;					// error
}

int main( )
{

}