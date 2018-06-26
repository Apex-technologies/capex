#include "./constants.h"

using std::cerr;
using std::endl;

// Buffer for saving the standard error before redirecting it
static std::streambuf *errbuf;

// File for saving the error redirection data
static std::ofstream err;

namespace capex
{

	namespace tools
	{

		// -------------------------------------------------------------------
		std::string CAPEX_CALL GetTime(const char *format)
		{
			bool NewFormat = false;

			if(format == NULL)
			{
				format = new char[32];
				NewFormat = true;
				sprintf((char*)format, "%%d/%%m/%%Y - %%H:%%M:%%S - ");
			}

			time_t rawtime;
			struct tm * timeinfo;
			char buffer [80];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, 80 , format, timeinfo);

			if(NewFormat)
				delete[] format;

			return std::string(&buffer[0]);
		}
		// -------------------------------------------------------------------


		// -------------------------------------------------------------------
		bool CAPEX_CALL InitLogFile(const char *file)
		{
			if(file == NULL)
				file = (char*)(&DefaultLogFile[0]);
			
			// redirect errors to the logfile
			errbuf = cerr.rdbuf();
			err.open(file, std::ios::out);
			bool opened = err.is_open();
			cerr.rdbuf(err.rdbuf());

			cerr << GetTime() << "Error output redirected into " << std::string(file) << endl;

			LogFile = std::string(file);

			return opened;
		}
		// -------------------------------------------------------------------


		// -------------------------------------------------------------------
		std::string CAPEX_CALL GetLogFile()
		{
			return LogFile;
		}
		// -------------------------------------------------------------------


