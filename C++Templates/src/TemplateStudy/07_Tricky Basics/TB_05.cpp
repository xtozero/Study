#include <iostream>
#include <deque>
#include <vector>

template <typename T, template<typename ELEM> class CONT = std::deque>
class Stack
{
private:
	CONT<T> m_elems;

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


template <typename T, template<typename> class CONT>
void Stack<T, CONT>::push( const T& value )
{
	m_elems.push_back( value );
}

template <typename T, template<typename> class CONT>
void Stack<T, CONT>::pop( )
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::pop() : empty stack" );
	}
	m_elems.pop_back( );
}

template <typename T, template<typename> class CONT>
T Stack<T, CONT>::top( ) const
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}
	return m_elems.back( );
}

template <typename T, template<typename> class CONT>
Stack<T, CONT>::Stack( const Stack<T, CONT>& stack )
{
	*this = stack;
}

template <typename T, template<typename> class CONT>
Stack<T, CONT>::Stack( Stack<T, CONT>&& stack )
{
	*this = std::move( stack );
}

template <typename T, template<typename> class CONT>
Stack<T, CONT>& Stack<T, CONT>::operator=( const Stack<T, CONT>& stack )
{
	if ( this == &stack )
	{
		return *this;
	}

	m_elems = stack.m_elems;
	return *this;
}

template <typename T, template<typename> class CONT>
Stack<T, CONT>& Stack<T, CONT>::operator=( Stack<T, CONT>&& stack )
{
	if ( this == &stack )
	{
		return *this;
	}

	m_elems = std::move( stack.m_elems );
	return *this;
}

int main( )
{
	Stack<int, std::vector> vStack; // error 수정 버전은 TB_06.cpp
}