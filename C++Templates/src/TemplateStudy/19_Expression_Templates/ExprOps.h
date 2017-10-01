#pragma once

template <typename T>
class A_Traits
{
public:
	using ExprRef = const T&;
};

template <typename T>
class A_Scalar;

template <typename T>
class A_Traits<A_Scalar<T>>
{
public:
	using ExprRef = A_Scalar<T>;
};

template <typename T, typename OP1, typename OP2>
class A_Add
{
private:
	typename A_Traits<OP1>::ExprRef m_lhs;
	typename A_Traits<OP2>::ExprRef m_rhs;

public:
	A_Add( const OP1& lhs, const OP2& rhs ) : m_lhs( lhs ), m_rhs( rhs ) {}

	T operator[] ( size_t idx ) const
	{
		return m_lhs[idx] + m_rhs[idx];
	}

	size_t size( ) const
	{
		assert( m_lhs.size( ) == 0 || m_rhs.size( ) == 0 || m_lhs.size( ) == m_rhs.size( ) );
		return m_lhs.size( ) != 0 ? m_lhs.size( ) : m_rhs.size( );
	}
};

template <typename T, typename OP1, typename OP2>
class A_Mult
{
private:
	typename A_Traits<OP1>::ExprRef m_lhs;
	typename A_Traits<OP2>::ExprRef m_rhs;

public:
	A_Mult( const OP1& lhs, const OP2& rhs ) : m_lhs( lhs ), m_rhs( rhs ) {}

	T operator[] ( size_t idx ) const
	{
		return m_lhs[idx] * m_rhs[idx];
	}

	size_t size( ) const
	{
		assert( m_lhs.size( ) == 0 || m_rhs.size( ) == 0 || m_lhs.size( ) == m_rhs.size( ) );
		return m_lhs.size( ) != 0 ? m_lhs.size( ) : m_rhs.size( );
	}
};

template <typename T>
class A_Scalar
{
private:
	const T& m_scalar;

public:
	A_Scalar( const T& v ) : m_scalar( v ) {}

	T operator[] ( size_t ) const
	{
		return m_scalar;
	}

	size_t size( ) const
	{
		return 0;
	}
};

template <typename T, typename A1, typename A2>
class A_Subscript
{
public:
	A_Subscript( const A1& a, const A2& b ) : a1( a ), a2( b ) {}

	T operator[] ( size_t idx ) const
	{
		return a1[a2[idx]];
	}

	T& operator[] ( size_t idx )
	{
		return a1[a2[idx]];
	}

	size_t size( ) const
	{
		return a2.size( );
	}

private:
	const A1& a1;
	const A2& a2;
};