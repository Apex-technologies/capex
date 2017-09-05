// -----------------------------------------------------------------------------
// MXM LIBRARY
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 12/11/2016
// -----------------------------------------------------------------------------
//
// This file includes all classes, functions, variables and constants
// of the Apex Technologies Library 'capex'
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
	#define CAPEX_DEBUG false
#endif

#define CAPEX_DBG_COLOR_RED "\033[0;41m"
#define CAPEX_DBG_COLOR_GRN "\033[0;42m"
#define CAPEX_DBG_COLOR_STD "\033[0m"
#define CAPEX_DBG_EMPHASE "\033[4m"

// -----------------------------------------------------------------------------
//                           CAPEX LIBRARY INCLUDE FILES
// -----------------------------------------------------------------------------

#include "./array.h"
#include "./usb.h"
