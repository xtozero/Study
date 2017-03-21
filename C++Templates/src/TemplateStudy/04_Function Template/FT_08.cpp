#include <iostream>

int max( const int& lhs, const int& rhs )
{
	std::cout << "max( int, int )" << std::endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& lhs, const T& rhs )
{
	std::cout << "max( T, T )" << std::endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& first, const T& second, const T& third )
{
	std::cout << "max( T, T, T )" << std::endl;
	return max( max( first, second ), third );
}

int main( )
{
	// �Լ� ���ø��� �����ε�
	::max( 7, 42, 68 );			// �� ���ڸ� ���� ���ø� ȣ��
	::max( 7.0, 42.0 );			// max<double> ȣ��
	::max( 'a', 'b' );			// max<char> ȣ��
	::max( 7, 42 );				// nontemplate �Լ� max ȣ��
	::max<>( 7, 42 );				// max<int> ȣ��
	::max<double>( 7, 42 );		// max<double> ȣ��
	::max( 'a', 42.7 );			// nontemplate �Լ� max ȣ��
}