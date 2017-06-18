template <typename T>
class Array
{
private:
	T* data = nullptr;

public:
	//...

	void exchange_with( Array<T>* args )
	{
		T* tmp = data;
		data = args->data;
		args->data = tmp;
	}
};

template <typename T>
inline void quick_exchange( T* a, T* b )				// 1
{
	T tmp( *a );
	*a = *b;
	*b = tmp;
}

template <typename T>
inline void quick_exchange( Array<T>* a, Array<T>* b )	// 2
{
	a->exchange_with( b );
}

int main( )
{
	int x = 42, y = -7;
	quick_exchange( &x, &y );

	Array<int> arr1, arr2;
	quick_exchange( &arr1, &arr2 );
}