#include <iostream>

// ������ �̸��� ���� ���
int x;

class B
{
public:
	int i;
};

class D : public B {};

void f( D* pd )
{
	pd->i = 3;		// B::i ã��
	// D::x = 2;		// error �ѷ��� �������� ::x�� ã�� ����
}

// �������� ���� �̸��� ���� ���
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
		lookup_example( count );		// �������� ���� count�� 3�� ����Ŵ
	}

	std::cout << count << std::endl;		// ?
	std::cout << ::count << std::endl;		// ?
	return count + ::count;				// ù ��° �������� ���� ī��Ʈ�� 2�� ����Ŵ
}

// ADL
template <typename T>
inline const T& max( const T& a, const T& b )
{
	return a < b ? b : a;
}

// ���� ���ø��� �ٸ� ���ӽ����̽��� ������ ���������� �����ؾ� �Ѵٰ� �ϸ�...
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