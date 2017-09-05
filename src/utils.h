#ifndef _CAPEX_UTILS_H
#define _CAPEX_UTILS_H

#include <stdio.h>


namespace capex
{
	
	namespace utils
	{

		enum iom
		{
			out = 0,
			in = 1,
			app = 2
		};

		// ---------------------------------------------------------------------
		//! \brief Get the time (day and hour) with the specified format
		//! \param TimeString  Pointer to the formatted time string
		//! \param format      Pointer specifying the format of the time string
		//!
		//! This function returns a string containing the time with the specified
		//! format. If no format is specified, the default one is used :
		//!
		//! \e Day/Month/Year - \e Hour:Min:Sec -
		//!
		//! For specifying a format, use special characters :
		//!     - \a %d : day number
		//!     - \a %m : month number
		//!     - \a %Y : year
		//!     - \a %H : hour
		//!     - \a %M : minute
		//!     - \a %S : seconds
		//! For other format characters, please refer to the \b strftime function
		//! of the library \b stdio.h
		//!
		// ---------------------------------------------------------------------
		bool CAPEX_CALL GetTime(char *TimeString, const char *format = NULL);
		
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, float *Values, int Number, const char *format = NULL);
		
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, double *Values, int Number, const char *format = NULL);
		
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, int *Values, int Number, const char *format = NULL);
		
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, char *Values, int Number, const char *format = NULL);
		
		bool CAPEX_CALL WriteInFile(const char *FileName, iom mode, char *String);
		
		template<typename T>
		bool CAPEX_CALL WriteInFile(const char *FileName, iom Mode, T *Values, int Number = 0, const char *format = NULL);
		
	}
	
}

#endif