		// -------------------------------------------------------------------
		void CAPEX_CALL WriteLogFile(const char *LogText)
		{
			cerr << GetTime() << LogText << endl;
		}
		// -------------------------------------------------------------------

		
		// -------------------------------------------------------------------
		void CAPEX_CALL CloseLogFile()
		{
			cerr << GetTime() << "Error output redirected into standard output" << endl;

			if(err.is_open())
				err.close();

			// redirect errors to the standard error output
			cerr.rdbuf(errbuf);
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		double CAPEX_CALL ConvertWavelengthOrFrequency(double Value)
		{
			if(Value <= lowerLimit)
			{
				#if CAPEX_DEBUG
					cerr << GetTime() << "capex::tools - Error in ConvertWavelengthOrFrequency at line " << __LINE__ << endl;
					cerr << GetTime() << "capex::tools - Value forced to 0.0" << endl;
				#endif
				return 0.0;
			}
			
			return VacuumCelerity / Value;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		array<double> CAPEX_CALL ConvertWavelengthOrFrequency(array<double> Array)
		{
			array<double> ConvertedArray;
			ConvertedArray.resize(Array.size());
			
			for(unsigned int i = 0; i < Array.size(); i++)
			{
				ConvertedArray[i] = ConvertWavelengthOrFrequency(Array[i]);
			}
			
			return ConvertedArray;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		array<float> CAPEX_CALL ConvertWavelengthOrFrequency(array<float> Array)
		{
			array<float> ConvertedArray;
			ConvertedArray.resize(Array.size());
			
			for(unsigned int i = 0; i < Array.size(); i++)
			{
				ConvertedArray[i] = ConvertWavelengthOrFrequency(Array[i]);
			}
			
			return ConvertedArray;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		double CAPEX_CALL ConvertDeltaWavelengthOrFrequency(double Delta, double Center)
		{
			if(Center <= lowerLimit)
			{
				#if CAPEX_DEBUG
					cerr << GetTime() << "capex::tools - Error in ConvertDeltaWavelengthOrFrequency at line " << __LINE__ << endl;
					cerr << GetTime() << "capex::tools - Value forced to 0.0" << endl;
				#endif
				return 0.0;
			}

			return VacuumCelerity * (Delta / (Center * Center));
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		double CAPEX_CALL ConvertLinearToBel(double Value, double Coefficient)
		{
			double db;
			try
			{
				db = Coefficient * std::log10(Value);
			}
			catch(...)
			{
				#if CAPEX_DEBUG
					cerr << GetTime() << "capex::tools - Error in ConvertLinearToBel at line " << __LINE__ << endl;
					cerr << GetTime() << "capex::tools - Value forced to -capex::inf" << endl;
				#endif
				db = -capex::inf;
			}
			return db;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		array<double> CAPEX_CALL ConvertLinearToBel(array<double> Array, double Coefficient)
		{
			array<double> ConvertedArray;
			ConvertedArray.resize(Array.size());
			
			for(unsigned int i = 0; i < Array.size(); i++)
			{
				ConvertedArray[i] = ConvertLinearToBel(Array[i], Coefficient);
			}
			
			return ConvertedArray;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		array<float> CAPEX_CALL ConvertLinearToBel(array<float> Array, double Coefficient)
		{
			array<float> ConvertedArray;
			ConvertedArray.resize(Array.size());
			
			for(unsigned int i = 0; i < Array.size(); i++)
			{
				ConvertedArray[i] = ConvertLinearToBel(Array[i], Coefficient);
			}
			
			return ConvertedArray;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		double CAPEX_CALL ConvertBelToLinear(double Value, double Coefficient)
		{
			double lin;
			try
			{
				lin = std::pow(10.0, Value / Coefficient);
			}
			catch(...)
			{
				#if CAPEX_DEBUG
					cerr << GetTime() << "capex::tools - Error in ConvertBelToLinear at line " << __LINE__ << endl;
					cerr << GetTime() << "capex::tools - Value forced to 0" << endl;
				#endif
				lin = 0.0;
			}
			return lin;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		array<double> CAPEX_CALL ConvertBelToLinear(array<double> Array, double Coefficient)
		{
			array<double> ConvertedArray;
			ConvertedArray.resize(Array.size());
			
			for(unsigned int i = 0; i < Array.size(); i++)
			{
				ConvertedArray[i] = ConvertBelToLinear(Array[i], Coefficient);
			}
			
			return ConvertedArray;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		array<float> CAPEX_CALL ConvertBelToLinear(array<float> Array, double Coefficient)
		{
			array<float> ConvertedArray;
			ConvertedArray.resize(Array.size());
			
			for(unsigned int i = 0; i < Array.size(); i++)
			{
				ConvertedArray[i] = ConvertBelToLinear(Array[i], Coefficient);
			}
			
			return ConvertedArray;
		}
		// -------------------------------------------------------------------
		
		
		//--------------------------------------------------------------------
		std::string CAPEX_CALL StrTrim(std::string strinit, TrimMode mode)
		{
			if(mode == tmStart)
			{
				while(strinit[0] == ' ' || strinit[0] == '\t')
					strinit.erase(0, 1);
			}
			else if(mode == tmEnd)
			{
				while(strinit[strinit.size() - 1] == ' ' || strinit[strinit.size() - 1] == '\t')
					strinit.erase(strinit.size() - 1, 1);
			}
			else if(mode == tmBoth)
			{
				while(strinit[0] == ' ' || strinit[0] == '\t')
					strinit.erase(0, 1);
				while(strinit[strinit.size() - 1] == ' ' || strinit[strinit.size() - 1] == '\t')
					strinit.erase(strinit.size() - 1, 1);
			}
			else
			{
				#if CAPEX_DEBUG
					cerr << GetTime() << "capex::tools - Error in StrTrim at line " << __LINE__ << endl;
					cerr << GetTime() << "capex::tools - String has not been trimmed" << endl;
				#endif
			}
			return strinit;
		}
		//--------------------------------------------------------------------
		
		
		//--------------------------------------------------------------------
		std::string CAPEX_CALL StrLower(std::string strinit)
		{
			// transforms a std::string into char*
			char *str = new char[strinit.length() + 1];
			std::copy(strinit.begin(), strinit.end(), str);
			str[strinit.length()] = '\0';

			for(unsigned int i = 0; i < strinit.length(); i++)
			{
				if(str[i] <= 'Z' && str[i] >= 'A')
					str[i] -= ('Z' - 'z');
			}

			std::string lstr = std::string(str);
			delete[] str;

			return lstr;
		}
		//--------------------------------------------------------------------
		
		
		//--------------------------------------------------------------------
		std::string CAPEX_CALL StrUpper(std::string strinit)
		{
			// transforms a std::string into char*
			char *str = new char[strinit.length() + 1];
			std::copy(strinit.begin(), strinit.end(), str);
			str[strinit.length()] = '\0';

			for(unsigned int i = 0; i < strinit.length(); i++)
			{
				if(str[i] <= 'z' && str[i] >= 'a')
					str[i] -= ('z' - 'Z');
			}
			
			std::string ustr = std::string(str);
			delete[] str;

			return ustr;
		}
		//--------------------------------------------------------------------


		//--------------------------------------------------------------------
		int CAPEX_CALL StrOccurences(std::string strinit, std::string pattern)
		{
			int Count = 0;

			size_t position = strinit.find_first_of(pattern);
			while(position != std::string::npos)
			{
				Count++;
				position = strinit.find_first_of(pattern, position + 1);
			}

			return Count;
		}
		//--------------------------------------------------------------------


		//--------------------------------------------------------------------
		int CAPEX_CALL StrOccurences(std::string strinit, const char pattern)
		{
			int Count = 0;

			size_t position = strinit.find_first_of((char)(pattern));
			while(position != std::string::npos)
			{
				Count++;
				position = strinit.find_first_of((char)(pattern), position + 1);
			}

			return Count;
		}
		//--------------------------------------------------------------------


		//--------------------------------------------------------------------
		std::vector<std::string> StrSplit(std::string strinit, const char *separator, bool any)
		{
			std::vector<std::string> results;
			results.clear();

			std::string sep;
			if(separator == NULL)
				sep = std::string(" \t\n");
			else
				sep = std::string(separator);

			std::string str = strinit;

			if(any)
			{
				unsigned int CPos = str.length();
				for(int c = 0; c < sep.length(); c++)
				{
					unsigned int pos = str.find_first_of((char)(sep[c]));
					if((pos != std::string::npos) && (pos < CPos))
					{
						CPos = pos;
					}
				}

				while(CPos <= str.length())
				{
					if(CPos <= str.length())
					{
						results.push_back(str.substr(0, CPos));
					}
					else
					{
						results.push_back("");
					}
					if(CPos < str.length())
					{
						str = str.substr(CPos + 1, str.length() - CPos);

						CPos = str.length();
						for(int c = 0; c < sep.length(); c++)
						{
							unsigned int pos = str.find_first_of((char)(sep[c]));
							if((pos != std::string::npos) && (pos < CPos))
							{
								CPos = pos;
							}
						}
					}
					else
					{
						CPos = str.length() + 1;
					}
				}
			}
			else
			{
				unsigned int CPos = str.length();
				unsigned int pos = str.find(sep);
				if((pos != std::string::npos) && (pos < CPos))
				{
					CPos = pos;
				}

				while(CPos <= str.length())
				{
					if(CPos <= str.length())
					{
						results.push_back(str.substr(0, CPos));
					}
					else
					{
						results.push_back("");
					}
					if(CPos < str.length())
					{
						str = str.substr(CPos + sep.length(), str.length() - CPos);

						CPos = str.length();
						unsigned int pos = str.find(sep);
						if((pos != std::string::npos) && (pos < CPos))
						{
							CPos = pos;
						}
					}
					else
					{
						CPos = str.length() + 1;
					}
				}
			}

			return results;
		}
		//--------------------------------------------------------------------


		//--------------------------------------------------------------------
		std::string CAPEX_CALL NumToStr(int value)
		{
			if (value == 0)
				return "0";

			std::string temp="";
			std::string returnvalue="";
			
			if(value < 0)
				returnvalue += "-";
			
			value = std::abs(value);
			
			while (value > 0)
			{
				temp += value % 10 + 48;
				value /= 10;
			}
			for(int i = 0; i < temp.length(); i++)
				returnvalue += temp[temp.length() - i - 1];

			return returnvalue;
		}
		//--------------------------------------------------------------------
		

		//--------------------------------------------------------------------
		std::string CAPEX_CALL NumToStr(double value, int precision)
		{
			std::string temp="";
			std::string returnvalue="";
			
			if(value < 0.0)
				returnvalue += "-";
			
			value = std::fabs(value);

			int IntPart = int(value);
			
			if (IntPart == 0)
				returnvalue += "0";
				
			while (IntPart > 0)
			{
				temp += IntPart % 10 + 48;
				IntPart /= 10;
			}
			for(int i = 0; i < temp.length(); i++)
				returnvalue += temp[temp.length() - i - 1];

			temp = "";
			value = double(value) - int(value);
			value *= std::pow(10.0, precision);
			int DecPart = int(value);
			for(int i = 0; i < precision; i++)
			{
				temp += DecPart % 10 + 48;
				DecPart /= 10;
			}
			returnvalue += ".";
			for(int i = 0; i < temp.length(); i++)
				returnvalue += temp[temp.length() - i - 1];

			return returnvalue;
		}
		//--------------------------------------------------------------------


		//--------------------------------------------------------------------
		std::string CAPEX_CALL NumToHex(unsigned int value)
		{
			std::stringstream stream;
			stream << std::hex << value;

			std::string result = std::string(stream.str());
			result = StrUpper(result);

			return result;
		}
		//--------------------------------------------------------------------


		//--------------------------------------------------------------------
		unsigned int CAPEX_CALL HexToNum(std::string hexa)
		{
			unsigned int value;

			hexa = StrTrim(hexa, tmBoth);
			hexa = StrLower(hexa);

			if(strcmp(hexa.c_str(), "0x") >= 2)
				hexa = hexa.substr(2, hexa.size());

			std::stringstream stream;
			stream << std::hex << hexa;

			stream >> value;

			return value;
		}
		//--------------------------------------------------------------------
	}

}





































