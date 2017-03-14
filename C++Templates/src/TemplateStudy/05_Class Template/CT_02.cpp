#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Stack
{
private:
	std::vector<T> m_elems;

public:
	void push( const T& value );
	/*
	void push( const T& value )
	{
	m_elems.push_back( value );
	}
	*/
	void pop( );
	T top( ) const;

	bool empty( ) const
	{
		return m_elems.empty( );
	}

	Stack( ) = default;
	Stack( const Stack<T>& stack );
	Stack( Stack<T>&& stack );
	Stack<T>& operator=( const Stack<T>& stack );
	Stack<T>& operator=( Stack<T>&& stack );
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
Stack<T>::Stack( const Stack<T>& stack )
{
	*this = stack;
}

template <typename T>
Stack<T>::Stack( Stack<T>&& stack )
{
	*this = std::move( stack );
}

template <typename T>
Stack<T>& Stack<T>::operator=( const Stack<T>& stack )
{
	m_elems = stack.m_elems;
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=( Stack<T>&& stack )
{
	m_elems = std::move( stack.m_elems );
	return *this;
}

int main( )
{
	Stack<int> istack[10];

	typedef Stack<int> IntStack;
	IntStack intStack[10];

	using IStack = Stack<int>;
	const IStack Istack;

	Stack<float*> floatPtrStack;
	Stack<Stack<int> > intStackStack;

	Stack<Stack<int>> sincecpp11StackStack;

	try
	{
		Stack<int> intStack;
		Stack<std::string> stringStack;

		intStack.push( 7 );
		std::cout << intStack.top( ) << std::endl;

		stringStack.push( "hello" );
		std::cout << stringStack.top( ) << std::endl;
		stringStack.pop( );
		stringStack.pop( );
	}
	catch ( const std::exception& ex )
	{
		std::cerr << "Exception: " << ex.what( ) << std::endl;
		return EXIT_FAILURE;
	}
}