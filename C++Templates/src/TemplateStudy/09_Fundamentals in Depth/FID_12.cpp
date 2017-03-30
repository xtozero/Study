#include <list>
// list�� ����
// naspace std {
// template <typename T,
// typename Allocator = aollcator<T>>
// class list;
// }

// template <typename T1, typename T2, template<typename> class Container> // Container�� �ϳ��� �Ķ���͸� ���� ���ø��� ��ٸ�
template <typename T1, typename T2, template<typename T, typename = std::allocator<T>> class Container> // Container�� ���� ǥ�� �����̳� ���ø��� ������ �� ����.
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
	Relation<int, double, std::list> rel; // ���� std::list�� �ϳ� �̻��� ���ø� �Ķ���͸� ����
}