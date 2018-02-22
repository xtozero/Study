#pragma once

#include <type_traits>

template <typename T>
class add_const_lvalue_reference
{
public:
	using type = const T&;
};

template <>
class add_const_lvalue_reference<void>
{
public:
	using type = void;
};

template <typename T1, typename T2>
class Duo
{
public:
	using Type1 = T1;
	using Type2 = T2;
	static constexpr int N = 2;

private:
	T1 value1 = T1();
	T2 value2 = T2();

public:
	Duo( ) {}
	Duo( const T1& a, const T2& b ) : value1( a ), value2( b ) {}

	// 생성 중 묵시적 데이터 형 변환을 위해
	template <typename U1, typename U2>
	Duo( const Duo<U1, U2>& d ) : value( d.v1( ) ), value2( d.v2( ) ) {}

	// 할당 중 묵시적 데이터 형 변환을 위해
	template <typename U1, typename U2>
	Duo<T1, T2>& operator=( const Duo<U1, U2>& d )
	{
		value1 = d.value1;
		value2 = d.value2;
		return *this;
	}

	T1& v1( )
	{
		return value1;
	}
	const T1& v1( ) const
	{
		return value1;
	}

	T2& v2( )
	{
		return value2;
	}
	const T2& v2( ) const
	{
		return value2;
	}
};

// 비교 연산자 (혼합된 데이터형 허용)
template <typename T1, typename T2, typename U1, typename U2>
inline bool operator==( const Duo<T1, T2>& lhs, const Duo<U1, U2>& rhs )
{
	return lhs.v1( ) == rhs.v1( ) && lhs.v2( ) == rhs.v2( );
}

template <typename T1, typename T2, typename U1, typename U2>
inline bool operator!=( const Duo<T1, T2>& lhs, const Duo<U1, U2>& rhs )
{
	return !( lhs == rhs );
}

// 생성과 초기화를 편리하게 하는 함수
template <typename T1, typename T2>
inline Duo<T1, T2> make_duo( const T1& a, const T2& b )
{
	return Duo<T1, T2>( a, b );
}

template <typename A, typename B, typename C>
class Duo<A, Duo<B, C>>
{
public:
	using T1 = A;
	using T2 = Duo<B, C>;
	static constexpr int N = T2::N + 1;

private:
	T1 value1 = T1();
	T2 value2 = T2();

public:
	Duo( ) {}
	Duo( const T1& a, const T2& b ) : value1( a ), value2( b ) {}

	// 생성 중 묵시적 데이터 형 변환을 위해
	template <typename U1, typename U2>
	Duo( const Duo<U1, U2>& d ) : value( d.v1( ) ), value2( d.v2( ) ) {}

	// 할당 중 묵시적 데이터 형 변환을 위해
	template <typename U1, typename U2>
	Duo<T1, T2>& operator=( const Duo<U1, U2>& d )
	{
		value1 = d.value1;
		value2 = d.value2;
		return *this;
	}

	T1& v1( )
	{
		return value1;
	}
	const T1& v1( ) const
	{
		return value1;
	}

	T2& v2( )
	{
		return value2;
	}
	const T2& v2( ) const
	{
		return value2;
	}
};

template <typename A>
class Duo<A, void>
{
public:
	using T1 = A;
	using T2 = void;
	static constexpr int N = 1;

private:
	T1 value1 = T1();

public:
	Duo( ) {}
	Duo( const T1& a ) : value1( a ) {}

	T1& v1( )
	{
		return value1;
	}
	const T1& v1( ) const
	{
		return value1;
	}

	void v2( ) {}
	void v2( ) const {}
};

template <int N, typename T>
class DuoT
{
public:
	using ResultT = void; // 일반적으로 결과 데이터형은 void
};

// 평범한 듀오의 첫 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoT<1, Duo<A, B>>
{
public:
	using ResultT = A;
};

// 평범한 듀오의 두 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoT<2, Duo<A, B>>
{
public:
	using ResultT = B;
};

// 재귀적 듀오의 N번째 필드를 위한 특수화
template <int N, typename A, typename B, typename C>
class DuoT<N, Duo<A, Duo<B, C>>>
{
public:
	using ResultT = typename DuoT<N - 1, Duo<B, C>>::ResultT;
};

// 재귀적 듀오의 첫번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoT<1, Duo<A, Duo<B, C>>>
{
public:
	using ResultT = A;
};

// 재귀적 듀오의 두번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoT<2, Duo<A, Duo<B, C>>>
{
public:
	using ResultT = B;
};

template <int N, typename T>
class DuoValue
{
public:
	static void get( T& ) {}	// 기본적으로는 반환값이 없다.
	static void get( const T& ) {}
};

// 평범한 듀오의 첫 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoValue<1, Duo<A, B>>
{
public:
	static A& get( Duo<A, B>& d )
	{
		return d.v1( );
	}

	static A get( const Duo<A, B>& d )
	{
		return d.v1( );
	}
};

// 평범한 듀오의 두 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoValue<2, Duo<A, B>>
{
public:
	static B& get( Duo<A, B>& d )
	{
		return d.v2( );
	}

	static B get( const Duo<A, B>& d )
	{
		return d.v2( );
	}
};

// 재귀적 듀오의 N번째 필드를 위한 특수화
template <int N, typename A, typename B, typename C>
class DuoValue<N, Duo<A, Duo<B, C>>>
{
public:
	static typename std::add_lvalue_reference<typename DuoT<N, Duo<A, Duo<B, C>>>::ResultT>::type get( Duo<A, Duo<B, C>>& d )
	{
		return DuoValue<N - 1, Duo<B, C>>::get( d.v2( ) );
	}

	static typename add_const_lvalue_reference<typename DuoT<N, Duo<A, Duo<B, C>>>::ResultT>::type get( const Duo<A, Duo<B, C>>& d )
	{
		return DuoValue<N - 1, Duo<B, C>>::get( d.v2( ) );
	}
};

// 재귀적 듀오의 1번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoValue<1, Duo<A, Duo<B, C>>>
{
public:
	static A& get( Duo<A, Duo<B, C>>& d )
	{
		return d.v1( );
	}

	static A get( const Duo<A, Duo<B, C>>& d )
	{
		return d.v1( );
	}
};

// 재귀적 듀오의 2번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoValue<2, Duo<A, Duo<B, C>>>
{
public:
	static B& get( Duo<A, Duo<B, C>>& d )
	{
		return d.v2( ).v1( );
	}

	static B get( const Duo<A, Duo<B, C>>& d )
	{
		return d.v2( ).v1( );
	}
};

template <int N, typename A, typename B>
inline typename std::add_lvalue_reference<typename DuoT<N, Duo<A, B>>::ResultT>::type val( Duo<A, B>& d )
{
	return DuoValue<N, Duo<A, B>>::get( d );
}

template <int N, typename A, typename B>
inline typename add_const_lvalue_reference<typename DuoT<N, Duo<A, B>>::ResultT>::type val( const Duo<A, B>& d )
{
	return DuoValue<N, Duo<A, B>>::get( d );
}