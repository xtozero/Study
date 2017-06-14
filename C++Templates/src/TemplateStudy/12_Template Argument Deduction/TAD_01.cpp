template <typename T>
const T& max( const T& a, const T& b )
{
	return a < b ? b : a;
}

template <typename T>
typename T::ElementT at( const T& a, int i )
{
	return a[i];
}

int main( )
{
	int g = max( 1, 1.0 );
	
	int *p = &g;
	int x = at( p, 7 );
	int z = at<int*>( p, 7 );
}