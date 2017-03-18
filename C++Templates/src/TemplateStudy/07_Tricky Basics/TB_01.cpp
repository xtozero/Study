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

	// typename이 없다면 SubType은 정적 멤버로 간주 될 수 있다.
	// 그러면 T::SubType * ptr 는 클래스 T의 정적 멤버인 SubType을 ptr과 곱하는 연산이 된다.
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

	// 위의 코드는 예제일 뿐이다.
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