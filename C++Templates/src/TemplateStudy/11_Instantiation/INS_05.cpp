template <typename T>
class S
{
public:
	typedef int I;
};

// 1
template <typename T>
void f( )
{
	S<char>::I var1 = 41;
	typename S<T>::I var2 = 42;
}

int main( )
{
	f<double>( );
}
// 2
// 2a
// 2b
