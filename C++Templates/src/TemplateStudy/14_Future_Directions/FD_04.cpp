#include <list>

template <typename T1, typename T2, template <typename> class Container>
class Relation
{
private:
	Container<T1> dom1;
	Container<T2> dom2;
};

int main( )
{
	Relation<int, double, std::list> rel;
}