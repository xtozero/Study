template <typename T>
inline const T& max( const T& lhs, const T& rhs )
{
	return lhs > rhs ? lhs : rhs;
}

template <typename DstT, typename SrcT>
inline DstT implicit_cast( const SrcT& src ) // SrcT�� ���ڷ� ���� �߷а��������� DstT�� �Ұ���
{
	return x;
}

int main( )
{
	max<double>( 1.0, -3.0 );	// ������� ���ø� ����
	max( 1.0, -3.0 );			// ���ø� ���ڰ� �Լ��� ���ڷ� ���� �߷�
	max<int>( 1.0, 3.0 );		// ������� <int>ǥ��� �߷е��� �ʰ� ����. �ᱹ max<int>ȣ��

	double value = implicit_cast<double>(-1);
}