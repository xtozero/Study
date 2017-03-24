#include <algorithm>
#include <functional>
#include <list>
#include <string>

int main( )
{
	std::list<std::string> coll;
	
	auto pos = std::find_if( coll.begin( ), coll.end( ), std::bind2nd(std::greater<int>(), "A") );
}