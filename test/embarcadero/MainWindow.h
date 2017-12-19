//---------------------------------------------------------------------------

#ifndef MainWindowH
#define MainWindowH

#include "capex.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>

#include <sstream>
#include <memory>

#define NB_POINTS					200

#define VR_SET_DATA_TO_EEPROM		0xB1
#define VR_GET_DATA_FROM_EEPROM		0xB2

using namespace capex;

struct point
{
	float x;
	float y;
};

struct EmbeddedData
{
	float TimeBase;
	float Sinus[NB_POINTS];
};

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *ArraySheet;
	TButton *Quit_Bt;
	TChart *Chart1;
	TFastLineSeries *Series1;
	TTrackBar *Frequency_Bar;
	TEdit *Threshold_Edit;
	TLabel *FreqLabel;
	TLabel *Label1;
	TButton *Noise_Bt;
	TTrackBar *Smooth_Bar;
	TLabel *Label2;
	TButton *SetSmooth_Bt;
	TButton *Sinus_Bt;
	TTabSheet *USBTest_Sheet;
	TButton *FindDevices_Bt;
	TStringGrid *DevicesList_Grid;
	TStatusBar *StatusBar1;
	TLabel *Label3;
	TEdit *VendorReq_Edit;
	TLabel *Label4;
	TEdit *Value_Edit;
	TLabel *Label5;
	TEdit *Index_Edit;
	TRadioGroup *RadioGroup1;
	TRadioButton *EP0Read_Radio;
	TRadioButton *EP0Write_Radio;
	TLabel *Label6;
	TEdit *BytesNumber_Edit;
	TButton *SendEP0_Bt;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label10;
	TStringGrid *DataEP0_Grid;
	TButton *DataToEEProm_Bt;
	TButton *GetDataFromEEProm_Bt;
	TButton *SendEP1_Bt;
	TRadioGroup *RadioGroup2;
	TRadioButton *SmoothSquare_Radio;
	TRadioButton *SmoothSinus_Radio;
	TRadioButton *SmoothSinc_Radio;
	TRadioButton *SmoothGaussian_Radio;
	TButton *Derivative1_Bt;
	TButton *Derivative2_Bt;
	TCheckBox *DerivativeDeltaX_Check;
	TTabSheet *INI_Sheet;
	TOpenDialog *OpenIniDialog;
	TSaveDialog *SaveIniDialog;
	TButton *Button1;
	TStringGrid *IniGrid;
	TButton *SinusNoise_Bt;
	void __fastcall Quit_BtClick(TObject *Sender);
	void __fastcall Frequency_BarChange(TObject *Sender);
	void __fastcall Threshold_EditChange(TObject *Sender);
	void __fastcall Noise_BtClick(TObject *Sender);
	void __fastcall Sinus_BtClick(TObject *Sender);
	void __fastcall SetSmooth_BtClick(TObject *Sender);
	void __fastcall FindDevices_BtClick(TObject *Sender);
	void __fastcall DevicesList_GridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall SendEP0_BtClick(TObject *Sender);
	void __fastcall DataToEEProm_BtClick(TObject *Sender);
	void __fastcall GetDataFromEEProm_BtClick(TObject *Sender);
	void __fastcall Derivative1_BtClick(TObject *Sender);
	void __fastcall Derivative2_BtClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall SinusNoise_BtClick(TObject *Sender);
private:	// User declarations

	array<float> x;
	array<float> y;

	usb *device;
	std::vector<DeviceUSB> devices;

	ini *parser;

	float Frequency;
	float Threshold;

	void __fastcall DisplayGraph();

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
