#include <iostream>

void DisplayNum(int) { std::cout << "DisplayNum(int)" << std::endl; }
void DisplayNum(double) { std::cout << "DisplayNum(double)" << std::endl; }

void Ambigouous(long) {}
void Ambigouous(double) {}

void Combine( int, double ) {}
void Combine( double, int ) {}

void PerfectMatch( const int ) { std::cout << "#1" << std::endl; }
void PerfectMatch( double ) { std::cout << "#2" << std::endl; }

void MinorAdjust( int* pArray ) { std::cout << "#1" << std::endl; }
//void MinorAdjust( int** ptr ) { std::cout << "#2" << std::endl; }
void MinorAdjust( int const* const* ptr ) { std::cout << "#3" << std::endl; }

void Promotion( char ) { std::cout << "#1" << std::endl; }
void Promotion( int ) { std::cout << "#2" << std::endl; }

void StandardConversion( char ) { std::cout << "#1" << std::endl; }
void StandardConversion( ... ) { std::cout << "#2" << std::endl; }

int main()
{
	std::cout << "Default overload resolution sample" << std::endl;	
	DisplayNum(1);
	DisplayNum(1.0);
	
        // Ambigouous(1); error 후보가 여러개 있어 모호한 호출
	
	// Combine( 1, 2 ); // error C2666: 'Combine': 2개 오버로드에 비슷한 변환이 있습니다. 

	std::cout << "Perfect match overload sample" << std::endl;	
	PerfectMatch( 1 ); // #1 이 호출

	std::cout << "Minor adjust overload sample" << std::endl;
	int arr[5] = {};
	MinorAdjust( arr ); // 배열을 포인터로 변환(decay)

	int* pArr = arr;
	int** ppArr = &pArr;
	MinorAdjust( ppArr ); // #2의 주석을 풀면 완벽한 일치로 #2
			      // #2가 없으면 int** -> int const* const*로 수정하여 #3 호출
	
	std::cout << "Promotion overload sample" << std::endl;	
	Promotion( true ); // bool -> int 데이터형 승격으로 #2 호출
	
	std::cout << "Standard conversion sample" << std::endl;	
	StandardConversion( true ); // bool -> char 로 표준 변환이 적용되서 #1 호출
}
