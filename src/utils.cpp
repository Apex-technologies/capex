#include "utils.h"

#include <iostream>
#include <fstream>


namespace capex
{
	
	namespace utils
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
		
		template<typename T>
		bool CAPEX_CALL WriteInFile(const char *FileName, iom Mode, T *Values, int Number, const char *format)
		{
			
		}
		
		// -------------------------------------------------------------------
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, float *Values, int Number, const char *format)
		{
			
			ofstream f;
			if(mode == out)
				f.open(FileName, std::ios::out);
			else if(mode == app)
				f.open(FileName, std::ios::app);
			if(!f.is_open())
				return false;

			if(format == NULL)
				sprintf(format, "%.3f\n");
			
			try
			{
				for(int i = 0; i < Number; i++)
				{
					buffer[64];
					sprintf(buffer, format, Values[i]);
					f << buffer;
				}
			}
			catch(...)
			{
				f.close();
				return false;
			}
			
			f.close();
			return true;
		}
		// -------------------------------------------------------------------
		
		// -------------------------------------------------------------------
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, double *Values, int Number, const char *format)
		{
			
			ofstream f;
			if(mode == out)
				f.open(FileName, std::ios::out);
			else if(mode == app)
				f.open(FileName, std::ios::app);
			if(!f.is_open())
				return false;

			if(format == NULL)
				sprintf(format, "%.3f\n");
			
			try
			{
				for(int i = 0; i < Number; i++)
				{
					buffer[64];
					sprintf(buffer, format, Values[i]);
					f << buffer;
				}
			}
			catch(...)
			{
				f.close();
				return false;
			}
			
			f.close();
			return true;
		}
		// -------------------------------------------------------------------
		
		// -------------------------------------------------------------------
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, int *Values, int Number, const char *format)
		{
			
			ofstream f;
			if(mode == out)
				f.open(FileName, std::ios::out);
			else if(mode == app)
				f.open(FileName, std::ios::app);
			if(!f.is_open())
				return false;

			if(format == NULL)
				sprintf(format, "%i\n");
			
			try
			{
				for(int i = 0; i < Number; i++)
				{
					buffer[64];
					sprintf(buffer, format, Values[i]);
					f << buffer;
				}
			}
			catch(...)
			{
				f.close();
				return false;
			}
			
			f.close();
			return true;
		}
		// -------------------------------------------------------------------
		
		// -------------------------------------------------------------------
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, int *Values, int Number, const char *format)
		{
			
			ofstream f;
			if(mode == out)
				f.open(FileName, std::ios::out);
			else if(mode == app)
				f.open(FileName, std::ios::app);
			if(!f.is_open())
				return false;

			if(format == NULL)
				sprintf(format, "%c\n");
			
			try
			{
				for(int i = 0; i < Number; i++)
				{
					buffer[64];
					sprintf(buffer, format, Values[i]);
					f << buffer;
				}
			}
			catch(...)
			{
				f.close();
				return false;
			}
			
			f.close();
			return true;
		}
		// -------------------------------------------------------------------
		
		
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, char *String)
		{
			
			ofstream f;
			if(mode == out)
				f.open(FileName, std::ios::out);
			else if(mode == app)
				f.open(FileName, std::ios::app);
			if(!f.is_open())
				return false;

			try
			{
				char c = *String;
				while(c != '\0')
				{
					f << c;
					c = *(++String);
				}
			}
			catch(...)
			{
				f.close();
				return false;
			}
			
			f.close();
			return true;
		}
		// -------------------------------------------------------------------
		
	}
	
}