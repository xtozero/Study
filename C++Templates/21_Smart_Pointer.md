# 스마트 포인터
동적으로 할당된 메모리는 할당된 메모리를 언제 회수할 것인가 결정하는 것과 같은 미묘한 문제를 가지고 있다. 메모리 회수에 관련된 프로그래밍을 간단히 하기 위해 다양한 기법이 나와 있으며 그중 하나가 스마트 포인터 템플릿이다.

## 예외로 부터 보호
예외는 C++ 프로그램의 신뢰성을 증가시키기 위해 도입되었으나 별생각 없이 예외를 사용한다면 문제가 발생할 뿐만 아니라 메모리 누수가 일어날 수 있다.
```c++
void do_something()
{
    Something* ptr = new Something;

    // *ptr로 몇가지 계산 수행
    ptr->perform();
    ...
    // 여기서 계산 중 예외 발생

    delete ptr;
}
```
위와 같이 객체를 생성한 후 삭제하기 전에 무엇인가 잘못돼 예외가 발생하면 객체의 메모리가 회수되지 않기 때문에 메모리가 누수된다. 이런 경우들은 exception handler를 사용해 쉽게 처리할 수 있다.
```c++
void do_something()
{
    Something* ptr = 0;
    try
    {
        Something* ptr = new Something;
        // *ptr로 몇가지 계산 수행
         ptr->perform();
         ...
         // 여기서 계산 중 예외 발생
    }
    catch(...)
    {
        delete ptr;
        throw; // 잡힌 예외를 다시 던짐
    }

    delete ptr;
}
```
이 경우 관리할만하지만 예외 처리 경로가 일반 경로보다 길고 객체를 두 군데에서 삭제하고 있다. 이런 방식을 사용하면 상황이 금방 나빠진다. 한 함수에서 객체를 두 개 생성해야 한다면 코드가 더 길어질 것이다.

## 소유자
다행이도 예외 처리에서 동적할당 객채의 문제를 해결하는 방법은 그다지 어렵지 않다. 포인터와 거의 동일하게 동작하지만 자기 자신이 소멸하거나 다른 포인터가 할당될 경우 스스로 자신이 가리키고 있던 객체를 삭제하는 클래스를 작성하면 된다.
```c++
// Holder.h
template <typename T>
class Holder
{
private:
	T* ptr = nullptr;

public:
	explicit Holder( T* p ) : ptr( p ) {}

	~Holder( )
	{
		delete ptr;
	}

	Holder<T>& operator=( T* p )
	{
		delete ptr;
		ptr = p;
		return *this;
	}

	T& operator*( ) const
	{
		return *ptr;
	}

	T* operator->( ) const
	{
		return ptr;
	}

	T* get( ) const
	{
		return ptr;
	}

	T* release( )
	{
        T* ret = ptr;
		ptr = nullptr;
        return ret;
	}

	void exchange_with( Holder<T>& h )
	{
		std::swap( ptr, h.ptr );
	}

	void exchange_with( T*& p )
	{
		std::swap( ptr, p )
	}

private:
	Holder( const Holder<T>& );
	Holder<T>& operator=( const Holder<T>& );
};
```
소유자는 ptr이 참조하는 객체에 대한 소유권을 갖는다. 소유자가 가진 객체를 삭제할 때 delete가 사용되기 때문에 이 객체는 new로 생성돼야 한다. 앞서 살펴본 예외 예제는 다음과 같이 바꿔 작성할 수 있다.
```c++
// SP_01.cpp
void do_something( )
{
	Holder<Something> first( new Something );
	first->perform( );
}
```
이 방식은 훨씬 깔끔하며 Holder 소멸자 덕분에 예외에서 안전하고 정규 경로를 따라 함수가 끝나더라도 자동으로 삭제가 이뤄진다. 소유자는 C++11 부터 unique\_ptr 이라는 형태로 추가되었다.

### 멤버로서의 소유자
클래스 내에서 소유자를 사용해 자원이 새는 것을 막을 수도 있다. 멤버가 일반 포인터 대신 소유자 멤버를 가진다면 소유자가 가리키는 객체는 소유자가 삭제될 때 같이 삭제되므로 소멸자에서 명시적으로 처리할 필요가 없다.

