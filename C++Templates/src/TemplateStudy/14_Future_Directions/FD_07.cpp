#include <array>

/*
template <typename T1, typename T2>
std::array<???, 10> operator+( const std::array<T1, 10>& lhs, const std::array<T2, 10>& rhs ) {}
*/

/*
template <typename T1, typename T2>
std::array<decltype(T1() + T2()), 10> operator+( const std::array<T1, 10>& lhs, const std::array<T2, 10>& rhs ) 
{
	std::array<decltype( T1() + T2() ), 10> result;
	return result;
}
*/

template <typename T1, typename T2>
auto operator+( const std::array<T1, 10>& lhs, const std::array<T2, 10>& rhs ) -> std::array<decltype( lhs[0] + rhs[0] ), 10> 
{
	std::array<decltype( lhs[0] + rhs[0] ), 10> result;
	return result;
}

class Base
{
public:
	virtual Base* clone( );
};

class Derived : public Base
{
public:
	virtual Derived* clone( ); // 공변 반환형
};

void demo( Base* p, Base* q )
{
	decltype( p->clone( ) ) tmp = p->clone( ); // tmp는 항상 Base* 형을 가짐
}

int main( )
{
	std::array<int, 10> lhs;
	std::array<float, 10> rhs;

	auto result = lhs + rhs;
}