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

	// + �����ڸ� �������� �ʾ� ����
	// add( lhs, rhs );
}