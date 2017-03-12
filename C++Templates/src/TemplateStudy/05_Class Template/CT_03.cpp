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
	
	// 이하 생략 CT_02.cpp 참고
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


// 잘 못된 방식 1
/*
template <>
class Stack<std::string>
{
private:
	std::vector<std::string> m_elems;
	T top( ) const; // 모두 특수화 해야한다.

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