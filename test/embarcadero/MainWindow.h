//---------------------------------------------------------------------------

#ifndef MainWindowH
#define MainWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include "capex.h"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>

using namespace capex;

struct point
{
	float x;
	float y;
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
	void __fastcall Quit_BtClick(TObject *Sender);
	void __fastcall Frequency_BarChange(TObject *Sender);
	void __fastcall Threshold_EditChange(TObject *Sender);
private:	// User declarations

	array<float> x;
	array<float> y;

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
