template <typename T> // or template <class T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

class UnsurpportedOperator {};

int main( )
{
	UnsurpportedOperator lhs;
	UnsurpportedOperator rhs;

	// + 연산자를 지원하지 않아 에러
	// add( lhs, rhs );
}