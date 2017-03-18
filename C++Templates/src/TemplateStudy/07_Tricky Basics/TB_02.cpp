#include <bitset>
#include <iostream>

template <int N>
void printBitset( const std::bitset<N>& bs )
{
	// .template 로 사용하지 않으면 gcc에서 컴파일 에러
	std::cout << bs.to_string<char, std::char_traits<char>, std::allocator<char>>( ) << std::endl;
}

int main( )
{
	std::bitset<10> bs = 1;
	// gcc에서는 인자를 통해서 추론 실패
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