#include "../../src/capex.h"
#include <iostream>

using namespace std;
using namespace capex;




/**********************************************************************/
template <typename T>
void display(mxm::array<T> a)
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
	cout << "-----------------USB AB3510 MENU-----------------" << endl;
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

    cout << std::endl << "\t\tUSB DEVICES" << endl << endl;

	usb dev(0x5553, 0x3510);
	if(dev.IsConnected())
	{
        cout << std::hex << std::setfill('0') << std::setw(4);
        cout << "VID = 0x" << dev.GetVID() << endl;
        cout << "PID = 0x" << dev.GetPID() << endl;
        cout << "USB " << dev.GetUsbVersion() << endl;
        cout << "Manufacturer : " << dev.GetManufacturer() << endl;
        cout << "Product : " << dev.GetProduct() << endl;
        cout << "Serial Number : " << dev.GetSerialNumber() << endl;
	}
	else
		cout << dev.GetErrorMessage() << endl;
	
	char key = '\0';
	while((key != 'q') && (key != 'Q') && (dev.IsConnected()))
	{
		key = DisplayMenu();
		
		unsigned short Freq;
		
		switch(key)
		{
			case 'a':
				dev.EP0Write(0xB6, 0, 0, NULL, 0);
				break;
			case 'b':
				dev.EP0Write(0xB7, 0, 0, NULL, 0);
				break;
			case 'c':
				cout << "New frequency : ";
				cin >> Freq;
				cout << endl;
				dev.EP0Write(0xB9, Freq, 0, NULL, 0);
				break;
			case 'd':
				dev.EP0Read(0xB8, 0, 0, (unsigned char*)(&Freq), 2);
				cout << "Frequency = " << (int)Freq << endl;
				break;
			case 'q':
				cout << "Quit the program" << endl;
				break;
			default:
				cout << "Wrong choice" << endl;
		}
		cout << endl;
	}
	
	
    dev.Close();

	return 0;
}



