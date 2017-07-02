template <typename T>
const T& max( const T&, const T& ) {} // 기본 템플릿

template <typename T>
const T*& max<T*>( const T*&, const T*& ) {} // 부분 특수화 : 동작하는 코드는 아님

int main( )
{
}