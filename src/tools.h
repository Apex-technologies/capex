#ifndef _CAPEX_TOOLS_H
#define _CAPEX_TOOLS_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>

#include "./constants.h"


namespace capex
{
	
	namespace tools
	{
		
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


		//! \brief The file path of the Log file
		static std::string LogFile;
		

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


		// ---------------------------------------------------------------------
		//! \brief Open a log file and redirect error output
		//! \param file path to the log file
		//! \return a \a boolean indicating if the file is created
		//!
		//! This function opens a file for saving all error output into it.
		//! The standard error output "std::cerr" is redirected into this file.
		//! This function returns \b true if the file is opened, \b false
		//! otherwise.
		//!
		//! If no file path is given, the default file path is used. See the
		//! default path into capex::DefaultLogFile
		//!
		//! Use function WriteLogFile to write data into this file and use
		//! CloseLogFile to close the file and redirect "std::cerr" into
		//! standard error output.
		//!
		// ---------------------------------------------------------------------
		bool CAPEX_CALL InitLogFile(const char *file = NULL);


		// ---------------------------------------------------------------------
		//! \brief Get the file path of the log file
		//! \return a \a string representing the file path
		//!
		//! This function returns the file path of the log file
		//!
		// ---------------------------------------------------------------------
		std::string CAPEX_CALL GetLogFile();


		// ---------------------------------------------------------------------
		//! \brief Write data into the log file
		//! \param LogText string pointer to write into the log file
		//!
		//! This function writes text into the standard error output. If the
		//! function InitLogFile has been called before, the text is saved
		//! into the opened log file.
		//!
		//! This function saves a string as follow:
		//!    Day/Month/Year - Hour:Min:Sec - LogText
		//!
		// ---------------------------------------------------------------------
		void CAPEX_CALL WriteLogFile(const char *LogText);


		// ---------------------------------------------------------------------
		//! \brief Close a log file and redirect error output
		//!
		//! This function closes a log file and redirect the error output
		//! "std::cerr" into the standard error output.
		//!
		// ---------------------------------------------------------------------
		void CAPEX_CALL CloseLogFile();
		
		
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
		//! \brief Converts an array of wavelengths into frequencies or invert
		//! \param Array  The array to convert
		//! \return an \e array representing the converted value
		//!
		//! This function converts vacuum wavelengths into frequencies or a frequencies
		//! into vacuum wavelengths.
		//!
		//! Here is a table representing the conversion units :
		//!     - m    <==>   Hz
		//!     - mm   <==>   kHz
		//!     - um   <==>   MHz
		//!     - nm   <==>   GHz
		//!     - pm   <==>   THz
		//!
		// ---------------------------------------------------------------------
		array<double> CAPEX_CALL ConvertWavelengthOrFrequency(array<double> Array);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts an array of wavelengths into frequencies or invert
		//! \param Array  The array to convert
		//! \return an \e array representing the converted value
		//!
		//! This function converts vacuum wavelengths into frequencies or a frequencies
		//! into vacuum wavelengths.
		//!
		//! Here is a table representing the conversion units :
		//!     - m    <==>   Hz
		//!     - mm   <==>   kHz
		//!     - um   <==>   MHz
		//!     - nm   <==>   GHz
		//!     - pm   <==>   THz
		//!
		// ---------------------------------------------------------------------
		array<float> CAPEX_CALL ConvertWavelengthOrFrequency(array<float> Array);
		
		
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
		//! \brief Converts a linear values array into a Bel values array
		//! \param Array         The array to convert
		//! \param Coefficient   Coefficient of the conversion (10 by default)
		//! \return an \e array with the converted values
		//!
		//! This function converts a linear values array into a Bel values array.
		//! Coefficient is the coefficient of the conversion. To get power 
		//! decibel, coefficient has to be 10.0 (default value). To get voltage
		//! decibel, coefficient has to be 20.0.
		//!
		// ---------------------------------------------------------------------
		array<double> CAPEX_CALL ConvertLinearToBel(array<double> Array, double Coefficient = 10.0);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a linear values array into a Bel values array
		//! \param Array         The array to convert
		//! \param Coefficient   Coefficient of the conversion (10 by default)
		//! \return an \e array with the converted values
		//!
		//! This function converts a linear values array into a Bel values array.
		//! Coefficient is the coefficient of the conversion. To get power 
		//! decibel, coefficient has to be 10.0 (default value). To get voltage
		//! decibel, coefficient has to be 20.0.
		//!
		// ---------------------------------------------------------------------
		array<float> CAPEX_CALL ConvertLinearToBel(array<float> Array, double Coefficient = 10.0);
		
		
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
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a Bel values array into a linear values array
		//! \param Array         The array to convert
		//! \param Coefficient   Coefficient of the conversion (10 by default)
		//! \return aa \e array with the converted values
		//!
		//! This function converts a Bel values array into a linear values array.
		//! Coefficient is the coefficient of the conversion. To get a linear
		//! value from a decibel power, coefficient has to be 10.0 (default value).
		//! To get a linear value from a decibel voltage, coefficient has to be
		//! 20.0.
		//!
		// ---------------------------------------------------------------------
		array<double> CAPEX_CALL ConvertBelToLinear(array<double> Array, double Coefficient = 10.0);
		
		
		// ---------------------------------------------------------------------
		//! \brief Converts a Bel values array into a linear values array
		//! \param Array         The array to convert
		//! \param Coefficient   Coefficient of the conversion (10 by default)
		//! \return aa \e array with the converted values
		//!
		//! This function converts a Bel values array into a linear values array.
		//! Coefficient is the coefficient of the conversion. To get a linear
		//! value from a decibel power, coefficient has to be 10.0 (default value).
		//! To get a linear value from a decibel voltage, coefficient has to be
		//! 20.0.
		//!
		// ---------------------------------------------------------------------
		array<float> CAPEX_CALL ConvertBelToLinear(array<float> Array, double Coefficient = 10.0);
		
		
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


        //-------------------------------------------------------------------------
		//!
		//! \brief    Count the number of occurences of the pattern in the string
		//! \param    strinit string where to find patterns
		//! \param    pattern string to look for
		//! \return   an \e integer representing the number of occurences
		//!
		//! This function counts the number of occurences of the pattern found
		//! into the given string
		//!
		//--------------------------------------------------------------------------
		int CAPEX_CALL StrOccurences(std::string strinit, std::string pattern);


		//-------------------------------------------------------------------------
		//!
		//! \brief    Count the number of occurences of the pattern in the string
		//! \param    strinit string where to find patterns
		//! \param    pattern string to look for
		//! \return   an \e integer representing the number of occurences
		//!
		//! This function counts the number of occurences of the pattern found
		//! into the given string
		//!
		//--------------------------------------------------------------------------
		int CAPEX_CALL StrOccurences(std::string strinit, const char pattern);


		//-------------------------------------------------------------------------
		//!
		//! \brief    Split a string using separator as the delimiter string
		//! \param    strinit string to split
		//! \param    separator character(s) to use as delimiter
		//! \param    any  boolean indicating if any of the seprators have to be used
		//! \return   a \e vector of \e strings
		//!
		//! This function splits a string into sub-strings using the separator
		//! as delimiter. If 'any' is set to \b false, the entire string will be used
		//! as delimiter. If 'any' is set to \b true (default), any character
		//! in 'separator' will be used as delimiter. If no separator is send,
		//! the delimitor character is one of ' ', '\t' or '\n'
		//!
		//--------------------------------------------------------------------------
		std::vector<std::string> StrSplit(std::string strinit, const char *separator = NULL, bool any = true);


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
