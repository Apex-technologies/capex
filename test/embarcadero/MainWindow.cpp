//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define PI 3.14

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	int Npt = 50000;

	this->Frequency = 1.0;
	this->Threshold = -1.0;

	this->x.linspace(0.0, 1.0, Npt);
	this->y = sin(2 * PI * this->Frequency * x);

	this->DisplayGraph();

	this->device = new usb();

	this->DevicesList_Grid->Cells[0][0] = "VID";
	this->DevicesList_Grid->Cells[1][0] = "PID";
	this->DevicesList_Grid->Cells[2][0] = "Manufacturer";
	this->DevicesList_Grid->Cells[3][0] = "Product";
	this->DevicesList_Grid->Cells[4][0] = "USB";

	this->DataEP0_Grid->Cells[0][0] = "Index";
	this->DataEP0_Grid->Cells[1][0] = "Data";
	for(int i = 0; i < 64; i++)
		this->DataEP0_Grid->Cells[0][i + 1] = IntToStr(i);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Quit_BtClick(TObject *Sender)
{
	delete this->device;
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DisplayGraph()
{
	this->Series1->Clear();
	for(unsigned int i = 0; i < this->x.size(); i++)
		this->Series1->AddXY(this->x[i], this->y[i]);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Frequency_BarChange(TObject *Sender)
{
	this->Frequency = (float)this->Frequency_Bar->Position;
	this->y = sin(2 * PI * this->Frequency * x);
	this->y.replace(this->y.threshold(this->Threshold).invert(), 0.0);

	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Threshold_EditChange(TObject *Sender)
{
	this->Threshold = StrToFloatDef(this->Threshold_Edit->Text, -1.0);

	this->y = sin(2 * PI * this->Frequency * x);
	this->y.replace(this->y.threshold(this->Threshold).invert(), 0.0);

	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Noise_BtClick(TObject *Sender)
{
	this->y.random(-5.0, 5.0, this->y.size());
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Sinus_BtClick(TObject *Sender)
{
	this->y = sin(2 * PI * this->Frequency * x);
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetSmooth_BtClick(TObject *Sender)
{
	this->y = this->y.smooth(this->Smooth_Bar->Position);
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FindDevices_BtClick(TObject *Sender)
{
	this->devices = this->device->FoundDevices();
	for(int i = 0; i < devices.size(); i++)
	{
		unsigned short uv = this->devices[i].USBVersion;
		unsigned char major, minor;
		major = this->devices[i].USBVersion >> 8;
		minor = this->devices[i].USBVersion & 0x00FF;
		this->DevicesList_Grid->Cells[0][i + 1] = "0x" + IntToHex((int)this->devices[i].VID, 4);
		this->DevicesList_Grid->Cells[1][i + 1] = "0x" + IntToHex((int)this->devices[i].PID, 4);
		this->DevicesList_Grid->Cells[2][i + 1] = UnicodeString(this->devices[i].Manufacturer.c_str());
		this->DevicesList_Grid->Cells[3][i + 1] = UnicodeString(this->devices[i].Product.c_str());
		this->DevicesList_Grid->Cells[4][i + 1] = IntToStr((int)major) + "." + IntToStr((int)minor);
	}
	this->StatusBar1->Panels->Items[0]->Text = "USB Status : " + UnicodeString(this->device->GetErrorMessage(1).c_str());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DevicesList_GridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	if(this->device->IsConnected())
	{
		this->device->Close();
	}

	int status = this->device->Open(this->devices[ARow - 1]);
	this->StatusBar1->Panels->Items[0]->Text = "USB Status : " + UnicodeString(this->device->GetErrorMessage(status).c_str());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SendEP0_BtClick(TObject *Sender)
{
	unsigned char VR = StrToIntDef(UnicodeString("$") + this->VendorReq_Edit->Text, 0);
	unsigned short Value = StrToIntDef(UnicodeString("$") + this->Value_Edit->Text, 0);
	unsigned short Index = StrToIntDef(UnicodeString("$") + this->Index_Edit->Text, 0);
	unsigned long Length = StrToIntDef(this->BytesNumber_Edit->Text, 0);

	unsigned char *Buffer;
	Buffer = NULL;
	if(Length > 0)
		Buffer = new unsigned char[Length];

	for(unsigned long i = 0; i < Length; i++)
		Buffer[i] = 0;

	int status;
	if(this->EP0Read_Radio->Checked)
	{
		status = this->device->EP0Read(VR, Value, Index, Buffer, Length);
		for(unsigned long i = 0; i < Length; i++)
			this->DataEP0_Grid->Cells[1][i + 1] = "0x" + IntToHex((int)Buffer[i], 2);
	}
	else
	{
		status = this->device->EP0Write(VR, Value, Index, Buffer, Length);
	}
	this->StatusBar1->Panels->Items[0]->Text = "USB Status : " + UnicodeString(this->device->GetErrorMessage(status).c_str());

	if(Buffer != NULL)
		delete[] Buffer;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DataToEEProm_BtClick(TObject *Sender)
{
	EmbeddedData eData;
	int NbPoints = NB_POINTS;
	array<float> x;
	x.linspace(0.0, 1.0, NbPoints);
	eData.TimeBase = x.max() / NbPoints;
	float Phi = 0.0;
	array<float> y = sin(2 * PI * 10.0 * x + Phi);
	for(int i = 0; i < y.size(); i++)
		eData.Sinus[i] = y[i];

	unsigned long Length = sizeof(eData);
	unsigned long iData = Length;
	unsigned long Index = 0;

	unsigned short RAZ_Address = 0xFF00;

	unsigned char *Data = new unsigned char[Length];
	memcpy((void*)Data, (void*)&eData, sizeof(eData));

	int status;

	while(iData > 0)
	{
		unsigned long length;
		unsigned short Value;

		if(iData >= 64)
			length = 64;
		else
			length = iData;

		Value = ((unsigned short)length) + RAZ_Address;

		status = this->device->EP0Write(VR_SET_DATA_TO_EEPROM, Value, 0x0000, &(Data[Index]), length);
		if(status < LIBUSB_SUCCESS)
		{
			this->StatusBar1->Panels->Items[0]->Text = "USB Status : " + UnicodeString(this->device->GetErrorMessage(status).c_str());
			delete[] Data;
			return;
		}

		RAZ_Address = 0x0000;
		iData -= length;
		Index += length;
	}

	delete[] Data;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GetDataFromEEProm_BtClick(TObject *Sender)
{
	EmbeddedData eData;
	int NbPoints = NB_POINTS;

	unsigned long Length = sizeof(eData);
	unsigned long iData = 0;

	unsigned short RAZ_Address = 0xFF00;

	unsigned char *Data = new unsigned char[Length];

	int status;

	while(iData < Length)
	{
		unsigned long length;
		unsigned short Value;

		length = 64;
		unsigned char buffer[64];

		Value = ((unsigned short)length) + RAZ_Address;

		status = this->device->EP0Read(VR_GET_DATA_FROM_EEPROM, Value, 0x0000, &(buffer[0]), length);
		if(status < LIBUSB_SUCCESS)
		{
			this->StatusBar1->Panels->Items[0]->Text = "USB Status : " + UnicodeString(this->device->GetErrorMessage(status).c_str());
			delete[] Data;
			return;
		}

		for(int i = 0; i < length; i++)
		{
			Data[iData] = buffer[i];
			iData++;
		}

		RAZ_Address = 0x0000;
	}

	memcpy((void*)&eData, (void*)Data, sizeof(eData));

	array<float> x;
	x.linspace(0.0, eData.TimeBase * NbPoints, NbPoints);
	array<float> y(eData.Sinus, NbPoints);

	this->Series1->Clear();
	for(unsigned int i = 0; i < x.size(); i++)
		this->Series1->AddXY(x[i], y[i]);

	delete[] Data;
}
//---------------------------------------------------------------------------

