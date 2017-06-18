#include <iostream>

// �⺻ ����
template <typename T>
class S
{
public:
	void info( )
	{
		std::cout << "generic (S<T>::info())" << std::endl;
	}
};

template <>
class S<void>
{
public:
	void msg( )
	{
		std::cout << "fully specialized (S<T>::msg())" << std::endl;
	}
};

// �⺻ ���ڸ� ���� ���ø� �Ķ������ ���
template <typename T>
class Types
{
public:
	typedef int I;
};

template <typename T, typename U = typename Types<T>::I>
class FS;

template <>
class FS<void> 
{
public:
	void f( );
};

template <>
class FS<char, char>;

template <>
class S<char, 0>;		// error

// Ŭ���� ���ø� ���� Ư��ȭ���� ��� �Լ��� ����
template<>

class S<char**>
{
public:
	void print( ) const;
};

void S<char**>::print( ) const
{
	std::cout << "Pointer to pointer to char" << std::endl;
}

int main( )
{
	FS<int>* pi;		// ok
	FS<int>	e1;			// error : ���� ����
	FS<void>* pv;		// ok
	FS<void, int> sv;	// ok
	FS<void, char> e2;	// error : ���� ����
	FS<char, char> e3;	// error : ���� ����
}