#include "../../src/capex.h"

#include <iostream>

using namespace std;
using namespace capex;

template <typename T>
void display(array<T> a)
{
	std::cout << "Values :";
	for(unsigned int i = 0; i < a.size(); i++)
		std::cout << " " << a[i];
	std::cout << std::endl;
}
//----------------------------------------------------------------------

int main(void)
{

	cout << "-------------------------------------------------" << endl;
	cout << "              TEST OF C++ ARRAY CLASS" << endl;
	cout << "-------------------------------------------------" << endl << endl;

	unsigned int N = 10;
	cout << "Test with " << N << " points" << endl;

	cout << endl << "\t\t1D ARRAYS" << endl << endl;

	array<float> a;
	a.linspace(0.0, 6.28, N);

	float *p = a.pointer();
	*(p + 2) = 42.0;

	a[-1] = 28.0;

	if(a.size() < 21)
		display(a);

	a = sin(a);

	if(a.size() < 21)
	{
		display(a);
		a = a.swap();
		display(a);
	}

	cout << std::endl << "\t\t2D ARRAYS" << endl << endl;
	array<float> z;
	z.linspace(0.0, N - 1.0, N);

	array<array<float>> *T = new array<array<float>>(z, 2);

	cout << "Reassign the 100th value : ";
	(*T)[0][100] = 4;
	cout << (*T)[0][100] << endl;
	delete T;

	apexUSB dev;

	return 0;
}



