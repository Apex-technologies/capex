// -----------------------------------------------------------------------------
// CAPEX LIBRARY
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 28/09/2017
// -----------------------------------------------------------------------------
//
// This file contains all constants and macros used in the CAPEX library
//
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _CAPEX_CONSTANTS_H
#define _CAPEX_CONSTANTS_H

// -----------------------------------------------------------------------------
//                              CONSTANTS AND MACROS
// -----------------------------------------------------------------------------

#if defined(_WIN32) || defined(__CYGWIN__) || defined(_WIN32_WCE)
	#define CAPEX_LOGFILE "C:\\temp\\capex.log"
#elif defined(__WIN32__)
	#define CAPEX_LOGFILE "C:\\temp\\capex.log"
#elif __linux__
	#define CAPEX_LOGFILE "/tmp/capex.log"
#else
	#define CAPEX_LOGFILE "./capex.log"
#endif

namespace capex
{

	//! \brief Lower value for the denominator of a quotient
	const double lowerLimit = 1e-30;

	//! \brief Approximative value of pi
	const double pi = 3.141592653589793;

	//! \brief Speed of light in vacuum in m/s
	const double VacuumCelerity = 299792458;

	//! \brief Approximative value of the vacuum permittivity in F/m
	const double VacuumPermittivity = 8.854187817620e-12;

	//! \brief Approximative value of the vacuum permeability in H/m
	const double VacuumPermeability = 1.2566370614e-6;

	//! \brief Approximative value of the Boltzmann constant in J/K
	const double Boltzmann = 1.3806485279e-23;

	//! \brief Approximative value of the electrical elementary charge in C
	const double ElectricCharge = 1.602176620898e-19;

	//! \brief Approximative value of the Planck constant in J.s
	const double Planck = 6.62607004081e-34;

	//! \brief Approximative value of the gravitational constant in m^3/(kg.s²)
	const double Gravitational = 6.6740831e-11;
}

#endif

