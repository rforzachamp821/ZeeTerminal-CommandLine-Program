//
// CommandFileAssets.cpp - Contains assets for the commands in CommandsFile.cpp.
//

extern ConfigFileSystem ConfigObjMain;


// A switch-case function for the ColourBackground function.
void ColourBackgroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable) {
	// Switch case for selecting colour
	switch (*nChoice) {
	case 1:
		colour(*sSettingVariable, BLK);
		*sSettingVariableBack = BLK;
		break;
	case 2:
		colour(*sSettingVariable, BLU);
		*sSettingVariableBack = BLU;
		break;
	case 3:
		colour(*sSettingVariable, GRN);
		*sSettingVariableBack = GRN;
		break;
	case 4:
		colour(*sSettingVariable, CYN);
		*sSettingVariableBack = CYN;
		break;
	case 5:
		colour(*sSettingVariable, RED);
		*sSettingVariableBack = RED;
		break;
	case 6:
		colour(*sSettingVariable, MAG);
		*sSettingVariableBack = MAG;
		break;
	case 7:
		colour(*sSettingVariable, YLW);
		*sSettingVariableBack = YLW;
		break;
	case 8:
		colour(*sSettingVariable, WHT);
		*sSettingVariableBack = WHT;
		break;
	case 9:
		colour(*sSettingVariable, GRAY);
		*sSettingVariableBack = GRAY;
		break;
	case 10:
		colour(*sSettingVariable, LBLU);
		*sSettingVariableBack = LBLU;
		break;
	case 11:
		colour(*sSettingVariable, LGRN);
		*sSettingVariableBack = LGRN;
		break;
	case 12:
		colour(*sSettingVariable, LCYN);
		*sSettingVariableBack = LCYN;
		break;
	case 13:
		colour(*sSettingVariable, LRED);
		*sSettingVariableBack = LRED;
		break;
	case 14:
		colour(*sSettingVariable, LMAG);
		*sSettingVariableBack = LMAG;
		break;
	case 15:
		colour(*sSettingVariable, LYLW);
		*sSettingVariableBack = LYLW;
		break;
	case 16:
		colour(*sSettingVariable, LWHT);
		*sSettingVariableBack = LWHT;
		break;
	default:
		VerbosityDisplay("In ColourBackgroundSwitch() - ERROR: Default switch case statement activated, so nChoice seems to be incorrect.\n");
		UserErrorDisplay("An error occured, and the colour has not been changed.\nPlease try again later.\n");
		break;
	}

	ConfigObjMain.WriteConfigFile();

	return;
}

// A switch-case function for the ColourForeground function.
void ColourForegroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable) 
{
	// Switch case for selecting colour
	switch (*nChoice) {
	case 1:
		colour(BLK, *sSettingVariableBack);
		*sSettingVariable = BLK;
		break;
	case 2:
		colour(BLU, *sSettingVariableBack);
		*sSettingVariable = BLU;
		break;
	case 3:
		colour(GRN, *sSettingVariableBack);
		*sSettingVariable = GRN;
		break;
	case 4:
		colour(CYN, *sSettingVariableBack);
		*sSettingVariable = CYN;
		break;
	case 5:
		colour(RED, *sSettingVariableBack);
		*sSettingVariable = RED;
		break;
	case 6:
		colour(MAG, *sSettingVariableBack);
		*sSettingVariable = MAG;
		break;
	case 7:
		colour(YLW, *sSettingVariableBack);
		*sSettingVariable = YLW;
		break;
	case 8:
		colour(WHT, *sSettingVariableBack);
		*sSettingVariable = WHT;
		break;
	case 9:
		colour(GRAY, *sSettingVariableBack);
		*sSettingVariable = GRAY;
		break;
	case 10:
		colour(LBLU, *sSettingVariableBack);
		*sSettingVariable = LBLU;
		break;
	case 11:
		colour(LGRN, *sSettingVariableBack);
		*sSettingVariable = LGRN;
		break;
	case 12:
		colour(LCYN, *sSettingVariableBack);
		*sSettingVariable = LCYN;
		break;
	case 13:
		colour(LRED, *sSettingVariableBack);
		*sSettingVariable = LRED;
		break;
	case 14:
		colour(LMAG, *sSettingVariableBack);
		*sSettingVariable = LMAG;
		break;
	case 15:
		colour(LYLW, *sSettingVariableBack);
		*sSettingVariable = LYLW;
		break;
	case 16:
		colour(LWHT, *sSettingVariableBack);
		*sSettingVariable = LWHT;
		break;
	default:
		VerbosityDisplay("In ColourForegroundSwitch() - ERROR: Default switch case statement activated, so nChoice seems to be incorrect.\n");
		UserErrorDisplay("An error occured, and the colour has not been changed.\nPlease try again later.\n");
		break;
	}

	ConfigObjMain.WriteConfigFile();

	return;
}

// A switch-case function that returns a colour associated with its number.
std::string NumberToColour(int nNumberChoice) {

	// Switch case based on number choice
	switch (nNumberChoice) {
	case 1:
		return BLK;
		break;
	case 2:
		return BLU;
		break;
	case 3:
		return GRN;
		break;
	case 4:
		return CYN;
		break;
	case 5:
		return RED;
		break;
	case 6:
		return MAG;
		break;
	case 7:
		return YLW;
		break;
	case 8:
		return WHT;
		break;
	case 9:
		return GRAY;
		break;
	case 10:
		return LBLU;
		break;
	case 11:
		return LGRN;
		break;
	case 12:
		return LCYN;
		break;
	case 13:
		return LRED;
		break;
	case 14:
		return LMAG;
		break;
	case 15:
		return LYLW;
		break;
	case 16:
		return LWHT;
		break;
	default:
		VerbosityDisplay("ERROR - An error occured when returning the colour string associated with its number. This is probably a bug.\n");
		break;
	}

	return "";
}

// A switch-case function that returns a number associated with one of the default colour strings.
// 0 is returned on error.
int ColourToNumber(std::string sColourChoice) 
{
	if (sColourChoice == BLK) {
		return 1;
	}
	else if (sColourChoice == BLU) {
		return 2;
	}
	else if (sColourChoice == GRN) {
		return 3;
	}
	else if (sColourChoice == CYN) {
		return 4;
	}
	else if (sColourChoice == RED) {
		return 5;
	}
	else if (sColourChoice == MAG) {
		return 6;
	}
	else if (sColourChoice == YLW) {
		return 7;
	}
	else if (sColourChoice == WHT) {
		return 8;
	}
	else if (sColourChoice == GRAY) {
		return 9;
	}
	else if (sColourChoice == LBLU) {
		return 10;
	}
	else if (sColourChoice == LGRN) {
		return 11;
	}
	else if (sColourChoice == LCYN) {
		return 12;
	}
	else if (sColourChoice == LRED) {
		return 13;
	}
	else if (sColourChoice == LMAG) {
		return 14;
	}
	else if (sColourChoice == LYLW) {
		return 15;
	}
	else if (sColourChoice == LWHT) {
		return 16;
	}
	else {
		VerbosityDisplay("ERROR - An error occured when returning the number associated with its colour string. This is probably a bug.\n");
		return 0;
	}

	return 0;
}

// ColourToDisplayColour - Converts an RGB colour string into a string appropriate for the average user.
std::string ColourToDisplayColour(std::string sRGBColourString) {
	if (sRGBColourString == BLK) {
		return "Black";
	}
	else if (sRGBColourString == BLU) {
		return "Blue";
	}
	else if (sRGBColourString == GRN) {
		return "Green";
	}
	else if (sRGBColourString == CYN) {
		return "Aqua";
	}
	else if (sRGBColourString == RED) {
		return "Red";
	}
	else if (sRGBColourString == MAG) {
		return "Purple";
	}
	else if (sRGBColourString == YLW) {
		return "Yellow";
	}
	else if (sRGBColourString == WHT) {
		return "White";
	}
	else if (sRGBColourString == GRAY) {
		return "Gray";
	}
	else if (sRGBColourString == LBLU) {
		return "Light Blue";
	}
	else if (sRGBColourString == LGRN) {
		return "Light Green";
	}
	else if (sRGBColourString == LCYN) {
		return "Light Aqua";
	}
	else if (sRGBColourString == LRED) {
		return "Light Red";
	}
	else if (sRGBColourString == LMAG) {
		return "Light Purple";
	}
	else if (sRGBColourString == LYLW) {
		return "Light Yellow";
	}
	else if (sRGBColourString == LWHT) {
		return "Bright White";
	}
	else {
		return "";
	}

	return "";
}

// A switch-case function for the MessageBox command (icon).
int MessageBoxIconSwitch(std::string sIconName) {
	// Make argument lowercase
	for (int i = 0; i < sIconName.length(); i++) {
		sIconName[i] = std::tolower(sIconName[i]);
	}

	if (sIconName == "error") {
		return 16;
	}
	else if (sIconName == "question") {
		return 32;
	}
	else if (sIconName == "warning") {
		return 48;
	}
	else if (sIconName == "info") {
		return 64;
	}
	else {
		VerbosityDisplay("In MessageBoxIconSwitch() - ERROR: Incorrect icon argument detected.\n");
		UserErrorDisplay("ERROR - The specified icon argument seems to be incorrect.\nPlease add one from the list of icon options.\nSee 'messagebox -h' for more info.\n");

		return 1;
	}

	return 1;
}

