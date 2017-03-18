#include <iostream>
#include <typeinfo>
#include <vector>

class Type
{
public:
	using SubType = int;
};

template <typename T>
class MyClass
{
public:
	typename T::SubType* ptr;

	// typename�� ���ٸ� SubType�� ���� ����� ���� �� �� �ִ�.
	// �׷��� T::SubType * ptr �� Ŭ���� T�� ���� ����� SubType�� ptr�� ���ϴ� ������ �ȴ�.
};

template <typename T>
void printcoll( const T& coll )
{
	typename T::const_iterator pos;

	typename T::const_iterator end( coll.end( ) );

	for ( pos = coll.begin( ); pos != end; ++pos )
	{
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;

	// ���� �ڵ�� ������ ���̴�.
	for ( const auto& elem : coll )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}

int main( )
{
	MyClass<Type> v;
	std::cout << typeid(v.ptr).name( ) << std::endl;

	std::vector<int> collection = { 1, 1, 2, 3, 5, 8, 13, 21 };
	printcoll( collection );
}