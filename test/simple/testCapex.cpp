#include "../../src/capex.h"
#include <iostream>

using namespace std;
using namespace capex;




/**********************************************************************/
template <typename T>
void display(capex::array<T> a)
{
	std::cout << "Values :";
	for(unsigned int i = 0; i < a.size(); i++)
		std::cout << " " << a[i];
	std::cout << std::endl;
}
/**********************************************************************/

/**********************************************************************/
char DisplayMenu()
{
	cout << "-----------------INI FILE MENU-----------------" << endl;
	cout << "\t'a'\tRun blinking" << endl;
	cout << "\t'b'\tStop blinking" << endl;
	cout << "\t'c'\tSet blinking frequency" << endl;
	cout << "\t'd'\tGet blinking frequency" << endl;
	cout << "\t'q'\tQuit" << endl;
	cout << "\nYour choice : ";
	char k;
	cin >> k;
	cout << endl;
	return k;
}
/**********************************************************************/

int main(void)
{

	cout << "-------------------------------------------------" << endl;
	cout << "              TEST OF C++ CAPEX CLASS" << endl;
	cout << "-------------------------------------------------" << endl << endl;

	unsigned int N = 10;
	cout << "Test with " << N << " points" << endl;

	cout << endl << "\t\t1D ARRAYS" << endl << endl;

	capex::array<float> a;
	a.linspace(0.0, 6.28, N);

	float *p = a.pointer();
	*(p + 2) = 42.0;

	capex::array<float> b = (float)5.0 + a;
	display(b);

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
	capex::array<float> z;
	z.linspace(0.0, N - 1.0, N);

	capex::array<capex::array<float>> *T = new capex::array<capex::array<float>>(z, 2);

	cout << "Reassign the 100th value : ";
	(*T)[0][100] = 4;
	cout << (*T)[0][100] << endl;
	delete T;
	
    cout << endl << "\t\tINI FILE" << endl << endl;
	
	capex::ini *parser = new capex::ini("../ini/test.ini");
	
	delete parser; 

	return 0;
}



