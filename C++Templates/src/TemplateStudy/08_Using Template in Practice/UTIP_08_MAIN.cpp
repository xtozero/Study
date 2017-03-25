#include <iostream>
#include <algorithm>
#include "UTIP_08.hpp"

int main( )
{
	// ���� �Է� �غ�
	SortTracer input[] = { 7, 3, 5, 6, 4, 2, 0, 1, 9, 8 };

	// �ʱⰪ ���
	for ( int i = 0; i < 10; ++i )
	{
		std::cerr << input[i].val( ) << ' ';
	}
	std::cerr << std::endl;

	// �ʱ� ������ ���
	long created_at_start = SortTracer::creations( );
	long max_live_at_start = SortTracer::max_live( );
	long assigned_at_start = SortTracer::assignments( );
	long compared_at_start = SortTracer::comparisions( );

	// �˰��� ����
	std::cerr << "---[ Start std::sort() ]---------------------------------\n";
	std::sort<>( &input[0], &input[9] + 1 );
	std::cerr << "---[ End std::sort() ]-----------------------------------\n";

	// ��� ����
	for ( int i = 0; i < 10; ++i )
	{
		std::cerr << input[i].val( ) << ' ';
	}
	std::cerr << "\n\n";

	// ������ ����
	std::cerr << "std::sort of 10 SortTracers"
		<< " was performed by:\n"
		<< SortTracer::creations( ) - created_at_start
		<< " temporary tracers\n"
		<< "up to "
		<< SortTracer::max_live( )
		<< " tracers at th same tiem ("
		<< max_live_at_start << " before)\n"
		<< SortTracer::assignments( ) - assigned_at_start
		<< " assignments\n"
		<< SortTracer::comparisions( ) - compared_at_start
		<< " comparisions\n\n";
}