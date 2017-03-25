template <typename T>
class Dynamic
{
public:
	virtual ~Dynamic( ) {} // ok Dynamic<T> 당 하나의 소멸자
	template <typename T2>
	virtual void copy( const T2& ) {} // error Dynamic<T>의 인스턴스 내에서 copy() 인스턴스의 수를 결정할 수 없으므로
};

int main( )
{

}