// A switch-case function for the MessageBox command (buttons)
int MessageBoxButtonSwitch(std::string sButtonName) {
	// Make argument lowercase
	for (int i = 0; i < sButtonName.length(); i++) {
		sButtonName[i] = std::tolower(sButtonName[i]);
	}

	if (sButtonName == "ok") {
		return 0;
	}
	else if (sButtonName == "okcancel") {
		return 1;
	}
	else if (sButtonName == "abortretryignore") {
		return 2;
	}
	else if (sButtonName == "yesnocancel") {
		return 3;
	}
	else if (sButtonName == "yesno") {
		return 4;
	}
	else if (sButtonName == "retrycancel") {
		return 5;
	}
	else if (sButtonName == "canceltrycontinue") {
		return 6;
	}
	else {
		VerbosityDisplay("In MessageBoxButtonSwitch() - ERROR: Incorrect button argument detected.\n");
		UserErrorDisplay("ERROR - Your button argument seems to be incorrect.\nPlease make sure it is from the list of button options.\nSee 'messagebox -h' for more info. Using default option...\n");

		return 0;
	}

	return 0;
}

// A switch-case function that returns the win32 equivalent of ANSI colours
std::string Win32ToAnsiColours(std::string sWin32Colour) 
{
	if (sWin32Colour == BLK_WIN32) {
		return BLK_ANSI;
	}
	else if (sWin32Colour == RED_WIN32) {
		return RED_ANSI;
	}
	else if (sWin32Colour == GRN_WIN32) {
		return GRN_ANSI;
	}
	else if (sWin32Colour == YLW_WIN32) {
		return YLW_ANSI;
	}
	else if (sWin32Colour == BLU_WIN32) {
		return BLU_ANSI;
	}
	else if (sWin32Colour == MAG_WIN32) {
		return MAG_ANSI;
	}
	else if (sWin32Colour == CYN_WIN32) {
		return CYN_ANSI;
	}
	else if (sWin32Colour == WHT_WIN32) {
		return WHT_ANSI;
	}
	else if (sWin32Colour == GRAY_WIN32) {
		return GRAY_ANSI;
	}
	else if (sWin32Colour == LRED_WIN32) {
		return LRED_ANSI;
	}
	else if (sWin32Colour == LGRN_WIN32) {
		return LGRN_ANSI;
	}
	else if (sWin32Colour == LYLW_WIN32) {
		return LYLW_ANSI;
	}
	else if (sWin32Colour == LBLU_WIN32) {
		return LBLU_ANSI;
	}
	else if (sWin32Colour == LMAG_WIN32) {
		return LMAG_ANSI;
	}
	else if (sWin32Colour == LCYN_WIN32) {
		return LCYN_ANSI;
	}
	else if (sWin32Colour == LWHT_WIN32) {
		return LWHT_ANSI;
	}
	else {
		return "";
	}
}

// A switch-case function that returns the ANSI RGB equivalent of Win32 colours
std::string AnsiToWin32Colours(std::string sAnsiColour)
{
	if (sAnsiColour == BLK_ANSI) {
		return BLK_WIN32;
	}
	else if (sAnsiColour == RED_ANSI) {
		return RED_WIN32;
	}
	else if (sAnsiColour == GRN_ANSI) {
		return GRN_WIN32;
	}
	else if (sAnsiColour == YLW_ANSI) {
		return YLW_WIN32;
	}
	else if (sAnsiColour == BLU_ANSI) {
		return BLU_WIN32;
	}
	else if (sAnsiColour == MAG_ANSI) {
		return MAG_WIN32;
	}
	else if (sAnsiColour == CYN_ANSI) {
		return CYN_WIN32;
	}
	else if (sAnsiColour == WHT_ANSI) {
		return WHT_WIN32;
	}
	else if (sAnsiColour == GRAY_ANSI) {
		return GRAY_WIN32;
	}
	else if (sAnsiColour == LRED_ANSI) {
		return LRED_WIN32;
	}
	else if (sAnsiColour == LGRN_ANSI) {
		return LGRN_WIN32;
	}
	else if (sAnsiColour == LYLW_ANSI) {
		return LYLW_WIN32;
	}
	else if (sAnsiColour == LBLU_ANSI) {
		return LBLU_WIN32;
	}
	else if (sAnsiColour == LMAG_ANSI) {
		return LMAG_WIN32;
	}
	else if (sAnsiColour == LCYN_ANSI) {
		return LCYN_WIN32;
	}
	else if (sAnsiColour == LWHT_ANSI) {
		return LWHT_WIN32;
	}
	else {
		return "";
	}
}

// Checks all ConfigObjMain.sColour colours to see if they don't exceed the WIN32 colour limit (8192)
// Returns TRUE for all correct, FALSE for 1 or more variables incorrect.
bool ValidateColourStringsWin32() {
	bool bSuccess = true;

	// Check validity of WIN32 values - They may not exceed 8192 (base 10).
	if (not (isNumberi(ConfigObjMain.sColourGlobal) && std::stoi(ConfigObjMain.sColourGlobal) < 8192)) {
		ConfigObjMain.sColourGlobal = LWHT_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourGlobalBack) && std::stoi(ConfigObjMain.sColourGlobalBack) < 8192)) {
		ConfigObjMain.sColourGlobalBack = BLK_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourHighlight) && std::stoi(ConfigObjMain.sColourHighlight) < 8192)) {
		ConfigObjMain.sColourHighlight = LWHT_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourHighlightBack) && std::stoi(ConfigObjMain.sColourHighlightBack) < 8192)) {
		ConfigObjMain.sColourHighlightBack = BLU_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourTitle) && std::stoi(ConfigObjMain.sColourTitle) < 8192)) {
		ConfigObjMain.sColourTitle = BLK_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourTitleBack) && std::stoi(ConfigObjMain.sColourTitleBack) < 8192)) {
		ConfigObjMain.sColourTitleBack = LCYN_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourSubheading) && std::stoi(ConfigObjMain.sColourSubheading) < 8192)) {
		ConfigObjMain.sColourSubheading = LWHT_WIN32;
		bSuccess = false;
	}
	if (not (isNumberi(ConfigObjMain.sColourSubheadingBack) && std::stoi(ConfigObjMain.sColourSubheadingBack) < 8192)) {
		ConfigObjMain.sColourSubheadingBack = MAG_WIN32;
		bSuccess = false;
	}

	return bSuccess;
}

// VerifyANSIColourString - Verifies an ANSI colour string with the following rules:
//                        - 1. It must only contain numbers and semicolons
//                        - 2. The numbers in the colour string must be less than 256.
// Parameters: sColourString - The colour string to check.
// Return Values: TRUE or 1 for a valid colour string, FALSE or 0 for a bad colour string.
//
bool VerifyANSIColourString(std::string sColourString)
{
	std::size_t nLastSemicolonPlus1 = 0;

	// Check if sColourString contains nothing - if so, it's not valid
	if (sColourString.empty()) return false;

	for (uint8_t i = 0; i < 3; i++)
	{
		// Parse up to first non-number
		std::string sBuffer = "";
		for (size_t j = nLastSemicolonPlus1; j < sColourString.length(); j++, nLastSemicolonPlus1 = j + 1) {
			if (sColourString[j] == ';') {
				break;
			}
			else sBuffer.push_back(sColourString[j]);
		}

		// Check if buffer is empty - if so, it means that the colour string doesn't have enough colour values to make a colour
		if (sBuffer == "") {
			return false;
		}
		// Check if buffer is a number
		if (!isNumberi(sBuffer)) {
			return false;
		}
		// Check if number is below 256 (convert as well)
		if (std::stoi(sBuffer) > 255) {
			return false;
		}
	}

	// Check if whole string checked - if not, it means that there's unwanted characters that are out of the scope of this algorithm, 
	// and therefore the colour string is invalid
	if (nLastSemicolonPlus1 - 1 < sColourString.length()) return false;

	return true;
}

// Checks all ConfigObjMain.sColour colours to see if they are valid, in the 255;255;255 format.
// Returns TRUE for all correct, FALSE for 1 or more variables incorrect.
bool ValidateColourStringsANSI() {
	bool bSuccess = true;

	// Check validity of ANSI string values
	if (!VerifyANSIColourString(ConfigObjMain.sColourGlobal)) {
		ConfigObjMain.sColourGlobal = LWHT_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourGlobalBack)) {
		ConfigObjMain.sColourGlobalBack = BLK_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourHighlight)) {
		ConfigObjMain.sColourHighlight = LWHT_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourHighlightBack)) {
		ConfigObjMain.sColourHighlightBack = BLU_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourTitle)) {
		ConfigObjMain.sColourTitle = BLK_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourTitleBack)) {
		ConfigObjMain.sColourTitleBack = LCYN_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourSubheading)) {
		ConfigObjMain.sColourSubheading = LWHT_ANSI;
		bSuccess = false;
	}
	if (!VerifyANSIColourString(ConfigObjMain.sColourSubheadingBack)) {
		ConfigObjMain.sColourSubheadingBack = MAG_ANSI;
		bSuccess = false;
	}

	return bSuccess;
}

