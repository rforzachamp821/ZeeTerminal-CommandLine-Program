//
// Settings.cpp - Responsible for modifying settings in ZeeTerminal.
//

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

			nChoice = oseColourFore.OptionSelect("Please choose your desired highlight foreground colour below:\n(Currently set to: " + ColourToDisplayColour(ConfigObjMain.sColourHighlight) + ")", " ___FOREGROUND COLOUR___ ");
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

			nChoice = oseColourBack.OptionSelect("Please choose your desired highlight background colour below:\n(Currently set to: " + ColourToDisplayColour(ConfigObjMain.sColourHighlightBack) + ")", " ___BACKGROUND COLOUR___ ");
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

			nChoice = oseColourFore.OptionSelect("Please choose your desired title foreground colour below:\n(Currently set to: " + ColourToDisplayColour(ConfigObjMain.sColourTitle) + ")", " ___FOREGROUND COLOUR___ ");
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

			nChoice = oseColourBack.OptionSelect("Please choose your desired title background colour below:\n(Currently set to: " + ColourToDisplayColour(ConfigObjMain.sColourTitleBack) + ")", " ___BACKGROUND COLOUR___ ");
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

			nChoice = oseColourFore.OptionSelect("Please choose your desired subheading foreground colour below:\n(Currently set to: " + ColourToDisplayColour(ConfigObjMain.sColourSubheading) + ")", " ___FOREGROUND COLOUR___ ");
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

			nChoice = oseColourBack.OptionSelect("Please choose your desired subheading background colour below:\n(Currently set to: " + ColourToDisplayColour(ConfigObjMain.sColourSubheadingBack) + ")", " ___BACKGROUND COLOUR___ ");
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

		nChoice = oseVerbose.OptionSelect("Please select your desired option for the Verbose Messages setting:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bDisplayVerboseMessages) + ")", " ___VERBOSE MESSAGES SETTINGS___ ");
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

		nChoice = oseDirections.OptionSelect("Please select your desired option for the Direction Messages setting:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bDisplayDirections) + ")", " ___DIRECTION MESSAGES SETTINGS___ ");
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

		nChoice = oseAnsi.OptionSelect("Please select your desired option for the ANSI setting:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bAnsiVTSequences) + ")", " ___ANSI SETTINGS___ ");
	}
	

	if (nChoice == 1) {
		if (EnableVTMode() != false) 
		{
			ConfigObjMain.bAnsiVTSequences = true;
			bAnsiVTSequences = true;

			// Write to config file immediately
			ConfigObjMain.WriteConfigFile();

			// Set new colours
			ColourTypeSwitch(); // This will write to config file by default
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			cls(); // Set colours to whole screen

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "ANSI VT sequences successfully enabled.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return;
		}
		else {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Sorry, you cannot enable ANSI escape codes as your terminal doesn't support it.");
			Exiting();
			return;
		}

	}
	else if (nChoice == 2) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("WARNING: This WILL disable RGB colours AND text formatting from the point of this message.\nThis will also revert any custom RGB values to default.\nRGB Colour Presets will NOT be affected.\n");
		
		if (YesNoInput(wordWrap("Would you like to proceed? [y/n] > ")))
		{
			ConfigObjMain.bAnsiVTSequences = false;
			bAnsiVTSequences = false;

			// Write to config file immediately
			ConfigObjMain.WriteConfigFile();

			// Set new colours
			ColourTypeSwitch(); // This will write to config file by default
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

		nChoice = oseWordWrap.OptionSelect("Please select your desired option for Word Wrapping:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bWordWrapToggle) + ")", " ___WORD WRAP SETTINGS___ ");
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

void CursorSettings(short int nChoice = 0, short int nChoiceBlink = 0, short int nChoiceShow = 0, long long int nChoiceShape = 0) {

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

			nChoiceBlink = oseBlink.OptionSelect("Please select your desired option for the Cursor Blinking Setting:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bCursorBlink) + ")", " ___CURSOR BLINKING SETTINGS___ ");
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

			std::string sCurrent = "";
			// For displaying current configuration
			if (ConfigObjMain.bShowCursor == true) {
				sCurrent = "Visible";
			}
			else sCurrent = "Hidden";

			nChoiceShow = oseShow.OptionSelect("Please select your desired option for cursor visibility:\n(Currently set to: " + sCurrent + ")", " ___CURSOR VISIBILITY SETTINGS___ ");
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

			// For displaying current configuration
			std::string sCurrent = "";
			if (ConfigObjMain.nCursorShape == 1 || ConfigObjMain.nCursorShape == 2) {
				sCurrent = "Block Shape";
			}
			else if (ConfigObjMain.nCursorShape == 3 || ConfigObjMain.nCursorShape == 4) {
				sCurrent = "Underline-style Shape";
			}
			else if (ConfigObjMain.nCursorShape == 5 || ConfigObjMain.nCursorShape == 6) {
				sCurrent = "Bar Shape";
			}

			nChoiceShape = oseShape.OptionSelect("Please select your desired shape for the console cursor:\n(Currently set to: " + sCurrent + ")", " ___CURSOR SHAPE SETTINGS___ ");
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

void LogFileSystemSettings(short int nChoice = 0, short int nChoiceLogging = 0, short int nChoiceVerboseLogging = 0, short int nChoiceUserErrorLogging = 0, short int nChoiceCommandLogging = 0, short int nChoiceUserInputLogging = 0)
{
	OptionSelectEngine oseLogFileSettings;

	// User UI
	if (nChoice == 0) {
		oseLogFileSettings.nSizeOfOptions = 5;
		std::string sOptions[] = {
			"Fully Enable/Disable ZeeTerminal Logging",
			"Toggle Verbose Message Logging",
			"Toggle User-Space Error Logging",
			"Toggle Command Input Info Logging",
			"Toggle User Input Info Logging"
		};
		oseLogFileSettings.sOptions = sOptions;

		nChoice = oseLogFileSettings.OptionSelect("Please select what setting you would like to modify for the LogFile System:", "___LOGFILE SYSTEM SETTINGS___");
	}

	// Fully Enable/Disable ZeeTerminal Logging
	if (nChoice == 1)
	{
		if (nChoiceLogging == 0)
		{
			oseLogFileSettings.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable ZeeTerminal Logging",
				"Disable ZeeTerminal Logging (Default)"
			};
			oseLogFileSettings.sOptions = sOptions;

			nChoiceLogging = oseLogFileSettings.OptionSelect("This option overrides all logging settings and acts as a master switch.\nPlease select your option for enabling/disabling ZeeTerminal logging:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bEnableLogging) + ")", "___ENABLE/DISABLE ZEETERMINAL LOGGING___");
		}

		// Enable
		if (nChoiceLogging == 1)
		{
			// Enable the setting
			ConfigObjMain.bEnableLogging = true;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nZeeTerminal Logging enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Disable
		else if (nChoiceLogging == 2)
		{
			// Enable the setting
			ConfigObjMain.bEnableLogging = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nZeeTerminal Logging disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Exit
		else if (nChoiceLogging == -1)
		{
			Exiting();
			return;
		}

		// Error
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}
	else if (nChoice == 2)
	{
		if (nChoiceVerboseLogging == 0)
		{
			oseLogFileSettings.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable Verbose Message Logging (Default)",
				"Disable Verbose Message Logging"
			};
			oseLogFileSettings.sOptions = sOptions;

			nChoiceVerboseLogging = oseLogFileSettings.OptionSelect("Please select your option for toggling Verbose Message logging:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bVerboseMessageLogging) + ")", "___TOGGLE VERBOSE MESSAGE LOGGING___");
		}

		// Enable
		if (nChoiceVerboseLogging == 1)
		{
			// Enable the setting
			ConfigObjMain.bVerboseMessageLogging = true;
			LogFileMain.UpdateEntryLineOnNextWrite();
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nVerbose Message Logging enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Disable
		else if (nChoiceVerboseLogging == 2)
		{
			// Enable the setting
			ConfigObjMain.bVerboseMessageLogging = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nVerbose Message Logging disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Exit
		else if (nChoiceVerboseLogging == -1)
		{
			Exiting();
			return;
		}

		// Error
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}
	else if (nChoice == 3)
	{
		if (nChoiceUserErrorLogging == 0)
		{
			oseLogFileSettings.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable User-space Error Message Logging",
				"Disable User-space Error Message Logging (Default)"
			};
			oseLogFileSettings.sOptions = sOptions;

			nChoiceUserErrorLogging = oseLogFileSettings.OptionSelect("Please select your option for toggling User-space Error Message logging:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bUserSpaceErrorLogging) + ")", "___TOGGLE USER-SPACE ERROR MESSAGE LOGGING___");
		}

		// Enable
		if (nChoiceUserErrorLogging == 1)
		{
			// Enable the setting
			ConfigObjMain.bUserSpaceErrorLogging = true;
			LogFileMain.UpdateEntryLineOnNextWrite();
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nUser-space Error Message Logging enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Disable
		else if (nChoiceUserErrorLogging == 2)
		{
			// Enable the setting
			ConfigObjMain.bUserSpaceErrorLogging = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nUser-space Error Message Logging disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Exit
		else if (nChoiceUserErrorLogging == -1)
		{
			Exiting();
			return;
		}

		// Error
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}
	else if (nChoice == 4)
	{
		if (nChoiceCommandLogging == 0)
		{
			oseLogFileSettings.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable Command Input Info Logging (Default)",
				"Disable Command Input Info Logging"
			};
			oseLogFileSettings.sOptions = sOptions;

			nChoiceCommandLogging = oseLogFileSettings.OptionSelect("Please select your option for toggling Command Input Info logging:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bCommandInputInfoLogging) + ")", "___TOGGLE COMMAND INPUT INFO LOGGING___");
		}

		// Enable
		if (nChoiceCommandLogging == 1)
		{
			// Enable the setting
			ConfigObjMain.bCommandInputInfoLogging = true;
			LogFileMain.UpdateEntryLineOnNextWrite();
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nCommand Input Info Logging enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Disable
		else if (nChoiceCommandLogging == 2)
		{
			// Enable the setting
			ConfigObjMain.bCommandInputInfoLogging = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nCommand Input Info Logging disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Exit
		else if (nChoiceCommandLogging == -1)
		{
			Exiting();
			return;
		}

		// Error
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}
	else if (nChoice == 5)
	{
		if (nChoiceUserInputLogging == 0)
		{
			oseLogFileSettings.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Enable User Input Info Logging",
				"Disable User Input Info Logging (Default)"
			};
			oseLogFileSettings.sOptions = sOptions;

			nChoiceUserInputLogging = oseLogFileSettings.OptionSelect("Please select your option for toggling User Input Info logging:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bUserInputInfoLogging) + ")", "___TOGGLE USER INPUT INFO LOGGING___");
		}

		// Enable
		if (nChoiceUserInputLogging == 1)
		{
			// Enable the setting
			ConfigObjMain.bUserInputInfoLogging = true;
			LogFileMain.UpdateEntryLineOnNextWrite();
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nUser Input Info Logging enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Disable
		else if (nChoiceUserInputLogging == 2)
		{
			// Enable the setting
			ConfigObjMain.bUserInputInfoLogging = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nUser Input Info Logging disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Exit
		else if (nChoiceUserInputLogging == -1)
		{
			Exiting();
			return;
		}

		// Error
		else {
			VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}
	else if (nChoice == -1)
	{
		Exiting();
		return;
	}
	else
	{
		VerbosityDisplay("In OtherSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
	}
}

void OtherSettings(short int nChoice = 0, long long int nChoiceSlowChSpeed = 0, bool bFromArg = false , short int nChoiceRandColStartup = 0, short int nTermCustomThemeSupport = 0, short int nReadableContrast = 0, std::string sTempConfigFileDir = "", short int nChoiceNewOptionSelect = 0) {

	// Standard interface
	if (nChoice == 0) {
		OptionSelectEngine oseOther;
		oseOther.nSizeOfOptions = 6;
		std::string sOptions[] = {
			"SlowChar Speed Value",
			"Enable/Disable Random Colours on Startup",
			"Enable/Disable Terminal Custom Theme Support",
			"Enable/Disable Readable Colour Contrast",
			"Temporary Custom Config File Directory",
			"Use New OptionSelect Session Style"
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
			std::cout << "\nDefault Speed: 32\nCurrent Speed: " << ConfigObjMain.nSlowCharSpeed << wordWrap("\n\nInput 0 to disable SlowChar entirely, and input a negative number to exit.") << '\n';

			nChoiceSlowChSpeed = NumInputll("Please input how fast you want SlowChar to be: > ");
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

			nChoiceRandColStartup = oseRandCol.OptionSelect("Please select your choice for Random Colours on Startup:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bRandomColoursOnStartup) + ")", " ___RANDOM COLOUR ON STARTUP SETTINGS___ ");
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

			nTermCustomThemeSupport = oseRandCol.OptionSelect("Note: This works by making the black background colour the stock terminal emulator colour (that ZeeTerminal is running on).\nPlease select your choice for Terminal Custom Theme Support:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bTermCustomThemeSupport) + ")", " ___TERMINAL CUSTOM THEME SETTINGS___ ");
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
				"Enable Auto-Readable Colour Contrast (Default)",
				"Disable Auto-Readable Colour Contrast"
			};
			oseReadableContrast.sOptions = sOptions;

			nReadableContrast = oseReadableContrast.OptionSelect("Please select desired option for Auto-Readable Colour Contrast:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bAutoReadableContrast) + ")", " __AUTO-READABLE CONTRAST SETTINGS__");

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

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nThis setting will only take effect for this session.\n");

			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("ZeeTerminal will treat the config file as it treats any other one. If ANY values are incorrect, they are either converted to values that are compatible with the current session, or overwritten with defaults if that's not possible.\n\nCurrent Directory: \"" + ConfigObjMain.sConfigFileUserLocation + "\"\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			sTempConfigFileDir = StrInput("Please input your desired custom config file directory (0 to exit, \"*open\" to use Windows File Dialogue): > ");

			if (sTempConfigFileDir == "0") {
				Exiting();
				return;
			}
		}

		if (sTempConfigFileDir == "*open") {
			FileOpenGUIEngine CustomDir;

			// Notify user of file dialogue opening
			std::cout << wordWrap("Opening with the Windows File Dialogue...\n");

			// Display the window
			if (CustomDir.FileOpenDialogue("Select a Configuration File of Choice") == false) {
				Exiting();
				return;
			}

			// Assign file name from file dialogue to input string
			sTempConfigFileDir = CustomDir.GetRetrievedPathName();

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
		// Check to make sure colours are correct for the session using ColourTypeSwitch().
		ColourTypeSwitch();
		// Write new values to the new config file
		ConfigObjMain.WriteConfigFile();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Temporary directory successfully set to ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\"' << sTempConfigFileDir << '\"';
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << ".\n";

		return;
	}

	// Use New OptionSelect Session Style
	else if (nChoice == 6) {

		// Non-argument UI
		if (nChoiceNewOptionSelect == 0) {

			OptionSelectEngine oseNewOptionSelect;
			oseNewOptionSelect.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"Use New OptionSelect Session Style",
				"DO NOT Use New OptionSelect Session Style"
			};
			oseNewOptionSelect.sOptions = sOptions;

			nChoiceNewOptionSelect = oseNewOptionSelect.OptionSelect("Please select if you want to use or not use the new OptionSelect Session Style:\n(Currently set to: " + SettingsBoolToString(ConfigObjMain.bUseNewOptionSelect) + ")", " __OPTIONSELECT SESSION STYLE SETTINGS__");
		}

		if (nChoiceNewOptionSelect == 1) {
			ConfigObjMain.bUseNewOptionSelect = true;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "New OptionSelect Session Style Enabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoiceNewOptionSelect == 2) {
			ConfigObjMain.bUseNewOptionSelect = false;
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "New OptionSelect Session Style Disabled!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoiceNewOptionSelect == -1) {
			Exiting();
			return;
		}
		else {
			VerbosityDisplay("In TitleColourSettings() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect(), in setting \"Use New OptionSelect Session Style\".\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
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
