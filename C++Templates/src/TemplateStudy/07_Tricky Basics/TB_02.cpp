#include <bitset>
#include <iostream>

template <int N>
void printBitset( const std::bitset<N>& bs )
{
	// .template �� ������� ������ gcc���� ������ ����
	std::cout << bs.to_string<char, std::char_traits<char>, std::allocator<char>>( ) << std::endl;
}

int main( )
{
	std::bitset<10> bs = 1;
	// gcc������ ���ڸ� ���ؼ� �߷� ����
	printBitset( bs );
}

/*
#include <bitset>
#include <iostream>

template <int N>
void printBitset( const std::bitset<N>& bs )
{
	std::cout << bs.template to_string<char, std::char_traits<char>, std::allocator<char>>( ) << std::endl;
}

int main( )
{
	std::bitset<10> bs = 1;
	printBitset<10>( bs );
}
*/