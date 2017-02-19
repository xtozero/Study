# 함수 템플릿
- 함수 템플릿은 다양한 데이터형에 대해 호출될 수 있는 함수이다.
- 즉 함수 템플릿은 함수군을 대표한다.
- 함수의 일부 요소가 정해지지 않았을 뿐 일반 함수와 거의 동일하며 이렇게 정해지지 않고 남은 요소를 파라미터화됐다고 한다.

# 함수 템플릿 정의
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

# 함수 템플릿 사용법
- add 함수 템플릿은 다음과 같이 사용할 수 있다.
```c++
int main()
{
	cout << add( 1, 2 ) << endl; // 3이 출력
	cout << add( 3.1, 4.1 ) << endl; // 7.2이 출력
	cout << add( string( "hello " ), string( "world" ) ) << endl; // "hello world" 출력
}
```