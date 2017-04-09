#include <iostream>

template <typename T>
class B
{
public:
	enum E { e1 = 6, e2 = 28, e3 = 496 };
	virtual void zero( E e = e1 ) { std::cout << "zero( E e )" << std::endl; }
	virtual void one( E& ) { std::cout << "one( E& )" << std::endl; }
};

template <typename T>
class D : public B<T>
{
public:
	void f( )
	{
		typename D<T>::E e; // this->E�� ��ȿ�� ������ �ƴ�
		this->zero( );		// D<T>::zero()�� ������ ������
		one( e );
	}
};

int main( )
{
	D<int> d;
	d.f( );
}