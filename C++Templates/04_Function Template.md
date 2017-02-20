# 함수 템플릿
## 개요
- 함수 템플릿은 다양한 데이터형에 대해 호출될 수 있는 함수이다.
- 즉 함수 템플릿은 함수군을 대표한다.
- 함수의 일부 요소가 정해지지 않았을 뿐 일반 함수와 거의 동일하며 이렇게 정해지지 않고 남은 요소를 파라미터화됐다고 한다.

## 함수 템플릿 정의
```c++
template <typename T>
T add( T lhs, T rhs )
{
    return lhs + rhs;
}
```
- 이 함수의 파라미터 데이터형은 템플릿 파라미터 T로서 아직 정해지지 않았다.
- 템플릿 파라미터는 다음과 같은 문법을 사용해 명시돼야 한다.
> template < parameter-list >

- T 는 데이터형 파라미터로 어떤 이름을 사용해도 좋지만 주로 T를 사용한다.
- 데이터형 파라미터는 임의의 데이터형을 대변하기 위해 사용되며 템플릿이 사용하는 동작을 제공한다면 이 함수의 인자로 어떠한 데이터형이든 사용할 수 있다.
> 위 함수는 + 연산자를 제공해야 한다.

- 데이터형 파라미터를 정의할 때 typename 대신 class를 사용할 수 있다.
> struct를 typename 대신 사용할 수 없다.

```c++
template <class T>
T add( T lhs, T rhs )
{
    return lhs + rhs;
}
```

## 함수 템플릿 사용법
- add 함수 템플릿은 다음과 같이 사용할 수 있다.
```c++
int main()
{
	cout << add( 1, 2 ) << endl; // 3이 출력
	cout << add( 3.1, 4.1 ) << endl; // 7.2이 출력
	cout << add( string( "hello " ), string( "world" ) ) << endl; // "hello world" 출력
}
```
- 일반적으로 템플릿은 어떤 데이터형이라도 다룰 수 있는 하나의 실체를 생성하지 않는다.
- 위의 예제는 세가지 데이터형에 맞는 함수가 생성된다.
```c++
// int형으로 호출하는 경우 아래와 같은 함수가 생성된다.
inline int add( int lhs, int rhs )
{
	return lhs + rhs;
}
```
- 템플릿 파라미터를 실제 데이터형으로 바꾸는 작업을 인스턴스화( instantiation )이라고 한다. 이를 통해 템플릿의 인스턴스가 생성된다.
> OOP에서 인스턴스는 클래스의 객체를 의미한다.

- 함수 템플릿 내에서 사용된 모든 연산자를 지원하지 않는 데이터형에 대해서 템플릿을 인스턴스화하면 컴파일 오류가 발생한다.
```c++
UnsurpportedOperator lhs;
UnsurpportedOperator rhs;

// + 연산자를 지원하지 않아 에러
add( lhs, rhs );
```
- 이를 위해 템플릿은 두 번 컴파일된다.
	
	1\. 인스턴스화 없이 템플릿의 문법을 검사. ex) 세미콜론이 빠졌는지 등을 확인

	2\. 인스턴스화되는 시점에서 호출이 유효한지 확인하기 위해서 템플릿 코드를 검사. ex) 지원하지 않는 함수 호출과 같은 잘못된 호출이 있는지 확인

- 이렇게 두번 컴파일되기 때문에 인스턴스화되는 시점에서 템플릿의 정의를 알아야 한다.
> 일반 함수에서는 컴파일과 링크가 분리되어 함수의 선언만으로도 함수를 컴파일하기에 충분하다.

## 인자 추론
- 함수 템플릿을 호출하면 인자를 기반으로 템플릿 파라미터가 결정된다.
- 인자 추론 과정에서 데이터형 변환은 적용되지 않는다.
```c++
add( 4, 7 ); // ok T는 두 인자에 대해 int
add( 4, 4.2 ); // error 첫 번째 T는 int 두 번째 T는 double

// 정상적으로 호출하기 위해서는 아래와 같이 호출하여야 한다.
cout <<  add( static_cast<double>(4), 4.2 ) << endl; // 두 인자가 일치하도록 명시적으로 형변환
cout <<  add<double>( 4, 4.2 ) << endl; // T의 데이터 형을 명시

template <typename T, typename U>
decltype( T() + U() ) new_add( T lhs, U rhs )
{
	return lhs + rhs;
}

cout <<  new_add( 4, 4.2 ) << endl; // 파라미터가 다른 데이터형을 가질 수 있도록 명시
```

## 템플릿에서의 인자 추론 방식
- 함수 템플릿의 선언은 대체로 이런 모습이다.
```c++
template <typename T?
void f(ParamType param) {}

f(expr) // 어떤 표현식으로 f를 호출
```
- 컴파일러는 expr을 통해서 함수 템플릿의 T와 ParamType을 추론한다.
> ParamType에 const와 같은 수식어가 붙기 때문에 T와 ParamType은 다를 수 있다.
- 템플릿의 추론 방식은 ParamType의 모양에 따라 3가지로 나눌 수 있다.

	- **ParamType이 reference 형식(T&)**일 경우

		1\. expr이 reference 형식이면 reference 부분을 무시한다. <br>
		
		2\. expr형식을 ParamType에 대해서 pattern-matching 방식으로 대응시켜 T를 결정한다.
		
		```c++
		template <typename T>
		void f( T& param ) {}

		int x = 27;
		int& rx = x;
		const int cx = x;
		const int& crx = x;
		```

	- **ParamType이 forwarding reference 형식(T&&)**일 경우

		1\. expr이 lvalue이면 T와 ParamType 모두 왼값 참조로 추론된다. <br>
		
		2\. expr이 rvalue이면 1의 규칙이 적용된다.
	
		```c++

		```

	- **1, 2에 해당되지 않는 경우**

		1\. expr이 reference 형식이면 reference 부분을 무시한다. <br>
		
		2\. expr에 const volatile mutable 키워드가 존재하면 해당 키워드를 무시한다.
		
		```c++
		class TypeDeduction
		{
		public:
			mutable int m_value;
		};

		TypeDeduction t = { 0 };
		auto deducted = t.m_value; // T: int ParamType int
		```