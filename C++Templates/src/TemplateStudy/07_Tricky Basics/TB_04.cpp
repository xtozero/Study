#include <iostream>
#include <deque>
#include <vector>

template <typename T>
class Stack
{
private:
	std::vector<T> m_elems;

public:
	void push( const T& value );
	void pop( );
	T top( ) const;

	bool empty( ) const
	{
		return m_elems.empty( );
	}

	Stack( ) = default;

	template <typename U>
	Stack<T>& operator= ( const Stack<U>& stack );
};

template <typename T>
void Stack<T>::push( const T& value )
{
	m_elems.push_back( value );
}

template <typename T>
void Stack<T>::pop( )
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::pop() : empty stack" );
	}
	m_elems.pop_back( );
}

template <typename T>
T Stack<T>::top( ) const
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}
	return m_elems.back( );
}

template <typename T>
template <typename U>
Stack<T>& Stack<T>::operator=( const Stack<U>& stack )
{
	std::cout << "Stack<T>& Stack<T>::operator=( const Stack<U>& stack )" << std::endl;

	if ( this == (void*)&stack )
	{
		return *this;
	}

	m_elems.clear( );
	Stack<U> copy( stack );
	std::deque<U> temp;

	while ( !copy.empty( ) )
	{
		temp.push_front( copy.top( ) );
		copy.pop( );
	}

	for ( const auto& elem : temp )
	{
		m_elems.push_back( elem );
	}

	return *this;
}

int main( )
{
	/*
	// ���� ��� ���ø� �Ҵ� �����ڰ� �����ٸ�
	Stack<int> intStack1, intStack2;	// int�� ���� ����
	Stack<float> floatStack;			// float �� ���� ����

	intStack1 = intStack2;				// OK : ���� ���������� ����
	floatStack = intStack1;				// ERROR : �ٸ� ���������� ����
	*/

	Stack<int> intStack;	// int�� ���� ����
	intStack.push( 1 );
	intStack.push( 2 );
	intStack.push( 3 );
	intStack.push( 4 );
	intStack.push( 5 );

	Stack<float> floatStack;			// float �� ���� ����

	floatStack = intStack;				// OK : �ٸ� ���������� ����

	while ( !intStack.empty( ) )
	{
		std::cout << intStack.top( ) << ' ';
		intStack.pop( );
	}
	std::cout << std::endl;

	while ( !floatStack.empty( ) )
	{
		std::cout << floatStack.top( ) << ' ';
		floatStack.pop( );
	}
	std::cout << std::endl;

	// Stack<double> doubleStack;
	// Stack<std::string> stringStack;

	// doubleStack = stringStack; // std::string�� double�� ��ȯ�� �� ����

	Stack<char> charStack1;
	Stack<char> charStack2;

	charStack1 = charStack2;
}