// Function that hides console cursor and returns value of previous setting to set later.
// Commonly used for progress bars to prevent cursor flickering
//
bool DisableCursorVisibility() {
	bool bPreviousSetting = ConfigObjMain.bShowCursor;

	// Set to FALSE and write cursor attributes
	ConfigObjMain.bShowCursor = false;
	SetCursorAttributes();

	// Return previous setting in case user wants to put back to normal
	return bPreviousSetting;
}

// Mission Impossible Theme Song in Beeps
//
void MissionImpossibleTheme() {
	MultimediaEngine meSong;

	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(932, 150);
	sleep(150);
	meSong.BeepSound(1047, 150);
	sleep(150);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(699, 150);
	sleep(150);
	meSong.BeepSound(740, 150);
	sleep(150);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(932, 150);
	sleep(150);
	meSong.BeepSound(1047, 150);
	sleep(150);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(699, 150);
	sleep(150);
	meSong.BeepSound(740, 150);
	sleep(150);
	meSong.BeepSound(932, 150);
	meSong.BeepSound(784, 150);
	meSong.BeepSound(587, 1200);
	sleep(75);
	meSong.BeepSound(932, 150);
	meSong.BeepSound(784, 150);
	meSong.BeepSound(554, 1200);
	sleep(75);
	meSong.BeepSound(932, 150);
	meSong.BeepSound(784, 150);
	meSong.BeepSound(523, 1200);
	sleep(150);
	meSong.BeepSound(466, 150);
	meSong.BeepSound(523, 150);

	return;
}

// Happy Birthday Song in Beep Sounds
//
void HappyBirthdaySong() {
	MultimediaEngine meSong;
	
	meSong.BeepSound(1059.274, 300);
	meSong.BeepSound(1059.274, 200);
	meSong.BeepSound(1188.995, 500);
	meSong.BeepSound(1059.274, 500);
	meSong.BeepSound(1413.961, 500);
	meSong.BeepSound(1334.601, 950);

	meSong.BeepSound(1059.274, 300);
	meSong.BeepSound(1059.274, 200);
	meSong.BeepSound(1188.995, 500);
	meSong.BeepSound(1059.274, 500);
	meSong.BeepSound(1587.117, 500);
	meSong.BeepSound(1413.961, 950);

	meSong.BeepSound(1059.274, 300);
	meSong.BeepSound(1059.274, 200);
	meSong.BeepSound(2118.547, 500);
	meSong.BeepSound(1781.479, 500);
	meSong.BeepSound(1413.961, 500);
	meSong.BeepSound(1334.601, 500);
	meSong.BeepSound(1188.995, 500);
	meSong.BeepSound(1887.411, 300);
	meSong.BeepSound(1887.411, 200);
	meSong.BeepSound(1781.479, 500);
	meSong.BeepSound(1413.961, 500);
	meSong.BeepSound(1587.117, 500);
	meSong.BeepSound(1413.961, 900);

	return;
}

// Super Mario Theme Song in Beep Sounds
//
void SuperMarioTheme() {
	MultimediaEngine meSong;

	meSong.BeepSound(660, 150);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(510, 100);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(770, 550);
	meSong.BeepSound(380, 575);
	meSong.BeepSound(510, 450);
	meSong.BeepSound(380, 400);
	meSong.BeepSound(320, 500);
	meSong.BeepSound(440, 300);
	meSong.BeepSound(480, 330);
	meSong.BeepSound(450, 150);
	meSong.BeepSound(430, 300);
	meSong.BeepSound(380, 200);
	meSong.BeepSound(660, 200);
	meSong.BeepSound(760, 150);
	meSong.BeepSound(860, 300);
	meSong.BeepSound(700, 150);
	meSong.BeepSound(760, 350);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(520, 150);
	meSong.BeepSound(580, 150);
	meSong.BeepSound(480, 500);
	meSong.BeepSound(510, 450);
	meSong.BeepSound(380, 400);
	meSong.BeepSound(320, 500);
	meSong.BeepSound(440, 300);
	meSong.BeepSound(480, 330);
	meSong.BeepSound(450, 150);
	meSong.BeepSound(430, 300);
	meSong.BeepSound(380, 200);
	meSong.BeepSound(660, 200);
	meSong.BeepSound(760, 150);
	meSong.BeepSound(860, 300);
	meSong.BeepSound(700, 150);
	meSong.BeepSound(760, 350);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(520, 150);
	meSong.BeepSound(580, 150);
	meSong.BeepSound(480, 500);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(760, 100);
	meSong.BeepSound(720, 150);
	meSong.BeepSound(680, 150);
	meSong.BeepSound(620, 300);
	meSong.BeepSound(650, 300);
	meSong.BeepSound(380, 150);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 100);
	meSong.BeepSound(570, 220);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(760, 100);
	meSong.BeepSound(720, 150);
	meSong.BeepSound(680, 150);
	meSong.BeepSound(620, 300);
	meSong.BeepSound(650, 300);
	meSong.BeepSound(1020, 300);
	meSong.BeepSound(1020, 150);
	meSong.BeepSound(1020, 300);
	meSong.BeepSound(380, 300);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(760, 100);
	meSong.BeepSound(720, 150);
	meSong.BeepSound(680, 150);
	meSong.BeepSound(620, 300);
	meSong.BeepSound(650, 300);
	meSong.BeepSound(380, 150);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 100);
	meSong.BeepSound(570, 420);
	meSong.BeepSound(585, 450);
	meSong.BeepSound(550, 420);
	meSong.BeepSound(500, 360);
	meSong.BeepSound(380, 300);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(760, 100);
	meSong.BeepSound(720, 150);
	meSong.BeepSound(680, 150);
	meSong.BeepSound(620, 300);
	meSong.BeepSound(650, 300);
	meSong.BeepSound(380, 150);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 100);
	meSong.BeepSound(570, 220);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(760, 100);
	meSong.BeepSound(720, 150);
	meSong.BeepSound(680, 150);
	meSong.BeepSound(620, 300);
	meSong.BeepSound(650, 300);
	meSong.BeepSound(1020, 300);
	meSong.BeepSound(1020, 150);
	meSong.BeepSound(1020, 300);
	meSong.BeepSound(380, 300);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(760, 100);
	meSong.BeepSound(720, 150);
	meSong.BeepSound(680, 150);
	meSong.BeepSound(620, 300);
	meSong.BeepSound(650, 300);
	meSong.BeepSound(380, 150);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(500, 100);
	meSong.BeepSound(570, 420);
	meSong.BeepSound(585, 450);
	meSong.BeepSound(550, 420);
	meSong.BeepSound(500, 360);
	meSong.BeepSound(380, 300);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 350);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(580, 350);
	meSong.BeepSound(660, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(380, 600);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 350);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(580, 150);
	meSong.BeepSound(660, 550);
	meSong.BeepSound(870, 325);
	meSong.BeepSound(760, 600);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(500, 350);
	meSong.BeepSound(500, 150);
	meSong.BeepSound(580, 350);
	meSong.BeepSound(660, 150);
	meSong.BeepSound(500, 300);
	meSong.BeepSound(430, 150);
	meSong.BeepSound(380, 600);
	meSong.BeepSound(660, 150);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(510, 100);
	meSong.BeepSound(660, 300);
	meSong.BeepSound(770, 550);
	meSong.BeepSound(380, 575);

	return;
}

// DunDunDun song in Beep Sounds
//
void DunDunDunSound() {
	MultimediaEngine meSong;

	meSong.BeepSound(1568, 250);
	meSong.BeepSound(1568, 250);
	meSong.BeepSound(1568, 250);
	meSong.BeepSound(1245, 1250);
	meSong.BeepSound(1397, 250);
	meSong.BeepSound(1397, 250);
	meSong.BeepSound(1397, 250);
	meSong.BeepSound(1175, 1250);

	return;
}

