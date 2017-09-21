#ifndef _CAPEX_UTILS_H
#define _CAPEX_UTILS_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>


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

		
		// ---------------------------------------------------------------------
		//! \brief Write values in a text file
		//! \param FilePath  Path of the file to write
		//! \param Mode        Opening mode of the file. see iom enumeration
		//! \param Values      Values to write
		//! \param Number      Number of values to write
		//! \param Precision   Precision of the values to write (0 by default)
		//! \param Separator   Separator between each values ("\n" by default)
		//! \return a \e boolean representing the success of the operation
		//!
		//! This function writes values in a text formatted file. The file can
		//! be opened in iom::out or iom::app mode. Precision is an integer
		//! representing the number of digit after the dot. And Separator is
		//! a string inserting between each values. If the write operation is
		//! successful, \b true is returned, \b false otherwise.
		//!
		// ---------------------------------------------------------------------
		template<typename T>
		bool CAPEX_CALL WriteInFile(const char *FilePath, iom Mode, T *Values, int Number, int Precision = 0, char *Separator = NULL);
		
	}
	
}

#include <tools.cpp>

#endif