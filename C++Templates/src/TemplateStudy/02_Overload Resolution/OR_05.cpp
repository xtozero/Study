#include <iostream>

using namespace std;

void MinorAdjust( int* pArray ) { cout << "#1" << endl; } // #1
// void MinorAdjust( int** ptr ) { cout << "#2" << endl; } // #2
void MinorAdjust( int const* const* ptr ) { cout << "#3" << endl; } // #3

int main( )
{
	int arr[5] = {};
	MinorAdjust( arr );

	int* pArr = arr;
	int** ppArr = &pArr;
	MinorAdjust( ppArr );
}