### Holder의 한계
Holder 템플릿만으로는 모든 문제를 해결할 수 없다. 다음과 같은 경우를 살펴보자.
```c++
// SP_02.cpp
Something* load_something( )
{
	Something* result = new Something;

	read_something( result );

	return result;
}
```
이 예제는 다음 두 사실 때문에 코드가 더 복잡해진다.
1. 함수 내부에서 read\_something() 함수라고 하는 일반 포인터를 인자로 받길 기대하는 함수를 호출한다.
2. load\_something()은 일반 포인터를 반환한다.

이 예제를 소유자를 통해 바꾸면 예외에서 안전해지긴 하지만 좀 더 복잡해진다.
```c++
// SP_02.cpp
Something* load_something_ver_holder( )
{
	Holder<Something> result( new Something );

	read_something( result.get() );

	Something* ret = result.get( );
	result.release( );

	return ret;
}
```
read\_something() 은 Holder 형에 대해 알지 못하는 함수일 것이다. 그래서 get()을 통해 실제 포인터를 전달해야 했다. 이 멤버 함수를 사용할때 소유자는 여전히 객체에 대한 제어를 유지하고 있으므로 함수의 반환 값을 받는 수신자는 자신이 받은 포인터가 가리키는 객체를 자신이 소유한 것이 아니라는 사실을 이해해야 한다.
get()과 같은 함수가 제공되지 않는다면 사용자 정의 간접 연산자인 *와 내장 주소 연산자인 &를 사용할 수도 있다. 그 이외에도 -> 연산자를 명시적으로 호출하는 방법도 있다.
```c++
read_something(&*result);
read_something(result.operator->());
```

### 소유권 복사
Holder 템플릿에서 복사 생성자와 복사 할당 연산자를 private로 선언해 소유자를 복사하는 것을 금지하였다. 복사는 대체로 원본과 동일한 두 번째 객체를 원하기 때문이다. 소유자를 복사하면 복사본도 객체를 소유하고 있기 때문에 두 소유자가 하나의 객체를 할당 해제하려 할 것이다. 따라서 소유자에 있어 복사는 바람직한 연산이 아니다.

### 함수 호출 너머로 소유자 복사
함수 호출을 통해 전달해야 할 경우는 좀 더 미묘한 상황이 발생할 수 있다. 다음과 같은 경우를 살펴보자
```c++
MyClass x;
callee(h1.release(), x); // x 전달 시 예외가 일어난다면?
```
컴파일러가 먼저 h1.release()를 처리하기로 했다면 소유자 h1에 의해 소유되었던 객체를 해제를 책임질 객체가 없기 때문에 x를 복사 전달하는 과정에서 예외가 발생하면 메모리 누수가 발생한다. 따라서 소유자는 함상 참조로 전달되어야 한다.
불행히도 소유자를 참조로 반환하는 것은 쉽지 않다. 참조로 반환하려면 소유자가 함수 자체보다 더 오랫동안 살아남아야 하는데 소유자는 지역변수이기 때문에 참조로 반환할 수 없다. 소유자를 반환하면서 예외에 안전한 코드를 작성하기 위해서는 C++11부터 추가된 move연산자를 사용해 소유권을 이전해야 한다.
```c++
// Holder.h
template <typename T>
class Holder
{
    //...

	Holder( Holder<T>&& h )
	{
		ptr = h.ptr;
		h.ptr = nullptr;
	}

	Holder<T>& operator=( Holder<T>&& h )
	{
		ptr = h.ptr;
		h.ptr = nullptr;
		return *this;
	}
    // ...
}

// SP_03.cpp
Holder<Something> creator()
{
    Holder<Something> h(new Something);
    MyClass x;
    return std::move(h);
}
```

## 참조 카운트
동적으로 할당된 객체에 관한 법칙은 간단하다. 동적으로 할당된 객체를 아무도 참조하지 않는다면 그 객체를 삭제하고 메모리를 재활용할 수 있어야 한다. 이런 정책을 자동화하는 방법으로 자주 구현돼온 한 방법으로 참조 카운트 방식을 들 수 있다.
각 객체는 자신을 가리키는 포인터가 몇 개인지 세는 카운터를 갖고 카운터 값이 0이 되면 객체를 삭제한다. C++에서 이 방식을 활용하기 위해서는 몇 가지 관례를 지켜야 한다. 객체에 대한 모든 포인터의 생성, 복사, 삭제를 추적하는 것은 실용적이지 않기 때문에 참조 카운트를 하는 객체에 대한 포인터들만을 스마트 포인터의 특수한 종류로 취급한다.
참조 카운트는 C++11 에서 shared\_ptr 이라는 형태로 추가되었다.
여기서는 참조 카운트 스마트 포인터의 구현을 살펴본다.