// Star Wars Imperial March Theme in Beep Sounds
//
void StarWarsImperialMarch() {
	MultimediaEngine meSong;

	meSong.BeepSound(440, 500);
	meSong.BeepSound(440, 500);
	meSong.BeepSound(440, 500);
	meSong.BeepSound(349, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(440, 500);
	meSong.BeepSound(349, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(440, 1000);
	meSong.BeepSound(659, 500);
	meSong.BeepSound(659, 500);
	meSong.BeepSound(659, 500);
	meSong.BeepSound(698, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(415, 500);
	meSong.BeepSound(349, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(440, 1000);

	return;
}

// Pac-Man Theme Song in Beep Sounds
//
void TetrisTheme() {
	MultimediaEngine meSong;

	meSong.BeepSound(493.9, 200);
	sleep(150);
	meSong.BeepSound(370, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(440, 200);
	sleep(150);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(370, 200);
	meSong.BeepSound(329.6, 200);
	sleep(150);
	meSong.BeepSound(329.6, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(493.9, 200);
	sleep(150);
	meSong.BeepSound(440, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(370, 200);
	sleep(150);
	meSong.BeepSound(370, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(440, 200);
	sleep(150);
	meSong.BeepSound(493.9, 200);
	sleep(150);
	meSong.BeepSound(392, 200);
	sleep(150);
	meSong.BeepSound(329.6, 200);
	sleep(150);
	meSong.BeepSound(329.6, 300);
	sleep(500);
	meSong.BeepSound(440, 200);
	meSong.BeepSound(440, 200);
	meSong.BeepSound(523.2, 200);
	meSong.BeepSound(659.2, 200);
	sleep(150);
	meSong.BeepSound(587.3, 200);
	meSong.BeepSound(523.2, 200);
	meSong.BeepSound(493.9, 200);
	sleep(150);
	meSong.BeepSound(493.9, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(493.9, 200);
	sleep(150);
	meSong.BeepSound(440, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(370, 200);
	sleep(150);
	meSong.BeepSound(370, 200);
	meSong.BeepSound(392, 200);
	meSong.BeepSound(440, 200);
	sleep(150);
	meSong.BeepSound(493.9, 200);
	sleep(150);
	meSong.BeepSound(392, 200);
	sleep(150);
	meSong.BeepSound(329.6, 200);
	sleep(150);
	meSong.BeepSound(329.6, 800);

	return;
}

// Dramatic Song in Beep Sounds
//
void DramaticSong() {
	MultimediaEngine meSong;

	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1175, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(988, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1175, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(1109, 200);
	meSong.BeepSound(740, 200);
	meSong.BeepSound(988, 200);
	meSong.BeepSound(740, 200);

	return;
}

// RickRoll Song in Beep Sounds
//
void RickRollSong() {
	MultimediaEngine meSong;

	meSong.BeepSound(523.25, 300);
	meSong.BeepSound(587.33, 300);
	meSong.BeepSound(659.25, 300);
	meSong.BeepSound(698.46, 300);
	meSong.BeepSound(587.33, 900);
	meSong.BeepSound(783.99, 300);
	meSong.BeepSound(880.00, 300);
	meSong.BeepSound(783.99, 1200);
	meSong.BeepSound(523.25, 150);
	meSong.BeepSound(587.33, 150);
	meSong.BeepSound(698.46, 150);
	meSong.BeepSound(587.33, 150);
	meSong.BeepSound(880.00, 450);
	meSong.BeepSound(880.00, 450);
	meSong.BeepSound(783.99, 1000);
	meSong.BeepSound(523.25, 150);
	meSong.BeepSound(587.33, 150);
	meSong.BeepSound(698.46, 150);
	meSong.BeepSound(587.33, 150);
	meSong.BeepSound(783.99, 450);
	meSong.BeepSound(783.99, 450);
	meSong.BeepSound(698.46, 450);
	meSong.BeepSound(659.25, 150);
	meSong.BeepSound(587.33, 300);
	meSong.BeepSound(523.25, 150);
	meSong.BeepSound(587.33, 150);
	meSong.BeepSound(698.46, 150);
	meSong.BeepSound(587.33, 150);
	meSong.BeepSound(698.46, 600);
	meSong.BeepSound(783.99, 300);
	meSong.BeepSound(659.25, 300);
	meSong.BeepSound(587.33, 125);
	meSong.BeepSound(523.25, 600);
	meSong.BeepSound(523.25, 300);
	meSong.BeepSound(783.99, 600);
	meSong.BeepSound(698.46, 1000);

	return;
}

// Get Einstein quote based on value (1 to 50)
//
std::string GetEinsteinQuote(int nQuoteValue) 
{
	switch (nQuoteValue) {
	case 1:
		return "Two things are infinite: the universe and human stupidity; and I'm not sure about the universe.";
		break;
	case 2:
		return "There are only two ways to live your life. One is as though nothing is a miracle. The other is as though everything is a miracle.";
		break;
	case 3:
		return "I am enough of an artist to draw freely upon my imagination. Imagination is more important than knowledge. Knowledge is limited. Imagination encircles the world.";
		break;
	case 4:
		return "If you can't explain it to a six year old, you don't understand it yourself.";
		break;
	case 5:
		return "If you want your children to be intelligent, read them fairy tales. If you want them to be more intelligent, read them more fairy tales.";
		break;
	case 6:
		return "Logic will get you from A to Z; imagination will get you everywhere.";
		break;
	case 7:
		return "Life is like riding a bicycle. To keep your balance, you must keep moving.";
		break;
	case 8:
		return "Anyone who has never made a mistake has never tried anything new.";
		break;
	case 9:
		return "I speak to everyone in the same way, whether he is the garbage man or the president of the university.";
		break;
	case 10:
		return "Never memorize something that you can look up.";
		break;
	case 11:
		return "When you are courting a nice girl an hour seems like a second. When you sit on a red-hot cinder a second seems like an hour. That's relativity.";
		break;
	case 12:
		return "A clever person solves a problem. A wise person avoids it.";
		break;
	case 13:
		return "Science without religion is lame, religion without science is blind.";
		break;
	case 14:
		return "Reality is merely an illusion, albeit a very persistent one.";
		break;
	case 15:
		return "Any fool can know. The point is to understand.";
		break;
	case 16:
		return "If we knew what it was we were doing, it would not be called research, would it?";
		break;
	case 17:
		return "I have no special talents. I am only passionately curious.";
		break;
	case 18:
		return "A human being is a part of the whole called by us universe, a part limited in time and space. He experiences himself, his thoughts and feeling as something separated from the rest, a kind of optical delusion of his consciousness. This delusion is a kind of prison for us, restricting us to our personal desires and to affection for a few persons nearest to us. Our task must be to free ourselves from this prison by widening our circle of compassion to embrace all living creatures and the whole of nature in its beauty.";
		break;
	case 19:
		return "Try not to become a man of success. Rather become a man of value.";
		break;
	case 20:
		return "The important thing is not to stop questioning. Curiosity has its own reason for existence. One cannot help but be in awe when he contemplates the mysteries of eternity, of life, of the marvelous structure of reality. It is enough if one tries merely to comprehend a little of this mystery each day.";
		break;
	case 21:
		return "The world as we have created it is a process of our thinking. It cannot be changed without changing our thinking.";
		break;
	case 22:
		return "Once you can accept the universe as matter expanding into nothing that is something, wearing stripes with plaid comes easy.";
		break;
	case 23:
		return "If I were not a physicist, I would probably be a musician. I often think in music. I live my daydreams in music. I see my life in terms of music.";
		break;
	case 24:
		return "The most beautiful experience we can have is the mysterious. It is the fundamental emotion that stands at the cradle of true art and true science.";
		break;
	case 25:
		return "I know not with what weapons World War III will be fought, but World War IV will be fought with sticks and stones.";
		break;
	case 26:
		return "You never fail until you stop trying.";
		break;
	case 27:
		return "Great spirits have always encountered violent opposition from mediocre minds.";
		break;
	case 28:
		return "The measure of intelligence is the ability to change.";
		break;
	case 29:
		return "Gravitation is not responsible for people falling in love.";
		break;
	case 30:
		return "It is not that I'm so smart. But I stay with the questions much longer.";
		break;
	case 31:
		return "Creativity is intelligence having fun.";
		break;
	case 32:
		return "The world is a dangerous place to live, not because of the people who are evil, but because of the people who don't do anything about it.";
		break;
	case 33:
		return "If A is a success in life, then A equals x plus y plus z. Work is x; y is play; and z is keeping your mouth shut.";
		break;
	case 34:
		return "Black holes are where God divided by zero.";
		break;
	case 35:
		return "Everything must be made as simple as possible. But not simpler.";
		break;
	case 36:
		return "The best way to cheer yourself is to cheer somebody else up.";
		break;
	case 37:
		return "When you trip over love, it is easy to get up. But when you fall in love, it is impossible to stand again.";
		break;
	case 38:
		return "Whoever is careless with the truth in small matters cannot be trusted with important matters.";
		break;
	case 39:
		return "What is right is not always popular and what is popular is not always right.";
		break;
	case 40:
		return "Peace cannot be kept by force; it can only be achieved by understanding.";
		break;
	case 41:
		return "In the middle of difficulty lies opportunity.";
		break;
	case 42:
		return "A question that sometimes drives me hazy: am I or are the others crazy?";
		break;
	case 43:
		return "Imagination is everything. It is the preview of life's coming attractions.";
		break;
	case 44:
		return "The pursuit of truth and beauty is a sphere of activity in which we are permitted to remain children all our lives.";
		break;
	case 45:
		return "We dance for laughter, we dance for tears, we dance for madness, we dance for fears, we dance for hopes, we dance for screams, we are the dancers, we create the dreams.";
		break;
	case 46:
		return "The woman who follows the crowd will usually go no further than the crowd. The woman who walks alone is likely to find herself in places no one has ever been before.";
		break;
	case 47:
		return "Time is an illusion.";
		break;
	case 48:
		return "It would be possible to describe everything scientifically, but it would make no sense; it would be without meaning, as if you described a Beethoven symphony as a variation of wave pressure.";
		break;
	case 49:
		return "I must be willing to give up what I am in order to become what I will be.";
		break;
	case 50:
		return "Love is a better master than duty.";
		break;
	default:
		VerbosityDisplay("In GetEinsteinQuote(): ERROR - Failed to get quote due to invalid value (value below 1 or above 50).\n");
		return "Failed to get quote.";
	}

	return "";
}

// Get Edison quote based on value (1 to 50)
//
std::string GetEdisonQuote(int nQuoteValue) {
	switch (nQuoteValue) {
	case 1:
		return "Our greatest weakness lies in giving up. The most certain way to succeed is always to try just one more time.";
		break;
	case 2:
		return "I have not failed. I've just found 10,000 ways that won't work.";
		break;
	case 3:
		return "Having a vision for what you want is not enough... Vision without execution is hallucination.";
		break;
	case 4:
		return "Opportunity is missed by most people because it is dressed in overalls and looks like work.";
		break;
	case 5:
		return "There is a better way for everything. Find it.";
		break;
	case 6:
		return "The successful person makes a habit of doing what the failing person doesn't like to do.";
		break;
	case 7:
		return "Success is 90% perspiration and 10% inspiration.";
		break;
	case 8:
		return "I never view mistakes as failures. They are simply opportunities to find out what doesn't work.";
		break;
	case 9:
		return "Tomorrow is my exam but I don't care because a single sheet of paper can't decide my future.";
		break;
	case 10:
		return "Never go to sleep without a request to your subconscious.";
		break;
	case 11:
		return "Your worth consists in what you are and not in what you have.";
		break;
	case 12:
		return "The greatest invention in the world is the mind of a child.";
		break;
	case 13:
		return "Each time you fail, you have eliminated another wrong option.";
		break;
	case 14:
		return "People are not remembered by how few times they fail, but by how often they succeed. Every wrong step is another step forward.";
		break;
	case 15:
		return "The value of an idea lies in the using of it.";
		break;
	case 16:
		return "Time is really the only capital that any human being has, and the only thing he can't afford to lose.";
		break;
	case 17:
		return "Restlessness is discontent and discontent is the first necessity of progress. Show me a thoroughly satisfied man and I will show you a failure.";
		break;
	case 18:
		return "What you are will show in what you do.";
		break;
	case 19:
		return "Do the thing and the power will come.";
		break;
	case 20:
		return "I find out what the world needs. Then I go ahead and try to invent it.";
		break;
	case 21:
		return "Every failure is a lesson learned about your strategy.";
		break;
	case 22:
		return "Before you reject an idea, find at least five good things about it.";
		break;
	case 23:
		return "Absorb ideas from every source.";
		break;
	case 24:
		return "A good intention, with a bad approach, often leads to a poor result.";
		break;
	case 25:
		return "There seems to be no limit to which some men will go to avoid the labor of thinking. Thinking is hard work.";
		break;
	case 26:
		return "When you have exhausted all possibilities, remember this - you haven't.";
		break;
	case 27:
		return "Many of life's failures are people who did not realize how close they were to success when they gave up.";
		break;
	case 28:
		return "I owe my success to the fact that I never had a clock in my workroom.";
		break;
	case 29:
		return "I have far more respect for the person with a single idea who gets there than for the person with a thousand ideas who does nothing.";
		break;
	case 30:
		return "If we did all the things we are capable of doing, we would literally astound ourselves.";
		break;
	case 31:
		return "Continued innovation is the best way to beat the competition.";
		break;
	case 32:
		return "Good fortune is what happens when opportunity meets with planning.";
		break;
	case 33:
		return "I didn't fail 1000 times. The light bulb was an invention with 1000 steps.";
		break;
	case 34:
		return "You can't realize your dreams unless you have one to begin with.";
		break;
	case 35:
		return "To get a great idea, come up with lots of them.";
		break;
	case 36:
		return "The trouble with most people is that they quit before they start.";
		break;
	case 37:
		return "The doctor of the future will no longer treat the human frame with drugs, but rather will cure and prevent disease with nutrition.";
		break;
	case 38:
		return "A teacher sent the following note home with a six-year-old boy 'He is too stupid to learn.' That boy was Thomas A. Edison.";
		break;
	case 39:
		return "I never perfected an invention that I did not think about in terms of the service it might give others... I find out what the world needs, then I proceed to invent.";
		break;
	case 40:
		return "Fools call wise men fools. A wise man never calls any man a fool.";
		break;
	case 41:
		return "I failed my way to success.";
		break;
	case 42:
		return "Most of my ideas belonged to other people who never bothered to develop them.";
		break;
	case 43:
		return "The strength of the constitution lies in the will of the people to defend it.";
		break;
	case 44:
		return "I'd put my money on the sun and solar energy. What a source of power! I hope we don't have to wait until oil and coal run out before we tackle that.";
		break;
	case 45:
		return "Non-violence leads to the highest ethics, which is the goal of all evolution. Until we stop harming all other living beings, we are still savages.";
		break;
	case 46:
		return "The most necessary task of civilization is to teach people how to think. It should be the primary purpose of our public schools. The mind of a child is naturally active, it develops through exercise. Give a child plenty of exercise, for body and brain. The trouble with our way of educating is that it does not give elasticity to the mind. It casts the brain into a mold. It insists that the child must accept. It does not encourage original thought or reasoning, and it lays more stress on memory than observation.";
		break;
	case 47:
		return "To do much clear thinking a person must arrange for regular periods of solitude when they can concentrate and indulge the imagination without distraction.";
		break;
	case 48:
		return "The world owes nothing to any man, but every man owes something to the world.";
		break;
	case 49:
		return "It's obvious that we don't know one millionth of one percent about anything.";
		break;
	case 50:
		return "To invent, you need a good imagination and a pile of junk.";
		break;
	default:
		VerbosityDisplay("In GetEdisonQuote(): ERROR - Failed to get quote due to invalid value (value below 1 or above 50).\n");
		return "Failed to get quote.";
	}

	return "";
}

// Get Tesla quote based on value (1 to 50)
//
std::string GetTeslaQuote(int nQuoteValue) {
	switch (nQuoteValue) {
	case 1:
		return "I do not think there is any thrill that can go through the human heart like that felt by the inventor as he sees some creation of the brain unfolding to success... Such emotions make a man forget food, sleep, friends, love, everything.";
	case 2:
		return "The scientists from Franklin to Morse were clear thinkers and did not produce erroneous theories. The scientists of today think deeply instead of clearly. One must be sane to think clearly, but one can think deeply and be quite insane.";
	case 3:
		return "Our virtues and our failings are inseparable, like force and matter. When they separate, man is no more.";
	case 4:
		return "Ere many generations pass, our machinery will be driven by a power obtainable at any point of the universe.";
	case 5:
		return "Man's new sense of pity began to interfere with the ruthless workings of nature. The only method compatible with our notions of civilization and the race is to prevent the breeding of the unfit by sterilization and the deliberate guidance of the mating instinct. The trend of opinion among eugenists is that we must make marriage more difficult. Certainly no one who is not a desirable parent should be permitted to produce progeny. A century from now it will no more occur to a normal person to mate with a person eugenically unfit than to marry a habitual criminal.";
	case 6:
		return "Most persons are so absorbed in the contemplation of the outside world that they are wholly oblivious to what is passing on within themselves. The premature death of millions is primarily traceable to this cause. Even among those who exercise care, it is a common mistake to avoid imaginary, and ignore the real dangers. And what is true of an individual also applies, more or less, to a people as a whole.";
	case 7:
		return "Alternate currents, especially of high frequencies, pass with astonishing freedom through even slightly rarefied gases. The upper strata of the air are rarefied. To reach a number of miles out into space requires the overcoming of difficulties of a merely mechanical nature.";
	case 8:
		return "If Edison had a needle to find in a haystack, he would proceed at once with the diligence of the bee to examine straw after straw until he found the object of his search.... I was a sorry witness of such doings, knowing that a little theory and calculation would have saved him ninety per cent of his labor.";
	case 9:
		return "It is a mere question of time when men will succeed in attaching their machinery to the very wheelwork of nature.";
	case 10:
		return "As a son of this country [Croatia], I consider it my duty to help the City of Zagreb in every way, either through counsel or through action.";
	case 11:
		return "General disarmament being for the present entirely out of question, a proportionate reduction might be recommended. The safety of any country and of the world's commerce depending not on the absolute, but relative amount of war material, this would be evidently the first reasonable step to take towards universal economy and peace. But it would be a hopeless task to establish an equitable basis of adjustment. Population, naval strength, force of army, commercial importance, water-power, or any other natural resource, actual or prospective, are equally unsatisfactory standards to consider.";
	case 12:
		return "The distance at which it can strike, and the destructive power of such a quasi-intelligent machine being for all practical purposes unlimited, the gun, the armor of the battleship and the wall of the fortress, lose their import and significance. One can prophesy with a Daniel's confidence that skilled electricians will settle the battles of the near future. But this is the least. In its effect upon war and peace, electricity offers still much greater and more wonderful possibilities. To stop war by the perfection of engines of destruction alone, might consume centuries and centuries. Other means must be employed to hasten the end.";
	case 13:
		return "A point of great importance would be first to know: what is the capacity of the earth? And what charge does it contain if electrified? Though we have no positive evidence of a charged body existing in space without other oppositely electrified bodies being near, there is a fair probability that the earth is such a body, for by whatever process it was separated from other bodies - and this is the accepted view of its origin - it must have retained a charge, as occurs in all processes of mechanical separation.";
	case 14:
		return "We crave for new sensations but soon become indifferent to them. The wonders of yesterday are today common occurrences.";
	case 15:
		return "The practical success of an idea, irrespective of its inherent merit, is dependent on the attitude of the contemporaries. If timely it is quickly adopted; if not, it is apt to fare like a sprout lured out of the ground by warm sunshine, only to be injured and retarded in its growth by the succeeding frost.";
	case 16:
		return "He had the highest regard for my attainments and gave me every evidence of his complete faith in my ability to ultimately achieve what I had set out to do. I am unwilling to accord to some small-minded and jealous individuals the satisfaction of having thwarted my efforts. These men are to me nothing more than microbes of a nasty disease. My project was retarded by laws of nature. The world was not prepared for it. It was too far ahead of time, but the same laws will prevail in the end and make it a triumphal success.";
	case 17:
		return "This mental activity, at first involuntary under the pressure of illness and suffering, gradually became second nature and led me finally to recognize that I was but an automaton devoid of free will in thought and action and merely responsible to the forces of the environment. Our bodies are of such complexity of structure, the motions we perform are so numerous and involved and the external impressions on our sense organs to such a degree delicate and elusive, that it is hard for the average person to grasp this fact. Yet nothing is more convincing to the trained investigator than the mechanistic theory of life which had been, in a measure, understood and propounded by Descartes three hundred years ago.";
	case 18:
		return "Even matter called inorganic, believed to be dead, responds to irritants and gives unmistakable evidence of a living principle within. Everything that exists, organic or inorganic, animated or inert, is susceptible to stimulus from the outside.";
	case 19:
		return "Ere long intelligence-transmitted without wires-will throb through the earth like a pulse through a living organism. The wonder is that, with the present state of knowledge and the experiences gained, no attempt is being made to disturb the electrostatic or magnetic condition of the earth, and transmit, if nothing else, intelligence.";
	case 20:
		return "So astounding are the facts in this connection, that it would seem as though the Creator, himself had electrically designed this planet...";
	case 21:
		return "Everyone should consider his body as a priceless gift from one whom he loves above all, a marvelous work of art, of indescribable beauty, and mystery beyond human conception, and so delicate that a word, a breath, a look, nay, a thought may injure it.";
	case 22:
		return "A single ray of light from a distant star falling upon the eye of a tyrant in bygone times may have altered the course of his life, may have changed the destiny of nations, may have transformed the surface of the globe, so intricate, so inconceivably complex are the processes in Nature.";
	case 23:
		return "We have to evolve means for obtaining energy from stores which are forever inexhaustible, to perfect methods which do not imply consumption and waste of any material whatever. I now feel sure that the realization of that idea is not far off... the possibilities of the development I refer to, namely, that of the operation of engines on any point of the earth by the energy of the medium.";
	case 24:
		return "The future will show whether my foresight is as accurate now as it has proved heretofore.";
	case 25:
		return "Throughout the infinite, the forces are in a perfect balance, and hence the energy of a single thought may determine the motion of a universe.";
	case 26:
		return "My definition of electricity is invisible light.";
	case 27:
		return "Sometimes I feel that by not marrying, I made too great a sacrifice to my work.";
	case 28:
		return "For ages this idea has been proclaimed in the consummately wise teachings of religion, probably not alone as a means of insuring peace and harmony among men, but as a deeply founded truth. The Buddhist expresses it in one way, the Christian in another, but both say the same: We are all one.";
	case 29:
		return "There is no subject more captivating, more worthy of study, than nature. To understand this great mechanism, to discover the forces which are active, and the laws which govern them, is the highest aim of the intellect of man.";
	case 30:
		return "The day when we shall know exactly what electricity is will chronicle an event probably greater, more important than any other recorded in the history of the human race. The time will come when the comfort, the very existence, perhaps, of man will depend upon that wonderful agent.";
	case 31:
		return "It has cost me years of thought to arrive at certain results, by many believed to be unattainable, for which there are now numerous claimants, and the number of these is rapidly increasing, like that of the colonels in the South after the war.";
	case 32:
		return "We may produce at will, from a sending station. an electrical effect in any particular region of the globe; we may determine the relative position or course of a moving object, such as a vessel at sea, the distance traversed by the same, or its speed.";
	case 33:
		return "In one of the sinking spells [due to Cholera] which was thought to be the last, my father rushed into the room. I still see his pallid face as he tried to cheer me in tones belying his assurance. \"Perhaps, \" I said, \"I may get well if you will let me study engineering.\" \"You will go to the best technical institution in the world, \" he solemnly replied, and I knew that he meant it. A heavy weight was lifted from my mind.... I came to life like Lazarus to the utter amazement of everybody.";
	case 34:
		return "Of all the endless variety of phenomena which nature presents to our senses, there is none that fills our minds with greater wonder than that inconceivably complex movement which, in its entirety, we designate as human life; Its mysterious origin is veiled in the forever impenetrable mist of the past, its character is rendered incomprehensible by its infinite intricacy, and its destination is hidden in the unfathomable depths of the future....";
	case 35:
		return "From childhood I was compelled to concentrate attention upon myself. This caused me much suffering, but to my present view, it was a blessing in disguise for it has taught me to appreciate the inestimable value of introspection in the preservation of life, as well as a means of achievement.";
	case 36:
		return "My ear barely caught signals coming in regular succession which could not have been produced on earth...";
	case 37:
		return "Man, like the universe, is a machine. Nothing enters our minds or determines our actions which is not directly or indirectly a response to stimuli beating upon our sense organs from without.";
	case 38:
		return "To conquer by sheer force is becoming harder and harder every day. Defensive is getting continuously the advantage of offensive, as we progress in the satanic science of destruction. The new art of controlling electrically the movements and operations of individualized automata at a distance without wires, will soon enable any country to render its coasts impregnable against all naval attacks.";
	case 39:
		return "We build but to tear down. Most of our work and resource is squandered. Our onward march is marked by devastation. Everywhere there is an appalling loss of time, effort and life. A cheerless view, but true.";
	case 40:
		return "Of all the frictional resistances, the one that most retards human movement is ignorance, what Buddha called 'the greatest evil in the world.' The friction which results from ignorance... can be reduced only by the spread of knowledge and the unification of the heterogeneous elements of humanity. No effort could be better spent.";
	case 41:
		return "We begin to think cosmically. Our sympathetic feelers reach out into the dim distance. The bacteria of the \"Weltschmerz\", are upon us. So far, however, universal harmony has been attained only in a single sphere of international relationship. That is the postal service. Its mechanism is working satisfactorily, but - how remote are we still from that scrupulous respect of the sanctity of the mail bag! And how much farther again is the next milestone on the road to peace - an international judicial service equally reliable as the postal!";
	case 42:
		return "The scientific man does not aim at an immediate result. He does not expect that his advanced ideas will be readily taken up. His work is like that of the planter - for the future. His duty is to lay the foundation for those who are to come, and point the way. He lives and labors and hopes.";
	case 43:
		return "Up to that time I never realized that I possessed any particular gift of discovery, but Lord Rayleigh, whom I always considered as an ideal man of science, had said so and if that was the case, I felt that I should concentrate on some big idea.";
	case 44:
		return "Marconi is a good fellow. Let him continue. He is using seventeen of my patents.";
	case 45:
		return "When wireless is perfectly applied the whole earth will be converted into a huge brain, which in fact it is, all things being particles of a real and rhythmic whole. We shall be able to communicate with one another instantly, irrespective of distance. Not only this, but through television and telephony we shall see and hear one another as perfectly as though we were face to face, despite intervening distances of thousands of miles; and the instruments through which we shall be able to do his will be amazingly simple compared with our present telephone. A man will be able to carry one in his vest pocket.";
	case 46:
		return "I am equally proud of my Serbian origin and Croatian homeland.";
	case 47:
		return "He declared that it could not be done and did me the honor of delivering a lecture on the subject, at the conclusion he remarked, \"Mr.Tesla may accomplish great things, but he certainly will never do this. It would be equivalent to converting a steadily pulling force, like that of gravity into a rotary effort. It is a perpetual motion scheme, an impossible idea.\" But instinct is something which transcends knowledge. We have, undoubtedly, certain finer fibers that enable us to perceive truths when logical deduction, or any other willful effort of the brain, is futile.";
	case 48:
		return "Money does not represent such a value as men have placed upon it. All my money has been invested into experiments with which I have made new discoveries enabling mankind to have a little easier life.";
	case 49:
		return "Though free to think and act, we are held together, like the stars in the firmament, with ties inseparable. These ties cannot be seen, but we can feel them.";
	case 50:
		return "It should be borne in mind that electrical energy obtained by harnessing a waterfall is probably fifty times more effective than fuel energy. Since this is the most perfect way of rendering the sun's energy available, the direction of the future material development of man is clearly indicated.";
	default:
		VerbosityDisplay("In GetTeslaQuote(): ERROR - Failed to get quote due to invalid value (value below 1 or above 50).\n");
		return "Failed to get quote.";
	}

	return "";
}

// Output cow
// sSayText is for making the cow output specific text.
//
void OutputCow(std::string sSayText, std::string sCowColourFore, std::string sCowColourBack) {
	if (sSayText != "") {
		OutputBoxWithText(sSayText, LBLU, ConfigObjMain.sColourGlobalBack, ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Output part of formatted cow with tubing to match output box
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||\n||\n|| ";
		colour(sCowColourFore, sCowColourBack);
		std::cout << "^__^\n";
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "|| ";
		colour(sCowColourFore, sCowColourBack);
		std::cout << "(OO)\\_______\n";
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||=";
		colour(sCowColourFore, sCowColourBack);
		std::cout << "(__)\\       )_/\\/\\\n";
	}
	else {
		colour(sCowColourFore, sCowColourBack);
		std::cout << "   ^__^\n"
			<< "   (OO)\\_______\n"
			<< "   (__)\\       )_/\\/\\\n";
	}


	std::cout	<< "       ||----W |\n"
				<< "       ||     ||\n";
}

// Output cat
// sSayText is for making the cat output specific text.
//
void OutputCat(std::string sSayText, std::string sCatColourFore, std::string sCatColourBack) {

	if (sSayText != "") {
		OutputBoxWithText(sSayText, LBLU, ConfigObjMain.sColourGlobalBack, ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Output part of formatted cat with tubing to match output box
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||\n||\n||  ";
		colour(sCatColourFore, sCatColourBack);
		std::cout << "|\\___/|\n";
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||  ";
		colour(sCatColourFore, sCatColourBack);
		std::cout << "/ ^ ^ \\\n";
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "|| ";
		colour(sCatColourFore, sCatColourBack);
		std::cout << "|   Y   |\n";
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||==";
		colour(sCatColourFore, sCatColourBack);
		std::cout << "\\  W  /\n";
	}
	else {
		colour(sCatColourFore, sCatColourBack);
		std::cout << "    |\\___/|\n"
			<< "    / ^ ^ \\\n"
			<< "   |   Y   |\n"
			<< "    \\  W  /\n";
	}


	std::cout << "    /'___''.\n"
		<< "   |        \\   __\n"
		<< "   \\         \\ (_ \\\n"
		<< "    | | | |   \\  \\ \\\n"
		<< "    | | | | _. \\_/ /\n"
		<< "    (_| (_|(______/\n";
}

// Output bunny
// sSayText is for making the bunny output specific text.
// sBunnyColourFore and Back is for choosing bunny colour.
//
void OutputBunny(std::string sSayText, std::string sBunnyColourFore, std::string sBunnyColourBack) {

	if (sSayText != "") {
		OutputBoxWithText(sSayText, LBLU, ConfigObjMain.sColourGlobalBack, ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Output part of formatted bunny with tubing to match output box
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||\n||\n||         ";
		colour(sBunnyColourFore, sBunnyColourBack);
		std::cout << "/\\ /|\n";
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << "||=========";
		colour(sBunnyColourFore, sBunnyColourBack);
		std::cout << "\\ | \\\n";
	}
	else {
		colour(sBunnyColourFore, sBunnyColourBack);
		std::cout << "           /\\ /|\n"
			<< "           \\ | \\\n";
	}

	std::cout	<< "       _ _ /  ^ ^\n"
			<< "     /    \\  =>X<=\n"
			<< "   /|      |   /\n"
			<< "   \\|     /__| |\n"
			<< "     \\_____\\ \\__\\\n";
}

// HackerTyper - Traditional hacker-typer using a snippet of the linux kernel source code
// Arguments: nSpeed - The speed of the character output in characters.
// Return Values: None
// 
void HackerTyper(uint64_t nSpeed = 3) {
	std::string sHackerText = "struct group_info init_groups = { .usage = ATOMIC_INIT(2) };\n\nstruct group_info *groups_alloc(int gidsetsize){\n\n   struct group_info *group_info;\n\n       int nblocks;\n\n        int i;\n\n\n\n  nblocks = (gidsetsize + NGROUPS_PER_BLOCK - 1) / NGROUPS_PER_BLOCK;\n\n /* Make sure we always allocate at least one indirect block pointer */\n\n      nblocks = nblocks ? : 1;\n\n    group_info = kmalloc(sizeof(*group_info) + nblocks*sizeof(gid_t *), GFP_USER);\n\n      if (!group_info)\n\n            return NULL;\n\n        group_info->ngroups = gidsetsize;\n\n   group_info->nblocks = nblocks;\n\n      atomic_set(&group_info->usage, 1);\n\n\n\n      if (gidsetsize <= NGROUPS_SMALL)\n\n            group_info->blocks[0] = group_info->small_block;\n\n    else {\n\n              for (i = 0; i < nblocks; i++) {\n\n                    gid_t *b;\n\n                    b = (void *)__get_free_page(GFP_USER);\n\n                      if (!b)\n\n            goto out_undo_partial_alloc;\n\n                 group_info->blocks[i] = b;\n\n          }\n\n   }\n\n   return group_info;\n\n\n\nout_undo_partial_alloc:\n\n   while (--i >= 0) {\n\n          free_page((unsigned long)group_info->blocks[i]);\n\n    }\n\n   kfree(group_info);\n\n  return NULL;\n\n}\n\n\n\nEXPORT_SYMBOL(groups_alloc);\n\n\n\nvoid groups_free(struct group_info *group_info)\n\n{\n\n   if (group_info->blocks[0] != group_info->small_block) {\n\n             int i;\n\n              for (i = 0; i < group_info->nblocks; i++)\n\n                   free_page((unsigned long)group_info->blocks[i]);\n\n    }\n\n   kfree(group_info);\n\n}\n\n\n\nEXPORT_SYMBOL(groups_free);\n\n\n\n/* export the group_info to a user-space array */\n\nstatic int groups_to_user(gid_t __user *grouplist,\n\n                     const struct group_info *group_info)\n\n{\n\n int i;\n\n      unsigned int count = group_info->ngroups;\n\n\n\n       for (i = 0; i < group_info->nblocks; i++) {\n\n         unsigned int cp_count = min(NGROUPS_PER_BLOCK, count);\n\n              unsigned int len = cp_count * sizeof(*grouplist);\n\n\n\n               if (copy_to_user(grouplist, group_info->blocks[i], len))\n\n   return -EFAULT;\n\n\n\n          grouplist += NGROUPS_PER_BLOCK;\n\n             count -= cp_count;\n\n  }\n\n   return 0;\n\n}\n\n\n\n/* fill a group_info from a user-space array - it must be allocated already */\n\nstatic int groups_from_user(struct group_info *group_info,\n\n    gid_t __user *grouplist)\n\n{\n\n     int i;\n\n      unsigned int count = group_info->ngroups;\n\n\n\n       for (i = 0; i < group_info->nblocks; i++) {\n\n         unsigned int cp_count = min(NGROUPS_PER_BLOCK, count);\n\n              unsigned int len = cp_count * sizeof(*grouplist);\n\n\n\n               if (copy_from_user(group_info->blocks[i], grouplist, len))\n\n                  return -EFAULT;\n\n\n\n         grouplist += NGROUPS_PER_BLOCK;\n\n             count -= cp_count;\n\n  }\n\n   return 0;\n\n}\n\n\n\n/* a simple Shell sort */\n\nstatic void groups_sort(struct group_info *group_info)\n\n{\n\n      int base, max, stride;\n\n      int gidsetsize = group_info->ngroups;\n\n\n\n   for (stride = 1; stride < gidsetsize; stride = 3 * stride + 1)\n\n              ; /* nothing */\n\n     stride /= 3;\n\n\n\n    while (stride) {\n\n            max = gidsetsize - stride;\n\n          for (base = 0; base < max; base++) {\n\n                        int left = base;\n\n                    int right = left + stride;\n\n gid_t tmp = GROUP_AT(group_info, right);\n\n\n\n                 while (left >= 0 && GROUP_AT(group_info, left) > tmp) {\n\n                             GROUP_AT(group_info, right) =\n\n                                   GROUP_AT(group_info, left);\n\n                             right = left;\n\n                               left -= stride;\n\n            }\n\n                    GROUP_AT(group_info, right) = tmp;\n\n          }\n\n           stride /= 3;\n\n        }\n\n}\n\n\n\n/* a simple bsearch */\n\nint groups_search(const struct group_info *group_info, gid_t grp)\n\n{\n\n      unsigned int left, right;\n\n\n\n       if (!group_info)\n\n            return 0;\n\n\n\n       left = 0;\n\n   right = group_info->ngroups;\n\n        while (left < right) {\n\n              unsigned int mid = left + (right - left)/2;\n\n        if (grp > GROUP_AT(group_info, mid))\n\n                 left = mid + 1;\n\n             else if (grp < GROUP_AT(group_info, mid))\n\n                   right = mid;\n\n                else\n\n                        return 1;\n\n   }\n\n  return 0;\n\n}\n\n\n\n";
	char cKey = 0; // Key pressed (for exit functions and stuff)

	// Change colour to RGB Green
	colour(LGRN, ConfigObjMain.sColourGlobalBack);

	// Output based on nSpeed speed, and exit on ESC keypress
	std::cout << " --> ";
	while (cKey != 27)
	{
		for (uint64_t i = 0; i < sHackerText.length(); i += nSpeed)
		{
			// Get key
			cKey = _getch();
			// Exit on ESC keypress (27 is ASCII Code)
			if (cKey == 27) break;

			// Near the end of the string - Output up to end of sHackerText
			if (sHackerText.length() - 1 < (i + nSpeed))
			{
				for (; i < sHackerText.length(); i++)
				{
					std::cout << sHackerText[i];
				}

				break;
			}

			// In the middle of string - Output normally
			else
			{
				uint64_t nCapChanger = 0; // to change limit of j
				for (uint64_t j = 0; j < nSpeed + nCapChanger; j++)
				{
					std::cout << sHackerText[i + j];

					// Ignore space counting by increasing cap
					if (sHackerText[i + j] == ' ') nCapChanger++;
				}

				// Increment i by the cap to get it up to speed
				i += nCapChanger;
			}
		}
	}

	// Switch colours to default
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << '\n';
	Exiting();
	return;
}

// HackerTyperFile - A hacker typer, but you can use your own file for the text.
// Arguments: sFilePath - The file path for the custom file to be used.
//            nSpeed - The speed of the character output in characters.
// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
// 
bool HackerTyperFile(std::string sFilePath, uint64_t nSpeed = 3) {
	std::string sFinalFilePath = "";
	char cKey = 0;

	// Check for speechmarks in case of copy from file explorer
	if (sFilePath[0] == '"' && sFilePath[sFilePath.length() - 1] == '"') {
		sFinalFilePath = sFilePath.substr(1, (sFilePath.length() - 2));
	}
	else sFinalFilePath = sFilePath;

	// Check if the file actually exists
	std::ifstream FilePathTest(sFinalFilePath);
	if (FilePathTest.fail()) {
		VerbosityDisplay("ERROR: In HackerTyperFile() - Test file stream failed to open file path. Incorrect filepath detected.\n");
		UserErrorDisplay("ERROR - File does not exist. Please ensure the filepath that has been used exists, and try again later.\n");
		FilePathTest.close();
		return false;
	}
	else FilePathTest.close();

	// Copy file into string
	std::ifstream FilePathIn(sFilePath);
	std::string sFileContents = "";
	std::string sBuffer = "";

	while (!FilePathIn.eof())
	{
		std::getline(FilePathIn, sBuffer, '\n');
		sBuffer += "\n"; // USE \\n for copying new text into string manually
		sFileContents += sBuffer;
		sBuffer = "";
	}

	// Change colour to RGB Green
	colour(LGRN, ConfigObjMain.sColourGlobalBack);

	// Output based on nSpeed speed, and exit on ESC keypress
	std::cout << " --> ";
	while (cKey != 27)
	{
		for (uint64_t i = 0; i < sFileContents.length(); i += nSpeed)
		{
			// Get key
			cKey = _getch();
			// Exit on ESC keypress (27 is ASCII Code)
			if (cKey == 27) break;

			// Near the end of the string - Output up to end of sFileContents
			if (sFileContents.length() - 1 < (i + nSpeed))
			{
				for (; i < sFileContents.length(); i++)
				{
					std::cout << sFileContents[i];
				}

				break;
			}

			// In the middle of string - Output normally
			else
			{
				uint64_t nCapChanger = 0; // to change limit of j
				for (uint64_t j = 0; j < nSpeed + nCapChanger; j++)
				{
					std::cout << sFileContents[i + j];

					// Ignore space counting by increasing cap
					if (sFileContents[i + j] == ' ') nCapChanger++;
				}

				// Increment i by the cap to get it up to speed
				i += nCapChanger;
			}
		}
	}

	// Switch colours to default
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << '\n';
	Exiting();

	return true;
}

// ResetExpl - Resets explorer.exe on the system running ZeeTerminal.
// Arguments: None
// Return values: TRUE or 1 for success, FALSE or 0 for fail.
//
bool ResetExpl() {
	
	// Kill explorer.exe
	system("taskkill /f /im explorer.exe");

	// Start explorer.exe using ShellExecuteA
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) {
		VerbosityDisplay("In ResetExpl() - ERROR: Failed to initialise the COM Library.\n");
		UserErrorDisplay("ERROR - Failed to load libraries that are required for operation. Please try again later.\n");

		return false;
	}

	ShellExecuteA(NULL, "open", "C:\\Windows\\explorer.exe", NULL, "C:\\Windows\\", NULL);

	return true;
}

// GetNumberDigitLength - Gets the number of characters before the decimal point of a long double floating-point number.
// Arguments: dNumber - The number to check and use.
// Return values: The number of characters before the decimal point.
// NOTE: If the number is less than 1, the number -1 will be returned.
//
int GetWholeNumberDigitLength(long double dNumber) {
	// -1 because if number was less than 1, it can support 16dp when long double is 64-bit (no. 0 would be taking no space of the 64-bit container)
	int nNumberDigitLength = -1; 
	constexpr uint64_t nMaxMultiplierNum = std::numeric_limits<uint64_t>::max() / 10; // divide by 10 so it stops early before overflow occurs

	// Count number of place value digits
	for (uint64_t i = 1; i < dNumber && i < nMaxMultiplierNum; i *= 8, nNumberDigitLength++) {
	}

	return nNumberDigitLength;
}

// EradicateTrailingZeroes - Remove any extra trailing zeroes and, if the string is truly a whole number, remove the decimal point as well.
// Arguments: sString - The string to perform the eradication on.
// Return values: The updated string with the eradication processes completed on.
//
std::string EradicateTrailingZeroes(std::string sString)
{
	// Get position of last decimal place
	size_t nFinalDecimalPlace = sString.find_last_of('.');

	// Get rid of trailing 0s
	for (size_t i = sString.size() - 1; i >= nFinalDecimalPlace; i--) {
		if (sString.at(i) == '0') {
			sString.pop_back(); // Remove if last digit is '0'.
		}
		else if (sString.at(i) == '.') {
			sString.pop_back(); // Remove dot.
			break; // Break after '.' is removed.
		}
		else {
			break; // Or break before a digit is removed.
		}
	}

	return sString;
}

// FormatValueForDisplay - Formats a specific value for display output.
//                       - Has a max of 15-16dp.
// Arguments: dValue - The number to format.
// Return Value: Formatted number as a string.
//
std::string FormatValueForEuropeanNotation(long double dValue) {
	// Create stringstream and send info to it
	std::stringstream ssFormatted;
	ssFormatted << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 - GetWholeNumberDigitLength(dValue) - 1) << dValue;

	std::string sFormatBuffer = EradicateTrailingZeroes(ssFormatted.str());

	// Change decimal point to European notation if necessary
	//
	// Find last decimal point and replace with european one
	size_t nDecimalPointPos = sFormatBuffer.find_last_of('.');

	// Exit when not found
	if (nDecimalPointPos == std::string::npos) return sFormatBuffer;

	// Replace
	sFormatBuffer.replace(nDecimalPointPos, 1, ",");

	// Return string from stringstream
	return sFormatBuffer;
}

// SettingsBoolToString - Converts a boolean value to either 'enabled' (TRUE) or 'disabled' (FALSE).
// Arguments: bValue - Value to convert.
// Return value: Final string.
//
std::string SettingsBoolToString(bool bValue) {
	if (bValue == true) {
		return "Enabled";
	}
	else if (bValue == false) {
		return "Disabled";
	}
	else {
		VerbosityDisplay("In SettingsBoolToString(): ERROR - Invalid argument value.\n");
		return "";
	}

	return "";
}

/* MessageBox Codes */
//////////////////////
/* Message box codes are the following for icons:
   [16] Error
   [32] Question Mark
   [48] Exclamation Mark
   [64] Information 'I'
*/
/* Message box codes are the following for buttons:
   [0] OK
   [1] OK + Cancel
   [2] Abort + Retry + Ignore
   [3] Yes + No + Cancel
   [4] Yes + No
   [5] Retry + Cancel
   [6] Cancel + Try Again + Continue
 */