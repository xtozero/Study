#include <cstdlib>
#include <iostream>
#include <string>

// template <typename T = int, int MAXSIZE = 100>
template <typename T, int MAXSIZE>
class Stack
{
private:
	T m_elems[MAXSIZE];
	int m_numElems = 0;

public:
	void push( const T& value );
	void pop( );
	T top( ) const;

	bool empty( ) const
	{
		return m_elems.empty( );
	}

	Stack( ) = default;
	Stack( const Stack<T, MAXSIZE>& stack );
	Stack( Stack<T, MAXSIZE>&& stack ) = delete;
	Stack<T, MAXSIZE>& operator=( const Stack<T, MAXSIZE>& stack );
	Stack<T, MAXSIZE>& operator=( Stack<T, MAXSIZE>&& stack ) = delete;
};

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push( const T& value )
{
	if ( m_numElems == MAXSIZE )
	{
		throw std::out_of_range( "Stack<>::push() : stack is full" );
	}

	m_elems[m_numElems] = value;
	++m_numElems;
}

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::pop( )
{
	if ( m_numElems <= 0 )
	{
		throw std::out_of_range( "Stack<>::pop() : empty stack" );
	}

	--m_numElems;
}

template <typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::top( ) const
{
	if ( m_numElems <= 0 )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}

	return m_elems[m_numElems - 1];
}

template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>::Stack( const Stack<T, MAXSIZE>& stack )
{
	*this = stack;
}

template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>& Stack<T, MAXSIZE>::operator=( const Stack<T, MAXSIZE>& stack )
{
	m_numElems = stack.m_numElems;
	
	for ( int i = 0; i < m_numElems; ++i )
	{
		m_elems[i] = stack.m_elems[i];
	}

	return *this;
}

int main( )
{
	try
	{
		Stack<int, 20> int20Stack;
		Stack<int, 40> int40Stack;
		Stack<std::string, 40> stringStack;

		int20Stack.push( 7 );
		std::cout << int20Stack.top( ) << std::endl;
		int20Stack.pop( );

		stringStack.push( "hello" );
		std::cout << stringStack.top( ) << std::endl;
		stringStack.pop( );
		stringStack.pop( );
	}
	catch ( std::exception ex )
	{
		std::cerr << "Exception" << ex.what( ) << std::endl;
		return EXIT_FAILURE;
	}
}