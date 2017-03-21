# 템플릿 실제 사용
## 포함 모델
- 대부분의 템플릿이 아닌 코드는 선언은 헤더파일( *.hpp, *.h, *.hh 등등 )에 놓고 정의는 C 파일( *.cpp, *.c, *.cc 등등 )에 놓는다.
- 이렇게 코드를 분리하여도 프로그램은 잘 동작한다. 하지만 템플릿에서는 분리된 코드는 에러를 일으킨다.
```c++
// UTIP_01.hpp
#ifndef  UTIP_01_HPP
#define UTIP_01_HPP

template <typename T>
void print_typeof( const T& );

#endif


// UTIP_01.cpp
#include "UTIP_01.hpp"

#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& )
{
	std::cout << typeid(x).name( ) << std::endl;
}

// UTIP_MAIN_01.cpp
#include "UTIP_01.hpp"

int main( )
{
	double ice = 3.0;
	print_typeof( ice ); // 링크 에러가 발생한다.
}
```
- 템플릿이 인스턴스화되려면 컴파일러는 어떤 정의가 어떤 템플릿 인자로 인스턴스화돼야 하는지 알아야한다.
- 하지만 코드가 분리되어 있는 경우 컴파일러가 정의를 알지 못하므로 어떤 인자에 대해서 템플릿 정의를 인스턴스화해야 하는지 모른다.
- 이 문제는 아래와 같은 방법으로 컴파일러가 정의를 알 수 있도록 해주면 해결할 수 있다.

1\. 헤더 파일에 소스 코드를 포함시키는 방법.
```c++
// UTIP_01.hpp
#ifndef  UTIP_01_HPP
#define UTIP_01_HPP

template <typename T>
void print_typeof( const T& );

#include "UTIP_01.cpp"

#endif

// UTIP_01.cpp
// UTIP_01.hpp include 부분 삭제
#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}
```

2\. 선언과 정의를 하나의 헤더 파일에 작성하는 방법.
- 이런 방식으로 템플릿 코드를 작성하는 것을 포함 모델이라 부른다.
- 포함 모델을 사용하면 문제를 해결할 수 있지만 **헤더파일( UTIP_01.hpp )을 포함하는데 드는 비용이 증가**된다.
> 이 예제의 경우 UTIP_01.cppd의 <iostream>, <typeinfo>가 추가로 불러들여진다.

- 또한 포함 모델의 경우 **인라인이 아닌 함수 템플릿은 인스턴스화될 때 함수의 새로운 복사본이 생성**(=POI)되는데 이런 복사본이 자동적으로 만들어지기 때문에 각기 다른 파일에 동일한 복사본을 생성할 수 있으며 ODR을 위배하여 에러가 발생할 수 있다.
```c++
```

## 명시적 인스턴스화
- c++ 표준은 직접 템플릿을 인스턴스화할 수 있게 명시적인 인스턴스화 지시자를 제공한다.
- 포함 모델 챕터의 링커 오류를 일으켰던 예제를 명시적 인스턴스화를 통해서 해결할 수 있다.
```c++
// UTIP_02_INST.cpp
#include "UTIP_02.cpp"

template void print_typeof<double>( const double& );
```
- 명시적 인스턴스화는 template 키워드 다음에 인스턴스화하고 싶은 실체에 대해 파라미터를 완전히 치환한 선언이 뒤따르는 형태로 구성된다.
- 명시적 인스턴스화는 멤버 함수나 정적 데이터 멤버에도 동일하게 적용될 수 있다.
```c++
// UTIP_03.cpp
// int에 대한 Stack<>의 명시적 인스턴스화
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
```
- 또한 간단하게 인스턴스화할 수 있는 모든 멤버를 명시적으로 인스턴스화할 수 있다. 다만 이미 인스턴스화된 멤버와 이전에 특수화된 멤버는 제외된다.
```c++
// UTIP_03.cpp
// int에 대한 Stack<>의 명시적 인스턴스화
template class Stack<int>;

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
```
- 적어도 프로그램 내에서 각기 다른 실체에 대해서는 하나의 명시적 인스턴스화가 있어야 한다. ([ODR 참조](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/03_One%20Definition%20Rule.md))
- 명시적 인스턴스화는 **함수 템플릿, 가변 템플릿, 멤버 함수, 클래스 템플릿의 정적 데이터 멤버, 멤버 함수 템플릿**의 경우에는 템플릿 정의 같은 번역단위에 존재하면 명시적 인스턴스화 구문전에 완전한 정의가 존재하지 않아도 된다.
- 반면 **클래스 템플릿, 클래스 템플릿의 멤버 클래스, 멤버 클래스 템플릿**의 경우에는 명시적 인스턴스화 구문 전에 완전한 정의가 존재해야 한다.
- 수동 인스턴스는 어떤 실체가 인스턴스화되는지 프로그래머가 추적해서 일일이 명시적으로 인스턴스화 해주어야 하기 때문에 좋지 않다.
- 다만 아래와 같은 몇가지 장점이 있다.
1\. 프로그램의 요구에 맞게 인스턴스화 할 수 있다. 특히 헤더의 크기가 지나치게 커지지 않는다.
2\. 템플릿 정의를 가진 소스코드를 숨길 수도 있다. 하지만 이 경우 추가로 인스턴스화를 시도할 수 없다.
3\. 템플릿 인스턴스의 정확한 위치를 제어할 수 있다.

## 포함 모델과 명시적 인스턴스화 결합
- 포함 모델이나 명시적 인스턴스화중 어느 것을 쓸지 결정하지 못한 상태에서 템플릿의 선언과 정의를 두 파일에 따로 둘 수 있다.
- 포함 모델을 사용하고 싶다면 간단히 템플릿 정의 헤더를 포함시키면 된다.
```c++
// UTIP_04.cpp
#ifndef  UTIP_04_CPP
#define UTIP_04_CPP

#include "UTIP_04.hpp"

#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}

#endif

// UTIP_04_MAIN.cpp
#include "UTIP_04.hpp"
// 정의 파일을 포함 하거나
#include "UTIP_04.cpp"

int main( )
{
	double ice = 3.0;
	print_typeof( ice );
}
```
- 명시적으로 인스턴스화하고 싶다면 명시적 인스턴스 지시자를 가지는 파일을 제공할 수도 있다.
```c++
// UTIP_04_INST.cpp
// 명시적 인스턴스화 지시자를 가지는 파일을 제공

#include "UTIP_04.cpp"

template void print_typeof<double>( const double& );
```

## 분리 모델
- 분리 모델을 구현한 컴파일러가 드물고 관련 키워드 export는 c++11 부터 사용하지 않게 되었다. ([참고링크](http://en.cppreference.com/w/cpp/keyword/export))

## 템플릿과 인라인