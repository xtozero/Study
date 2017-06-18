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
	exchange( x, y );			// �ùٸ� �˰����� ��� ������ ���ΰ�?
}