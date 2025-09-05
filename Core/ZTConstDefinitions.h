#pragma once

// ZeeTerminal Source Code Version
constexpr const char* ZT_VERSION = "1.0.0";

// Array size for all argument arrays
constexpr int nArgArraySize = 256;

// Text formatting definitions
#define ULINE 4
#define BOLD 1
#define BLINK 5
#define STRIKE 9

// Text formatting definitions - Reset
#define NOULINE 24
#define NOBOLD 22
#define NOBLINK 25
#define NOSTRIKE 29

#define RESETALL 0

#define RESETALL_STR "\x1b[0m"

// RESETS EVERYTHING (Soft Reset)
#define RESETEVERYTHING_STR "\x1b[!p"

// Windows.h definition to prevent min()/max() conflicts
#define NOMINMAX

// Definition to use math definitions
#define _USE_MATH_DEFINES

// Definition to use the codecvt library - it is deprecated but no safe replacement exists yet
#ifndef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif // !_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING