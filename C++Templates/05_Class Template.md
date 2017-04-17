# 클래스 템플릿
## 개요
- 클래스도 함수와 마찬가지로 하나 이상의 데이터형으로 파라미터화 될 수 있다.
- 클래스 템플릿을 사용하면 어떤 데이터형을 다룰지 모르는 상태에서도 클래스를 구현할 수 있다.
- 아래의 코드는 클래스 템플릿을 사용하여 구현한 Stack이다.
```c++
template <typename T>
// CT_01.cpp
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
};
```
## 클래스 템플릿 선언
- 클래스 템플릿을 선언하기 전에 먼저 데이터형 파라미터로 사용할 식별자를 선언해야 한다.
```c++
// CT_01.cpp
template <typename T>
class Stack
{
    ...
};

// typename을 class 로 대체할 수 있다.
template <class T>
class Stack
{
    ...
};
```
- 클래스 템플릿 내부에서 멤버와 멤버 함수를 선언할 때 템플릿 파라미터를 사용할 수 있다.
```c++
// CT_01.cpp
template <typename T>
class Stack
{
private:
	std::vector<T> m_elems;

public:
	void push( const T& value );
    ...
};
```
- Stack 클래스의 데이터형은 Stack\<\>이고 T는 템플릿 파라미터이다. 따라서 선언 내에서 Stack 클래스의 데이터형을 써야 한다면 Stack\<T\>로 표기해야 한다.
```c++
// CT_01.cpp
template <typename T>
class Stack
{
    ...
    Stack( const Stack<T>& stack );
	Stack( Stack<T>&& stack );
	Stack<T>& operator=( const Stack<T>& stack );
	Stack<T>& operator=( Stack<T>&& stack );
};
```
- 클래스의 데이터형이 아니라 이름이 필요한 경우에는 Stack만 사용한다.
> 클래스의 이름과 생성자, 소멸자를 명시할 때 등이 이름만 필요한 경우다.

## 멤버 함수 구현
- 클래스 템플릿의 멤버 함수를 정의할 때는 이것이 함수 템플릿이라는 것을 명시해야 한다.
- 멤버 함수가 함수 템플릿임을 명시할 때는 전체 데이터형 한정자를 사용한다.
```c++
//CT_01.cpp
template <typename T>
void Stack<T>::push( const T& value )
{
	m_elems.push_back( value );
}
```
- Stack의 요소를 반환하는 멤버 함수 top을 구현하기 위해서 데이터형 파라미터 T를 사용할 수 있다.
```c++
template <typename T>
//CT_01.cpp
T Stack<T>::top( ) const
{
	if ( empty( ) )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}
	return m_elems.back( );
}
```
- 또한 템플릿의 멤버 함수를 클래스 내에서 인라인 함수처럼 구현할 수 있다.
```c++
//CT_01.cpp
template <typename T>
class Stack
{
...
public:
	...
	void push( const T& value )
	{
		m_elems.push_back( value );
	}
	...
```
## 클래스 템플릿의 사용
- 템플릿 객체를 사용하기 위해서는 템플릿 인자를 명시해야 한다. (c++17 부터는 추론 가능 예정 [en.cppreference.com/w/cpp/language/class_template_deduction](en.cppreference.com/w/cpp/language/class_template_deduction) 참고)
```c++
// CT_01.cpp
int main( )
{
	try
	{
		// int가 T라는 데이터형 대신 사용된다.
		// 따라서 intStack은 int의 벡터를 가지게 생성되며 Stack<int>형에서 호출된 모든 멤버 함수에 대한 코드가 인스턴스화 된다.
		Stack<int> intStack;
		// std::string의 벡터를 사용하는 객체가 생성된다.
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
```
- 클래스 템플릿에서 멤버 함수는 **사용될 때에만 인스턴스화**된다. 따라서 시간과 공간을 아낄 수 있다.
- 어떤 데이터형이 멤버 함수의 모든 연산을 처리할 수 없다 하더라도 처리할 수 없는 연산이 들어있는 함수를 호출하지 않으면 해당 데이터형에 대한 클래스를 인스턴스화할 수 있다.
- 클래스 템플릿이 정적 멤버를 갖는다면 이들은 각 데이터형에 대해서 단 한번만 인스턴스화 된다.
- 인스턴스화된 클래스 템플릿의 데이터형은 다른 데이터형들과 마찬가지로 사용될 수 있다.
```c++
// CT_02.cpp
// 배열로 사용할 수 있다.
Stack<int> istack[10];

// 데이터형 선언을 통해서 편하게 사용할 수 있다.
typedef Stack<int> IntStack;
IntStack intStack[10];

// 한정자 또한 사용할 수 있다.
using IStack = Stack<int>;
const IStack Istack;

// 포인터형에 대한 스택도 사용할 수 있다.
Stack<float*> floatPtrStack;
// c++11 이전에는 꺾쇠 사이 공백이 없으면 >> 연산자로 인식돼 문법 오류가 발생할 수 있다.
Stack<Stack<int> > intStackStack;

// c++11 부터는 >> 를 붙여서 사용할 수 있다.
Stack<Stack<int>> sincecpp11StackStack;
```
## 클래스 템플릿의 특수화
- 클래스 템플릿을 특정 템플릿 인자로 특수화할 수 있다.
```c++
// CT_03.cpp
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
```
- 클래스 템플릿을 특수화하려면 모든 멤버 함수를 특수화해야 한다.
```c++
// CT_03.cpp
template <>
class Stack<std::string>
{
private:
	std::vector<std::string> m_elems;
	T top( ) const; // error : 모두 특수화 해야 한다.

public:
	void push( const std::string& value );
};

void Stack<std::string>::push( const std::string& value )
{
	m_elems.push_back( value );
}
```
## 부분 특수화
- 클래스 템플릿은 부분적으로 특수화될 수 있습니다. 이를 통해 특정 환경에서 필요한 동작을 구현할 수 있다.
```c++
// CT_04.cpp
// Default
template <typename T1, typename T2>
class PartialSpecialization
{
};

// Partial Specializations
// 두 템플릿 파라미터가 같은 데이터형
template <typename T>
class PartialSpecialization<T, T>
{
};

// 두 번째 데이터형이 int
template <typename T>
class PartialSpecialization<T, int>
{
};

// 두 템플릿 파라미터가 포인터형
template <typename T1, typename T2>
class PartialSpecialization<T1*, T2*>
{
};

int main( )
{
	PartialSpecialization<int, float> pif;		// PartialSpecialization<T1, T2>
	PartialSpecialization<float, float> pff;	// PartialSpecialization<T, T>
	PartialSpecialization<float, int> pfi;		// PartialSpecialization<T, int>
	PartialSpecialization<int*, float*> pipip;	// PartialSpecialization<T1* T2*>
}
```
- 현재 선언에서 하나 이상의 부분 특수화가 동일한 수준으로 일치한다면 모호한 선언이므로 에러가 발생한다.
```c++
// CT_04.cpp
PartialSpecialization<int, int> pii; // Error : PartialSpecialization<T, int>, PartialSpecialization<T, T>에 일치
PartialSpecialization<int*, int*> pipip;	// Error : PartialSpecialization<T1*, T2*>, PartialSpecialization<T, T>에 일치

// PartialSpecialization<int*, int*> pipip; 의 모호함을 해결하기 위해서 아래와 같은 부가적인 부분 특수화를 제공할 수 있다.
template <typename T>
class PartialSpecialization<T*, T*>
{
};
```
## 기본 템플릿 인자
- 클래스 템플릿에는 템플릿 파라미터의 기본값을 지정할 수 있다.
```c++
// CT_05.cpp
template <typename T, typename CONT = std::vector<T>>
class Stack
{
private:
	CONT elems;

public:
	void push( const T& elems );
	void pop( );
	T top( ) const;
	bool empty( ) const
	{
		return elems.empty( );
	}

	Stack( ) = default;
	Stack( const Stack<T, CONT>& stack );
	Stack( Stack<T, CONT>&& stack );
	Stack<T, CONT>& operator=( const Stack<T, CONT>& stack );
	Stack<T, CONT>& operator=( Stack<T, CONT>&& stack );
};
```
- 기본값을 가지고 있는 파라미터라도 함수를 정의할 때는 파라미터를 명시해야 한다.
```c++
// CT_05.cpp
template <typename T, typename CONT>
void Stack<T, CONT>::push( const T& value )
{
	m_elems.push_back( value );
}
```
- 기본값을 가지고 있는 파라미터에 대한 템플릿 인자를 명시하지 않으면 기본값이 사용된다.
```c++
Stack<int> intStack; // 컨테이너로 vector를 사용
```

- 템플릿 인자를 직접 명시할 수도 있다.
```c++
Stack<double, std::deque<double>> dequeStack; // 컨테이너로 deque를 사용
```