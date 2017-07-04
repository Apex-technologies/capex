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
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Quit_BtClick(TObject *Sender)
{
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

