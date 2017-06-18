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
inline void exchange( T* lhs, T* rhs )
{
	T tmp( *a );
	*a = *b;
	*b = tmp;
}

template <typename T>
void generic_algorithm( T* x, T* y )
{
	exchange( x, y );			// 올바른 알고리즘을 어떻게 선택할 것인가?
}