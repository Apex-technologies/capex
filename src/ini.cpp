//--------------------------------------------------------------------------
//                                INIPARSER.CPP
//--------------------------------------------------------------------------
//!
//! \file ini.cpp
//! \brief Class for parsing INI file
//! \author Maxime Fontaine
//! \version 0.1
//! \date 2015-02-08
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

	CAPEX_CALL ini::ini(const char* File)
	{
		this->dico = new dictionary;
		this->Keys = new std::vector<std::string>;
		this->KeysLines = new std::vector<unsigned int>;
		this->Comments = new std::vector<comment>;
		this->LinesType = new std::vector<int>;

		this->FileEndLine = 0;
		this->EndLine = 0;
		
		if(File != NULL)
		{
			this->Open(File);
		}
	}
	//-------------------------------------------------------------------------

	
	CAPEX_CALL ini::~ini()
	{
		delete this->dico;
		delete this->Keys;
		delete this->KeysLines;
		delete this->Comments;
		delete this->LinesType;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL ini::Open(const char* File)
	{
		this->KeysLines->clear();
		this->dico->sections.clear();
		this->dico->Keys.clear();
		this->Keys->clear();

		this->FileName = File;
		std::ifstream f;
		f.open(this->FileName, std::ios::in);

		if(!f.is_open())
			return false;

		std::string line = "";
		while (!f.eof())
		{
			char c = f.get();
			if((int)(c) == -1)
				c = '\0';
			if(c != '\r')
				line += (char)c;
			if(c == '\n')
			{
				this->TextFile += line;
				line = "";
			}
		}
		f.close();

	    this->GetLinesType();
		
        return true;
	}
	//-------------------------------------------------------------------------
	
	
	std::vector<std::string> CAPEX_CALL ini::GetLines()
	{
		std::vector<std::string> v;
		v.clear();

	    std::string txt = this->TextFile;
	    char *str = &(txt[0]);

		char *pch;
	    pch = strtok(str, "\n");
		while (pch != NULL)
		{
			v.push_back(std::string(pch));
			pch = strtok (NULL, "\n\r");
		}

		this->FileEndLine = v.size();
		if(this->EndLine == 0)
			this->EndLine = this->FileEndLine;
		
		return v;
	}
	//-------------------------------------------------------------------------
	
	
	void CAPEX_CALL ini::GetLinesType()
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
			int pcomma = L[i].find_first_of(";", 0);
			if(pcomma >= 0 && pcomma < L[i].size())
				p = pcomma;

			if(p == 0)
				this->LinesType->push_back(0);
			else if(p == -1)
				this->LinesType->push_back(1);
			else if(p > 0)
				this->LinesType->push_back(2);

			comment c;
			if(p >= 0)
				c.text = L[i].substr(p, L[i].size() - p);
			else
				c.text = "";
			c.line = i;
			this->Comments->push_back(c);
		}
		
	}
	//-------------------------------------------------------------------------
	
	
	std::vector<std::string> CAPEX_CALL ini::GetSectionsName()
	{
		if(this->Keys->size() == 0)
		{
			this->KeysLines->clear();

			std::vector<std::string> p = this->GetLines();

			for(unsigned int i = 0; i < p.size(); i++)
			{
				p[i] = tools::StrTrim(p[i], tools::tmBoth);

				// transforme une std::string en char*
				char *str = new char[p[i].length() + 1];
				std::copy(p[i].begin(), p[i].end(), str);
				str[p[i].length()] = '\0';

				char *pch;
				if(str[0] == '[' && str[p[i].length() - 1] == ']')
				{
					pch = strtok (str,"[]");
					while (pch != NULL)
					{
						this->Keys->push_back(std::string(pch));
						pch = strtok (NULL, "[]");
						this->KeysLines->push_back(i);
					}
				}
			}
		}

		this->KLines = *(this->KeysLines);

		return *(this->Keys);
	}
	//-------------------------------------------------------------------------
	
	
	int CAPEX_CALL ini::GetSectionNumber()
	{
		if(this->Keys->size() == 0)
			this->GetSectionsName();

		return this->Keys->size();
	}
	//-------------------------------------------------------------------------
	
	
	section CAPEX_CALL ini::GetSection(const char *section)
	{
		std::vector<std::string> p = this->GetLines();
		int KNumber = -1;

		struct section s;
		s.key = "";
		s.parameters.clear();

		for(int i = 0; i < this->GetSectionNumber(); i++)
		{
			if(std::strcmp(std::string(section).c_str(), this->Keys->at(i).c_str()) == 0)
				KNumber = i;
		}

		if(KNumber < 0)
			return s;

		s.key = std::string(section);
		s.line = this->KeysLines->at(KNumber);

		unsigned int EndLine;
		if(KNumber >= this->KeysLines->size() - 1)
			EndLine = p.size();
		else
			EndLine = this->KeysLines->at(KNumber + 1);

		for(unsigned int i = 0; i < p.size(); i++)
		{
			if(i >= EndLine)
				break;

			if(i >= this->KeysLines->at(KNumber) + 1)
			{
				parameter sp;

				p[i] = tools::StrTrim(p[i], tools::tmBoth);

				// transforme une std::string en char*
				char *str = new char[p[i].length() + 1];
				copy(p[i].begin(), p[i].end(), str);
				str[p[i].length()] = '\0';

				char *pch;
				if(str[0] != '#' && str[0] != '\n' && str[0] != ';')
				{
					pch = std::strtok (str,"=");
					if(pch != NULL)
					{
						sp.name = tools::StrTrim(std::string(pch), tools::tmBoth);
						pch = std::strtok (NULL, "=#;");
						sp.value = tools::StrTrim(std::string(pch), tools::tmBoth);
						pch = std::strtok (NULL, "#;");
						if(pch != NULL)
							sp.comment = tools::StrTrim(std::string(pch), tools::tmBoth);
						sp.line = i;
						s.parameters.push_back(sp);
					}
				}
			}
		}

		return s;
	}
	//-------------------------------------------------------------------------


	std::vector<std::string> CAPEX_CALL ini::GetKeysName(const char *section)
	{
		struct section s = this->GetSection(section);
		std::vector<std::string> Keys;
		Keys.clear();

		for(unsigned int i = 0; i < s.parameters.size(); i++)
		{
			Keys.push_back(s.parameters[i].name);
		}

		return Keys;
	}
	//-------------------------------------------------------------------------


	bool CAPEX_CALL ini::KeyExists(const char* section, const char *key)
	{
		struct section s = this->GetSection(section);
		bool Exists = false;

		for(unsigned int i = 0; i < s.parameters.size(); i++)
		{
			if(std::strcmp(s.parameters[i].name.c_str(), std::string(key).c_str()) == 0)
			{
				Exists = true;
				break;
			}
		}

		return Exists;
	}
	//-------------------------------------------------------------------------

	
	dictionary CAPEX_CALL ini::GetDictionary()
	{
		if(this->dico->sections.size() == 0)
		{
			if(this->Keys->size() == 0)
				this->GetSectionsName();

			for(unsigned int i = 0; i < this->Keys->size(); i++)
			{
				this->dico->sections.push_back(this->GetSection(this->Keys->at(i).c_str()));
			}
		}

		return *(this->dico);
	}
	//-------------------------------------------------------------------------
	
	
	bool CAPEX_CALL ini::GetBoolean(const char *section, const char *key)
	{
		bool v = false;

		struct section s;
		s.key = "";
		s.parameters.clear();
		s = this->GetSection(section);

		for(unsigned int i = 0; i < s.parameters.size(); i++)
		{
			if(std::strcmp(s.parameters[i].name.c_str(), std::string(key).c_str()) == 0)
			{
				if(std::strcmp(tools::StrLower(s.parameters[i].value).c_str(), "true") == 0 || std::strcmp(s.parameters[i].value.c_str(), "1") == 0)
					v = true;
				else
					v = false;
			}
		}

		return v;
	}
	//-------------------------------------------------------------------------
	
	
	std::string CAPEX_CALL ini::GetString(const char *section, const char *key)
	{
		struct section s;
		s.key = "";
		s.parameters.clear();
		s = this->GetSection(section);

		for(unsigned int i = 0; i < s.parameters.size(); i++)
		{
			if(std::strcmp(s.parameters[i].name.c_str(), std::string(key).c_str()) == 0)
			{
				return s.parameters[i].value.c_str();
			}
		}

		return "";
	}
	//-------------------------------------------------------------------------
	
	
	int CAPEX_CALL ini::GetInteger(const char *section, const char *key)
	{
		int v = 0;

		struct section s;
		s.key = "";
		s.parameters.clear();
		s = this->GetSection(section);

		for(unsigned int i = 0; i < s.parameters.size(); i++)
		{
			if(std::strcmp(s.parameters[i].name.c_str(), std::string(key).c_str()) == 0)
			{
				try
				{
					v = int(std::strtod(s.parameters[i].value.c_str(), NULL));
				}
				catch(...)
				{}
			}
		}

		return v;
	}
	//-------------------------------------------------------------------------
	
	
	double CAPEX_CALL ini::GetDouble(const char *section, const char *key)
	{
		double v = 0.0;

		struct section s;
		s.key = "";
		s.parameters.clear();
		s = this->GetSection(section);

		for(unsigned int i = 0; i < s.parameters.size(); i++)
		{
			if(std::strcmp(s.parameters[i].name.c_str(), std::string(key).c_str()) == 0)
			{
				try
				{
					v = std::strtod(s.parameters[i].value.c_str(), NULL);
				}
				catch(...)
				{}
			}
		}

		return v;
	}
	//-------------------------------------------------------------------------
	
	
	std::string CAPEX_CALL ini::DicoToString(const dictionary *d)
	{
		std::string s = "";

		if(d == NULL)
			return s;

		if(this->LinesType->size() != 0)
		{
			for(unsigned int l = 0; l < this->LinesType->size(); l++)
			{
				if(this->LinesType->at(l) == 0)
					s += this->Comments->at(l).text + "\n";
				else if(this->LinesType->at(l) == 1 || this->LinesType->at(l) == 2)
				{
					bool WriteDone = false;
					for(unsigned int i = 0; i < d->sections.size(); i++)
					{
						if(d->sections[i].line == l)
						{
							WriteDone = true;
					        if(l != 0)
						        s += "\n";
					        s += "[" + d->sections[i].key + "]" + this->Comments->at(l).text + "\n";
						}
					}
					if(!WriteDone)
					{
						for(unsigned int i = 0; i < d->sections.size(); i++)
						{
							for(unsigned int j = 0; j < d->sections[i].parameters.size(); j++)
							{
								if(d->sections[i].parameters[j].line == l)
								{
									s += d->sections[i].parameters[j].name + " = " + d->sections[i].parameters[j].value + \
										 this->Comments->at(l).text + "\n";
								}
							}
						}
					}
				}
			}
		}
		else
		{
			for(unsigned int i = 0; i < d->sections.size(); i++)
			{
				s += "\n[" + d->sections[i].key + "]" + "\n";

				for(unsigned int j = 0; j < d->sections[i].parameters.size(); j++)
				{
					s += d->sections[i].parameters[j].name + " = " + d->sections[i].parameters[j].value + "\n";
				}
			}
		}

		return s;
	}
	//-------------------------------------------------------------------------

	
	bool CAPEX_CALL ini::WriteINI(const dictionary *d, const char *File)
	{
		if(File == NULL)
			File = this->FileName;

		if(d == NULL)
			return false;

		try
		{
			std::ofstream f;
			f.open(File, std::ios::out);
			std::string s = this->DicoToString(d);
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
	
	
	bool CAPEX_CALL ini::SetValue(const char *section, const char *key, bool value)
	{
		if(value)
			return this->WriteValue(section, key, "true");
		else
			return this->WriteValue(section, key, "false");
	}
	//-------------------------------------------------------------------------
	
	
	bool CAPEX_CALL ini::SetValue(const char *section, const char *key, int value)
	{
		return this->WriteValue(section, key, tools::NumToStr(value));
	}
	//-------------------------------------------------------------------------
	
	
	bool CAPEX_CALL ini::SetValue(const char *section, const char *key, double value, int precision)
	{
		return this->WriteValue(section, key, tools::NumToStr(value, precision));
	}
	//-------------------------------------------------------------------------
	
	
	bool CAPEX_CALL ini::SetValue(const char *section, const char *key, std::string value)
	{
		return this->WriteValue(section, key, value);
	}
	//-------------------------------------------------------------------------
	
	
	bool CAPEX_CALL ini::WriteValue(const char *section, const char *parameter, std::string value)
	{
		bool success = false;

		if(this->dico->sections.size() == 0)
			*(this->dico) = this->GetDictionary();

		bool sExists = false;
		bool pExists = false;
		for(unsigned int i = 0; i < this->dico->sections.size(); i++)
		{
			if(std::strcmp(this->dico->sections[i].key.c_str(), std::string(section).c_str()) == 0)
			{
				sExists = true;
				for(unsigned int j = 0; j < this->dico->sections[i].parameters.size(); j++)
				{
					if(std::strcmp(this->dico->sections[i].parameters[j].name.c_str(), std::string(parameter).c_str()) == 0)
					{
						pExists = true;
						this->dico->sections[i].parameters[j].value = value;
					}
				}
				if(!pExists)
				{
					struct parameter p;
					struct comment c;
					std::vector<int>::iterator LIt = this->LinesType->begin();
					std::vector<comment>::iterator CIt = this->Comments->begin();
					c.text = "";
					p.name = std::string(parameter);
					p.value = value;
					p.line = this->dico->sections[i].parameters[this->dico->sections[i].parameters.size() - 1].line + 1;
					c.line = p.line;
					this->ChangeLine(p.line);
					(this->EndLine)++;
				    this->LinesType->insert(LIt + p.line, 1);
				    this->Comments->insert(CIt + p.line, c);

					this->dico->sections[i].parameters.push_back(p);
				}
			}
		}

		if(!sExists)
		{
			struct section s;
			struct parameter p;
			struct comment c;
			c.text = "";
			s.key = std::string(section);
			s.line = this->EndLine;
			c.line = this->EndLine;
			(this->EndLine)++;
			this->LinesType->push_back(1);
			this->Comments->push_back(c);

			p.name = std::string(parameter);
			p.value = value;
			p.line = this->EndLine;
			c.line = this->EndLine;
			(this->EndLine)++;
			this->LinesType->push_back(1);
			this->Comments->push_back(c);

			s.parameters.push_back(p);
			this->dico->sections.push_back(s);
		}

		return success;
	}
	//-------------------------------------------------------------------------
	
	
	void CAPEX_CALL ini::ChangeLine(unsigned int NewLine)
	{
		for(unsigned int i = 0; i < this->dico->sections.size(); i++)
		{
			if(this->dico->sections[i].line >= NewLine)
			{
				(this->dico->sections[i].line)++;
			}

			for(unsigned int j = 0; j < this->dico->sections[i].parameters.size(); j++)
			{
				if(this->dico->sections[i].parameters[j].line >= NewLine)
				{
					(this->dico->sections[i].parameters[j].line)++;
				}
			}
		}

		for(unsigned int i = 0; i < this->Comments->size(); i++)
		{
			if(this->Comments->at(i).line >= NewLine)
				(this->Comments->at(i).line)++;
		}

	}
	//-------------------------------------------------------------------------

}
