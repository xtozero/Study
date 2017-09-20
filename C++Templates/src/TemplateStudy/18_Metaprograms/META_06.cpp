template <typename T, typename U>
struct Doublify {};

template <int N>
struct Trouble
{
	typedef Doublify<typename Trouble<N - 1>::LongType, typename Trouble<N - 1>::LongType> LongType;
};

template <>
struct Trouble<0>
{
	typedef double LongType;
};

Trouble<10>::LongType ouch;

int main( )
{

}