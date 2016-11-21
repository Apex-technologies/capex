#include "apexusb.h"

using std::cout;
using std::endl;

//namespace capex
//{

	CALL apexUSB::apexUSB()
	{

		libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices

		libusb_context *ctx = NULL; //a libusb session

		int r; //for return values

		ssize_t cnt; //holding number of devices in list

		r = libusb_init(&ctx); //initialize a library session

		if(r < 0)
		    cout<< "Init Error " << r << endl; //there was an error

		libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
		cnt = libusb_get_device_list(ctx, &devs); //get the list of devices

		if(cnt < 0)
		    cout << "Get Device Error" << endl; //there was an error

		cout << cnt << " Devices in list." << endl; //print total number of usb devices
		ssize_t i; //for iterating through the list
		for(i = 0; i < cnt; i++)
		{
		    printdev(devs[i]); //print specs of this device
		}
		libusb_free_device_list(devs, 1); //free the list, unref the devices in it
		libusb_exit(ctx); //close the session

	}
	// -------------------------------------------------------------------


	CALL apexUSB::~apexUSB()
	{

	}
	// -------------------------------------------------------------------

//}
