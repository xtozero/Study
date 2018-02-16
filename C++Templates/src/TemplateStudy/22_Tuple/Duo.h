#pragma once

template <typename T1, typename T2>
class Duo
{
public:
	using Type1 = T1;	// 첫번째 필드의 데이터형
	using Type2 = T2;	// 두번째 필드의 데이터형
	static constexpr int N = 2;	// 필드의 수
	
	T1 v1 = T1();	// 첫번째 필드
	T2 v2 = T2();	// 두번째 필드

	Duo( ) {}
	Duo( const T1& a, const T2& b ) : v1( a ), v2( b ) {}
};

template <typename T1, typename T2>
inline Duo<T1, T2> make_duo( const T1& a, const T2& b )
{
	return Duo<T1, T2>( a, b );
}