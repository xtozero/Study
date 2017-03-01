#include <iostream>
#include <cstring>
#include <string>

using namespace std;

template <typename T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

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
decltype( T1() + T2() ) new_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2>
decltype( auto ) auto_add( T1 lhs, T2 rhs )
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
void CallByReference( T& param ) {}

template <typename T>
void CallByForwardReference( T&& param ) {}

template <typename T>
void CallByValue( T param ) {}

template <typename T = int> // c++ 11 ���� �����Ϸ� ���� ����
void DefaultParameter( T value ) {}

int max( const int& lhs, const int& rhs )
{
	cout << "max( int, int )" << endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& lhs, const T& rhs )
{
	cout << "max( T, T )" << endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& first, const T& second, const T& third )
{
	cout << "max( T, T, T )" << endl;
	return max( max( first, second ), third );
}

//template <typename T1, typename T2>
//auto max( T1&, T2& )
//{
//	cout << "max( T1, T2 )" << endl;
//}

template <typename T>
T* const& max( T* const & a, T* const & b )
{
	cout << "T* const & a, T* const & b" << endl;
	return *a < *b ? b : a;
}

const char* const& max( const char* const& a, const char* const& b )
{
	cout << "max( const char* const& a, const char* const& b )" << endl;
	return strcmp( a, b ) < 0 ? b : a;
}

template <typename T>
const T& new_max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

const char* new_max( const char* lhs, const char* rhs )
{
	return strcmp( lhs, rhs ) < 0 ? rhs : lhs;
}

template <typename T>
const T& new_max( const T& first, const T& second, const T& third )
{
	return new_max( new_max( first, second ), third );
}

template <typename T>
const T& min( const T& lhs, const T& rhs )
{
	cout << "min( T, T )" << endl;
	return lhs < rhs ? lhs : rhs;
}

template <typename T>
const T& min( const T& first, const T& second, const T& third )
{
	cout << "min( T, T, T )" << endl;
	return min( min( first, second ), third );
}

const int& min( const int& lhs, const int& rhs )
{
	cout << "min( const int& lhs, const int& rhs )" << endl;
	return lhs < rhs ? lhs : rhs;
}

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

	CallByReference( x );		// T: int ParamType : int&
	CallByReference( rx );		// T: int ParamType : int&
	CallByReference( cx );		// T: const int, ParamType : const int&
	CallByReference( crx );		// T: const int, ParamType : const int&

	// T&& �� ���
	CallByForwardReference( x );		// T: int& ParamType : int&
	CallByForwardReference( rx );		// T: int& ParamType : int&
	CallByForwardReference( cx );		// T: const int&, ParamType : const int&
	CallByForwardReference( crx );		// T: const int&, ParamType : const int&
	CallByForwardReference( 27 );		// T: int, ParamType : int&&

	// T �� ���
	CallByValue( x );		// T: int ParamType : int
	CallByValue( rx );		// T: int ParamType : int
	CallByValue( cx );		// T: int, ParamType : int
	CallByValue( crx );		// T: int, ParamType : int

	TypeDeduction t = { 0 };
	auto deducted = t.m_value; // T: int ParamType : int

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

	// �Լ� ���ø��� �����ε�
	max( 7, 42, 68 );			// �� ���ڸ� ���� ���ø� ȣ��
	max( 7.0, 42.0 );			// max<double> ȣ��
	max( 'a', 'b' );			// max<char> ȣ��
	max( 7, 42 );				// nontemplate �Լ� max ȣ��
	max<>( 7, 42 );				// max<int> ȣ��
	max<double>( 7, 42 );		// max<double> ȣ��
	max( 'a', 42.7 );			// nontemplate �Լ� max ȣ��

	string hey = "hey";
	string you = "you";

	max( hey, you );

	int a = 1;
	int b = 2;
	int* p1 = &b;
	int* p2 = &a;

	max( p1, p2 );

	const char* s1 = "Alpha";
	const char* s2 = "Bong";
	max( s1, s2 );

	// �Լ� ���ø� �����ε��� ����ġ ���ϰ� �����ϴ� ���
	// VS2015������ �� �����ϵǳ� gcc������ ũ���ð� ����.
	const char* st1 = "Template";
	const char* st2 = "Study";
	const char* st3 = "Successfull";
	cout << new_max( st1, st2, st2 ) << endl;

	// �Լ� ���ø� �����ε��� ����ġ ���ϰ� �����ϴ� ���2
	min( 1, 2, 3 );
}