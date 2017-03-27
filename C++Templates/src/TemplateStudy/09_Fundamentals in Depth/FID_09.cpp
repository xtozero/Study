#include <iostream>

typedef char RT1;

struct RT2
{
	char a[2];
};

template <typename T> RT1 test( typename T::X const* ) { return RT1( ); }
template <typename T> RT2 test( T ) { return RT2( ); }

namespace detail
{
	template <typename T> char test( int T::* );
	struct two { char c[2]; };
	template <typename T> two test( ... );
}

template <typename T, T v>
class x_integral_constant
{
public:
	static constexpr T value = v;
};

template <typename T>
class x_is_class : public x_integral_constant<bool, sizeof( detail::test<T>( 0 ) ) == 1 && !std::is_union<T>::value>
{
};

template <int N> void f( int( &)[24 / (4 - N)] );
template <int N> void f( int( &)[24 / (4 + N)] );

int main( )
{
	test( 1 ); // ok SFINAE

	std::cout << "int is class ? : " << ( x_is_class<int>::value ? "true" : "false" ) << std::endl;
	std::cout << "RT2 is class ? : " << (x_is_class<RT2>::value ? "true" : "false" ) << std::endl;

	union X
	{
		int n;
		float f;
	};

	std::cout << "X is class ? : " << (x_is_class<X>::value ? "true" : "false") << std::endl;

	//&f<4>; // gcc������ ��������. vs 2015 community������ ������ ������ 0���� ������ �߻��ϴ� ������ �ƴϴ�.
}