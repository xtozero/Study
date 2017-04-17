template <template <typename> class TT> class X
{
};

template <typename T> class C
{
	C* a;				// OK : C<T>* a 와 같다.
	C<void> b;			// ok
	//X<C> c;			// 템플릿 인자 목록이 없는 C는 템플릿을 나타내지 않음
	//X<::C> d;			// error <: 는 [를 나타내는 동의어
	X< ::C> e;
};

int main( )
{

}