## 카운터 위치
객체에 대한 포인터의 수를 세는 것이 참조 카운트의 목적이기 때문에 객체에 카운터를 두는 것은 합당해 보인다. 하지만 참조 카운터를 생각하지 않고 만든 객체형을 가리켜야 한다면 이 방식을 쓸 수 없다.
카운트할 객체 내에 카운터가 없다면 카운터는 객체만큼 오래 살아남을 수 있어야 한다. 즉 카운터는 동적할당되어야 한다.

## 동시 카운터 접근
한 개의 스레드만 있다면 매우 직관적으로 카운터를 관리할 수 있다. 하지만 멀티스레드 상황에서는 각기 다른 스레드 내 스마트 포인터들이 카운터를 공유한다. 이 경우 두 스레드에서 들어온 동시 증감 연산이 적절한 순서로 실행될 수 있도록 잠금이 필요하다.
잠금이 어떻게 일어나는지 명시하는 대신 카운터에 잠금 연산을 도입하기에 충분히 높은 수준을 갖는 인터페이스를 명시했다. 카운터는 다음과 같은 인터페이스를 가져야한다.
```c++
class CounterPolicy
{
public:
	CounterPolicy( );
	CounterPolicy( const CounterPolicy& );
	~CounterPolicy( );
	CounterPolicy& operator=( const CounterPolicy& );

	void init( T* );		// 1로 초기화 카운터 할당을 포함할 수 있음
	void dispose( T* );		// 카운터의 삭제를 포함할 수도 있음
	void increment( T* );	// 1 증가
	void decrement( T* );	// 1 감소
	bool is_zeof( T* );		// 0 인지 검사
};
```

## 소멸과 할당 해제
객체를 가리키고 있는 카운터 포인터가 없다면 위에서 정의한 정책은 해당 객체를 삭제한다. C++에서는 표준 delete 연산자를 가지고 객체를 삭제한다. 하지만 항상 그런것만은 아니다. 때때로는 free()와 같은 다른 함수를 사용해 할당 해제되어야만 한다. 객체 삭제에 대한 합리적인 표준이 있는 건 아니기 때문에 삭제를 위한 객체 정책을 따로 추가했다.
```c++
class ObjectPolicy
{
	public:
		ObjectPolicy();
		ObjectPolicy( const ObjectPolicy& );
		~ObjectPolicy();
		ObjectPolicy& operator=( const ObjectPolicy& );

		void dispose( T* ); // 객체를 삭제
}
```
다음과 같은 간단한 객체 정책을 사용할 수 있다.
```c++
// CounthingPtr.h

class StandardObjectPolicy
{
public:
	template <typename T> void dispose( T* object )
	{
		delete object;
	}
};
```
물론 이 정책은 할당된 배열을 해제하는 경우에는 동작하지 않는데 이런 경우는 대안 정책을 도입하여 간단하게 해결할 수 있다.
```c++
// CounthingPtr.h

class StandardArrayPolicy
{
public:
	template <typename T> void dispose( T* object )
	{
		delete[] object;
	}
};
```

