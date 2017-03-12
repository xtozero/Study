#include <cstdlib>
#include <iostream>
#include <deque>
#include <vector>

template <typename T, typename CONT = std::vector<T>>
class Stack
{
private:
	CONT m_elems;

public:
	void push( const T& elems );
	void pop( );
	T top( ) const;
	bool empty( ) const
	{
		return m_elems.empty( );
	}

	Stack( ) = default;
	Stack( const Stack<T, CONT>& stack );
	Stack( Stack<T, CONT>&& stack );
	Stack<T, CONT>& operator=( const Stack<T, CONT>& stack );
	Stack<T, CONT>& operator=( Stack<T, CONT>&& stack );
};

template <typename T, typename CONT>
void Stack<T, CONT>::push( const T& value )
{
	m_elems.push_back( value );
}

template <typename T, typename CONT>
void Stack<T, CONT>::pop( )
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::pop() : empty stack" );
	}
	m_elems.pop_back( );
}

template <typename T, typename CONT>
T Stack<T, CONT>::top( ) const
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}
	return m_elems.back( );
}

template <typename T, typename CONT>
Stack<T, CONT>::Stack( const Stack<T, CONT>& stack )
{
	m_elems = stack.m_elems;
}

template <typename T, typename CONT>
Stack<T, CONT>::Stack( Stack<T, CONT>&& stack )
{
	m_elems = std::move( stack.m_elems );
}

template <typename T, typename CONT>
Stack<T, CONT>& Stack<T, CONT>::operator=( const Stack<T, CONT>& stack )
{
	m_elems = stack.m_elems;
	*this;
}

template <typename T, typename CONT>
Stack<T, CONT>& Stack<T, CONT>::operator=( Stack<T, CONT>&& stack )
{
	m_elems = std::move( stack.m_elems );
	return *this;
}

int main( )
{
	try 
	{
		Stack<int> intStack;

		Stack<double, std::deque<double>> dequeStack;

		intStack.push( 7 );
		std::cout << intStack.top( ) << std::endl;
		intStack.pop( );

		dequeStack.push( 42.42 );
		std::cout << dequeStack.top( ) << std::endl;
		dequeStack.pop( );
		dequeStack.pop( );
	}
	catch ( std::exception ex )
	{
		std::cerr << "Exception: " << ex.what( ) << std::endl;
		return EXIT_FAILURE;
	}
}