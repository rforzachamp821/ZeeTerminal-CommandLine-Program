
void ColourForegroundSwitch(int*, std::string*, std::string*);
void ColourBackgroundSwitch(int*, std::string*, std::string*);
std::string wordWrap(std::string);
bool EnableVTMode();
void colour(std::string, std::string);
bool YesNo(std::string);
void Exiting();
long double num(std::string);
void SetCursorAttributes();
void colourSubheading();
void ColourTypeSwitch();

extern bool bDisplayDirections;
extern bool bDisplayVerboseMessages;
extern bool bAnsiVTSequences;
extern bool bRandomColoursOnStartup;
extern bool bShowCursor;
extern bool bWordWrapToggle;
extern bool bCursorBlink;
extern bool bTermCustomThemeSupport;

extern int nSlowCharSpeed;
extern int nCursorShape;

extern std::string sColourHighlight;
extern std::string sColourHighlightBack;

extern std::string sColourTitle;
extern std::string sColourTitleBack;

extern std::string sColourSubheading;
extern std::string sColourSubheadingBack;

std::string sOptionsColour[] = {
	"Black",
	"Blue",
	"Green",
	"Aqua",
	"Red",
	"Purple",
	"Yellow",
	"White",
	"Gray",
	"Light Blue",
	"Light Green",
	"Light Aqua",
	"Light Red",
	"Light Purple",
	"Light Yellow",
	"Bright White"
};


