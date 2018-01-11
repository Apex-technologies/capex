#ifndef _CAPEX_TOOLS_H
#define _CAPEX_TOOLS_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "./constants.h"


namespace capex
{
	
	namespace tools
	{
		//! \brief Light celerity in vacuum
		const double celerity = 299792458.0;
	
		
		//! \brief Input/Output mode for file
		enum iom
		{
			//! \brief File to open in output mode
			out = 0,
			//! \brief File to open in input mode
			in = 1,
			//! \brief File to open in append mode
			app = 2
		};

		// \brief Trim Mode of the string
		enum TrimMode
		{
			// \brief trims the start of the string
			tmStart = 0,
			// \brief trims the end of the string
			tmEnd = 1,
			// \brief trims the start and the end of the string
			tmBoth = -1
		};
		

		// ---------------------------------------------------------------------
		//! \brief Get the time (day and hour) with the specified format
		//! \param format      Pointer specifying the format of the time string
		//! \return a \a string with the formatted time 
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
		std::string CAPEX_CALL GetTime(const char *format = NULL);
		
		
		void CAPEX_CALL InitLogFile(char *file = NULL);
		void CAPEX_CALL WriteLogFile(char *LogText);
		void CAPEX_CALL CloseLogFile(char *file = NULL);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a wavelength into frequency or invert
		//! \param Value  Value to convert
		//! \return a \e double representing the converted value
		//!
		//! This function converts a vacuum wavelength into frequency or a frequency
		//! into vacuum wavelength.
		//!
		//! Here is a table representing the conversion units :
		//!     - m    <==>   Hz
		//!     - mm   <==>   kHz
		//!     - um   <==>   MHz
		//!     - nm   <==>   GHz
		//!     - pm   <==>   THz
		//!
		// ---------------------------------------------------------------------
		double CAPEX_CALL ConvertWavelengthOrFrequency(double Value);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a delta wavelength into delta frequency or invert
		//! \param Delta  Delta value to convert
		//! \param Center Center wavelength or frequency of the delta value
		//! \return a \e double representing the converted value
		//!
		//! This function converts a vacuum delta wavelengths into a delta
		//! frequencies or a delta frequencies into a vacuum delta wavelengths
		//!
		//! Here is a table representing the conversion units :
		//!     - m    <==>   Hz
		//!     - mm   <==>   kHz
		//!     - um   <==>   MHz
		//!     - nm   <==>   GHz
		//!     - pm   <==>   THz
		//!
		// ---------------------------------------------------------------------
		double CAPEX_CALL ConvertDeltaWavelengthOrFrequency(double Delta, double Center);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a linear value into a Bel value
		//! \param Value         Value to convert
		//! \param Coefficient   Coefficient of the conversion (10 by default)
		//! \return a \e double representing the converted value
		//!
		//! This function converts a linear value into a Bel value. Coefficient
		//! is the coefficient of the conversion. To get power decibel, coefficient
		//! has to be 10.0 (default value). To get voltage decibel, coefficient
		//! has to be 20.0.
		//!
		// ---------------------------------------------------------------------
		double CAPEX_CALL ConvertLinearToBel(double Value, double Coefficient = 10.0);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a Bel value into a linear value
		//! \param Value         Value to convert
		//! \param Coefficient   Coefficient of the conversion (10 by default)
		//! \return a \e double representing the converted value
		//!
		//! This function converts a Bel value into a linear value. Coefficient
		//! is the coefficient of the conversion. To get a linear value from a 
		//! decibel power, coefficient has to be 10.0 (default value). To get a
		//! linear value from a decibel voltage, coefficient has to be 20.0.
		//!
		// ---------------------------------------------------------------------
		double CAPEX_CALL ConvertBelToLinear(double Value, double Coefficient = 10.0);
		
		
		//-------------------------------------------------------------------------
		//!
		//! \brief    Trim spaces in a string at start, end or both
		//! \param    strinit string to trim
		//! \param    mode    TrimMode describing what part to trim (optional)
		//! \return   a \e string representing the trimmed string
		//! 
		//! This function trims spaces and tabulations which are at start and at end of a string
		//! mode is a TrimMode variable which can be:
		//!    tmStart : trims the start of the string
		//!    tmEnd : trims the end of the string
		//!    tmBoth : trims the start and the end of the string (default)
		//! 
		//! This function returns the trimmed string.
		//!
		//--------------------------------------------------------------------------
		std::string CAPEX_CALL StrTrim(std::string strinit, TrimMode mode = tmBoth);
		
		
		//-------------------------------------------------------------------------
		//!
		//! \brief    Converts a string in lower case
		//! \param    strinit string to convert
		//! \return   a \e string representing the converted string
		//! 
		//! This function converts all characters of a string into their lower case.
		//! 
		//! This function returns the lower case converted string.
		//!
		//--------------------------------------------------------------------------
		std::string CAPEX_CALL StrLower(std::string strinit);
		
		
		//-------------------------------------------------------------------------
		//!
		//! \brief    Converts a string in upper case
		//! \param    strinit string to convert
		//! \return   a \e string representing the converted string
		//! 
		//! This function converts all characters of a string into their upper case.
		//! 
		//! This function returns the upper case converted string.
		//!
		//--------------------------------------------------------------------------
		std::string CAPEX_CALL StrUpper(std::string strinit);
		
		
		//--------------------------------------------------------------------------
		//!
		//! \brief   Converts an integer into a string
		//! \param   value integer to convert
		//! \return  a \e string representing the converted value
		//! 
		//! this function converts an integer to a string.
		//! 
		//! this function returns the converted string.
		//!
		//--------------------------------------------------------------------------
		std::string CAPEX_CALL NumToStr(int value);
		
		//--------------------------------------------------------------------------
		//!
		//! \brief   Converts a double in a string
		//! \param   value double to convert
		//! \param   precision integer representing the decimal number after point (default = 6)
		//! \return  a \e string representing the converted value
		//! 
		//! this function converts a double to a string with a specified decimal number.
		//! 
		//! this function returns the converted string.
		//!
		//--------------------------------------------------------------------------
		std::string CAPEX_CALL NumToStr(double value, int precision = 6);

		//--------------------------------------------------------------------------
		//!
		//! \brief   Converts an integer into a string representing the hexa value
		//! \param   value integer to convert
		//! \return  a \e string representing the hexa converted value
		//!
		//! this function converts an integer to an hexadecimal string.
		//!
		//! this function returns the converted string.
		//!
		//--------------------------------------------------------------------------
		std::string CAPEX_CALL NumToHex(unsigned int value);

		//--------------------------------------------------------------------------
		//!
		//! \brief   Converts an hexadecimal string to an integer
		//! \param   hexa string to convert
		//! \return  an \e int representing the value
		//!
		//! this function converts an hexadecimal string to an integer.
		//!
		//! this function returns the converted integer.
		//!
		//--------------------------------------------------------------------------
		unsigned int CAPEX_CALL HexToNum(std::string hexa);
	}

}

#include "./tools.cpp"

#endif
