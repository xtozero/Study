#include <list>
#include <map>
#include <string>

int main( )
{
	std::map<std::string, std::list<int>>* dict = new std::map<std::string, std::list<int>>;

	auto auto_dict = new std::map<std::string, std::list<int>>;

	auto a = { 1, 2, 3, 4 };

	auto b{ 1 };
}