void HighlightColourSettings(short int nResult = 0, int nChoice = 0) {

	// 0 is default, so 0 is used as an indication that there isn't any argument being passed
	if (nResult == 0) {
		OptionSelectEngine oseHighlight;
		oseHighlight.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Modify Foreground Colour",
			"Modify Background Colour"
		};
		oseHighlight.sOptions = sOptions;
		std::cout << std::endl;

		nResult = oseHighlight.OptionSelect("Please select what you want to do for Highlight Colour:", " ___HIGHLIGHT COLOUR SETTINGS___ ");
	}
	

	if (nResult == 1)
	{
		if (nChoice == 0) {
			OptionSelectEngine oseColourFore;
			oseColourFore.nSizeOfOptions = 16;
			oseColourFore.sOptions = sOptionsColour;

			nChoice = oseColourFore.OptionSelect("Please choose your desired highlight foreground colour below:", " ___FOREGROUND COLOUR___ ");
			std::cout << std::endl;
		}
		
		ColourForegroundSwitch(&nChoice, &sColourHighlightBack, &sColourHighlight);

		colour(LGRN, sColourGlobalBack);
		std::cout << CentreText("Highlight foreground colour successfully set!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nResult == 2) {

		if (nChoice == 0) {
			OptionSelectEngine oseColourBack;
			oseColourBack.nSizeOfOptions = 16;
			oseColourBack.sOptions = sOptionsColour;

			nChoice = oseColourBack.OptionSelect("Please choose your desired highlight background colour below:", " ___BACKGROUND COLOUR___ ");
			std::cout << std::endl;
		}

		ColourBackgroundSwitch(&nChoice, &sColourHighlightBack, &sColourHighlight);

		colour(LGRN, sColourGlobalBack);
		std::cout << CentreText("Highlight background colour successfully set!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nResult == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	return;
}

void TitleColourSettings(short int nResult = 0, int nChoice = 0) {

	// 0 is default, so 0 is used as an indication that there isn't any argument being passed
	if (nResult == 0) {
		OptionSelectEngine oseTitle;
		oseTitle.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Modify Foreground Colour",
			"Modify Background Colour"
		};
		oseTitle.sOptions = sOptions;
		std::cout << std::endl;

		nResult = oseTitle.OptionSelect("Please select what you want to do for Title Colour:", " ___TITLE COLOUR SETTINGS___ ");
	}
	

	if (nResult == 1)
	{
		if (nChoice == 0) {
			OptionSelectEngine oseColourFore;
			oseColourFore.nSizeOfOptions = 16;
			oseColourFore.sOptions = sOptionsColour;

			nChoice = oseColourFore.OptionSelect("Please choose your desired title foreground colour below:", " ___FOREGROUND COLOUR___ ");
			std::cout << std::endl;
		}

		ColourForegroundSwitch(&nChoice, &sColourTitleBack, &sColourTitle);

		colour(LGRN, sColourGlobalBack);
		std::cout << CentreText("Title foreground colour successfully set!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nResult == 2) {

		if (nChoice == 0) {
			OptionSelectEngine oseColourBack;
			oseColourBack.nSizeOfOptions = 16;
			oseColourBack.sOptions = sOptionsColour;

			nChoice = oseColourBack.OptionSelect("Please choose your desired title background colour below:", " ___BACKGROUND COLOUR___ ");
			std::cout << std::endl;
		}

		ColourBackgroundSwitch(&nChoice, &sColourTitleBack, &sColourTitle);

		colour(LGRN, sColourGlobalBack);
		std::cout << CentreText("Title background colour successfully set!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nResult == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	return;
}

void SubheadingColourSettings(short int nResult = 0, int nChoice = 0) {

	// 0 is default, so 0 is used as an indication that there isn't any argument being passed
	if (nResult == 0) {
		OptionSelectEngine oseSubheading;
		oseSubheading.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Modify Foreground Colour",
			"Modify Background Colour"
		};
		oseSubheading.sOptions = sOptions;
		std::cout << std::endl;

		int nResult = oseSubheading.OptionSelect("Please select what you want to do for Subheading Colour:", " ___SUBHEADING COLOUR SETTINGS___ ");
	}


	if (nResult == 1)
	{
		if (nChoice == 0) {
			OptionSelectEngine oseColourFore;
			oseColourFore.nSizeOfOptions = 16;
			oseColourFore.sOptions = sOptionsColour;

			int nChoice = oseColourFore.OptionSelect("Please choose your desired subheading foreground colour below:", " ___FOREGROUND COLOUR___ ");
			std::cout << std::endl;
		}

		ColourForegroundSwitch(&nChoice, &sColourSubheadingBack, &sColourSubheading);

		colour(LGRN, sColourGlobalBack);
		std::cout << CentreText("Subheading foreground colour successfully set!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nResult == 2) {

		if (nChoice == 0) {
			OptionSelectEngine oseColourBack;
			oseColourBack.nSizeOfOptions = 16;
			oseColourBack.sOptions = sOptionsColour;

			int nChoice = oseColourBack.OptionSelect("Please choose your desired background colour below:", " ___BACKGROUND COLOUR___ ");
			std::cout << std::endl;
		}

		ColourBackgroundSwitch(&nChoice, &sColourSubheadingBack, &sColourSubheading);

		colour(LGRN, sColourGlobalBack);
		std::cout << CentreText("Subheading background colour successfully set!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nResult == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	return;
}

void VerboseMessagesSettings(short int nChoice = 0) {

	// 0 is default, so 0 is used as an indication that there isn't any argument being passed
	if (nChoice == 0) {
		OptionSelectEngine oseVerbose;

		oseVerbose.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Enable Verbose Messages",
			"Disable Verbose Messages (DEFAULT)"
		};
		oseVerbose.sOptions = sOptions;
		std::cout << std::endl;

		nChoice = oseVerbose.OptionSelect("Please select your desired option for the Verbose Messages setting:", " ___VERBOSE MESSAGES SETTINGS___ ");
		std::cout << std::endl;
	}
	

	if (nChoice == 1) {
		bDisplayVerboseMessages = true;
		colour(LGRN, sColourGlobalBack);
		std::cout << "Verbosity Messages have been enabled successfully.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nChoice == 2) {
		bDisplayVerboseMessages = false;
		colour(LGRN, sColourGlobalBack);
		std::cout << "Verbosity Messages have been disabled successfully.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nChoice == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}

	return;
}

void DirectionMessagesSettings(short int nChoice = 0) {

	// 0 is default, so 0 is used as an indication that there isn't any argument being passed
	if (nChoice == 0) {
		OptionSelectEngine oseDirections;

		// Set up environment
		oseDirections.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Enable Direction (Help) Messages (DEFAULT)",
			"Disable Direction (Help) Messages"
		};
		oseDirections.sOptions = sOptions;
		std::cout << std::endl;

		int nChoice = oseDirections.OptionSelect("Please select your desired option for the Direction Messages setting: ", " ___DIRECTION MESSAGES SETTINGS___ ");
		std::cout << std::endl;
	}
	

	if (nChoice == 1) {
		bDisplayDirections = true;
		colour(LGRN, sColourGlobalBack);
		std::cout << "Direction (Help) Messages have been enabled successfully.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else if (nChoice == 2) {
		bDisplayDirections = false;
		colour(LGRN, sColourGlobalBack);
		std::cout << "Direction (Help) Messages have been disabled successfully.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;

	}
	else if (nChoice == -1) {
		// Warn user that setting modification is terminated.
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}
	else {
		// Warn user that error occured.
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);
	}

	return;
}

void AnsiSettings(short int nChoice = 0) {

	if (nChoice == 0) {
		OptionSelectEngine oseAnsi;

		oseAnsi.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Enable ANSI (Virtual Terminal) Escape Sequences (DEFAULT)",
			"Disable ANSI (Virtual Terminal) Escape Sequences"
		};
		oseAnsi.sOptions = sOptions;
		std::cout << std::endl;

		int nChoice = oseAnsi.OptionSelect("Please select your desired option for the ANSI setting:", " ___ANSI SETTINGS___ ");
		std::cout << std::endl;
	}
	

	if (nChoice == 1) {
		if (EnableVTMode() != false) {
			bAnsiVTSequences = true;

			// Set new colours
			ColourTypeSwitch();
			colour(sColourGlobal, sColourGlobalBack);
			cls(); // Set colours to whole screen

			colour(LGRN, sColourGlobalBack);
			std::cout << "ANSI VT sequences successfully enabled.\n";
			colour(sColourGlobal, sColourGlobalBack);
			return;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << wordWrap("Sorry, you cannot enable ANSI escape codes as your terminal doesn't support it.") << std::endl;
			colour(YLW, sColourGlobalBack);
			std::cout << "Exiting...\n";
			colour(sColourGlobal, sColourGlobalBack);
			return;
		}

	}
	else if (nChoice == 2) {
		colour(YLW, sColourGlobalBack);
		std::cout << wordWrap("WARNING: This WILL disable RGB colours AND text formatting from the point of this message.") << '\n';
		
		if (YesNo(wordWrap("Would you like to proceed? [y/n] > "))) 
		{
			bAnsiVTSequences = false;

			// Set new colours
			ColourTypeSwitch();
			colour(sColourGlobal, sColourGlobalBack);
			cls(); // Set to whole screen

			colour(LGRN, sColourGlobalBack);
			std::cout << "ANSI VT sequences successfully disabled.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
	}
	else if (nChoice == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}

	return;
}

void WordWrapSettings(short int nChoice = 0) {
	if (nChoice == 0) {
		OptionSelectEngine oseWordWrap;

		oseWordWrap.nSizeOfOptions = 2;
		std::string sOptions[] = {
			"Enable Word Wrapping (Default)",
			"Disable Word Wrapping (Less CPU intensive)"
		};
		oseWordWrap.sOptions = sOptions;

		nChoice = oseWordWrap.OptionSelect("Please select your desired option for Word Wrapping:", " ___WORD WRAP SETTINGS___ ");
		std::cout << std::endl;
	}

	if (nChoice == 1) {
		bWordWrapToggle = true;
		colour(LGRN, sColourGlobalBack);
		std::cout << "Word Wrapping has been enabled successfully.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}
	else if (nChoice == 2) {
		bWordWrapToggle = false;
		colour(LGRN, sColourGlobalBack);
		std::cout << "Word Wrapping has been disabled successfully.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}
	else if (nChoice == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}
}

void CursorSettings(short int nChoice = 0, short int nChoiceBlink = 0, short int nChoiceShow = 0, short int nChoiceShape = 0) {

	if (nChoice == 0) {
		OptionSelectEngine oseCursor;
		oseCursor.nSizeOfOptions = 3;
		std::string sOptions[] = {
			"Enable/Disable Cursor Blinking",
			"Show/Hide Cursor",
			"Cursor Shape"
		};
		oseCursor.sOptions = sOptions;

		while (true) {
			nChoice = oseCursor.OptionSelect("Please select your desired option for the Cursor settings:", " ___CURSOR SETTINGS___ ");

			if (nChoice == 1 || nChoice == 3) {

				// Doesn't work without ANSI
				if (!bAnsiVTSequences) {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("Sorry, but this setting cannot be modified without terminal ANSI VT support.") << '\n';
					Exiting();
					colour(sColourGlobal, sColourGlobalBack);
				}
				else break;
			}
			else break;
		}
	}

	// Enable/Disable Cursor blinking
	if (nChoice == 1) {

		if (nChoiceBlink == 0) {
			OptionSelectEngine oseBlink;
			oseBlink.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable Cursor Blinking (Default)",
				"Disable Cursor Blinking"
			};
			oseBlink.sOptions = sOptions;

			nChoiceBlink = oseBlink.OptionSelect("Please select your desired option for the Cursor Blinking Setting:", " ___CURSOR BLINKING SETTINGS___ ");
		}

		if (nChoiceBlink == 1) {
			bCursorBlink = true;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor Blinking has been enabled successfully.\n";
			colour(sColourGlobal, sColourGlobalBack);
			

			return;
		}
		else if (nChoiceBlink == 2) {
			bCursorBlink = false;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor Blinking has been disabled successfully.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceBlink == -1) {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "An error occured. Please try again later.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}

	}

	// Show/Hide Cursor
	else if (nChoice == 2) {

		if (nChoiceShow == 0) {
			OptionSelectEngine oseShow;
			oseShow.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Show Console Cursor (Default)",
				"Hide Console Cursor"
			};
			oseShow.sOptions = sOptions;

			nChoiceShow = oseShow.OptionSelect("Please select your desired option for cursor visibility:", " ___CURSOR VISIBILITY SETTINGS___ ");
		}

		if (nChoiceShow == 1) {
			bShowCursor = true;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'visible'.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceShow == 2) {
			bShowCursor = false;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'hidden'.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceShow == -1) {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "An error occured. Please try again later.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}

	}

	// Cursor Shape
	else if (nChoice == 3) {

		if (nChoiceShape == 0) {
			OptionSelectEngine oseShape;
			oseShape.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Block Shape",
				"Underline-style Shape",
				"Bar Shape (Default)"
			};
			oseShape.sOptions = sOptions;

			nChoiceShape = oseShape.OptionSelect("Please select your desired shape for the console cursor:", " ___CURSOR SHAPE SETTINGS___ ");
		}

		if (nChoiceShape == 1) {
			if (bCursorBlink == true) nCursorShape = 1; else nCursorShape = 2;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'block'.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceShape == 2) {
			if (bCursorBlink == true) nCursorShape = 3; else nCursorShape = 4;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'underline'.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceShape == 3) {
			if (bCursorBlink == true) nCursorShape = 5; else nCursorShape = 6;
			// Set cursor attributes immediately
			SetCursorAttributes();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'bar'.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceShape == -1) {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "An error occured. Please try again later.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
	}

	// Exit
	else if (nChoice == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying settings terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}

	// Error
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}
}

void OtherSettings(short int nChoice = 0, int nChoiceSlowChSpeed = 0, bool bFromArg = false , short int nChoiceRandColStartup = 0, short int nTermCustomThemeSupport = 0) {

	// Standard interface
	if (nChoice == 0) {
		OptionSelectEngine oseOther;
		oseOther.nSizeOfOptions = 3;
		std::string sOptions[] = {
			"SlowChar Speed Value",
			"Enable/Disable Random Colours on Startup",
			"Enable/Disable Terminal Custom Theme Support"
		};
		oseOther.sOptions = sOptions;

		nChoice = oseOther.OptionSelect("Please select your option from the list of Other Settings:", " ___OTHER SETTINGS___ ");
	}

	// SlowChar Speed Value
	if (nChoice == 1) {
		if (nChoiceSlowChSpeed == 0 && !bFromArg) {
			CentreColouredText(" ___SLOWCHAR SPEED SETINGS___ ", 1);
			std::cout << "\n";
			colourSubheading(); // extra info colour is the same as subheading colour
			std::cout << "Higher numbers are faster." << NOULINE_STR;
			colour(sColourGlobal, sColourGlobalBack);
			std::cout << "\nDefault Speed: 45\nCurrent Speed: " << nSlowCharSpeed << "\n\n" << wordWrap("Input 0 to disable SlowChar entirely, and input a negative number to exit.") << '\n';

			nChoiceSlowChSpeed = num("Please input how fast you want SlowChar to be: > ");
		}

		if (nChoiceSlowChSpeed < 0) {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);
			return;
		}

		nSlowCharSpeed = nChoiceSlowChSpeed;
		colour(LGRN, sColourGlobalBack);
		std::cout << "SlowChar Speed has successfully been set to " << nSlowCharSpeed << "ms (per char).\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;

	}

	// Random Colours on Startup
	else if (nChoice == 2) {
		if (nChoiceRandColStartup == 0) {
			OptionSelectEngine oseRandCol;
			oseRandCol.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable Random Colours on Startup",
				"Disable Random Colours on Startup (Default)"
			};
			oseRandCol.sOptions = sOptions;

			nChoiceRandColStartup = oseRandCol.OptionSelect("Please select your choice for Random Colours on Startup:", " ___RANDOM COLOUR ON STARTUP SETTINGS___ ");
		}

		if (nChoiceRandColStartup == 1) {
			bRandomColoursOnStartup = true;
			colour(LGRN, sColourGlobalBack);
			std::cout << "Random Colours on Startup Enabled.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nChoiceRandColStartup == 2) {
			bRandomColoursOnStartup = false;
			colour(LGRN, sColourGlobalBack);
			std::cout << "Random Colours on Startup Disabled.\n";
			colour(sColourGlobal, sColourGlobalBack);
			
			return;
		}
		else if (nChoiceRandColStartup == -1) {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "An error occured. Please try again later.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
	}

	// Terminal Custom Themes Support
	else if (nChoice == 3) {
		if (nTermCustomThemeSupport == 0) {
			OptionSelectEngine oseRandCol;
			oseRandCol.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable Terminal Custom Theme Support",
				"Disable Terminal Custom Theme Support (Default)"
			};
			oseRandCol.sOptions = sOptions;

			nTermCustomThemeSupport = oseRandCol.OptionSelect("Note: This works by making the black background colour the default terminal colour.\nPlease select your choice for Terminal Custom Theme Support:", " ___TERMINAL CUSTOM THEME SETTINGS___ ");
		}

		if (nTermCustomThemeSupport == 1) {
			bTermCustomThemeSupport = true;
			// Clear screen FULLY to make changes take effect
			colour(sColourGlobal, sColourGlobalBack);
			cls();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Terminal Custom Theme Support Enabled.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nTermCustomThemeSupport == 2) {
			bTermCustomThemeSupport = false;
			// Clear screen FULLY to make changes take effect
			colour(sColourGlobal, sColourGlobalBack);
			cls();

			colour(LGRN, sColourGlobalBack);
			std::cout << "Terminal Custom Theme Support Disabled.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else if (nTermCustomThemeSupport == -1) {
			colour(YLW, sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "An error occured. Please try again later.\n";
			colour(sColourGlobal, sColourGlobalBack);

			return;
		}
	}

	// Terminated
	else if (nChoice == -1) {
		colour(YLW, sColourGlobalBack);
		std::cout << "Modifying settings terminated.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}

	// Error
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "An error occured. Please try again later.\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}

	return;
}