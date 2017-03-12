#include <iostream>

// Default
template <typename T1, typename T2>
class PartialSpecialization
{
};

//Partial Specializations
template <typename T>
class PartialSpecialization<T, T>
{
};

template <typename T>
class PartialSpecialization<T, int>
{
};

template <typename T1, typename T2>
class PartialSpecialization<T1*, T2*>
{
};

int main( )
{
	PartialSpecialization<int, float> pif;		// PartialSpecialization<T1, T2>
	PartialSpecialization<float, float> pff;	// PartialSpecialization<T, T>
	PartialSpecialization<float, int> pfi;		// PartialSpecialization<T, int>
	PartialSpecialization<int*, float*> pipfp;  // PartialSpecialization<T1*, T2*>

	// PartialSpecialization<int, int> pii; // Error
	// PartialSpecialization<int*, int*> pipip;	// Error
}