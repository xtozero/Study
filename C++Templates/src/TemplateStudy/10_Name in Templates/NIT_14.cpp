template <typename X>
class Base
{
public:
	int basefield;
	typedef int T;
};

template <typename T>
class DD : public Base<T>			// ���� �⺻ Ŭ����
{
public:
	void f( ) { basefield = 0; }	// 1
};

template <typename T>
class DD1 : public Base<T>
{
public:
	void f( ) { this->basefield = 0; }
};

template <typename T>
class DD2 : public Base<T>
{
public:
	void f( ) { Base<T>::basefield = 0; }
};

template <typename T>
class DD3 : public Base<T>
{
public:
	using Base<T>::basefield;		// ���� �̸��� ���� ���� ����
	void f( ) { basefield = 0; }	// ok
};

template <>							// ����� Ư��ȭ
class Base<bool>
{
public:
	enum { basefield = 42 };		// 2
};

void g( DD<bool>& d )
{
	d.f( );							// 3
}

int main( )
{

}