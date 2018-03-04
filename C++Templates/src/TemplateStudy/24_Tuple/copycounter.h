#pragma once

template <int N>
struct CopyCounter
{
	static int numCopies;
	CopyCounter( ) {}
	CopyCounter( const CopyCounter& ) { ++numCopies; }
};

template <int N>
int CopyCounter<N>::numCopies = 0;