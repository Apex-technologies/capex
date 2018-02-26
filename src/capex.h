// -----------------------------------------------------------------------------
// CAPEX LIBRARY
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 12/11/2016
// -----------------------------------------------------------------------------
//
// This file includes all header files of the Apex Technologies Library 'capex'
//
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
//                      CALLING CONVENTION USED FOR FUNTIONS
// -----------------------------------------------------------------------------

#if defined(_WIN32) || defined(__CYGWIN__) || defined(_WIN32_WCE)
	#define CAPEX_CALL __stdcall
#elif defined(__WIN32__)
	#define CAPEX_CALL __fastcall
#elif __linux__
	#define CAPEX_CALL
#else
	#define CAPEX_CALL
#endif


// -----------------------------------------------------------------------------
//                           DEBUG CONSTANTS AND MACROS
// -----------------------------------------------------------------------------

#ifndef CAPEX_DEBUG
	#define CAPEX_DEBUG true
#endif



// -----------------------------------------------------------------------------
//                           CAPEX LIBRARY INCLUDE FILES
// -----------------------------------------------------------------------------

#include "./constants.h"
#include "./array.h"
#include "./tools.h"
#include "./ini.h"
