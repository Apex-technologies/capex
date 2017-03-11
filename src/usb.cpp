#include "usb.h"

using std::cout;
using std::endl;

namespace mxm
{

	MXM_CALL usb::usb()
	{
		// Initialize a library session
		this->session = NULL;
		this->status = libusb_init(&(this->session));

		this->devices.clear();
		this->connected = false;
	}
	// -------------------------------------------------------------------

	MXM_CALL usb::usb(int VID, int PID)
	{
		// Initialize a library session
		this->session = NULL;
		this->status = libusb_init(&(this->session));

		// Get the list of devices with corresponding VID PID
		this->connected = false;
		this->devices = this->FoundDevices(VID, PID);
		
		//std::cout << "Devices found : " << this->devices.size() << std::endl;

		// If only one device has been found, the constructor connects automatically to this device
		if(this->devices.size() < 1)
			this->status = LIBUSB_ERROR_NO_DEVICE;
		else if(this->devices.size() > 1)
			this->status = MXMUSB_TOO_MUCH_DEVICES;
		else if(this->devices.size() == 1)
			this->status = this->Open(this->devices[0]);

	}
	// -------------------------------------------------------------------


	MXM_CALL usb::~usb()
	{
		// Close the session
		libusb_exit(this->session);
	}
	// -------------------------------------------------------------------


	std::vector<DeviceUSB> MXM_CALL usb::FoundDevices(int VID, int PID)
	{
		std::vector<DeviceUSB> list;
		list.clear();
		// Pointer to pointer of device, for getting a list of devices
		libusb_device **devs;
		// Get the list of devices
		ssize_t CountDevices = libusb_get_device_list(this->session, &devs);

		// Get descriptor of searched devices
		for(ssize_t i = 0; i < CountDevices; i++)
		{
			libusb_device_descriptor desc;
			this->status = libusb_get_device_descriptor(devs[i], &desc);
			if(((desc.idVendor == VID) || (VID == -1)) && ((desc.idProduct == PID) || (PID == -1)))
			{
				DeviceUSB d;
				d.VID = desc.idVendor;
				d.PID = desc.idProduct;
				d.USBVersion = desc.bcdUSB;
				d.DeviceClass = desc.bDeviceClass;
				d.lib.device = devs[i];
				this->status = libusb_open(devs[i], &(d.lib.handle));
				if(this->status >= 0)
				{
					unsigned char Buffer[256];
					this->status = libusb_get_string_descriptor(d.lib.handle, desc.iManufacturer, 0, &Buffer[0], 256);
					if(this->status >= 0)
						d.Manufacturer = std::string((char*)(&Buffer[2]), this->status - 2);
					this->status = libusb_get_string_descriptor(d.lib.handle, desc.iProduct, 0, &Buffer[0], 256);
					if(this->status >= 0)
						d.Product = std::string((char*)(&Buffer[2]), this->status - 2);
					this->status = libusb_get_string_descriptor(d.lib.handle, desc.iSerialNumber, 0, &Buffer[0], 256);
					if(this->status >= 0)
						d.SerialNumber = std::string((char*)(&Buffer[2]), this->status - 2);
					libusb_close(d.lib.handle);
				}
				list.push_back(d);
			}
		}

		// Free the list of USB devices
		libusb_free_device_list(devs, 1);

		return list;
	}
	// -------------------------------------------------------------------


	int MXM_CALL usb::Open(DeviceUSB device, int interface)
	{
		this->status = libusb_open(device.lib.device, &(device.lib.handle));
		if(this->status >= 0)
		{
			this->device = device;
			this->status = libusb_claim_interface(device.lib.handle, interface);
			this->connected = true;
			
			return LIBUSB_SUCCESS;
		}
		return ((int)(this->status));
	}
	// -------------------------------------------------------------------


	void MXM_CALL usb::Close()
	{
		if(this->connected)
		{
			libusb_close(this->device.lib.handle);
			this->connected = false;
		}
	}
	// -------------------------------------------------------------------


	bool MXM_CALL usb::IsConnected()
	{
		return this->connected;
	}
	// -------------------------------------------------------------------


	int MXM_CALL usb::GetVID()
	{
		return this->device.VID;
	}
	// -------------------------------------------------------------------


	int MXM_CALL usb::GetPID()
	{
		return this->device.PID;
	}
	// -------------------------------------------------------------------


	std::string MXM_CALL usb::GetUsbVersion()
	{
		unsigned char Major, Minor;
		Major = this->device.USBVersion >> 8;
		Minor = this->device.USBVersion & 0xFF;
		std::string s1, s2;
		s1 = std::to_string(Major);
		s2 = std::to_string(Minor);
		return (s1 + "." + s2);
	}
	// -------------------------------------------------------------------


	std::string MXM_CALL usb::GetManufacturer()
	{
		return this->device.Manufacturer;
	}
	// -------------------------------------------------------------------


	std::string MXM_CALL usb::GetProduct()
	{
		return this->device.Product;
	}
	// -------------------------------------------------------------------


	std::string MXM_CALL usb::GetSerialNumber()
	{
		return this->device.SerialNumber;
	}
	// -------------------------------------------------------------------
	
	
	std::string MXM_CALL usb::GetErrorMessage(int Status)
	{
		if(Status == -1)
			Status = this->status;
		
		std::string msg = "";
		
		if(Status >= -12)
			msg = libusb_strerror((libusb_error)(Status));
		else
		{
			switch(Status)
			{
				case MXMUSB_TOO_MUCH_DEVICES:
					msg = "Too much USB devices found";
					break;
				case MXMUSB_EP0_WRITE_ERROR:
					msg = "Error for writing in EP0";
					break;
				case MXMUSB_EP0_READ_ERROR:
					msg = "Error for reading in EP0";
					break;
				default:
					msg = "Error " + std::to_string(Status) + " not known";
					break;
			}
		}
		
		return msg;
	}
	// -------------------------------------------------------------------
	
	
	int MXM_CALL usb::EP0Write(unsigned char Request, unsigned short Value, unsigned short Index, unsigned char *Data, unsigned long Length)
	{
		unsigned int timeout = 1000;
		static const int CONTROL_REQUEST_TYPE_OUT = LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE;
		this->status = libusb_control_transfer(this->device.lib.handle,
											CONTROL_REQUEST_TYPE_OUT,
											Request, Value, Index,
											Data, Length, timeout);
		return this->status;
	}
	// -------------------------------------------------------------------
	
	
	int MXM_CALL usb::EP0Read(unsigned char Request, unsigned short Value, unsigned short Index, unsigned char *Data, unsigned long Length)
	{
		unsigned int timeout = 1000;
		static const int CONTROL_REQUEST_TYPE_IN = LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE;
		this->status = libusb_control_transfer(this->device.lib.handle,
											CONTROL_REQUEST_TYPE_IN,
											Request, Value, Index,
											Data, Length, timeout);
		return this->status;
	}
	// -------------------------------------------------------------------
}



























