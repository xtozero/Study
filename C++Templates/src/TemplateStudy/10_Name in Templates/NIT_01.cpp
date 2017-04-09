#include <iostream>

// 한정된 이름에 대한 룩업
int x;

class B
{
public:
	int i;
};

class D : public B {};

void f( D* pd )
{
	pd->i = 3;		// B::i 찾음
	// D::x = 2;		// error 둘러싼 영역에서 ::x를 찾지 못함
}

// 한정되지 않은 이름에 대한 룩업
int count = -1;							// 1

int lookup_example( int count )			// 2
{
	if ( count < 0 )
	{
		std::cout << count << std::endl;	// ?
		std::cout << ::count << std::endl;	// ?

		int count = 0;					// 3

		std::cout << count << std::endl;	// ?
		std::cout << ::count << std::endl;	// ?
		lookup_example( count );		// 한정되지 않은 count는 3을 가리킴
	}

	std::cout << count << std::endl;		// ?
	std::cout << ::count << std::endl;		// ?
	return count + ::count;				// 첫 번째 한정되지 않은 카운트는 2를 가리킴
}

// ADL
template <typename T>
inline const T& max( const T& a, const T& b )
{
	return a < b ? b : a;
}

// 위의 템플릿을 다른 네임스페이스에 정의한 데이터형에 적용해야 한다고 하면...
namespace BigMath
{
	class BigNumber
	{

	};

	bool operator< ( const BigNumber&, const BigNumber& ) { return true; }
}

void g( const BigMath::BigNumber& a, const BigMath::BigNumber& b )
{
	BigMath::BigNumber x = max( a, b );
}

int main( )
{
	lookup_example( -2 );

	BigMath::BigNumber rhs;
	BigMath::BigNumber lhs;

	g( lhs, rhs );
}