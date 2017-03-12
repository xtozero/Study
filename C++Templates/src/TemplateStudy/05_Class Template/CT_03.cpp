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
	
	// ���� ���� CT_02.cpp ����
};

template <typename T>
void Stack<T>::push( const T& value )
{
	m_elems.push_back( value );
}

template <>
class Stack<std::string>
{
private:
	std::vector<std::string> m_elems;

public:
	void push( const std::string& value );
};

void Stack<std::string>::push( const std::string& value )
{
	m_elems.push_back( value );
}


// �� ���� ��� 1
/*
template <>
class Stack<std::string>
{
private:
	std::vector<std::string> m_elems;
	T top( ) const; // ��� Ư��ȭ �ؾ��Ѵ�.

public:
	void push( const std::string& value );
};

void Stack<std::string>::push( const std::string& value )
{
	m_elems.push_back( value );
}
*/

int main( )
{
}