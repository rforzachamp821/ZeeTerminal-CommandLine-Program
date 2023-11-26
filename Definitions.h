#pragma once

// ZeeTerminal Source Code Version
constexpr const char* ZT_VERSION = "0.4.3";

// Array size for all argument arrays
constexpr int nArgArraySize = 128;

// Normal colour definitions - ANSI-only
const std::string BLK_ANSI = "0;0;0";
const std::string RED_ANSI = "230;0;0";
const std::string GRN_ANSI = "22;198;12";
const std::string YLW_ANSI = "231;186;0";
const std::string BLU_ANSI = "0;0;255";
const std::string MAG_ANSI = "136;23;152";
const std::string CYN_ANSI = "58;150;221";
const std::string WHT_ANSI = "215;215;215"; // Used to be 242;242;242
// Bright colour definitions - ANSI-only
const std::string GRAY_ANSI = "118;118;118";
const std::string LRED_ANSI = "251;96;127"; // 231;72;86 is normal
const std::string LGRN_ANSI = "0;255;0";
const std::string LYLW_ANSI = "255;255;0";
const std::string LBLU_ANSI = "59;120;255";
const std::string LMAG_ANSI = "180;0;158";
const std::string LCYN_ANSI = "97;214;214";
const std::string LWHT_ANSI = "255;255;255";


// Normal colour definitions - WIN32
const std::string BLK_WIN32 = "0";
const std::string BLU_WIN32 = "1";
const std::string GRN_WIN32 = "2";
const std::string CYN_WIN32 = "3";
const std::string RED_WIN32 = "4";
const std::string MAG_WIN32 = "5";
const std::string YLW_WIN32 = "6";
const std::string WHT_WIN32 = "7";
// Bright colour definitions - WIN32
const std::string GRAY_WIN32 = "8";
const std::string LBLU_WIN32 = "9";
const std::string LGRN_WIN32 = "10";
const std::string LCYN_WIN32 = "11";
const std::string LRED_WIN32 = "12";
const std::string LMAG_WIN32 = "13";
const std::string LYLW_WIN32 = "14";
const std::string LWHT_WIN32 = "15";


// Normal colour definitions
std::string BLK = "0;0;0";
std::string RED = "230;0;0";
std::string GRN = "22;198;12";
std::string YLW = "231;186;0";
std::string BLU = "0;0;255";
std::string MAG = "136;23;152";
std::string CYN = "58;150;221";
std::string WHT = "215;215;215"; // Used to be 242;242;242

// Bright colour definitions
std::string GRAY = "118;118;118";
std::string LRED = "251;96;127"; // 231;72;86 is normal
std::string LGRN = "0;255;0";
std::string LYLW = "255;255;0";
std::string LBLU = "59;120;255";
std::string LMAG = "180;0;158";
std::string LCYN = "97;214;214";
std::string LWHT = "255;255;255";

// Text formatting definitions
#define ULINE 4
#define BOLD 1
#define BLINK 5
#define STRIKE 9

// Test formatting definitions as a string (easier for output)
std::string ULINE_STR = "\x1b[4m";
std::string BOLD_STR = "\x1b[1m";
std::string BLINK_STR = "\x1b[5m";
std::string STRIKE_STR = "\x1b[9m";


// Text formatting definitions - Reset
#define NOULINE 24
#define NOBOLD 22
#define NOBLINK 25
#define NOSTRIKE 29

#define RESETALL 0

// Text formatting strings (reset) - as a string (easier for output)
std::string NOULINE_STR = "\x1b[24m";
std::string NOBOLD_STR = "\x1b[22m";
std::string NOBLINK_STR = "\x1b[25m";
std::string NOSTRIKE_STR = "\x1b[29m";

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

// Define wordWrap function with default arguments
std::string wordWrap(std::string, long long int = -1, long long int = 0);