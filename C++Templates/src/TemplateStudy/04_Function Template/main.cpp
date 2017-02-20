#include <iostream>
#include <string>

using namespace std;

template <typename T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

template <typename T, typename U>
decltype( T() + U() ) new_add( T lhs, U rhs )
{
	return lhs + rhs;
}

class UnsurpportedOperator{};

class TypeDeduction
{
public:
	mutable int m_value;
};

template <typename T>
void f( T& param ) {}

int main()
{
	cout << add( 1, 2 ) << endl; // 3�� ���
	cout << add( 3.1, 4.1 ) << endl; // 7.2�� ���
	cout << add( string( "hello " ), string( "world" ) ) << endl; // "hello world" ���

	UnsurpportedOperator lhs;
	UnsurpportedOperator rhs;

	// + �����ڸ� �������� �ʾ� ����
	// add( lhs, rhs );

	cout <<  add( 4, 7 ) << endl; // ok T�� �� ���ڿ� ���� int
	//add( 4, 4.2 ); // error ù ��° T�� int �� ��° T�� double

	// ���������� ȣ���ϱ� ���ؼ��� �Ʒ��� ���� ȣ���Ͽ��� �Ѵ�.
	cout <<  add( static_cast<double>(4), 4.2 ) << endl; // �� ���ڰ� ��ġ�ϵ��� ��������� ����ȯ
	cout <<  add<double>( 4, 4.2 ) << endl; // T�� ������ ���� ���
	
	cout <<  new_add( 4, 4.2 ) << endl; // �Ķ���Ͱ� �ٸ� ���������� ���� �� �ֵ��� ���

	// T&�� ���
	int x = 27;
	int& rx = x;
	const int cx = x;
	const int& crx = x;

	f( x );			// T: int ParamType : int&
	f( rx );		// T: int ParamType : int&
	f( cx );		// T: const int, ParamType : const int&
	f( crx );		// T: const int, ParamType : const int&
	// T&& �� ���

	// T �� ���
	TypeDeduction t = { 0 };
	auto deducted = t.m_value;
}