## CountingPtr 템플릿
정책 인터페이스를 정했으니 CounthingPtr 인터페이스 자체를 구현하자.
```c++
// CounthingPtr.h

#include <cassert>

class StandardObjectPolicy
{
public:
	template <typename T> void dispose( T* object )
	{
		delete object;
	}
};

class StandardArrayPolicy
{
public:
	template <typename T> void dispose( T* object )
	{
		delete[] object;
	}
};

template <typename T, 
	typename CounterPolicy = SimpleReferenceCount,
	typename ObjectPolicy = StandardObjectPolicy>
class CountingPtr : private CounterPolicy, private ObjectPolicy
{
private:
	using CP = CounterPolicy;
	using OP = ObjectPolicy;

	T* object_pointed_to = nullptr;
public:
	explicit CountingPtr( T* p )
	{
		init( p ); // 포인터로 초기화
	}

	CountingPtr( const CountingPtr<T, CP, OP>& cp ) :
		CP( static_cast<const CP&>( cp ) ),
		OP( static_cast<const OP&>( cp ) )
	{
		attach( cp ); // 포인터를 복사하고 카운터를 증가시킴
	}

	~CountingPtr( )
	{
		detach( );
	}

	CountingPtr<T, CP, OP>& operator= ( T* p )
	{
		assert( p != object_pointed_to );
		detach( );
		init( p );
		return *this;
	}

	CountingPtr<T, CP, OP>& operator=( const CountingPtr<T, CP, OP>& cp )
	{
		if ( this->object_pointed_to != cp.object_pointed_to )
		{
			detach( );
			CP::operator=( static_cast<const CP&>( cp ) );
			OP::operator=( static_cast<const OP&>( cp ) );
			attach( cp )
		}

		return *this;
	}


	T* operator->( ) const
	{
		return object_pointed_to;
	}

	T& operator*( ) const
	{
		return *object_pointed_to;
	}

private:
	void init( T* p )
	{
		if ( p != nullptr )
		{
			CounterPolicy::init( p );
		}
		object_pointed_to = p;
	}

	void attach( const CountingPtr<T, CP, OP>& cp )
	{
		object_pointed_to = cp.object_pointed_to;
		if ( cp.object_pointed_to != nullptr )
		{
			CounterPolicy::increment( cp.object_pointed_to );
		}
	}

	void detach( )
	{
		if ( object_pointed_to != nullptr )
		{
			CounterPolicy::decrement( object_pointed_to );
			if ( CounterPolicy::is_zero( object_pointed_to ) )
			{
				CounterPolicy::dispose( object_pointed_to );
				ObjectPolicy::dispose( object_pointed_to );
			}
		}
	}
};
```
복사 할당 연산자로 자신을 할당하는 경우를 조심히 처리해야 한다는 점을 빼면 이 템플릿의 복잡도는 높지 않다. 대부분의 할당 연산자는 자신이 가리키고 있던 객체에서 카운터 포인터를 떼어내고 카운트가 0이 되면 객체를 삭제한다.
널 포인터는 관련된 카운터를 가지지 않기 때문에 해당 포인터가 널인지 아닌지를 확인해야 한다.

## 간단한 비침습성 카운터
이제 카운터 정책에 대한 코드를 작성할 차례이다. 가리키는 객체 안에 저장되지 않은 카운터( 비침습성 nonivasive )를 위한 정책을 살펴보자.
비침습성 카운터에서의 가장 큰 문제는 할당이다. 비침습성 카운터는 적어도 마지막 스마트 포인터가 소멸되기 전까지는 살아남아야 한다.
```c++
// CounthingPtr.h

class SimpleReferenceCount
{
public:
	template <typename T> 
	void init( T* )
	{
		counter = new size_t;
		*counter = 1;
	}

	template <typename T>
	void dispose( T* )
	{
		delete counter;
	}

	template <typename T>
	void increment( T* )
	{
		++*counter;
	}

	template <typename T>
	void decrement( T* )
	{
		--*counter;
	}

	template <typename T>
	bool is_zero( T* )
	{
		return *counter == 0;
	}

private:
	size_t* counter = nullptr;
};
```
위 정책은 빈 클래스가 아니기 때문에 CountingPtr의 크기가 커진다. 스마트 포인터 클래스에 직접 정책을 저장하는 대신 객체의 포인터를 카운터에 저장한다면 클래스의 크기가 줄어들 것이다.
이 특정 정책은 카운트될 객체 자체는 사용하지 않는다. 이 파라미터를 사용하는 다른 정책을 알아보자.

## 간단한 침습성 카운터 템플릿
침습성 카운터 정책은 객체 자신의 데이터형에 카운터를 두는 방식이다. 이런 방식을 사용하려면 객체형을 설계할 때부터 카운터를 고려해야한다.
```c++
// CounthingPtr.h

template <typename ObjectT, typename CountT, CountT ObjectT::*CountP>
class MemberReferenceCount
{
public:
	template <typename T>
	void init( T* object )
	{
		object->*CountP = 1;
	}

	template <typename T>
	void dispose( T* object )
	{
	}

	template <typename T>
	void increment( T* object )
	{
		++object->*CountP;
	}

	template <typename T>
	void decrement( T* object )
	{
		--object->*CountP;
	}

	template <typename T>
	bool is_zero( T* object )
	{
		return object->*CountP == 0;
	}
};
```

## 정리
스마트 포인터 템플릿은 컨테이너 템플릿과 함께 템플릿을 사용할 수 있는 좋은 응용 사례이다.
C++ 표준 라이브러리에서는 unique\_ptr, shared\_ptr, weak\_ptr 이라는 스마트 포인터 템플릿을 제공한다.