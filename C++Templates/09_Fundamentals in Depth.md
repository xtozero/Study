# 템플릿 기호 원리의 깊은 이해
## 개요
- 이 장에서는 템플릿 선어, 템플릿 파라미터에 대한 제한과 템플릿 인자에 대한 제약 등에 대해 자세히 살펴본다.

## 파라미터화된 선언
- c++은 클래스 템플릿과 함수 템플릿이라는 두 종류의 템플릿을 지원한다. 물론 여기에는 멤버 템플릿도 포함된다.
- 이 같은 템플릿 선언은 일반 클래스나 함수와 유사하지만 다음과 같은 형테의 파라미터화 절이 붙는다는 점이 다르다.
```c++
template <... 파라미터 ...>
```
- 멤버 템플릿이 자신의 클래스 내부에서 선언될 때와 외부에서 선언될 때 파라미터화 절은 다음과 같이 작성한다.
```c++
// FID_01.cpp
template <typename T>
class List
{
public:
	template <typename T2>
	List( const List<T2>& list );
};

template <typename T>
template <typename T2>
List<T>::List( const List<T2>& list )
{
	// ...
}
```
- 멤버 템플릿이 자신의 클래스 외부에서 정의될 떄 파라미터화 절은 **가장 밖을 둘러싼 클래스 템플릿에서부터 하나씩 나열**된다.
- 공용체 템플릿도 선언할 수 있고 클래스 템플릿의 일종으로 간주된다.
```c++
// FID_01.cpp
template <typename T>
union AllocChuck
{
	T object;
	unsigned char bytes[sizeof( T )];
};
```
- 함수 템플릿은 다른 일반 함수 선언처럼 기본 호출 인자를 가질 수 있다.
```c++
// FID_01.cpp
template <typename T>
void report_top( const std::vector<T>&, int number = 10 )
{
	// ...
}

template <typename T>
void fill( const std::vector<T>&, const T& = T( ) )
{
	// ...
}
```
- 두 번째 선언을 보면 기본 호출 인자가 템플릿 파라미터에 종속될 수 있다는걸 알 수 있다.
- 함수 템플릿이 인스턴스화 될 떄 기본 호출 인자를 명시적으로 제공한다면 기본 인자는 인스턴스화되지 않는다. 이를 통해서 특정 T에서는 인스턴스화될 수 없는 기본 호출 인자를 사용하더라도 오류가 발생하지 않게 할 수 있다.
```c++
class Value
{
public:
	Value( int ) {}		// 기본 생성자 없음
};

int main( )
{
	Value zero( 0 );
	std::vector<Value> v;

	fill( v, zero ); // T() 가 사용되지 않음.
	// fill( v ); error T() 가 사용됨.
}
```
- 기본적인 두 종류의 템플릿과 더불어 다음 세 가지 클래스 템플릿 멤버의 정의도 모두 파라미터화될 수 있다.
1\. 클래스 템플릿의 멤버 함수 정의

2\. 클래스 템플릿에 내포된 클래스 멤버 정의

3\. 클래스 템플릿의 정적 데이터 멤버 정의

- 이들도 파라미터화될 수 있지만 이 정의가 항상 템플릿을 의미하는 것은 아니다. 이들의 파라미터는 전적으로 그들이 멤버로 속한 템플릿에 의해 결정된다.
```c++
template <int N>
class CupBoard
{
	void open( );
	class Shelf;
	static double total_weight;
};

template <int N>
void CupBoard<N>::open( )
{
	// ...
}

template <int N>
class CupBoard<N>::Shelf
{
	// ...
};

template <int N>
double CupBoard<N>::total_weight = 0.0;
```
- 파라미터화 선언을 보통 템플릿이라고 부르지만 위의 예제처럼 꼭 들어맞는 건 아니다.

## 가상 멤버 함수
- 멤버 함수 템플릿은 virtual로 선언 될 수 없다.
> 가상 함수 호출 매커니즘은 대체로 가상 함수 하나당 하나의 엔트리를 갖는 고정 크기의 테이블(vftable)을 쓰는 방식으로 구현되는데 멤버 함수 템플릿은 템플릿 인자에 따라 무한히 인스턴스화 될 수 있기 때문이다.

- 이와 대조적으로 클래스 템플릿의 일반 멤버는 클래스가 인스턴스화될 때 그 수가 고정되기 때문에 virtual로 선언될 수 있다.
```c++
template <typename T>
class Dynamic
{
public:
	virtual ~Dynamic( ) {} // ok Dynamic<T> 당 하나의 소멸자
	template <typename T2>
	virtual void copy( const T2& ) {} // error Dynamic<T>의 인스턴스 내에서 copy() 인스턴스의 수를 결정할 수 없으므로
};
```

## 템플릿의 링크