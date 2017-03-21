#include <stdexcept>
#include <string>
#include <vector>

// 함수 클래스 생성자에 대한 명시적 인스턴스화
template <typename T>
class MyClass 
{
public:
	MyClass( ) noexcept {};
};

template MyClass<int>::MyClass( ) noexcept;

// 함수 템플릿에 대한 명시적 인스턴스화
template <typename T>
const T& max( const T& lhs, const T& rhs ) { return lhs > rhs ? lhs : rhs; }

template const int& max( const int&, const int& );

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

	Stack( ) noexcept {};
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
	if ( this == &stack )
	{
		return *this;
	}

	m_elems = stack.m_elems;
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=( Stack<T>&& stack )
{
	if ( this == &stack )
	{
		return *this;
	}

	m_elems = std::move( stack.m_elems );
	return *this;
}

// int에 대한 Stack<>의 명시적 인스턴스화
template class Stack<int>;

// float 에 대한 특수화
template<>
class Stack<float>
{

};

// String에 대한 Stack<> 일부 멤버 함수의 명시적 인스턴스화
template Stack<std::string>::Stack( ) noexcept;
template void Stack<std::string>::push( const std::string& );
template std::string Stack<std::string>::top( ) const;

// error 중복된 명시적 인스턴스화
// template Stack<int>::Stack( );

// 이미 특수화된 템플릿 인수에 대해서는 어떤 영향도 주지 않는다.
// Explicit instantiation has no effect if an explicit specialization appeared before for the same set of template arguments.
// http://en.cppreference.com/w/cpp/language/class_template
template class Stack<float>;

int main( )
{

}