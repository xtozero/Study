template <typename T>
const T& max( const T&, const T& ) {} // �⺻ ���ø�

template <typename T>
const T*& max<T*>( const T*&, const T*& ) {} // �κ� Ư��ȭ : �����ϴ� �ڵ�� �ƴ�

int main( )
{
}