/*
template <typename T>
class Array
{
	// ...
};

// 함수 템플릿의 오버로딩이 불가능했던 때에는 이렇게 operator== 을 정의하면
// 다른 클래스를 위한 operator==을 정의할 수 없었다.
template <typename T>
bool operator==( const Array<T>& lhs, const Array<T>& rhs )
{
	// ...
}
*/

template <typename T>
class Array;

template <typename T>
bool ArrayAreEqual( const Array<T>& lhs, const Array<T>& rhs );

// 바튼-넥만 트릭을 사용한 경우
template <typename T>
class Array
{
public:
	friend bool operator==( const Array<T>& lhs, const Array<T>& rhs )
	{
		return ArrayAreEqual( lhs, rhs ); // example code
	}
};

// 컴파일 에러를 내지 않기 위한 함수 구현 부
template<typename T>
bool ArrayAreEqual( const Array<T>& lhs, const Array<T>& rhs )
{
	return false;
}

// 주입된 프렌드 함수의 가시화
class S {};

template <typename T>
class Wrapper
{
private:
	T object;
public:
	Wrapper( T obj ) : object( obj ) {}
	friend void f( const Wrapper<T>& arg ) {}
};

int main()
{
	S s;
	Wrapper<S> w( s );

	f( w );
	f( s ); // vs 2015 : ok , g++ : error
}