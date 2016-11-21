// -----------------------------------------------------------------------------
// USB CLASS FOR MANIPULATING DEVICES
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 20/11/2016
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _APEXUSB_H
#define _APEXUSB_H

#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>

//namespace capex
//{

	struct DeviceUSB
	{
		unsigned short Handle;
		unsigned short PID;
		unsigned short VID;
		unsigned short USBVersion;
		unsigned short DeviceClass;
	};

	class apexUSB
	{
	  	public: // Public methods
	  		CALL apexUSB();
	  		CALL ~apexUSB();

	  	public: // Public attributs

	  	private:

	};

//}

#endif
