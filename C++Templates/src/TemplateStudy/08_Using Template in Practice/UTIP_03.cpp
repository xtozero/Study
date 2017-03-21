#include <stdexcept>
#include <string>
#include <vector>

// �Լ� Ŭ���� �����ڿ� ���� ����� �ν��Ͻ�ȭ
template <typename T>
class MyClass 
{
public:
	MyClass( ) noexcept {};
};

template MyClass<int>::MyClass( ) noexcept;

// �Լ� ���ø��� ���� ����� �ν��Ͻ�ȭ
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

// int�� ���� Stack<>�� ����� �ν��Ͻ�ȭ
template class Stack<int>;

// float �� ���� Ư��ȭ
template<>
class Stack<float>
{

};

// String�� ���� Stack<> �Ϻ� ��� �Լ��� ����� �ν��Ͻ�ȭ
template Stack<std::string>::Stack( ) noexcept;
template void Stack<std::string>::push( const std::string& );
template std::string Stack<std::string>::top( ) const;

// error �ߺ��� ����� �ν��Ͻ�ȭ
// template Stack<int>::Stack( );

// �̹� Ư��ȭ�� ���ø� �μ��� ���ؼ��� � ���⵵ ���� �ʴ´�.
// Explicit instantiation has no effect if an explicit specialization appeared before for the same set of template arguments.
// http://en.cppreference.com/w/cpp/language/class_template
template class Stack<float>;

int main( )
{

}