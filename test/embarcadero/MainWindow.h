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
	TStatusBar *StatusBar1;
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
	TButton *OpenINI_Bt;
	TStringGrid *IniGrid;
	TButton *SinusNoise_Bt;
	TButton *SaveINI_Bt;
	void __fastcall Quit_BtClick(TObject *Sender);
	void __fastcall Frequency_BarChange(TObject *Sender);
	void __fastcall Threshold_EditChange(TObject *Sender);
	void __fastcall Noise_BtClick(TObject *Sender);
	void __fastcall Sinus_BtClick(TObject *Sender);
	void __fastcall SetSmooth_BtClick(TObject *Sender);
	void __fastcall Derivative1_BtClick(TObject *Sender);
	void __fastcall Derivative2_BtClick(TObject *Sender);
	void __fastcall OpenINI_BtClick(TObject *Sender);
	void __fastcall SinusNoise_BtClick(TObject *Sender);
	void __fastcall SaveINI_BtClick(TObject *Sender);
private:	// User declarations

	array<float> x;
	array<float> y;

	ini *parser;

	float Frequency;
	float Threshold;

	void __fastcall DisplayGraph();

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	__fastcall ~TMainForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
