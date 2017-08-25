#include <iostream>

template <typename T>
class IsClassT
{
private:
	using One = char;
	using Two = struct { char a[2]; };
	template <typename C> static One test( int C::* );
	template <typename C> static Two test( ... );
public:
	enum { Yes = sizeof( IsClassT<T>::test<T>( 0 ) ) == 1 };
	enum { No = !Yes };
};

class MyClass {};

struct MyStruct {};

union MyUnion {};

void myfunc( ) {}

enum E { e1 } e;

template <typename T>
void check( )
{
	if ( IsClassT<T>::Yes )
	{
		std::cout << " IsClassT " << std::endl;
	}
	else
	{
		std::cout << " !IsClassT " << std::endl;
	}
}

template <typename T>
void checkT( T )
{
	check<T>( );
}

int main()
{
	std::cout << "int: ";
	check<int>( );

	std::cout << "MyClass: ";
	check<MyClass>( );
	std::cout << "MyStruct: ";
	MyStruct s;
	checkT( s );

	std::cout << "MyUnion: ";
	check<MyUnion>( );

	std::cout << "enum: ";
	checkT( e );

	std::cout << "myfunc(): ";
	checkT( myfunc );
}