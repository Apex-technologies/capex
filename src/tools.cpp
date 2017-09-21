
using std::cout;
using std::endl;

namespace capex
{
	
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
		double CAPEX_CALL ConvertWavelengthOrFrequency(double Value)
		{
			return celerity / Value;
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
					cout << "Error in ConvertLinearToBel at line " << __LINE__ << endl;
					cout << "Value forced to -999" << endl;
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
					cout << "Error in ConvertBelToLinear at line " << __LINE__ << endl;
					cout << "Value forced to 0" << endl;
				#endif
				lin = 0.0;
			}
			return lin;
		}
		// -------------------------------------------------------------------
		
		
		// -------------------------------------------------------------------
		template<typename T>
		bool CAPEX_CALL WriteInFile(const char *FilePath, iom Mode, T *Values, int Number, int Precision, char *Separator)
		{
			ofstream f;
			if(mode == out)
				f.open(FileName, std::ios::out);
			else if(mode == app)
				f.open(FileName, std::ios::app);
			if(!f.is_open())
				return false;

			f.precision(Precision);
			
			if(Separator == NULL)
				sprintf(Separator, "\n");
			
			try
			{
				for(int i = 0; i < Number; i++)
				{
					f << Values[i];
					if(i < Number - 1)
						f << std::string(Separator);
				}
			}
			catch(...)
			{
				#if CAPEX_DEBUG
					cout << "Error in WriteInFile at line " << __LINE__ << endl;
					cout << "File '" << std::string(FilePath) << "' has been closed" << endl;
				#endif
				f.close();
				return false;
			}
			
			f.close();
			return true;
		}
		// -------------------------------------------------------------------
		
		
	}
	
}





































