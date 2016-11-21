// -----------------------------------------------------------------------------
// APEX TECHNOLOGIES LIBRARY
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 12/11/2016
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// This file includes all classes, functions, variables and constants
// of the Apex Technologies Library 'capex'

#if __WIN32__
	#define CALL __fastcall
#elif __linux__
	#define CALL
#else
	#define CALL
#endif

#include "./array.h"
#include "./apexusb.h"
