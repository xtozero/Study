#include <iostream>

template <typename T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2>
decltype(T1( ) + T2( )) new_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

int main( )
{
	// + �����ڸ� �������� �ʾ� ����
	// add( lhs, rhs );

	std::cout << add( 4, 7 ) << std::endl; // ok T�� �� ���ڿ� ���� int
								 //add( 4, 4.2 ); // error ù ��° T�� int �� ��° T�� double

								 // ���������� ȣ���ϱ� ���ؼ��� �Ʒ��� ���� ȣ���Ͽ��� �Ѵ�.
	std::cout << add( static_cast<double>(4), 4.2 ) << std::endl; // �� ���ڰ� ��ġ�ϵ��� ��������� ����ȯ
	std::cout << add<double>( 4, 4.2 ) << std::endl; // T�� ������ ���� ���

	std::cout << new_add( 4, 4.2 ) << std::endl; // �Ķ���Ͱ� �ٸ� ���������� ���� �� �ֵ��� ���

}