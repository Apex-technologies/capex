#include "./tools.h"
#include "./constants.h"

using std::cerr;
using std::endl;

namespace capex
{

	std::streambuf *errbuf;

	namespace tools
	{

		// -------------------------------------------------------------------
		void CAPEX_CALL GetTime(char *TimeString, char *format)
		{
			if(format == NULL)
				sprintf(format, "%d/%m/%Y - %H:%M:%S - ");

			time_t rawtime;
			struct tm * timeinfo;
			char buffer [80];

			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, 80 , format, timeinfo);
			for(int i = 0; i < 80; i++)
			{
				*(TimeString + i) = ((char)(buffer[i]));
				if(((char)(buffer[i])) == '\0')
					break;
			}
		}
		// -------------------------------------------------------------------


		// -------------------------------------------------------------------
		void CAPEX_CALL InitLogFile(char *file)
		{
			if(file == NULL)
				file = CAPEX_LOGFILE;

			// redirect errors to the logfile
			std::streambuf *errbuf = cerr.rdbuf();
			std::ofstream err(file);
			cerr.rdbuf(err.rdbuf());

			#if CAPEX_DEBUG
				cerr << "Error output redirected into " << std::string(file) << endl;
			#endif
		}
		// -------------------------------------------------------------------

		
		// -------------------------------------------------------------------
		void CAPEX_CALL WriteLogFile(char *LogText)
		{
			char TimeStamp [20];
			GetTime(&TimeStamp[0]);
			
			cerr << TimeStamp << LogText << endl;
		}
		// -------------------------------------------------------------------

		
		// -------------------------------------------------------------------
		void CAPEX_CALL CloseLogFile(char *file)
		{
			// redirect errors to the standard error output
			cerr.rdbuf(errbuf);
			
			#if CAPEX_DEBUG
				cerr << "Error output redirected into standard output" << endl;
			#endif
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		double CAPEX_CALL ConvertWavelengthOrFrequency(double Value)
		{
			if(Value <= lowerLimit)
			{
				#if CAPEX_DEBUG
					cerr << "Error in ConvertWavelengthOrFrequency at line " << __LINE__ << endl;
					cerr << "Value forced to 0.0" << endl;
				#endif
				return 0.0;
			}
			
			return VacuumCelerity / Value;
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
					cerr << "Error in ConvertLinearToBel at line " << __LINE__ << endl;
					cerr << "Value forced to -999" << endl;
				#endif
				db = -999.0;
			}
			return db;
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
					cerr << "Error in ConvertBelToLinear at line " << __LINE__ << endl;
					cerr << "Value forced to 0" << endl;
				#endif
				lin = 0.0;
			}
			return lin;
		}
		// -------------------------------------------------------------------
		
		
		//--------------------------------------------------------------------
		std::string CAPEX_CALL StrTrim(std::string strinit, int mode)
		{
			if(mode == 0)
			{
				while(strinit[0] == ' ' || strinit[0] == '\t')
					strinit.erase(0, 1);
			}
			else if(mode == 1)
			{
				while(strinit[strinit.size() - 1] == ' ' || strinit[strinit.size() - 1] == '\t')
					strinit.erase(strinit.size() - 1, 1);
			}
			else
			{
				while(strinit[0] == ' ' || strinit[0] == '\t')
					strinit.erase(0, 1);
				while(strinit[strinit.size() - 1] == ' ' || strinit[strinit.size() - 1] == '\t')
					strinit.erase(strinit.size() - 1, 1);
			}
			return strinit;
		}
		//--------------------------------------------------------------------
		
		
		//--------------------------------------------------------------------
		std::string CAPEX_CALL StrLower(std::string strinit)
		{
			// transforme une std::string en char*
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
			// transforme une std::string en char*
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

		
	}

}





































