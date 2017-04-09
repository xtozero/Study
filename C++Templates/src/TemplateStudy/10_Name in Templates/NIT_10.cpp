#include <iostream>

template <typename T>
class Shell
{
public:
	template <int N>
	class In
	{
	public:
		template <int M>
		class Deep
		{
		public:
			template <typename U>
			void g( )
			{
				std::cout << "g()" << std::endl;
			}
		};
	};
};

template <typename T, int N>
class Weird
{
public:
	void case1( typename Shell<T>::template In<N>::template Deep<N>* p )
	{
		p->template g<int>( );
	}

	void case2( typename Shell<T>::template In<N>::template Deep<N>& p )
	{
		p.template g<int>( );
	}
};

int main( )
{
	Weird<int, 10> a;

	Shell<int>::In<10>::Deep<10> b;
	a.case1( &b );
}