template <typename T>
inline const T& max( const T& lhs, const T& rhs )
{
	return lhs > rhs ? lhs : rhs;
}

template <typename DstT, typename SrcT>
inline DstT implicit_cast( const SrcT& src ) // SrcT는 인자로 부터 추론가능하지만 DstT는 불가능
{
	return x;
}

int main( )
{
	max<double>( 1.0, -3.0 );	// 명시적인 템플릿 인자
	max( 1.0, -3.0 );			// 템플릿 인자가 함수의 인자로 부터 추론
	max<int>( 1.0, 3.0 );		// 명시적인 <int>표기로 추론되지 않게 만듬. 결국 max<int>호출

	double value = implicit_cast<double>(-1);
}