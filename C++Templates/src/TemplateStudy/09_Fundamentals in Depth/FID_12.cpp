#include <list>
// list의 선언
// naspace std {
// template <typename T,
// typename Allocator = aollcator<T>>
// class list;
// }

// template <typename T1, typename T2, template<typename> class Container> // Container는 하나의 파라미터를 갖는 템플릿을 기다림
template <typename T1, typename T2, template<typename T, typename = std::allocator<T>> class Container> // Container는 이제 표준 컨테이너 템플릿을 수용할 수 있음.
class Relation
{
public:
	// ...

private:
	Container<T1> dom1;
	Container<T2> dom2;
};

int main( )
{
	Relation<int, double, std::list> rel; // 오류 std::list는 하나 이상의 템플릿 파라미터를 가짐
}