#include <iostream>
#include <typeinfo>

template <typename T>
class Outer
{
public:
	template <typename U>
	class Inner
	{
	private:
		static int count;
	};

	static int code;
	void print( ) const
	{
		std::cout << "generic" << std::endl;
	}
};

template <typename T>
int Outer<T>::code = 6;

template <typename T>
template <typename U>
int Outer<T>::Inner<U>::count = 7;

template <>
class Outer<bool>
{
	template<typename U>
	class Inner
	{
	private:
		static int count;
	};
	void print( ) const {}
};

// template <>
// int Outer<void>::code;

template <>
void Outer<void>::print( ) const;

template <>
int Outer<void>::code = 12;

template <>
void Outer<void>::print() const
{
	std::cout << "Outer<void>" << std::endl;
}

class DefaultInitOnly
{
public:
	DefaultInitOnly() {}

	int value;
private:
	DefaultInitOnly( const DefaultInitOnly& ); // 복사 불가
};

template <typename T>
class Statics
{
public:
	static T sm;
};

// 다음은 선언이다.
// 정의를 제공할 방법이 없다.
template<>
DefaultInitOnly Statics<DefaultInitOnly>::sm;

template <>
template <typename X>
class Outer<wchar_t>::Inner
{
public:
	static long count;	// 멤버 데이터형이 바뀌었음
};

template <>
template <typename X>
long Outer<wchar_t>::Inner<X>::count;

template<>
template<>
class Outer<char>::Inner<wchar_t>
{
public:
	enum { count = 1 };
};

template <typename X>
template <>
class Outer<X>::Inner<void>; // error : tempalte<>는 템플릿 파라미터의 목록 뒤에 위치할 수 없음

template <>
class Outer<bool>::Inner<wchar_t>
{
public:
	enum { count = 2 };
};

int main( )
{
	Outer<void> o;
	std::cout << o.code << std::endl;

	std::cout << Statics<DefaultInitOnly>::sm.value << std::endl;
}