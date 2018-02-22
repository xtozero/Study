 #pragma once
#include "Duo_Final.h"

class NullT {};

template<typename P1,
		typename P2 = NullT,
		typename P3 = NullT,
		typename P4 = NullT,
		typename P5 = NullT>
class Tuple : public Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>::BaseT>
{
public:
	using BaseT = Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>::BaseT>;

	Tuple( ) {}
	Tuple( typename add_const_lvalue_reference<P1>::type a1,
			typename add_const_lvalue_reference<P2>::type a2,
			typename add_const_lvalue_reference<P3>::type a3 = NullT( ),
			typename add_const_lvalue_reference<P4>::type a4 = NullT( ),
			typename add_const_lvalue_reference<P5>::type a5 = NullT( ) ) : BaseT( a1, Tuple<P2, P3, P4, P5, NullT>( a2, a3, a4, a5 ) ) {}
};


// 재귀적 상속을 끝내기 위한 특수화
template<typename P1, typename P2>
	class Tuple<P1, P2, NullT, NullT, NullT> : public Duo<P1, P2>
{
public:
	using BaseT = Duo<P1, P2>;

	Tuple( ) {}
	Tuple( typename add_const_lvalue_reference<P1>::type a1,
			typename add_const_lvalue_reference<P2>::type a2,
			typename add_const_lvalue_reference<NullT>::type = NullT( ),
			typename add_const_lvalue_reference<NullT>::type = NullT( ),
			typename add_const_lvalue_reference<NullT>::type = NullT( ) ) : BaseT(a1, a2) {}
};

// 한 인자를 위한 편의 함수
template <typename T1>
inline Tuple<T1> make_tuple( const T1& a1 )
{
	return Tuple<T1>( a1 );
}

// 두 인자를 위한 편의 함수
template <typename T1, typename T2>
inline Tuple<T1, T2> make_tuple( const T1& a1, const T2& a2 )
{
	return Tuple<T1, T2>( a1, a2 );
}

// 세 인자를 위한 편의 함수
template <typename T1, typename T2, typename T3>
inline Tuple<T1, T2, T3> make_tuple( const T1& a1, const T2& a2, const T3& a3 )
{
	return Tuple<T1, T2, T3>( a1, a2, a3 );
}

// 네 인자를 위한 편의 함수
template <typename T1, typename T2, typename T3, typename T4>
inline Tuple<T1, T2, T3, T4> make_tuple( const T1& a1, const T2& a2, const T3& a3, const T4& a4 )
{
	return Tuple<T1, T2, T3, T4>( a1, a2, a3, a4 );
}

// 다섯 인자를 위한 편의 함수
template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline Tuple<T1, T2, T3, T4, T5> make_tuple( const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5 )
{
	return Tuple<T1, T2, T3, T4, T5>( a1, a2, a3, a4, a5 );
}
