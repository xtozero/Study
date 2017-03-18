#include <iostream>
#include <deque>
#include <vector>

template <typename T,
		template<typename ELEM, typename Alloc = std::allocator<ELEM> >
		typename CONT = std::deque> // c++11 지원 컴파일러에서 typename을 사용해도 정상적으로 컴파일. gcc, vs 2015 community 동일
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


template <typename T, template<typename, typename> typename CONT>
void Stack<T, CONT>::push( const T& value )
{
	m_elems.push_back( value );
}

template <typename T, template<typename, typename> typename CONT>
void Stack<T, CONT>::pop( )
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::pop() : empty stack" );
	}
	m_elems.pop_back( );
}

template <typename T, template<typename, typename> typename CONT>
T Stack<T, CONT>::top( ) const
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}
	return m_elems.back( );
}

template <typename T, template<typename, typename> typename CONT>
Stack<T, CONT>::Stack( const Stack<T, CONT>& stack )
{
	*this = stack;
}

template <typename T, template<typename, typename> typename CONT>
Stack<T, CONT>::Stack( Stack<T, CONT>&& stack )
{
	*this = std::move( stack );
}

template <typename T, template<typename, typename> typename CONT>
Stack<T, CONT>& Stack<T, CONT>::operator=( const Stack<T, CONT>& stack )
{
	if ( this == &stack )
	{
		return *this;
	}

	m_elems = stack.m_elems;
	return *this;
}

template <typename T, template<typename, typename> typename CONT>
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
	Stack<int, std::vector> vStack;
	vStack.push( 42 );
	vStack.push( 7 );
	std::cout << vStack.top( ) << std::endl;
	vStack.pop( );
}