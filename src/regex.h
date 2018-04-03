// -----------------------------------------------------------------------------
// ARRAY CLASS FOR MANIPULATING NUMBERS
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 22/03/2016
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _CAPEX_ARRAY_H
#define _CAPEX_ARRAY_H

#ifndef CAPEX_CALL
	#define CAPEX_CALL
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>


// look for any character
#define CAPEX_REGEX_DOT				.
// look for 0 or more repetitions
#define CAPEX_REGEX_STAR			*
// look for 1 or more repetitions
#define CAPEX_REGEX_PLUS			+
// look for 0 or 1 repetition
#define CAPEX_REGEX_QUESTION		?
// matches the start of the string
#define CAPEX_REGEX_POWER			^
// matches the end of the string
#define CAPEX_REGEX_DOLLAR			$

namespace capex
{
	
	namespace regex
	{
		
		int find(std::string src, std::string pattern, std::string match, int start = 0);
		
	}
	
	
}

#include "regex.cpp"

#endif