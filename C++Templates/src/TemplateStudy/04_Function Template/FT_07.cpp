#include <iostream>

template <typename T = int> // c++ 11 ���� �����Ϸ� ���� ����
void DefaultParameter( T value ) {}

template <typename T1, typename T2>
T1 add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2, typename R>
R add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename R, typename T1, typename T2>
R add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2>
decltype(T1( ) + T2( )) new_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

// c++ 14 ���� ����
template <typename T1, typename T2>
decltype(auto) auto_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

int main( )
{
	// �Լ� ���ø��� �⺻ �Ķ���� ���
	DefaultParameter( 1 );

	// ���� �ٸ� ���ø� �Ķ���͸� ����� add ����
	add( 1.f, 1 );

	// ��ȯ���� ������ �� �ֵ����� add ���� 1
	add<int, double, double>( 1, 1.f );

	// ��ȯ���� ������ �� �ֵ����� add ���� 2
	add<double>( 1, 1.f );

	// decltype, auto�� ����� add ����
	std::cout << new_add( 5.1234, 1 ) << std::endl;
	std::cout << auto_add( 1.2345f, 2L ) << std::endl;
}