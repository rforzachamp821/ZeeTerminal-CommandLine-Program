#pragma once

// Normal colour definitions
#define BLK "0;0;0"
#define RED "255;0;0"
#define GRN "22;198;12"
#define YLW "231;186;0"
#define BLU "0;0;255"
#define MAG "136;23;152"
#define CYN "58;150;221"
#define WHT "242;242;242"

// Bright colour definitions
#define GRAY "118;118;118"
#define LRED "231;72;86"
#define LGRN "0;255;0"
#define LYLW "255;255;0"
#define LBLU "59;120;255"
#define LMAG "180;0;158"
#define LCYN "97;214;214"
#define LWHT "255;255;255"

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

// Text formatting definitions (reset) - as a string (easier for output)
#define NOULINE_STR "\x1b[24m"
#define NOBOLD_STR "\x1b[22m"
#define NOBLINK_STR "\x1b[25m"
#define NOSTRIKE_STR "\x1b[29m"

#define RESETALL_STR "\x1b[0m"

// RESETS EVERYTHING (Soft Reset)
#define RESETEVERYTHING_STR "\x1b[!p"

// Windows.h definition to prevent min()/max() conflicts
#define NOMINMAX

// Definition to use math definitions
#define _USE_MATH_DEFINES