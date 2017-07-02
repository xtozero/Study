#include <iostream>
#include <vector>

template <typename T1, typename T2 = int>
T2 count( const T1& x ) 
{
	return x.size();
}

//template <typename T1 = int, typename T2>
//class Bad{};

template <typename T1 = int, typename T2>
T1 count2( const T2& x )
{
	return x.size( );
}

int main( )
{
	std::vector<int> v{ 1, 2, 3, 4, 5, 6 };

	int i = count( v );
	std::cout << i << std::endl;

	// Bad<int>* b; // �־��� int�� � ���ڿ� ���� ġȯ���� �� �� ����.

	i = count2( v );
	i = count2<int>( v );
	std::cout << i << std::endl;
}