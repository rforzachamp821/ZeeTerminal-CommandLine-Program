#pragma once

// Normal colour definitions
std::string BLK = "0;0;0";
std::string RED = "255;0;0";
std::string GRN = "22;198;12";
std::string YLW = "231;186;0";
std::string BLU = "0;0;255";
std::string MAG = "136;23;152";
std::string CYN = "58;150;221";
std::string WHT = "242;242;242";

// Bright colour definitions
std::string GRAY = "118;118;118";
std::string LRED = "231;72;86";
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
#define ULINE_STR "\x1b[4m"
#define BOLD_STR "\x1b[1m"
#define BLINK_STR "\x1b[5m"
#define STRIKE_STR "\x1b[9m"


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