#include <iostream>

using namespace std;

class StaticMember
{
public:
	static int member;
	//static constexpr int member = 1;
};

//int StaticMember::member = 1; // Á¤ÀÇ

int main()
{
	cout << StaticMember::member << endl;
}