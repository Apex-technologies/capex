//--------------------------------------------------------------------------
//                                INIPARSER.CPP
//--------------------------------------------------------------------------
//!
//! \file csv.cpp
//! \brief Class for parsing CSV file
//! \author Maxime Fontaine
//! \version 0.1
//! \date 2018-06-12
//!
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
//                            PRE-COMPILER DECLARATIONS
//--------------------------------------------------------------------------
#include <iostream>
#include <fstream>

//--------------------------------------------------------------------------

namespace capex
{

	CAPEX_CALL csv::csv(const char* File)
	{
		this->tab = new csv::table;
		this->Comments = new std::vector<csv::comment>;
		this->LinesType = new std::vector<int>;

		this->FileEndLine = 0;
		this->EndLine = 0;

		this->separator = ",;\t";

		if(File != NULL)
		{
			this->Open(File);
		}
	}
	//-------------------------------------------------------------------------

	
	CAPEX_CALL csv::~csv()
	{
		delete this->tab;
		delete this->Comments;
		delete this->LinesType;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::Open(const char* File)
	{
		this->tab->lines.clear();
		this->Comments->clear();
		this->LinesType->clear();

		this->FileName = std::string(File);
		std::ifstream f;
		f.open(File, std::ios::in);

		if(!f.is_open())
			return false;

		std::string line = "";
		while(!f.eof())
		{
			char c = f.get();
			if((int)(c) == -1)
				c = '\0';
			if(c != '\r')
				line += (char)c;
			if(c == '\n')
			{
				if(std::strcmp(line.c_str(), "\n") == 0)
					line = " \n";
				this->TextFile += line;
				line = "";
			}
		}
		f.close();

		this->GetLinesType();
		*this->tab = this->GetTable(true);
		
        return true;
	}
	//-------------------------------------------------------------------------


	void CAPEX_CALL csv::SetSeparator(const char *Sep)
	{
		this->separator = std::string(Sep);
	}
	//-------------------------------------------------------------------------


	std::string CAPEX_CALL csv::GetSeparator()
	{
		return this->separator;
	}
	//-------------------------------------------------------------------------
	
	
	std::vector<std::string> CAPEX_CALL csv::GetLines()
	{
		std::vector<std::string> v;
		v.clear();

		std::string txt = this->TextFile;
		char *str = &(txt[0]);

		char *pch;
		pch = strtok(str, "\n\r");
		while(pch != NULL)
		{
			v.push_back(std::string(pch));
			pch = strtok(NULL, "\n\r");
		}

		this->FileEndLine = v.size();
		if(this->EndLine == 0)
			this->EndLine = this->FileEndLine;
		
		return v;
	}
	//-------------------------------------------------------------------------
	
	
	void CAPEX_CALL csv::GetLinesType()
	{
		std::vector<std::string> L = this->GetLines();
		this->LinesType->clear();
		this->Comments->clear();

		for(unsigned int i = 0; i < L.size(); i++)
		{

			L[i] = tools::StrTrim(L[i], tools::tmBoth);

			int p = -1;
			int psharp = L[i].find_first_of("#", 0);
			unsigned int s = L[i].size();
			if(psharp >= 0 && psharp < L[i].size())
				p = psharp;

			if((p == 0) || (s == 0))
				this->LinesType->push_back(0);
			else if(p == -1)
				this->LinesType->push_back(1);
			else if(p > 0)
				this->LinesType->push_back(2);

			csv::comment c;
			if(p >= 0)
				c.text = L[i].substr(p, L[i].size() - p);
			else
				c.text = L[i];
			c.line = i;
			this->Comments->push_back(c);
		}
		
	}
	//-------------------------------------------------------------------------
	
	
	int CAPEX_CALL csv::GetLinesNumber()
	{
		this->GetLinesType();
		int lines = 0;
		for(int l = 0; l < this->LinesType->size(); l++)
		{
			if(this->LinesType->at(l) > 0)
				lines++;
		}

		return lines;
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumnsNumber()
	{
		int Col = 0;

		std::vector<std::string> L = this->GetLines();
		for(int n = 0; n < L.size(); n++)
		{
			csv::line l = this->GetLine(n);
			if(l.values.size() > Col)
				Col = l.values.size();
		}

		return Col;
	}
	//-------------------------------------------------------------------------
	
	
	csv::line CAPEX_CALL csv::GetLine(unsigned int Line)
	{
		std::vector<std::string> L = this->GetLines();

		csv::line l;
		l.values.clear();

		if(Line < L.size())
		{
			l.line = Line;
			std::string strLine = capex::tools::StrTrim(L[Line], capex::tools::tmBoth);
			std::string SubString = strLine;
			if((strLine[0] == '#') || (strLine.size() == 0))
			{
				l.type = csv::ltComment;
				l.comment = strLine;
			}
			else
			{
				l.type = csv::ltValue;
				int Position = 0;

				unsigned int CPos = SubString.length();
				for(int c = 0; c < this->separator.length(); c++)
				{
					unsigned int pos = SubString.find_first_of((char)(this->separator[c]));
					if((pos != std::string::npos) && (pos < CPos))
					{
						CPos = pos;
					}
				}

				while(CPos <= SubString.length())
				{
					csv::value v;
					if(CPos <= SubString.length())
					{
						v.value = SubString.substr(0, CPos);
						v.line = Line;
						v.position = Position++;
						l.values.push_back(v);
					}
					else
					{
						v.value = std::string("");
						v.line = Line;
						v.position = Position++;
						l.values.push_back(v);
					}
					if(CPos < SubString.length())
					{
						SubString = SubString.substr(CPos + 1, SubString.length() - CPos);

						CPos = SubString.length();
						for(int c = 0; c < this->separator.length(); c++)
						{
							unsigned int pos = SubString.find_first_of((char)(this->separator[c]));
							if((pos != std::string::npos) && (pos < CPos))
							{
								CPos = pos;
							}
						}
					}
					else
					{
						CPos = SubString.length() + 1;
					}
				}
			}
		}

		return l;
	}
	//-------------------------------------------------------------------------
	
	
	csv::table CAPEX_CALL csv::GetTable(bool FromFile)
	{
		if(FromFile)
		{
			this->tab->lines.clear();
			this->tab->comments.clear();

			std::vector<std::string> L = this->GetLines();
			for(int n = 0; n < L.size(); n++)
			{
				std::string sl = L[n];
				csv::line l = this->GetLine(n);
				this->tab->lines.push_back(l);
			}
		}

		return *(this->tab);
	}
	//-------------------------------------------------------------------------
	

	bool CAPEX_CALL csv::GetBoolean(unsigned int line, unsigned int position)
	{
		bool v = false;

		csv::line L = this->GetLine(line);
		if(position < L.values.size())
		{
			std::string val = capex::tools::StrLower(L.values[position].value);
			if((strcmp(val.c_str(), "true") == 0) || (strcmp(val.c_str(), "1") == 0))
				v = true;
			else
				v = false;
		}

		return v;
	}
	//-------------------------------------------------------------------------

	
	std::string CAPEX_CALL csv::GetString(unsigned int line, unsigned int position)
	{
		std::string v = "";

		csv::line L = this->GetLine(line);
		if(position < L.values.size())
		{
			v = L.values[position].value;
		}

		return v;
	}
	//-------------------------------------------------------------------------
	

	int CAPEX_CALL csv::GetInteger(unsigned int line, unsigned int position)
	{
		int v = 0;

		csv::line L = this->GetLine(line);
		if(position < L.values.size())
		{
			try
			{
				v = int(std::strtod(L.values[position].value.c_str(), NULL));
			}
			catch(...)
			{}
		}

		return v;
	}
	//-------------------------------------------------------------------------

	
	double CAPEX_CALL csv::GetDouble(unsigned int line, unsigned int position)
	{
		double v = 0.0;

		csv::line L = this->GetLine(line);
		if(position < L.values.size())
		{
			try
			{
				v = std::strtod(L.values[position].value.c_str(), NULL);
			}
			catch(...)
			{}
		}

		return v;
	}
	//-------------------------------------------------------------------------


	std::string CAPEX_CALL csv::TableToString(const table *t)
	{
		std::string s = "";

		for(int l = 0; l < t->lines.size(); l++)
		{
			csv::line Line = t->lines[l];
			if(Line.values.size() != 0)
			{
				for(int c = 0; c < Line.values.size(); c++)
				{
					s += Line.values[c].value;
					if(c < Line.values.size() - 1)
						s += this->separator[0];
				}
			}
			else
			{
				s += Line.comment;
			}
			s += "\n";
		}

		return s;
	}
	//-------------------------------------------------------------------------
	

	bool CAPEX_CALL csv::WriteValue(unsigned int line, unsigned int position, std::string value)
	{
		bool success = false;

		if(line < this->tab->lines.size())
		{
			int LIndex = -1;
			for(int l = 0; l < this->tab->lines.size(); l++)
			{
				if(this->tab->lines[l].line == line)
				{
					LIndex = l;
					break;
				}
			}
			if(LIndex >= 0)
			{
				int NbVal = this->tab->lines[LIndex].values.size();
				if(position < NbVal)
				{
					for(int c = 0; c < NbVal; c++)
					{
						if(this->tab->lines[LIndex].values[c].position == position)
						{
							std::string val = this->tab->lines[LIndex].values[c].value;
							this->tab->lines[LIndex].values[c].value = value;
							val = this->tab->lines[LIndex].values[c].value;
							success = true;
							break;
						}
					}
				}
				else
				{
					int NullValuesToAdd = position - NbVal;
					for(int c = 0; c < NullValuesToAdd; c++)
					{
						csv::value v;
						v.value = "";
						v.line = this->tab->lines[LIndex].line;
						v.position = NbVal + c;
						this->tab->lines[LIndex].values.push_back(v);
					}
					csv::value v;
					v.value = value;
					v.line = this->tab->lines[LIndex].line;
					v.position = position;
					this->tab->lines[LIndex].values.push_back(v);
					success = true;
				}
			}
		}
		else
		{
			int NbLines = this->tab->lines.size();
			int NullLinesToAdd = line - NbLines;
			for(int l = 0; l < NullLinesToAdd; l++)
			{
				csv::line l;
				l.values.clear();
				//l.line = ((int)(NbLines + l));
				l.comment = "";
				this->tab->lines.push_back(l);
			}
			csv::line l;
			l.type = csv::ltValue;
            l.values.clear();
			l.line = line;
			l.comment = "";

			int NullValuesToAdd = position;
			for(int c = 0; c < NullValuesToAdd; c++)
			{
				csv::value v;
				v.value = "";
				v.line = line;
				v.position = c;
				l.values.push_back(v);
			}
			csv::value v;
			v.value = value;
			v.line = line;
			v.position = position;
			l.values.push_back(v);
			this->tab->lines.push_back(l);
			success = true;
		}

		return success;
	}
	//-------------------------------------------------------------------------
	
	
	void CAPEX_CALL csv::ChangeLine(unsigned int NewLine)
	{


	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, std::vector<std::string> *values, std::string def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					values->push_back(l.values[column].value);
				}
				else if(l.type == csv::ltValue)
				{
					values->push_back(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, std::vector<bool> *values, bool def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					std::string val = capex::tools::StrLower(l.values[column].value);
					bool v = false;
					if((strcmp(val.c_str(), "true") == 0) || (strcmp(val.c_str(), "1") == 0))
						v = true;
					else
						v = false;
					values->push_back(v);
				}
				else if(l.type == csv::ltValue)
				{
					values->push_back(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, std::vector<int> *values, int def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					try
					{
						int v = int(std::strtod(l.values[column].value.c_str(), NULL));
						values->push_back(v);
					}
					catch(...)
					{
						values->push_back(def);
					}
				}
				else if(l.type == csv::ltValue)
				{
					values->push_back(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, std::vector<double> *values, double def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					try
					{
						double v = std::strtod(l.values[column].value.c_str(), NULL);
						values->push_back(v);
					}
					catch(...)
					{
						values->push_back(def);
					}
				}
				else if(l.type == csv::ltValue)
				{
					values->push_back(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, capex::array<bool> *values, bool def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					std::string val = capex::tools::StrLower(l.values[column].value);
					bool v = false;
					if((strcmp(val.c_str(), "true") == 0) || (strcmp(val.c_str(), "1") == 0))
						v = true;
					else
						v = false;
					values->append(v);
				}
				else if(l.type == csv::ltValue)
				{
					values->append(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, capex::array<int> *values, int def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					try
					{
						int v = int(std::strtod(l.values[column].value.c_str(), NULL));
						values->append(v);
					}
					catch(...)
					{
						values->append(def);
					}
				}
				else if(l.type == csv::ltValue)
				{
					values->append(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, capex::array<float> *values, float def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					try
					{
						float v = std::strtod(l.values[column].value.c_str(), NULL);
						values->append(v);
					}
					catch(...)
					{
						values->append(def);
					}
				}
				else if(l.type == csv::ltValue)
				{
					values->append(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	int CAPEX_CALL csv::GetColumn(unsigned int column, capex::array<double> *values, double def)
	{
		if(values == NULL)
			return 0;

		values->clear();

		bool DataPresent = false;
		for(int n = 0; n < this->tab->lines.size(); n++)
		{
			csv::line l = this->tab->lines[n];
			if(l.values.size() > column)
			{
				DataPresent = true;
				break;
			}
		}

		if(DataPresent)
		{
			for(int n = 0; n < this->tab->lines.size(); n++)
			{
				csv::line l = this->tab->lines[n];
				if(l.values.size() > column)
				{
					try
					{
						double v = std::strtod(l.values[column].value.c_str(), NULL);
						values->append(v);
					}
					catch(...)
					{
						values->append(def);
					}
				}
				else if(l.type == csv::ltValue)
				{
					values->append(def);
				}
			}
		}

		return values->size();
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, std::vector<std::string> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, std::vector<bool> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, std::vector<int> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, std::vector<double> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, capex::array<bool> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, capex::array<int> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, capex::array<float> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetColumn(unsigned int column, capex::array<double> values, int start)
	{
		bool success = true;

		for(unsigned int i = 0; i < values.size(); i++)
		{
			bool ok = this->SetValue(start + i, column, values[i]);
			success &= ok;
		}

		return success;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::WriteCSV(const table *t, const char *File)
	{
		std::string SaveFile;

		if(File == NULL)
			SaveFile = this->FileName;
		else
			SaveFile = std::string(File);

		if(t == NULL)
			return false;

		try
		{
			std::ofstream f;
			f.open(SaveFile.c_str(), std::ios::out);
			std::string s = this->TableToString(t);
			f.write(s.c_str(), s.size());
			f.close();
			return true;
		}
		catch(...)
		{
			return false;
		}
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetValue(unsigned int line, unsigned int position, std::string value)
	{
		return this->WriteValue(line, position, value);
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetValue(unsigned int line, unsigned int position, bool value)
	{
		if(value)
			return this->WriteValue(line, position, "true");
		else
			return this->WriteValue(line, position, "false");
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetValue(unsigned int line, unsigned int position, int value)
	{
		return this->WriteValue(line, position, tools::NumToStr(value));
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL csv::SetValue(unsigned int line, unsigned int position, double value, int precision)
	{
		return this->WriteValue(line, position, tools::NumToStr(value, precision));
	}
	//-------------------------------------------------------------------------

}
