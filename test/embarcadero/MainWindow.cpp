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
	int Npt = 50000;

	this->Frequency = 1.0;
	this->Threshold = -1.0;

	this->x.linspace(0.0, 1.0, Npt);
	this->y = sin(2 * capex::pi * this->Frequency * x);

	this->DisplayGraph();

	this->IniGrid->Cells[0][0] = "Section";
	this->IniGrid->Cells[1][0] = "Parameter";
	this->IniGrid->Cells[2][0] = "Value";
	this->OpenIniDialog->InitialDir = ExtractFilePath(Application->ExeName);
	//ShowMessage(ExtractFilePath(Application->ExeName));

	this->parser = new capex::ini();
}
//---------------------------------------------------------------------------

__fastcall TMainForm::~TMainForm()
{
	delete this->parser;
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
	this->y = sin(2 * capex::pi * this->Frequency * x);
	this->y.replace(this->y.threshold(this->Threshold).invert(), 0.0);

	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Threshold_EditChange(TObject *Sender)
{
	this->Threshold = StrToFloatDef(this->Threshold_Edit->Text, -1.0);

	this->y = sin(2 * capex::pi * this->Frequency * x);
	this->y.replace(this->y.threshold(this->Threshold).invert(), this->Threshold);

	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Noise_BtClick(TObject *Sender)
{
	this->y.random(0.0, 1.0, this->y.size(), capex::rsGauss);
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Sinus_BtClick(TObject *Sender)
{
	this->y = sin(2 * capex::pi * this->Frequency * x);
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetSmooth_BtClick(TObject *Sender)
{
	SmoothShape shape;
	if(this->SmoothSquare_Radio->Checked)
		shape = ssSquare;
	else if(this->SmoothSinus_Radio->Checked)
		shape = ssSin;
	else if(this->SmoothSinc_Radio->Checked)
		shape = ssSinc;
	else if(this->SmoothGaussian_Radio->Checked)
		shape = ssGauss;
	this->y = this->y.smooth(this->Smooth_Bar->Position, shape);
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Derivative1_BtClick(TObject *Sender)
{
	double Dt = this->x[1] - this->x[0];
	this->y = this->y.derivative(1);
	if(this->DerivativeDeltaX_Check->Checked)
		this->y /= Dt;

	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Derivative2_BtClick(TObject *Sender)
{
	double Dt = this->x[1] - this->x[0];
	this->y = this->y.derivative(2);
	if(this->DerivativeDeltaX_Check->Checked)
		this->y /= std::pow(Dt, 2.0);

	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenINI_BtClick(TObject *Sender)
{
	if(this->OpenIniDialog->Execute())
	{
		AnsiString fname = AnsiString(this->OpenIniDialog->FileName);
		if(this->parser->Open(fname.c_str()))
		{
			int Line = 1;
			std::vector<std::string> sec = this->parser->GetSectionsName();
			for(int n = 0; n < sec.size(); n++)
			{
				section s = this->parser->GetSection(sec[n].c_str());
				for(int k = 0; k < s.parameters.size(); k++)
				{
					this->IniGrid->Cells[0][Line] = AnsiString(sec[n].c_str());
					this->IniGrid->Cells[1][Line] = AnsiString(s.parameters[k].name.c_str());
					this->IniGrid->Cells[2][Line] = AnsiString(s.parameters[k].value.c_str());
					Line++;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SinusNoise_BtClick(TObject *Sender)
{
	this->y = sin(2 * capex::pi * this->Frequency * this->x);
	array<float> noise;
	noise.random(0.0, 0.5, this->y.size(), capex::rsGauss);
	this->y += noise;
	this->DisplayGraph();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveINI_BtClick(TObject *Sender)
{
	if(this->SaveIniDialog->Execute())
	{
		for(int r = 0; r < 1000; r++)
		{
			if(this->IniGrid->Cells[0][r + 1] != "")
			{
				AnsiString section = AnsiString(this->IniGrid->Cells[0][r + 1]);
				AnsiString parameter = AnsiString(this->IniGrid->Cells[1][r + 1]);
				std::string value = std::string(AnsiString(this->IniGrid->Cells[2][r + 1]).c_str());
				this->parser->SetValue(section.c_str(), parameter.c_str(), value);
			}
		}
		dictionary d = this->parser->GetDictionary();
		AnsiString fname = AnsiString(this->SaveIniDialog->FileName);
		this->parser->WriteINI(&d, fname.c_str());
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NewLogFile_BtClick(TObject *Sender)
{
	if(this->SaveLogDialog->Execute())
	{
		this->LogFilePath_Edit->Text = this->SaveLogDialog->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::InitLogFile_BtClick(TObject *Sender)
{
	std::string Path = std::string(AnsiString(this->LogFilePath_Edit->Text).c_str());
	capex::tools::InitLogFile(&Path[0]);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CloseLogFile_BtClick(TObject *Sender)
{
	capex::tools::CloseLogFile();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WriteLog_BtClick(TObject *Sender)
{
	std::string str = "";

	for(int l = 0; l < this->WriteLog_Memo->Lines->Count; l++)
	{
		str += std::string(AnsiString(this->WriteLog_Memo->Lines->Strings[l]).c_str());
		if(l < this->WriteLog_Memo->Lines->Count - 1)
			str += std::string("\n");
	}

	capex::tools::WriteLogFile(&str[0]);
}
//---------------------------------------------------------------------------

