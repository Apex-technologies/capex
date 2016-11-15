//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	int Npt = 100000;

	array<float> x;
	x.linspace(0.0, 62.8, Npt);
	array<float> y = sin(x);

	this->Series1->Clear();
	for(unsigned int i = 0; i < x.size(); i++)
		this->Series1->AddXY(x[i], y[i]);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Quit_BtClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

