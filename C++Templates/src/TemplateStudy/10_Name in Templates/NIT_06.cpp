template <template <typename> class TT> class X
{
};

template <typename T> class C
{
	C* a;				// OK : C<T>* a �� ����.
	C<void> b;			// ok
	//X<C> c;			// ���ø� ���� ����� ���� C�� ���ø��� ��Ÿ���� ����
	//X<::C> d;			// error <: �� [�� ��Ÿ���� ���Ǿ�
	X< ::C> e;
};

int main( )
{

}