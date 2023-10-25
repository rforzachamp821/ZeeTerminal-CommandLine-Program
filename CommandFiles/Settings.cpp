
void ColourForegroundSwitch(int*, std::string*, std::string*);
void ColourBackgroundSwitch(int*, std::string*, std::string*);
std::string wordWrap(std::string);
bool EnableVTMode();
void colour(std::string, std::string);
bool YesNo(std::string);
void Exiting();
long double NumInput(std::string);
std::string StrInput(std::string);
void SetCursorAttributes();
void colourSubheading();
void ColourTypeSwitch();

extern ConfigFileSystem ConfigObjMain;
extern bool bAnsiVTSequences;

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
			if (nChoice == -1) {
				Exiting();
				return;
			}
			std::cout << std::endl;
		}
		
		ColourForegroundSwitch(&nChoice, &ConfigObjMain.sColourHighlightBack, &ConfigObjMain.sColourHighlight);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Highlight foreground colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nResult == 2) {

		if (nChoice == 0) {
			OptionSelectEngine oseColourBack;
			oseColourBack.nSizeOfOptions = 16;
			oseColourBack.sOptions = sOptionsColour;

			nChoice = oseColourBack.OptionSelect("Please choose your desired highlight background colour below:", " ___BACKGROUND COLOUR___ ");
			if (nChoice == -1) {
				Exiting();
				return;
			}
			std::cout << std::endl;
		}

		ColourBackgroundSwitch(&nChoice, &ConfigObjMain.sColourHighlightBack, &ConfigObjMain.sColourHighlight);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Highlight background colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nResult == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	else {
		VerbosityDisplay("In HighlightColourSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
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
			if (nChoice == -1) {
				Exiting();
				return;
			}
			std::cout << std::endl;
		}

		ColourForegroundSwitch(&nChoice, &ConfigObjMain.sColourTitleBack, &ConfigObjMain.sColourTitle);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Title foreground colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nResult == 2) {

		if (nChoice == 0) {
			OptionSelectEngine oseColourBack;
			oseColourBack.nSizeOfOptions = 16;
			oseColourBack.sOptions = sOptionsColour;

			nChoice = oseColourBack.OptionSelect("Please choose your desired title background colour below:", " ___BACKGROUND COLOUR___ ");
			if (nChoice == -1) {
				Exiting();
				return;
			}
			std::cout << std::endl;
		}

		ColourBackgroundSwitch(&nChoice, &ConfigObjMain.sColourTitleBack, &ConfigObjMain.sColourTitle);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Title background colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nResult == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	else {
		VerbosityDisplay("In TitleColourSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
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

		nResult = oseSubheading.OptionSelect("Please select what you want to do for Subheading Colour:", " ___SUBHEADING COLOUR SETTINGS___ ");
	}


	if (nResult == 1)
	{
		if (nChoice == 0) {
			OptionSelectEngine oseColourFore;
			oseColourFore.nSizeOfOptions = 16;
			oseColourFore.sOptions = sOptionsColour;

			nChoice = oseColourFore.OptionSelect("Please choose your desired subheading foreground colour below:", " ___FOREGROUND COLOUR___ ");
			if (nChoice == -1) {
				Exiting();
				return;
			}
			std::cout << std::endl;
		}

		ColourForegroundSwitch(&nChoice, &ConfigObjMain.sColourSubheadingBack, &ConfigObjMain.sColourSubheading);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Subheading foreground colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nResult == 2) {

		if (nChoice == 0) {
			OptionSelectEngine oseColourBack;
			oseColourBack.nSizeOfOptions = 16;
			oseColourBack.sOptions = sOptionsColour;

			nChoice = oseColourBack.OptionSelect("Please choose your desired background colour below:", " ___BACKGROUND COLOUR___ ");
			if (nChoice == -1) {
				Exiting();
				return;
			}
			std::cout << std::endl;
		}

		ColourBackgroundSwitch(&nChoice, &ConfigObjMain.sColourSubheadingBack, &ConfigObjMain.sColourSubheading);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Subheading background colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nResult == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	else {
		VerbosityDisplay("In SubheadingColourSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
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
	}
	

	if (nChoice == 1) {
		ConfigObjMain.bDisplayVerboseMessages = true;
		// Write to configuration file immediately
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Verbosity Messages have been enabled successfully.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nChoice == 2) {
		ConfigObjMain.bDisplayVerboseMessages = false;
		// Write to configuration file immediately
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Verbosity Messages have been disabled successfully.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nChoice == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else {
		VerbosityDisplay("In VerboseMessagesSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
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

		nChoice = oseDirections.OptionSelect("Please select your desired option for the Direction Messages setting: ", " ___DIRECTION MESSAGES SETTINGS___ ");
	}
	

	if (nChoice == 1) {
		ConfigObjMain.bDisplayDirections = true;
		// Write to configuration file immediately
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Direction (Help) Messages have been enabled successfully.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else if (nChoice == 2) {
		ConfigObjMain.bDisplayDirections = false;
		// Write to configuration file immediately
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Direction (Help) Messages have been disabled successfully.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;

	}
	else if (nChoice == -1) {
		// Warn user that setting modification is terminated.
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	else {
		// Warn user that error occured.
		VerbosityDisplay("In DirectionMessagesSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
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

		nChoice = oseAnsi.OptionSelect("Please select your desired option for the ANSI setting:", " ___ANSI SETTINGS___ ");
	}
	

	if (nChoice == 1) {
		if (EnableVTMode() != false) 
		{
			bAnsiVTSequences = true;
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			// Set new colours
			ColourTypeSwitch();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			cls(); // Set colours to whole screen

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "ANSI VT sequences successfully enabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return;
		}
		else {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Sorry, you cannot enable ANSI escape codes as your terminal doesn't support it.") << std::endl;
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Exiting...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return;
		}

	}
	else if (nChoice == 2) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("WARNING: This WILL disable RGB colours AND text formatting from the point of this message.") << '\n';
		
		if (YesNo(wordWrap("Would you like to proceed? [y/n] > "))) 
		{
			bAnsiVTSequences = false;
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			// Set new colours
			ColourTypeSwitch();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			cls(); // Set to whole screen

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "ANSI VT sequences successfully disabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
	}
	else if (nChoice == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}
	else {
		VerbosityDisplay("In AnsiSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

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
		ConfigObjMain.bWordWrapToggle = true;
		// Write to configuration file immediately
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Word Wrapping has been enabled successfully.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}
	else if (nChoice == 2) {
		ConfigObjMain.bWordWrapToggle = false;
		// Write to configuration file immediately
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Word Wrapping has been disabled successfully.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}
	else if (nChoice == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying setting terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}
	else {
		VerbosityDisplay("In WordWrapSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

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
					colour(RED, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("Sorry, but this setting cannot be modified without terminal ANSI VT support.") << '\n';
					Exiting();
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
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
			ConfigObjMain.bCursorBlink = true;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor Blinking has been enabled successfully.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			

			return;
		}
		else if (nChoiceBlink == 2) {
			ConfigObjMain.bCursorBlink = false;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor Blinking has been disabled successfully.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceBlink == -1) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else {
			VerbosityDisplay("In CursorSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Enable/Disable Cursor Blinking\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

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
			ConfigObjMain.bShowCursor = true;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'visible'.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceShow == 2) {
			ConfigObjMain.bShowCursor = false;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'hidden'.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceShow == -1) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else {
			VerbosityDisplay("In CursorSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Show/Hide Cursor\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

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
			if (ConfigObjMain.bCursorBlink == true) ConfigObjMain.nCursorShape = 1; else ConfigObjMain.nCursorShape = 2;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'block'.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceShape == 2) {
			if (ConfigObjMain.bCursorBlink == true) ConfigObjMain.nCursorShape = 3; else ConfigObjMain.nCursorShape = 4;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'underline'.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceShape == 3) {
			if (ConfigObjMain.bCursorBlink == true) ConfigObjMain.nCursorShape = 5; else ConfigObjMain.nCursorShape = 6;
			// Set cursor attributes immediately
			SetCursorAttributes();
			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Cursor has successfully been set to 'bar'.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceShape == -1) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else {
			VerbosityDisplay("In CursorSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Cursor Shape\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}

	// Exit
	else if (nChoice == -1) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Modifying settings terminated.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Error
	else {
		VerbosityDisplay("In CursorSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
	}
}

void OtherSettings(short int nChoice = 0, int nChoiceSlowChSpeed = 0, bool bFromArg = false , short int nChoiceRandColStartup = 0, short int nTermCustomThemeSupport = 0, short int nReadableContrast = 0, std::string sTempConfigFileDir = "") {

	// Standard interface
	if (nChoice == 0) {
		OptionSelectEngine oseOther;
		oseOther.nSizeOfOptions = 5;
		std::string sOptions[] = {
			"SlowChar Speed Value",
			"Enable/Disable Random Colours on Startup",
			"Enable/Disable Terminal Custom Theme Support",
			"Enable/Disable Readable Colour Contrast",
			"Temporary Custom Config File Directory"
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
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nDefault Speed: 45\nCurrent Speed: " << ConfigObjMain.nSlowCharSpeed << "\n\n" << wordWrap("Input 0 to disable SlowChar entirely, and input a negative number to exit.") << '\n';

			nChoiceSlowChSpeed = NumInput("Please input how fast you want SlowChar to be: > ");
		}

		if (nChoiceSlowChSpeed < 0) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return;
		}

		ConfigObjMain.nSlowCharSpeed = nChoiceSlowChSpeed;
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "SlowChar Speed has successfully been set to " << ConfigObjMain.nSlowCharSpeed << "ms (per char).\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

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
			ConfigObjMain.bRandomColoursOnStartup = true;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Random Colours on Startup Enabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceRandColStartup == 2) {
			ConfigObjMain.bRandomColoursOnStartup = false;
			ConfigObjMain.WriteConfigFile();
			
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Random Colours on Startup Disabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nChoiceRandColStartup == -1) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Enable/Disable Random Colours on Startup\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

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
			ConfigObjMain.bTermCustomThemeSupport = true;
			ConfigObjMain.WriteConfigFile();

			// Clear screen FULLY to make changes take effect
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			cls();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Terminal Custom Theme Support Enabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nTermCustomThemeSupport == 2) {
			ConfigObjMain.bTermCustomThemeSupport = false;
			ConfigObjMain.WriteConfigFile();

			// Clear screen FULLY to make changes take effect
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			cls();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Terminal Custom Theme Support Disabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else if (nTermCustomThemeSupport == -1) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying setting terminated.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Enable/Disable Terminal Custom Theme Support\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}

	// Enable Readable Colour Contrast
	else if (nChoice == 4) {

		// Non-argument UI
		if (nReadableContrast == 0) {

			OptionSelectEngine oseReadableContrast;
			oseReadableContrast.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable Auto-Readable Colour Contrast (DEFAULT)",
				"Disable Auto-Readable Colour Contrast"
			};
			oseReadableContrast.sOptions = sOptions;

			nReadableContrast = oseReadableContrast.OptionSelect("Please select desired option for Auto-Readable Colour Contrast:", " __AUTO-READABLE CONTRAST SETTINGS__");

		}

		// Enable
		if (nReadableContrast == 1) {
			// Enable the setting
			ConfigObjMain.bAutoReadableContrast = true;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nAuto-Readable Colour Contrast enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Disable
		else if (nReadableContrast == 2) {
			// Disable the setting
			ConfigObjMain.bAutoReadableContrast = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nAuto-Readable Colour Contrast disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Exit
		else if (nReadableContrast == -1) {
			Exiting();
			return;
		}

		// Failed
		else {
			VerbosityDisplay("In TitleColourSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Enable/Disable Readable Colour Contrast\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}

		return;
	}

	// Temporary Custom Config File Directory
	else if (nChoice == 5) 
	{
		// Normal User UI
		if (sTempConfigFileDir == "") {
			std::cout << '\n';
			CentreColouredText(" ___CUSTOM CONFIG FILE DIR___ ", 1);
			std::cout << "\n\n";
			sTempConfigFileDir = StrInput("Please input your desired custom config file directory (0 to exit, \"^open\" to use Windows File Dialogue): > ");

			if (sTempConfigFileDir == "0") {
				Exiting();
				return;
			}
			else if (sTempConfigFileDir == "^open") {
				FileOpenGUIEngine CustomDir;
				if (CustomDir.FileOpenDialogue("Select a Configuration File of Choice") == false) {
					Exiting();
					return;
				}

				// Assign file name from file dialogue to input string
				sTempConfigFileDir = CustomDir.GetFileName();
				
				// User cancelled if string is empty
				if (sTempConfigFileDir == "") {
					Exiting();
					return;
				}
			}

			// Check for speechmarks in case of copy from file explorer
			if (sTempConfigFileDir[0] == '"' && sTempConfigFileDir[sTempConfigFileDir.length() - 1] == '"') {
				sTempConfigFileDir = sTempConfigFileDir.substr(1, (sTempConfigFileDir.length() - 2));
			}
		}

		// Test user input
		std::ifstream TestConfigIn(sTempConfigFileDir);
		if (TestConfigIn.fail()) {
			// Output error message
			VerbosityDisplay("In OtherSettings(): ERROR - File validation failed. Possibly incorrect file or file directory invalid, or inaccessible/nonexistent file.\n");
			UserErrorDisplay("ERROR - File could not be opened. Please make sure the file directory is valid, and try again later.\n");
			Exiting();
			TestConfigIn.close();
			return;
		}
		else {
			VerbosityDisplay("In OtherSettings(): Note - Custom Config File Dir Setting Check - Passed.\n");
		}

		// Assign directory to main config file object
		ConfigObjMain.sConfigFileUserLocation = sTempConfigFileDir;
		// Read new config file immediately
		ConfigObjMain.ReadConfigFile();
		// Make sure it still works
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Temporary directory successfully set to ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\"' << sTempConfigFileDir << '\"';
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << ".\n";

		return;
	}

	// Terminated
	else if (nChoice == -1) {
		Exiting();

		return;
	}

	// Error
	else {
		VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
	}

	return;
}