//
// CommandsFile.cpp - All command code is here.
//


#include "CommandFileAssets.cpp"
#include "CalculationAlgorithm.cpp"
#include "Settings.cpp"
#include "CPUStress.cpp"
#include "CommandHelpMessages.cpp"


// External variable definitions
extern std::string				sCommandInputRAW;
extern std::string				sStringOptionCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
																		 // on multi-argument commands.
extern std::string				sStringDataCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
																	   // on multi-argument commands.
extern RGBColourPresetSystem	RGBPreset[3];
extern ConfigFileSystem			ConfigObjMain;
extern NotesSystem				NotesMain;
extern LogFileSystem			LogFileMain;
extern bool						bAnsiVTSequences;
extern bool						bDisp;

extern uint64_t					nNumOfInputtedCommands;
extern uint64_t					nNumOfSuccessfulInputtedCommands;

void Commands(const std::string, char*, const std::string);
void help(bool);


// Tutorial function
void Tutorial() {
	std::string sInput;
	cls();

	CentreColouredText(" ___TUTORIAL___ ", 1);
	std::cout << '\n';
	CentreColouredText(" Understand how this terminal operates with this tutorial. ", 2);
	std::cout << "\n\n";

	sleep(750);
	slowcolourfn(LBLU, ConfigObjMain.sColourGlobalBack, "Using this terminal is very straightforward, and all terminals are similar in some way.");
	sleep(500);
	slowcolourfn(GRN, ConfigObjMain.sColourGlobalBack, "\nFirstly, let's begin with the normal terminal screen. This is what it would look like before typing a command:\n\n");
	sleep(150);
	std::cout << "Command: > \n\n";
	sleep(1000);
	slowcolourfn(YLW, ConfigObjMain.sColourGlobalBack, "The 'Help' command tells us what commands are in this terminal.\n");
	sleep(150);
	
	// Input 'help' to continue
	while (true) {
		slowcolourfn(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack, "Type in \"Help\" to execute this command: > ");
		sInput = StrInput("");

		// Change all input characters to lowercase and remove spaces
		for (int i = 0; i < sInput.length(); i++) {
			if (sInput[i] == ' ') {
				std::cout << sInput.erase(i, 1) << '\n';
				if (i == 0) i = -1; // as counting from start of string shouldn't start on the spaces, and -1 to counteract i++
				else i--;

				continue;
			}
			else sInput[i] = std::tolower(sInput[i]);
		}

		if (sInput == "help") {
			bool bPreviousHelpMsg = ConfigObjMain.bDisplayDirections;
			ConfigObjMain.bDisplayDirections = true; // only temporary; gets put back to normal next 2 lines
			help(true);
			ConfigObjMain.bDisplayDirections = bPreviousHelpMsg;
			break;
		}
		else {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "Please try again.\n";
		}
	}
	slowcharfn(false, "\nThat previous command also taught you how to use the ScreenNavigate engine.\nYou can move left and right between 'screens' using the the ");
	slowcolourfn(LCYN, ConfigObjMain.sColourGlobalBack, "A, D and left/right arrow keys");
	slowcharfn(true, ", to look through any information provided.\n");
	
	// OptionSelect Engine Tutorial
	sleep(1000);
	slowcolourfn(GRN, ConfigObjMain.sColourGlobalBack, "\nNow is the next step, the OptionSelect engine.\nThis will teach you how to select options in this terminal.\n");
	sleep(500);
	slowcharfn(true, "\nYou will be given a set of options each time this engine is used.");
	sleep(500);
	slowcolourfn(LCYN, ConfigObjMain.sColourGlobalBack, "To select an option, you will have to use the ");
	slowcolourfn(GRN, ConfigObjMain.sColourGlobalBack, "W key/up-arrow key");
	slowcolourfn(LCYN, ConfigObjMain.sColourGlobalBack, " to move the index up, or the ");
	slowcolourfn(GRN, ConfigObjMain.sColourGlobalBack, "S key/down-arrow key");
	slowcolourfn(LCYN, ConfigObjMain.sColourGlobalBack, " to move the index down.\n");
	sleep(700);
	OptionSelectEngine oseTutorial;
	oseTutorial.nSizeOfOptions = 3;
	std::string sOptions[] = {
		"Option 1",
		"Option 2",
		"Option 3"
	};
	oseTutorial.sOptions = sOptions;
	oseTutorial.SetDirectionsText("Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit the whole tutorial completely.");

	bool bPreviousHelpMsg = ConfigObjMain.bDisplayDirections;
	ConfigObjMain.bDisplayDirections = true; // only temporary; gets put back to normal afterwards

	// Start option 1
	int nOption1 = 0;
	while (nOption1 != 1) {
		nOption1 = oseTutorial.OptionSelect("Please select Option 1 from the set of options:", "___OPTIONSELECT TUTORIAL___");
		switch (nOption1) {
		case 1:
			slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "\nThat is correct!\n\n");
			break;
		case 2:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nIncorrect. Look carefully for Option 1, and try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sleep(500);
			break;
		case 3:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nIncorrect. Look carefully for Option 1, and try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sleep(500);
			break;
		case -1:
			// Put help messages setting back to original value
			ConfigObjMain.bDisplayDirections = bPreviousHelpMsg;
			Exiting();

			return;
		default:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "An unknown error occured. Please try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			break;
		}
	}

	sleep(780);
	// Start option 2
	int nOption2 = 0;
	while (nOption2 != 2) {
		nOption2 = oseTutorial.OptionSelect("Please select Option 2 from the set of options:", "___OPTIONSELECT TUTORIAL___");
		switch (nOption2) {
		case 1:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nIncorrect. Look carefully for Option 2, and try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sleep(500);
			break;
		case 2:
			slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "\nThat is correct!!\n\n");
			break;
		case 3:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nIncorrect. Look carefully for Option 2, and try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sleep(500);
			break;

		case -1:
			// Put help messages setting back to original value
			ConfigObjMain.bDisplayDirections = bPreviousHelpMsg;
			Exiting();

			return;
		default:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "An unknown error occured. Please try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			break;
		}
	}

	// Start option 3
	sleep(780);
	int nOption3 = 0;
	while (nOption3 != 3) {
		nOption3 = oseTutorial.OptionSelect("Please select Option 3 from the set of options:", "___OPTIONSELECT TUTORIAL___");
		switch (nOption3) {
		case 1:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nIncorrect. Look carefully for Option 3, and try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sleep(500);
			break;
		case 2:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nIncorrect. Look carefully for Option 3, and try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			sleep(500);
			break;
		case 3:
			slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "\nThat is correct!!!\n\n");
			break;
		case -1:
			// Put help messages setting back to original value
			ConfigObjMain.bDisplayDirections = bPreviousHelpMsg;
			Exiting();

			return;
		default:
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "An unknown error occured. Please try again.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			break;
		}
	}
	// Put help messages setting back to original value
	ConfigObjMain.bDisplayDirections = bPreviousHelpMsg;

	// Yes/No prompt tutorial
	sleep(750);
	slowcolourfn(GRN, ConfigObjMain.sColourGlobalBack, "\nNow for the final tutorial: the Yes/No prompt.\n\n");
	sleep(500);
	slowcharfn(true, "Yes/No prompts are incredibly important, as they manage the most important terminal functions.");
	sleep(500);
	slowcolourfn(LCYN, ConfigObjMain.sColourGlobalBack, "\nThey require you to input the letter 'y' (for yes) or the letter 'n' (for no).\n");
	sleep(500);
	slowcolourfn(YLW, ConfigObjMain.sColourGlobalBack, "\nHere is a yes/no prompt. Answer 'y' for this:\n\n");

	// The yes prompt
	bool bInput = false;
	while (bInput != true) {
		bInput = YesNoInput("Is this program called ZeeTerminal? [y/n] > ");
		if (bInput == true) {
			slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "Well done!\n\n");
			break;
		}
		else {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "Incorrect input. Try again by inputting 'y' (for yes).\n\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	}

	// The no prompt
	slowcolourfn(YLW, ConfigObjMain.sColourGlobalBack, "Here is another yes/no prompt. Answer 'n' for this:\n\n");
	while (bInput != false) {
		bInput = YesNoInput("Are you asleep right now? [y/n] > ");
		if (bInput == false) {
			slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "Well done!\n");
			sleep(500);
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nCongratulations, you have finished the tutorial!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			break;
		}
		else {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << "Incorrect input. Try again by inputting 'n' (for no).\n\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	}

	return;
}

// A function that gives an interface to modify the global foreground colour of the terminal.
void ColourForeground(int nChoice = 0) {

	// Execute menu if wrong argument input or no argument
	if (nChoice <= 0 || nChoice > 17) {
		OptionSelectEngine oseColourFore;
		oseColourFore.nSizeOfOptions = 17;
		std::string sOptions[] = {
			"[1] Black",
			"[2] Blue",
			"[3] Green",
			"[4] Aqua",
			"[5] Red",
			"[6] Purple",
			"[7] Yellow",
			"[8] White",
			"[9] Gray",
			"[10] Light Blue",
			"[11] Light Green",
			"[12] Light Aqua",
			"[13] Light Red",
			"[14] Light Purple",
			"[15] Light Yellow",
			"[16] Bright White (DEFAULT)",
			"Custom RGB Colour Code (Advanced)"
		};
		oseColourFore.sOptions = sOptions;

		nChoice = oseColourFore.OptionSelect("Please choose your desired foreground colour below:", " ___FOREGROUND COLOUR___ ");
	}
	else if (nChoice == 17) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Sorry, but changing RGB foreground colours from arguments has been locked in development for a future update.") << "\nExiting...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}



	if (nChoice == 17) {
		short int nRed = 0, nGreen = 0, nBlue = 0;
		int nRGBForegroundColour[3] = { 255,255,255 };

		if (bAnsiVTSequences == false) {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Sorry, you cannot use RGB colours with a non-ANSI compatible terminal. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}

		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nWarning: Although supported program-wide, RGB is still a new and possibly unstable colour method for ZeeTerminal. Be prepared for bugs and issues.")
			<< std::endl;
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Type in a negative number to exit.") << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);


		// Red value
		while (true) {
			nRGBForegroundColour[0] = NumInputi("Please type in Red value: > ");
			if (nRGBForegroundColour[0] > 255) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (nRGBForegroundColour[0] < 0) {
				std::cout << std::endl;
				Exiting();
				return;
			}
			break;
		}

		// Green value
		while (true) {
			nRGBForegroundColour[1] = NumInputi("Please type in Green value: > ");
			if (nRGBForegroundColour[1] > 255) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (nRGBForegroundColour[1] < 0) {
				Exiting();
				return;
			}
			break;
		}

		// Blue value
		while (true) {
			nRGBForegroundColour[2] = NumInputi("Please type in Blue value: > ");
			if (nRGBForegroundColour[2] > 255) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (nRGBForegroundColour[2] < 0) {
				Exiting();
				return;
			}
			break;
		}

		// Output ESC with all the values accumulated
		if (bAnsiVTSequences) {
			// Load values into sColourGlobal
			ConfigObjMain.sColourGlobal =
				std::to_string(nRGBForegroundColour[0]) + ';' +
				std::to_string(nRGBForegroundColour[1]) + ';' +
				std::to_string(nRGBForegroundColour[2]);

			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			// Output finishing message
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Foreground colour successfully set!") << std::endl;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return;
	}
	else if (nChoice == -1) {
		Exiting();
		return;
	}
	else if (nChoice < 1 || nChoice > 17) {
		VerbosityDisplay("In ColourForeground() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

		return;
	}

	ColourForegroundSwitch(&nChoice, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);

	colour(LGRN, ConfigObjMain.sColourGlobalBack);
	std::cout << CentreText("Foreground colour successfully set!") << std::endl;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	return;
}

// A function that gives an interface to modify the global background colour of the terminal.
void ColourBackground(int nChoice = 0) {

	// Execute menu if wrong argument input or no argument
	if (nChoice <= 0 || nChoice > 17) {
		OptionSelectEngine oseColourBack;
		oseColourBack.nSizeOfOptions = 17;
		std::string sOptions[] = {
			"[1] Black (DEFAULT)",
			"[2] Blue",
			"[3] Green",
			"[4] Aqua",
			"[5] Red",
			"[6] Purple",
			"[7] Yellow",
			"[8] White",
			"[9] Gray",
			"[10] Light Blue",
			"[11] Light Green",
			"[12] Light Aqua",
			"[13] Light Red",
			"[14] Light Purple",
			"[15] Light Yellow",
			"[16] Bright White",
			"Custom RGB Colour Code (Advanced)"
		};
		oseColourBack.sOptions = sOptions;

		// Display options
		nChoice = oseColourBack.OptionSelect("Please choose your desired background colour below:", " ___COLOUR___ ");
	}
	else if (nChoice == 17) {
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Sorry, but changing RGB background colours from arguments has been locked in development for a future update.") << "\nExiting...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}


	if (nChoice == 17) {
		short int nRed = 0, nGreen = 0, nBlue = 0;
		int nRGBBackgroundColour[3] = { 0,0,0 };

		if (bAnsiVTSequences == false) {
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Sorry, you cannot use RGB colours with a non-ANSI compatible terminal. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			return;
		}

		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nWarning: Although supported program-wide, RGB is still a new and possibly unstable colour method for ZeeTerminal. Be prepared for bugs and issues.")
			<< std::endl;
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Type in a negative number to exit.") << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);


		// Red value
		while (true) {
			nRGBBackgroundColour[0] = NumInputi("Please type in Red value: > ");
			if (nRGBBackgroundColour[0] > 255) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (nRGBBackgroundColour[0] < 0) {
				Exiting();
				return;
			}
			break;
		}

		// Green value
		while (true) {
			nRGBBackgroundColour[1] = NumInputi("Please type in Green value: > ");
			if (nRGBBackgroundColour[1] > 255) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (nRGBBackgroundColour[1] < 0) {
				Exiting();
				return;
			}
			break;
		}

		// Blue value
		while (true) {
			nRGBBackgroundColour[2] = NumInputi("Please type in Blue value: > ");
			if (nRGBBackgroundColour[2] > 255) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (nRGBBackgroundColour[2] < 0) {
				Exiting();
				return;
			}
			break;
		}

		// Output ESC with all the values accumulated
		if (bAnsiVTSequences) {
			// Load values into ConfigObjMain.sColourGlobalBack
			ConfigObjMain.sColourGlobalBack =
				std::to_string(nRGBBackgroundColour[0]) + ';' +
				std::to_string(nRGBBackgroundColour[1]) + ';' +
				std::to_string(nRGBBackgroundColour[2]);

			// Write to configuration file immediately
			ConfigObjMain.WriteConfigFile();

			// Output finishing message
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Background colour successfully set!") << std::endl;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return;
	}
	else if (nChoice == -1) {
		Exiting();
		return;
	}
	else if (nChoice < 1 || nChoice > 17) {
		VerbosityDisplay("In ColourBackground() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
		UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		return;
	}

	ColourBackgroundSwitch(&nChoice, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);

	// Apply colours to whole screen
	cls();

	colour(LGRN, ConfigObjMain.sColourGlobalBack);
	std::cout << CentreText("Background colour successfully set!") << std::endl;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	return;
}

// A function to give an interface to modify and load RGB colour presets.
void RGBColourPresets() {
	OptionSelectEngine oseRGBPresets;

	// Read config file immediately
	ConfigObjMain.ReadConfigFile();

	// Display options
	while (true) {
		oseRGBPresets.nSizeOfOptions = 3;
		std::string sOptions[] = {
			"Load Preset",
			"Save Preset",
			"Reset all Custom Presets"
		};
		oseRGBPresets.sOptions = sOptions;

		int nOption = oseRGBPresets.OptionSelect("Please select what you want to do with Custom RGB Presets:", " ___CUSTOM RGB PRESETS___ ");

		// Load presets
		if (nOption == 1)
		{
			std::string sOptions[] = {
				"Preset Slot 1 (" + RGBPreset[0].sPresetName + ")",
				"Preset Slot 2 (" + RGBPreset[1].sPresetName + ")",
				"Preset Slot 3 (" + RGBPreset[2].sPresetName + ")"
			};
			oseRGBPresets.sOptions = sOptions;

			// Display load options
			nOption = oseRGBPresets.OptionSelect("Please select which option you want to load:", " ___LOAD CUSTOM PRESET___ ");
			if (nOption == -1) {
				Exiting();
				continue;
			}

			// Display error messages if the RGB preset does not match the current colour-type environment
			if (RGBPreset[nOption - 1].CheckIfAnsiPreset() != bAnsiVTSequences)
			{
				if (RGBPreset[nOption - 1].CheckIfAnsiPreset() == true) {
					colour(YLW, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("Warning: You cannot set ANSI RGB colour presets to an environment using WIN32 colours. Setting preset terminated.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else if (RGBPreset[nOption - 1].CheckIfAnsiPreset() == false) {
					colour(YLW, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("Warning: You cannot set WIN32 colour presets to an environment using ANSI RGB colours. Setting preset terminated.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}

				continue;
			}

			bool bValidColours = true; // Variable that shows if colours are valid or not

			// Set colours and check if bSetByUser is true
			if (RGBPreset[nOption - 1].bSetByUser == true) {
				// Load colours and variables from objects based on nOption - 1 (OptionSelect returns based on 1, not 0)
				ConfigObjMain.sColourGlobal = RGBPreset[nOption - 1].sColourPresetForeground;
				ConfigObjMain.sColourGlobalBack = RGBPreset[nOption - 1].sColourPresetBackground;

				// Check validity of colours
				if (RGBPreset[nOption - 1].CheckIfAnsiPreset() == false) {
					if (ValidateColourStringsWin32() == false) {
						bValidColours = false;
					}
				}
				else if (RGBPreset[nOption - 1].CheckIfAnsiPreset() == true) {
					if (ValidateColourStringsANSI() == false) {
						bValidColours = false;
					}
				}

			}

			// Set colours
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			// Clear screen to set new colours to whole screen
			cls();

			// Warn user that default colours will be set if the preset hasn't been initialised by user
			if (RGBPreset[nOption - 1].bSetByUser == false) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("Warning: This preset is an empty, undefined preset, so nothing will be changed. Please save values to this preset and try again.") << std::endl;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				continue;
			}
			else if (bValidColours == false) 
			{
				// Should be safe to change colours as colours have been validated/reset
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				if (bAnsiVTSequences) {
					std::cout << wordWrap("Warning: This preset contains invalid ANSI string values, so one or all of the colours will be set to default to prevent errors.") << std::endl;
				}
				else {
					std::cout << wordWrap("Warning: This preset contains invalid WIN32 values, so one or all of the colours will be set to default to prevent errors.") << std::endl;
				}

			}

			// Write to config file immediately (for current global colours)
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("RGB Preset successfully loaded!") << std::endl;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Save presets
		else if (nOption == 2) 
		{
			std::string sOptions[] = {
				"Preset Slot 1 (" + RGBPreset[0].sPresetName + ')',
				"Preset Slot 2 (" + RGBPreset[1].sPresetName + ')',
				"Preset Slot 3 (" + RGBPreset[2].sPresetName + ')'
			};
			oseRGBPresets.sOptions = sOptions;

			// Display save options
			nOption = oseRGBPresets.OptionSelect("Please select which option you would like to save the current colour settings to:", " ___SAVE TO RGB PRESET___ ");
			if (nOption == -1) {
				Exiting();
				continue;
			}

			std::string sPresetName = StrInput("Please input a name for Preset " + std::to_string(nOption) + ": > ");

			// Display overwrite message if preset was set by user already
			if (RGBPreset[nOption - 1].bSetByUser == true) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("This RGB preset (" + RGBPreset[nOption - 1].sPresetName + ") is already user-defined and has user-set values.") << std::endl;

				if (!YesNoInput(wordWrap("Are you sure you want to overwrite these values? [y/n] > "))) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Aborted.\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

					continue;
				}
			}

			// Initialise colours and variables in objects based on runtime terminal colours and nOption
			RGBPreset[nOption - 1].sPresetName = sPresetName;
			RGBPreset[nOption - 1].sColourPresetForeground = ConfigObjMain.sColourGlobal;
			RGBPreset[nOption - 1].sColourPresetBackground = ConfigObjMain.sColourGlobalBack;
			// Show that object has been edited and initialised by user's consent
			RGBPreset[nOption - 1].bSetByUser = true;

			// Write to config file immediately
			ConfigObjMain.WriteConfigFile();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("RGB Preset successfully saved!") << std::endl;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		}

		// Reset presets
		else if (nOption == 3) 
		{
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("WARNING: ALL PRESETS MADE BY USER WILL BE DESTROYED AND INITIALISED TO DEFAULT VAULES.") << std::endl;
			if (YesNoInput("Would you like to proceed? [y/n] > ")) {
				// Set all RGBPreset objects to default values
				for (int i = 0; i <= 2; i++) {
					RGBPreset[i].ResetPreset();
					VerbosityDisplay("RGBPreset " + std::to_string((i + 1)) + " has been set to default values.");
				}

				// Write to config file immediately
				ConfigObjMain.WriteConfigFile();

				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "All presets have successfully been set to default values.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Preset deletion aborted.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		// Exit
		else if (nOption == -1) 
		{
			Exiting();
			return;
		}

		// Unknown error
		else {
			VerbosityDisplay("In RGBColourPresets() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}

	return;
}

// A function that displays all help info for the terminal.
// Also has tutorial directions text support.
//
void help(bool bFromTutorial) {
	ScreenNavigateEngine sneHelp;

	sneHelp.nSizeOfScreens = 4;
	std::string sScreens[] =
	{
		"___LIST OF COMMANDS___\n\nTo see more about a command, type in \"<command> -h\". This will work for all commands, except: echo and title.\n\n[1] Help\n[2] Exit\n[3] Tutorial\n[4] Echo\n[5] CLS\n[6] DevTools\n[7] CPUStress\n[8] Colour\n[9] Settings\n[10] Title\n[11] Date\n[12] ColourNumbers\n[13] MediaPlayer\n[14] AudioPlayer\n[15] TTS\n[16] Stopwatch\n[17] Read\n[18] Timer\n[19] Beep\n[20] MessageBox\n[21] Copy\n[22] CopyFile\n[23] TextInfo\n[24] ConfigAction\n[25] BeepSounds\n[26] RickRoll\n[27] ShellExecute\n[28] Hacker\n[29] Calculator\n[30] Logoff\n[31] Shutdown\n[32] Reboot (or Restart)\n[33] Hibernate\n[34] ResetExpl\n[35] MemTest\n[36] RandCol\n[37] Pause\n[38] CommandNum\n[39] SlowChar\n[40] ReverseText\n[41] Notes\n[42] FileParse\n[43] Disp\n[44] SysInfo\n[45] Einstein\n[46] Edison\n[47] Tesla\n[48] Cow\n[49] Cat\n[50] Bunny\n\nMore will be added soon!\n",

		"___FREQUENTLY ASKED QUESTIONS___\n\n"
		"1) I can't see the terminal text. How can I zoom in?\n  1a) You can zoom in, of course. Press and hold the Ctrl button and scroll with the mouse to your desired text size.\n"
		"\n\n2) The error messages shown aren't detailed enough. How do I get better-quality error messages?\n  2a) To get better quality error messages, just enable the Verbosity Messages setting in the Settings command.\n"
		"\n\n3) I'm using the Windows 7 terminal. How do I scroll up and down in the terminal without using the mouse?\n  3a) To scroll up and down without the mouse, press Alt + Space and then the keys 'E' and 'L', and then scroll with the up/down arrow keys. Use the PageUp/PageDown keys to scroll full pages in the terminal.\n"
		"\n\n4) What is the difference between the 'old' and 'new' OptionSelect Session styles?\n  4a) The 'old' style is an inspiration from the TerminalAppGen2, the previous iteration of this program. It is very robust, simple and works by associating a number with each option, which you type in and press ENTER to select.\nThe 'new' style isn't exactly new, and has been in ZeeTerminal since v0.1.0. However, it is newer than the 'old' style, hence it's referred to as 'new'. It relies on using the arrow/WS keys to move a highlight up and down, to select an option.\n",

		"___ABOUT THIS PROGRAM___\n\nThis is the ZeeTerminal Commandline Program, Build " + std::string(ZT_VERSION) + ".\n" +
		"This is an early alpha build of ZeeTerminal, with an entirely new engine and components.\nThis program is made in C++, with a few very small parts of C." +
		"\n\nThis program uses the DirectShow API in the MediaPlayer command, which is licensed by Microsoft Corporation. (c) Microsoft Corporation.\n\n" +
		"This program uses the BASS API in the AudioPlayer command, which is licensed by Un4Seen Developments. (c) Un4Seen Developments.\n\n" +
		"\n(c) Ryan Zorkot, 2024. ZeeTerminal is licensed under the MIT License. The license and credits can be viewed on Page 4.\n\n"
		"  _____        _____                   _             _ \n"
		" |__  /___  __|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |\n"
		"   / // _ \\/ _ \\| |/ _ \\ '__| '_ \\` _ \\| | '_ \\ / _\\` |\n"
		"  / /|  __/  __/| |  __/ |  | | | | | | | | | | (_| | |\n"
		" /____\\___|\\___||_|\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|\n"
		"                                                       ",

		"___LICENSE AND CREDITS___\n\n"
		"Massive thank-you to my dad, Hazem Zorkot, for assisting with this project, including with the logo design, name, high-level component ideas, and lots of heads-up messages along the way.\n\n"
		"ZeeTerminal is licensed under the MIT License. Below is the license info:\n\nCopyright (c) 2024 Ryan Zorkot\n\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal"
		" in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell"
		" copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n"
		"The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\n"
		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\n"
	};

	sneHelp.sScreens = sScreens;

	if (bFromTutorial) {
		// Set custom direction text when coming from tutorial
		sneHelp.SetDirectionsText("Press the 'A' key or left arrow key to move left.\nPress the 'D' key or right arrow key to move right.\nPress ESC to exit the Help command and continue with the tutorial.");
	}

	// Call sneHelp.ScreenNavigate for screen strings set.
	sneHelp.ScreenNavigate(" ___HELP___ ");

	return;
}

// DevTools - A function for accessing developer tools.
// These can include test interfaces and functionality testers.
void DevTools(short int nToolNum) {

	// Colour Tester
	if (nToolNum == 1) {
		CentreColouredText(" ___COLOUR TESTER___ ", 1);
		std::cout << "\n\n";

		// Firstly, output all default colours
		// Foreground
		colourSubheading();
		std::cout << "Default Foreground Colours" << NOULINE_STR << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		for (int i = 30; i <= 37; i++) {
			std::cout << "\x1b[" << i << "mThis is foreground ANSI escape sequence colour <" << i << ">. 1234567890\n";
		}
		for (int i = 90; i <= 97; i++) {
			std::cout << "\x1b[" << i << "mThis is foreground ANSI escape sequence colour <" << i << ">. 1234567890 (Light)\n";
		}
		// Reset foreground for the next background test
		std::cout << "\x1b[39m\nPress any key to view the background colours...\n";
		_getch();

		// Background
		colourSubheading();
		std::cout << "\nDefault Background Colours" << NOULINE_STR << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		for (int i = 40; i <= 47; i++) {
			std::cout << "\x1b[" << i << "mThis is background ANSI escape code colour <" << i << ">. 1234567890\n";
		}
		for (int i = 100; i <= 107; i++) {
			std::cout << "\x1b[" << i << "mThis is background ANSI escape code colour <" << i << ">. 1234567890 (Light)\n";
		}
		// Reset background
		std::cout << "\x1b[49m\n";

		std::cout << "Press any key to exit...\n";
		_getch();

		return;
	}

	// Beep Sound Test
	else if (nToolNum == 2) {
		CentreColouredText(" ___BEEP SOUND TEST___ ", 1);

		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(false, "This is a tester for the 'Beep' function in Windows.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << NOULINE_STR << std::endl;
		std::cout << wordWrap("ZeeTerminal will output a pitch of sound that increases by 100hz every second, until 22000hz.") << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press any key to exit in the middle of the test.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nPress any key to begin the test, or ESC to exit...\n");
		char cKey = _getch();
		if (cKey == 27) {
			Exiting();
			return;
		}

		for (int i = 100; i < 22000; i += 100) {
			// clear line
			std::cout << "\r                      \r";
			// output
			std::cout << "Outputting " << i << " hz...";
			Beep(i, 1000);
			// stop if kbhit is true / keyboard key is pressed
			if (_kbhit()) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nBeep Sound Test stopped.\n";
				ClearKeyboardBuffer();
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				return;
			}
		}

		std::cout << '\n' << CentreText("Beep Sound Test completed successfully.");
		return;
	}

	// ColourNumbers
	else if (nToolNum == 3) {
		// Execute the ColourNumbers command from the Command function
		char cTemp[3] = { ' ', ' ', ' ' };
		Commands("colournumbers", cTemp, "");

		return;
	}

	// OptionSelectEngine Tester
	else if (nToolNum == 4) {
		CentreColouredText(" ___OPTIONSELECT ENGINE TESTER___ ", 1);
		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(false, "This allows you to test the OptionSelect Engine that is in this program.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << NOULINE_STR << wordWrap("\n\nThe OptionSelect Engine is an engine that manages the option input UI, and therefore requires a set array of options to work.\n\n");

		// Use a vector as it has a dynamic array structure
		std::vector<std::string> sOptions;

		// Input all options up to nNumOfOptions
		for (int i = 0 ;; i++) {
			sOptions.push_back(StrInput("Please input your desired string for Option " + std::to_string(i+1) + " (0 to finish input, -1 to exit entirely): > "));
			if (sOptions[i] == "-1") {
				Exiting();
				return;
			}
			else if (sOptions[i] == "0") {
				sOptions.pop_back(); // Remove "0"

				// To prevent crash with 0 options
				if (i < 1) {
					UserErrorDisplay("ERROR - Input cannot be finished until one valid string is provided (other than 0). Please continue with input.");
					i--;
					continue;
				}
				
				break;
			}
		}

		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nNow for everything else...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		// Get title, prompt
		std::string sTitle = StrInput("Please input your desired title for the window (0 to exit): > ");
		if (sTitle == "0") {
			Exiting();
			return;
		}
		std::string sPrompt = StrInput("Please input your desired prompt for the window (0 to exit): > ");
		if (sPrompt == "0") {
			Exiting();
			return;
		}

		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nStarting custom OptionSelect session...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Create an OptionSelectEngine object and assign accumulated data to members
		OptionSelectEngine oseTester;
		oseTester.nSizeOfOptions = sOptions.size();
		std::string* sOptionsArr = sOptions.data();
		oseTester.sOptions = sOptionsArr;

		// Call the display function
		oseTester.OptionSelect(sPrompt, sTitle);

		// Completed message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("OptionSelectEngine Tester Completed Successfully!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// ScreenNavigateEngine Tester
	else if (nToolNum == 5) {
		CentreColouredText(" ___SCREENNAVIGATE ENGINE TESTER___ ", 1);
		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(false, "This allows you to test the ScreenNavigate Engine that is in this program.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << NOULINE_STR << wordWrap("\n\nThe ScreenNavigate Engine is an engine that manages the screen viewing UI, and therefore requires a set array of screen data to work.\n\n");

		// Use a vector as it has a dynamic array structure
		std::vector<std::string> sScreens;

		// Input all screens up to nNumOfScreens
		for (long long int i = 0;; i++) {
			sScreens.push_back(StrInput("Please input your desired string for Screen " + std::to_string(i+1) + " (0 to finish, -1 to exit entirely) : > "));
			if (sScreens[i] == "-1") {
				Exiting();
				return;
			}
			else if (sScreens[i] == "0") {
				sScreens.pop_back(); // Remove "0"

				// To prevent crash with 0 options
				if (i < 1) {
					UserErrorDisplay("ERROR - Input cannot be finished until one valid string is provided (other than 0). Please continue with input.");
					i--;
					continue;
				}

				break;
			}
		}

		// Get title, prompt
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nNow for everything else...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::string sTitle = StrInput("Please input your desired title for the window (0 to exit): > ");
		if (sTitle == "0") {
			Exiting();
			return;
		}

		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nStarting custom ScreenNavigate session...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Create a ScreenNavigateEngine object and assign accumulated data to members
		ScreenNavigateEngine sneTester;
		sneTester.nSizeOfScreens = sScreens.size();
		std::string* sScreensArr = sScreens.data();
		sneTester.sScreens = sScreensArr;

		// Call the display function
		sneTester.ScreenNavigate(sTitle);

		// Completed message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("ScreenNavigateEngine Tester Completed Successfully!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	// TableEngine Tester
	else if (nToolNum == 6) {
		CentreColouredText(" ___TABLE-ENGINE TESTER___ ", 1);
		std::cout << std::endl;
		colourSubheading();
		slowcharCentredFn(false, "This allows you to test the Table Engine that is in this program.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << NOULINE_STR << wordWrap("\n\nThis engine's main purpose is for making tables.") << "\n";
		// Get rows and columns from user for next for loop
		uint64_t nNumOfRows = PositiveNumInputull("\nPlease input how many rows you would like to create (0 to exit): > ");
		if (nNumOfRows <= 0) {
			Exiting();
			return;
		}
		uint64_t nNumOfColumns = PositiveNumInputull("\nPlease input now many columns you would like to create (0 to exit): > ");
		if (nNumOfColumns <= 0) {
			Exiting();
			return;
		}

		// Input rows
		TableEngine teTester;
		for (uint64_t i = 0; i < nNumOfRows; i++) {
			std::vector<std::string> nRow;
			// Take all members of 1 row from user
			for (uint64_t j = 0; j < nNumOfColumns; j++) {
				nRow.push_back(StrInput("Please input table member " + std::to_string(j + 1) + "/" + std::to_string(nNumOfColumns) + " for row " + std::to_string(i + 1) + "/" + std::to_string(nNumOfRows) + " (input 0 to exit): > "));
				if (nRow[j] == "0") {
					Exiting();
					return;
				}
			}

			if (i <= (nNumOfRows - 1)) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nMoving to next row..." << std::endl;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << '\n' << CentreText("Generating table...") << "\n\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			// Send in another row using TableEngine::addRow()
			teTester.addRow(nRow);
		}

		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nStarting custom OptionSelect session...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Finally, output table using TableEngine::OutputTable()
		teTester.OutputTable();

		std::cout << "\n\nPress ENTER to exit...\n";
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		return;
	}

	// High-Res Nanosecond Stopwatch
	else if (nToolNum == 7) {
		CentreColouredText(" ___NANOSECOND STOPWATCH___ ", 1);
		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(false, "This is a CPU-intensive, nanosecond-accurate stopwatch that uses CPU ticks for the time.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << NOULINE_STR;

		// Prompt to start
		std::cout << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press any key in the middle of the stopwatch run to stop it.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\n\nPress any key to start the stopwatch, or ESC to exit...");
		char cKey = _getch();
		if (cKey == 27) {
			Exiting();
			return;
		}

		std::cout << "\n\n";

		// Main Nanosecond Stopwatch Part
		// Create timestamp variables
		auto start = std::chrono::high_resolution_clock::now();
		auto end = std::chrono::high_resolution_clock::now();

		// _kbhit() to exit on keypress
		while (!_kbhit()) {
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " ns\r";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Output final stopwatch time after keyboard press
		ClearKeyboardBuffer();
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nTimer stopped.";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nFinal stopwatch time: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " nanoseconds.\n";

		return;
	}

	// ANSI VT Testing Environment
	else if (nToolNum == 8) {
		std::string sANSI;
		CentreColouredText(" ___ANSI VT TESTING ENVIRONMENT___ ", 1);
		std::cout << std::endl;
		colourSubheading();
		slowcharCentredFn(false, "This is a sandbox-style testing enviroment for ANSI (VT) escape codes.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << NOULINE_STR << wordWrap("\n\nYou can test any ANSI escape code here. Everything will be reset after exiting the sandbox (by typing in 0 or \"zero\").");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nYou can get a list of ANSI VT escape codes here: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences") << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		while (true) {
			sANSI = StrInput("Please input your ANSI escape code, excluding \\x1b (ESC) and the '[' after it (0 or \"zero\" to exit): > ");
			if (sANSI == "0" || sANSI == "zero") {
				Exiting();
				std::cout << "\x1b[" << RESETALL << "m" << RESETEVERYTHING_STR << "\033c";
				// Set console cursor attributes
				SetCursorAttributes();
				// Set colour
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				cls();
				return;
			}
			std::cout << "\x1b[" << sANSI << std::endl;
		}
	}

	// MMSYSTEM API Sound Test
	else if (nToolNum == 9) {
		CentreColouredText(" ___MMSYSTEM API SOUND TEST___ ", 1);
		std::cout << std::endl;
		colourSubheading();
		slowcharCentredFn(false, "This is a sound test similar to the Beep Sound Test, but by interacting directly with drivers.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << NOULINE_STR << wordWrap("\n\nZeeTerminal will output a pitch of sound that starts at 20hz and increases by 100hz every second, until 22000hz.") << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press any key to exit in the middle of the test.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nPress any key to begin the test, or ESC to exit now...") << '\n';
		char cKey = _getch();
		if (cKey == 27) {
			Exiting();
			return;
		}
		else std::cout << '\n';

		MultimediaEngine meMMSYSTEMAPI;

		for (int i = 20; i <= 22000; i += 100)
		{
			std::cout << "Outputting ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << i << "hz...\r";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			

			// Leave when MultimediaEngine::BeepSound() returns FALSE (indicating pressed key)
			if (!meMMSYSTEMAPI.BeepSound(i, 1000, true)) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n\nMMSYSTEM API Sound Test stopped.\n";
				ClearKeyboardBuffer();
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				return;
			}
		}

		// Close stream and output success message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << std::endl << CentreText("Beep Sound Test completed successfully.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	return;
}



// Commands function - all command interfaces/start menus will go here
void Commands(const std::string sCommand, char* cCommandArgs, const std::string sCommandArgsBuffer = "") {

	// Before checking commands, check for anything other than a command
	if (sCommand[0] == '#') return;


	// Help
	if (sCommand == "help" || sCommand == "1") {
		
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			// help message
			if (cCommandArgs[i] == 'h') {
				HelpHelp();
				return;
			}
		}

		help(false);
		return;
	}

	// Tutorial
	else if (sCommand == "tutorial" || sCommand == "3") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				TutorialHelp();
				return;
			}
		}

		// Start the tutorial
		if (YesNoInput("Are you sure you want to start the tutorial? [y/n] > ")) {
			Tutorial();
		}
		else {
			Exiting();
			return;
		}

		return;
	}

	// Echo
	else if (sCommand == "echo" || sCommand == "4") {

		// Output what is after echo
		if (sCommandArgsBuffer != " ") {
			std::cout << sCommandArgsBuffer;
			return;
		}
		// Output what user wants to input within echo
		else {
			std::string sEcho = StrInput("Input what you would like ZeeTerminal to output: > ");
			// Output the input
			std::cout << sEcho << std::endl;
			return;
		}

		return;
	}

	// CLS
	else if (sCommand == "cls" || sCommand == "5") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ClsHelp();
				return;
			}
		}

		cls();
		return;
	}

	// DevTools
	else if (sCommand == "devtools" || sCommand == "6") {

		// Arguments
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				DevToolsHelp();
				return;
			}
			else if (cCommandArgs[i] == '1') {
				DevTools(1);
				return;
			}
			else if (cCommandArgs[i] == '2') {
				DevTools(2);
				return;
			}
			else if (cCommandArgs[i] == '3') {
				DevTools(3);
				return;
			}
			else if (cCommandArgs[i] == '4') {
				DevTools(4);
				return;
			}
			else if (cCommandArgs[i] == '5') {
				DevTools(5);
				return;
			}
			else if (cCommandArgs[i] == '6') {
				DevTools(6);
				return;
			}
			else if (cCommandArgs[i] == '7') {
				DevTools(7);
				return;
			}
			else if (cCommandArgs[i] == '8') {
				DevTools(8);
				return;
			}
			else if (cCommandArgs[i] == '9') {
				DevTools(9);
				return;
			}
		}

		OptionSelectEngine oseDev;

		oseDev.nSizeOfOptions = 9;
		std::string sOptions[] = // Options
		{
			"Colour Tester",
			"Beep Sound Test",
			"Colour Numbers",
			"Test The OptionSelect Engine",
			"Test the ScreenNavigate Engine",
			"Test the Table Engine",
			"High-Res Nanosecond Stopwatch",
			"ANSI Testing Environment",
			"MMSYSTEM API Sound Test"
		};

		oseDev.sOptions = sOptions;

		while (true) {
			// Call OptionSelectEngine::OptionSelect() for option strings set.
			int nInput = oseDev.OptionSelect("Please select your desired developer tool below:", " ___DEVELOPER TOOLS___ ");

			switch (nInput)
			{
			case -1:
				Exiting();
				return;
			case 1:
				DevTools(1);
				break;
			case 2:
				DevTools(2);
				break;
			case 3:
				DevTools(3);
				break;
			case 4:
				DevTools(4);
				break;
			case 5:
				DevTools(5);
				break;
			case 6:
				DevTools(6);
				break;
			case 7:
				DevTools(7);
				break;
			case 8:
				DevTools(8);
				break;
			case 9:
				DevTools(9);
				break;
			default:
				VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				break;
			}
		}

		return;
	}

	// CPUStress
	else if (sCommand == "cpustress" || sCommand == "7") {

		CentreColouredText(" ___CPUSTRESS___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CpuStressHelp();
				return;
			}
			else if (cCommandArgs[i] == '1') {
				std::cout << '\n';
				// First, check if it's a number
				if (isNumberll(sStringDataCommandArgs[0]) == true) {
					CpuBenchmark(1, std::stoll(sStringDataCommandArgs[0]));
				}
				else {
					CpuBenchmark(1, -1);
				}

				return;
			}
			else if (cCommandArgs[i] == '2') {
				std::cout << '\n';
				if (isNumberll(sStringDataCommandArgs[0]) == true) {
					CpuBenchmark(2, std::stoll(sStringDataCommandArgs[0]));
				}
				else {
					CpuBenchmark(2, -1);
				}

				return;
			}
			else if (cCommandArgs[i] == '3') {
				std::cout << '\n';
				CpuStressTest(1, true);
				return;
			}
			else if (cCommandArgs[i] == '4') {
				std::cout << '\n';
				CpuStressTest(2, true);
				return;
			}
		}

		OptionSelectEngine CpuStress;

		while (true) {

			std::cout << "\n";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("You can stop a test at any time by pressing a key on the keyboard.");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			CpuStress.nSizeOfOptions = 4;
			std::string sOptions[] = {
				"CPU Benchmark - Single Core",
				"CPU Benchmark - Multi Core",
				"CPU Stress Test - Single Core",
				"CPU Stress Test - Multi Core"
			};
			CpuStress.sOptions = sOptions;

			int nChoice = CpuStress.OptionSelect("Please select your desired option (single core is less intensive, multi core is more intensive):", "");

			if (nChoice == 1) {
				std::cout << '\n';
				CpuBenchmark(1);
			}
			else if (nChoice == 2) {
				std::cout << '\n';
				CpuBenchmark(2);
			}
			else if (nChoice == 3) {
				std::cout << '\n';
				CpuStressTest(1);
			}
			else if (nChoice == 4) {
				std::cout << '\n';
				CpuStressTest(2);
			}
			else if (nChoice == -1) {
				Exiting();
				return;
			}
			else {
				VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

				return;
			}
		}

		return;
	}

	// Colour
	else if (sCommand == "colour" || sCommand == "8") {
		bool bForeUserArg = false;
		bool bBackUserArg = false;

		int nChoiceFirst = 0;
		int nForeArg = 0; // 0 is not from argument, anything else means from argument
		int nBackArg = 0; // 0 is not from argument, anything else means from argument

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ColourHelp();
				return;
			}
			else if (cCommandArgs[i] == 'f') {

				if (isNumberi(sStringDataCommandArgs[i]) == true) {
					nChoiceFirst = 1;
					nForeArg = std::stoi(sStringDataCommandArgs[i]);
				}
				else {
					// Can't process a non-number
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured while processing your foreground argument. Make sure your argument syntax is correct, and try again.\nSee \"colour -h\" for more info.\n");
					Exiting();
					return;
				}

				bForeUserArg = true;
			}
			else if (cCommandArgs[i] == 'b') {

				// Check if argument is a number
				if (isNumberi(sStringDataCommandArgs[i]) == true) {
					nChoiceFirst = 2;
					nBackArg = std::stoi(sStringDataCommandArgs[i]);
				}
				else {
					// Can't process a non-number
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured while processing your background argument. Make sure your argument syntax is correct, and try again.\nSee \"colour -h\" for more info.\n");
					Exiting();
					return;
				}

				bBackUserArg = true;
			}
			else if (cCommandArgs[i] == 'r') {
				nChoiceFirst = 4;
			}
		}

		// First menu
		OptionSelectEngine oseColour;
		oseColour.nSizeOfOptions = 4;
		std::string sOptions[] = {
			"Foreground Colour",
			"Background Colour",
			"Custom RGB Colour Presets",
			"Reset Colours to Default"
		};
		oseColour.sOptions = sOptions;

		while (true) {
			bool bArgumentForFirstOption = nChoiceFirst; // indicates that the user interface will be triggered

			// User Interface
			if (nChoiceFirst == 0) {
				std::cout << '\n';
				nChoiceFirst = oseColour.OptionSelect("Please choose the colour that you want to change below:", " ___COLOUR___ ");
			}

			if (nChoiceFirst == 1) {
				ColourForeground(nForeArg);
				if (bBackUserArg) ColourBackground(nBackArg); // in case of user-set argument

				// in case of argument
				if (nForeArg != 0) return;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == 2) {
				ColourBackground(nBackArg);
				if (bForeUserArg) ColourForeground(nForeArg); // in case of user-set argument

				// in case of argument
				if (nBackArg != 0) return;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == 3) {
				RGBColourPresets();

				if (bArgumentForFirstOption) return;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == 4) {
				// Reset colours prompt
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nTHIS WILL RESET ALL SET COLOURS TO DEFAULT VALUES.\nRGB Colour presets will NOT be affected.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (YesNoInput(wordWrap("Are you sure you would like to proceed? [y/n] > "))) {
					// Reset colours and update config file with new colours
					ResetColour();
					ConfigObjMain.WriteConfigFile();
					cls(); // To apply default colours to whole terminal screen

					// Output success message
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("Colours successfully reset.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "\nAborted.\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}

				if (bArgumentForFirstOption) return;
				else nChoiceFirst = 0;
			}
			else if (nChoiceFirst == -1) {
				Exiting();
				break;
			}
			else {
				VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				return;
			}
		}

		return;
	}

	// Settings
	else if (sCommand == "settings" || sCommand == "9") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				SettingsHelp();
				return;
			}
			else if (sStringOptionCommandArgs[0] == "highlightfore") {

				// Check if argument is a number, post error message if not and call function if yes
				if (isNumberi(sStringDataCommandArgs[0])) {
					HighlightColourSettings(1, std::stoi(sStringDataCommandArgs[0]));
				}
				else {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "highlightback") {
					if (isNumberi(sStringDataCommandArgs[0])) {
						HighlightColourSettings(2, std::stoi(sStringDataCommandArgs[0]));
					}
					else {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
						return;
					}
				
				return;
			}
			else if (sStringOptionCommandArgs[0] == "titlefore") {
					if (isNumberi(sStringDataCommandArgs[0])) {
						TitleColourSettings(1, std::stoi(sStringDataCommandArgs[0]));
					}
					else {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
						return;
					}
				return;
			}
			else if (sStringOptionCommandArgs[0] == "titleback") {
					if (isNumberi(sStringDataCommandArgs[0])) {
						TitleColourSettings(2, std::stoi(sStringDataCommandArgs[0]));
					}
					else {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
						return;
					}
				return;
			}
			else if (sStringOptionCommandArgs[0] == "subheadingfore") {
					if (isNumberi(sStringDataCommandArgs[0])) {
						SubheadingColourSettings(1, std::stoi(sStringDataCommandArgs[0]));
					}
					else {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
						return;
					}
				return;
			}
			else if (sStringOptionCommandArgs[0] == "subheadingback") {
					if (isNumberi(sStringDataCommandArgs[0])) {
						SubheadingColourSettings(2, std::stoi(sStringDataCommandArgs[0]));
					}
					else {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "verbose") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					VerboseMessagesSettings(1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					VerboseMessagesSettings(2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "directions") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						DirectionMessagesSettings(1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						DirectionMessagesSettings(2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "ansi") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						AnsiSettings(1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						AnsiSettings(2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "wordwrap") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						WordWrapSettings(1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						WordWrapSettings(2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "cursorblink") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						CursorSettings(1, 1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						CursorSettings(1, 2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "showcursor") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						CursorSettings(2, 0, 1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						CursorSettings(2, 0, 2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "cursorstyle") {
					if (sStringDataCommandArgs[0] == "block") {
						CursorSettings(3, 0, 0, 1);
					}
					else if (sStringDataCommandArgs[0] == "underline") {
						CursorSettings(3, 0, 0, 2);
					}
					else if (sStringDataCommandArgs[0] == "bar") {
						CursorSettings(3, 0, 0, 3);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct 'block', 'underline' or 'bar' value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's either 'block', 'underline', or 'bar'. Type \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "slowcharspeed") {
					if (isNumberll(sStringDataCommandArgs[0])) {
						OtherSettings(1, std::stoll(sStringDataCommandArgs[0]), true);
					}
					else {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "randcolstartup") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						OtherSettings(2, 0, true, 1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						OtherSettings(2, 0, true, 2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "customtheme") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						OtherSettings(3, 0, true, 0, 1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						OtherSettings(3, 0, true, 0, 2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "autocontrast") {
					if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
						OtherSettings(4, 0, true, 0, 0, 1);
					}
					else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
						OtherSettings(4, 0, true, 0, 0, 2);
					}
					else {
						VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
						return;
					}
				
				return;
			}
			else if (sStringOptionCommandArgs[0] == "tempconfigdir") {
				if (sStringDataCommandArgs[0] != "") {
					OtherSettings(5, 0, true, 0, 0, 0, sStringDataCommandArgs[0]);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect any argument string after option.\n");
					UserErrorDisplay("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again. Type \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "enablelogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(1, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(1, 2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "vmessagelogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(2, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(2, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "usrerrorlogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(3, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(3, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "commandlogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(4, 0, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(4, 0, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "usrinputlogging") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					LogFileSystemSettings(5, 0, 0, 0, 0, 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					LogFileSystemSettings(5, 0, 0, 0, 0, 2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
			else if (sStringOptionCommandArgs[0] == "newoptionselect") {
				if (sStringDataCommandArgs[0] == "t" || sStringDataCommandArgs[0] == "true") {
					OtherSettings(6, 0, true, 0, 0, 0, "", 1);
				}
				else if (sStringDataCommandArgs[0] == "f" || sStringDataCommandArgs[0] == "false") {
					OtherSettings(6, 0, true, 0, 0, 0, "", 2);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Could not detect correct t/f or true/false value in argument string.\n");
					UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's \"t\" or \"f\" and try again.\nType \"settings -h\" for more info.\n");
					return;
				}

				return;
			}
		}

		OptionSelectEngine oseSettings;
		oseSettings.nSizeOfOptions = 10;
		std::string sOptions[] = {
			"Highlight Colour Settings",
			"Title Colour Settings",
			"Subheading Colour Settings",
			"Disable/Enable Verbose Messages",
			"Disable/Enable Direction Messages",
			"Disable/Enable ANSI",
			"Disable/Enable Word Wrapping",
			"Cursor Settings",
			"LogFile System Settings",
			"Other Settings"
		};
		oseSettings.sOptions = sOptions;

		// Leave only when the user decides to press the ESC key
		while (true) {
			std::cout << std::endl;
			int nChoice = oseSettings.OptionSelect("Please select the setting you would like to modify:", " ___SETTINGS___ ");

			switch (nChoice) {
			case -1:
				Exiting();
				return;
			case 1:
				HighlightColourSettings();
				break;
			case 2:
				TitleColourSettings();
				break;
			case 3:
				SubheadingColourSettings();
				break;
			case 4:
				VerboseMessagesSettings();
				break;
			case 5:
				DirectionMessagesSettings();
				break;
			case 6:
				AnsiSettings();
				break;
			case 7:
				WordWrapSettings();
				break;
			case 8:
				CursorSettings();
				break;
			case 9:
				LogFileSystemSettings();
				break;
			case 10:
				OtherSettings();
				break;

			default:
				VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				return;
			}
		}

		return;
	}

	// Title
	else if (sCommand == "title" || sCommand == "10") {

		if (sCommandArgsBuffer == " ") {
			CentreColouredText(" ___TITLE___ ", 1);
			std::cout << "\n";

			// Take title input
			std::string sTitle = StrInput("Please input your desired title (256 characters max): > ");
			// Set window title using WindowTitleSet engine function
			if (SetWindowTitle(sTitle)) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("Setting console window title succeeded!\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				UserErrorDisplay("Setting console window title failed!\nPlease check if your title is too long. It cannot be longer than 256 characters.\n");
			}
		}
		else {
			if (SetWindowTitle(sCommandArgsBuffer)) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("Setting console window title succeeded!\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				UserErrorDisplay("Setting console window title failed!\nPlease check if your title is too long. It cannot be longer than 256 characters.\n");
			}
		}

		return;
	}

	// Date
	else if (sCommand == "date" || sCommand == "11") {

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				DateHelp();
				return;
			}
		}

		time_t currentTime = time(0);
		struct tm localTime {};

		time(&currentTime);
		localtime_s(&localTime, &currentTime);

		colourSubheading();
		std::cout << "Current Date/Time Info:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);


		std::cout << "\n\nLocal Date: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << localTime.tm_mday << "/" << (localTime.tm_mon + 1) << "/" << (localTime.tm_year + 1900); 
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " (DD/MM/YYYY)\n";
		std::cout << "Local Time: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << "\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// ColourNumbers
	else if (sCommand == "colournumbers" || sCommand == "12") {
		CentreColouredText(" ___COLOURNUMBERS___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ColourNumbersHelp();
				return;
			}
		}

		// Display all colours in the colour array inside Settings.cpp
		std::cout << '\n';
		colourSubheading();
		std::cout << "Colour numbers are below:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n';

		for (int i = 0; i < 16; i++) {
			std::cout << '[' << (i + 1) << "] "<< sOptionsColour[i] << "\n";
		}
		std::cout << wordWrap("\nThe colour number for each colour is in between the square brackets.") << '\n';

		return;
	}

	// MediaPlayer
	else if (sCommand == "mediaplayer" || sCommand == "13") {

		std::wstring wsFilePath = L"";

		CentreColouredText(" ___MEDIAPLAYER___ ", 1);
		std::cout << "\n";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				MediaPlayerHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				wsFilePath = s2ws(sStringDataCommandArgs[0]);
			}
		}

		// Information
		if (wsFilePath == L"") {
			std::cout << "\n";
			colourSubheading();
			std::cout << wordWrap("The following file formats are supported:") << NOULINE_STR;
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nWMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, MP3(Only MPEG Audio Layer - 3 codec), JPG, JPEG, BMP\n\nYou can type in \"*open\" without quotes to use the Windows File Dialogue to open a file.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Prompt
			std::cout << "Enter your desired audio/video/image file path (0 to exit): > ";
			colour(LYLW, ConfigObjMain.sColourGlobalBack);
			std::getline(std::wcin, wsFilePath);
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Exit on 0
			if (wsFilePath == L"0") {
				Exiting();
				return;
			}
		}

		// Open with the Windows File Dialogue
		if (wsFilePath == L"*open") {
			std::cout << "Opening with the Windows File Dialogue...\n";
			FileOpenGUIEngine MediaPlayer;
			MediaPlayer.FileOpenDialogue("Open a Media File to Play");
			wsFilePath = s2ws(MediaPlayer.GetRetrievedPathName());
			// Cancelled
			if (wsFilePath == L"") {
				Exiting();
				return;
			}
		}

		// Execute multimedia player with the inputted file path
		VerbosityDisplay("Executing media file using MediaPlayer: \"" + ws2s(wsFilePath) + "\"...\n");
		MultimediaEngine meMediaPlayer;
		meMediaPlayer.DShowMultimediaPlayer(wsFilePath);

		return;

	}

	// AudioPlayer
	else if (sCommand == "audioplayer" || sCommand == "14") {
		std::string sFilePath = "";

		CentreColouredText("___AUDIO PLAYER___", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				AudioPlayerHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sFilePath = sStringDataCommandArgs[0];
			}
		}

		// Information
		if (sFilePath == "") {
			std::cout << "\n";
			colourSubheading();
			std::cout << wordWrap("The following file formats are supported:") << NOULINE_STR;
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nMP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC\n\nType \"*open\" without quotes to use the Windows File Dialogue to open an audio file.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Prompt
			sFilePath = StrInput("Enter your desired audio file path (0 to exit): > ");
			std::cout << '\n';

			// Exit on 0
			if (sFilePath == "0") {
				Exiting();
				return;
			}
		}

		// Open the file dialogue on *open
		if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "Opening with the Windows File Dialogue...\n";
			FileOpenGUIEngine AudioPlayer;
			AudioPlayer.FileOpenDialogue("Open an Audio File to Play");
			sFilePath = AudioPlayer.GetRetrievedPathName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return;
			}
		}

		VerbosityDisplay("Executing audio file using AudioPlayer: \"" + sStringDataCommandArgs[0] + "\"...\n");
		MultimediaEngine meAudioPlayer;
		meAudioPlayer.BASSAudioPlayer(sFilePath);

		return;
	}

	// TTS
	else if (sCommand == "tts" || sCommand == "15") {
		
		std::string sText = "";

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				TTSHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sText = sStringDataCommandArgs[0];
			}
		}

		// User UI
		if (sText == "") {
			CentreColouredText(" ___TEXT TO SPEECH___ ", 1);
			std::cout << "\n\n";
			// Take input
			sText = StrInput("Please input your desired text (0 to exit): > ");
			if (sText == "0") {
				Exiting();
				return;
			}
		}

		// Check for speechmarks; if so, remove them so they don't get pronounced
		if (sText[0] == '"' && sText[sText.length() - 1] == '"') {
			sText = sText.substr(1, (sText.length() - 2));
		}

		// Output using MultimediaEngine::TTS() //
		// Output message
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("Outputting TTS Message...") << '\n';

		MultimediaEngine meTTS;
		VerbosityDisplay("TTS starting with text \"" + sText + "\"...\n");
		meTTS.TTSOutput(s2ws(sText));

		// Output success message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("TTS Message successfully outputted!") << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Stopwatch
	else if (sCommand == "stopwatch" || sCommand == "16") {

		bool bSkipStartScreen = false;
		bool bUserCursorVisibilitySetting = true;

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				StopwatchHelp();
				return;
			}
			else if (cCommandArgs[i] == 'i') {
				bSkipStartScreen = true;
			}
		}

		CentreColouredText(" ___STOPWATCH___ ", 1);
		
		if (!bSkipStartScreen) {
			std::cout << wordWrap("\n\nYou can exit the stopwatch at any time by pressing a key on the keyboard.\nPress any key to start, or ESC to exit now...\n");
			char c = _getch();

			// Exit on ESC key press
			if (c == 27) {
				Exiting();
				return;
			}
		}
		else { 
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\nStopwatch starting immediately.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Start stopwatch
		std::cout << '\n';
		std::chrono::duration<long double> elapsedSeconds;

		// Disable cursor visibility
		bUserCursorVisibilitySetting = DisableCursorVisibility();

		auto start = std::chrono::steady_clock::now();

		while (!_kbhit()) { // exit on keypress
			elapsedSeconds = std::chrono::steady_clock::now() - start;
			std::cout << "Time: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << elapsedSeconds.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " seconds...                \r"; // 16 spaces for decimal space buffer
			sleep(3); // Optimisation for CPU usage; puts CPU to sleep for 3ms
		}

		// Assume keyboard has been pressed
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nKeyboard pressed.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Output final time
		std::cout << "Final time: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << elapsedSeconds.count();
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " seconds.\n\n";

		ClearKeyboardBuffer();
		// Reset cursor visibility to user settings
		ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
		SetCursorAttributes();

		return;
	}

	// Read
	else if (sCommand == "read" || sCommand == "17") {
		bool bOutputInBinaryMode = false;
		std::string sFilePath = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ReadHelp();
				return;
			}
			else if (cCommandArgs[i] == 'b') {
				bOutputInBinaryMode = true;
			}

			if (sStringDataCommandArgs[0] != "") {
				sFilePath = sStringDataCommandArgs[0];
			}
		}
		
		if (sFilePath == "") {
			CentreColouredText(" ___READ___ ", 1);
			std::cout << "\n\n";
			sFilePath = StrInput("Please input file directory (0 to exit, \"*open\" without quotes to use the Windows File Dialogue): > ");
			if (sFilePath == "0") {
				Exiting();
				return;
			}
		}

		// Open the file dialogue on *open
		if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "Opening with the Windows File Dialogue...\n";
			FileOpenGUIEngine ReadCommand;
			ReadCommand.FileOpenDialogue("Open a File to Read");
			sFilePath = ReadCommand.GetRetrievedPathName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return;
			}
		}
		else std::cout << '\n';

		// Firstly, test if file is actually real
		std::ifstream fileTestIn;

		// Check if the start of the first argument has a speechmark; 
		// if there is one, use text from the start to the ending speechmark (if there is one)
		if (sFilePath[0] == '\"') {
			size_t nFirstMarkPos = sFilePath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sFilePath.find('\"', nFirstMarkPos) - 1;
			sFilePath = sFilePath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		fileTestIn.open(sFilePath);
		if (fileTestIn.fail()) {
			VerbosityDisplay("In Commands() - ERROR: Unknown directory/file detected. Read operation failed.\n");
			UserErrorDisplay("ERROR - The directory or file doesn't exist. Please try again with a directory/file that exists.\n");

			fileTestIn.close();
			Exiting();
			return;
		}
		fileTestIn.close();

		// Open a new stream for reading
		std::ifstream fileIn;
		if (bOutputInBinaryMode) {
			// Read file in binary mode
			fileIn.open(sFilePath, std::ios::binary);
		}
		else {
			// Read file in default text mode
			fileIn.open(sFilePath);
		}

		std::string* sFileContents = new std::string;
		std::string* sBuffer = new std::string;
		
		// Copy line by line using std::getline() using buffer
		while (!fileIn.eof()) {
			std::getline(fileIn, *sBuffer);
			*sFileContents += '\n';
			*sFileContents += *sBuffer;
			*sBuffer = "";
		}

		// Output file contents
		if (bAnsiVTSequences) {
			colourHighlight();
			std::cout << ULINE_STR << "File contents are below:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n" << *sFileContents << "\n\n";
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << ULINE_STR << "File Finished." << NOULINE_STR << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else std::cout << "File contents are below:\n\n" << *sFileContents << "\n\nFile Finished.\n";

		fileIn.close();
		delete sFileContents;
		return;
	}

	// Timer
	else if (sCommand == "timer" || sCommand == "18") {
		long double dInput = 0;
		bool bUserCursorVisibilitySetting = true;

		CentreColouredText(" ___TIMER___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				TimerHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				// Firstly, check if argument is a real and usable number
				if (isNumberld(sStringDataCommandArgs[0]) == false) {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("ERROR - Number argument is either too big or not a number.\nPlease try again with a number between 0 and 2 billion.\n");

					return;
				}

				// Convert string to integral value
				dInput = std::stold(sStringDataCommandArgs[0]);
				break;
			}
		}

		// Only display prompt if no input was provided
		if (dInput == 0) {
			std::cout << "\n";
			dInput = NumInputld("Please input the number of seconds for the timer (0 to exit): > ");
			// Exit on 0 input
			if (dInput <= 0.0) {
				Exiting();
				return;
			}
		}

		// Start timer with prompts
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nPress any key to exit the timer.\n\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Disable cursor visibility
		bUserCursorVisibilitySetting = DisableCursorVisibility();

		std::chrono::duration<long double> elapsedTime{};
		auto start = std::chrono::steady_clock::now();
		auto time = std::chrono::steady_clock::now();

		for (; elapsedTime.count() < dInput; elapsedTime = time - start) {
			std::cout << "Timer: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << dInput - elapsedTime.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " sec (out of ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << dInput;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << " sec)                      \r";
			// Check for keypress
			if (_kbhit()) {
				ClearKeyboardBuffer();
				std::cout << "\n";
				Exiting();
				return;
			}
			// Check for pause press
			time = std::chrono::steady_clock::now();
			// Optimisation for cpu time/usage
			sleep(10);
		}

		// Make the final time appear as 0 seconds
		std::cout << "Timer: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "0";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " sec (out of ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << dInput;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " sec)                      ";

		std::cout << '\n';
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Timer finished!") << '\n';
		MessageBeep(MB_OK);
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Reset cursor visibility to user settings
		ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
		SetCursorAttributes();

		return;

	}

	// Beep
	else if (sCommand == "beep" || sCommand == "19") {

		long double dFrequency = 0;
		long double dDuration = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				BeepHelp();
				return;
			} 
			if (sStringDataCommandArgs[0] != "") {
				// Firstly, check if argument is a real and usable number
				if (isNumberld(sStringDataCommandArgs[0]) == false) {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("ERROR - Your frequency argument is either too big or not a number.\nPlease try again with a number between 0 and 2 billion.\n");

					return;
				}

				// Use the specified number in the BeepSound call.
				dFrequency = std::stold(sStringDataCommandArgs[0]);

				if (dFrequency < 0) {
					VerbosityDisplay("ERROR: In Commands() - Numerical value argument incorrect (negative number).\n");
					UserErrorDisplay("ERROR - Your frequency argument is a negative number.\nPlease try again with a number between 0 and 2 billion.\n");

					return;
				}

				dDuration = 1; // just in case no time argument was passed, use the default 1 second beep
			}
			if (sStringDataCommandArgs[1] != "") {
				// Firstly, check if argument is a real and usable number
				if (isNumberld(sStringDataCommandArgs[1]) == false) {
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("ERROR - Your time argument is either too big or not a number.\nPlease try again with a number between 0 and 2 billion.\n");

					return;
				}

				// Use the specified number in the BeepSound call.
				dDuration = std::stold(sStringDataCommandArgs[1]);

				// Negative numbers are not allowed.
				if (dDuration < 0) {
					VerbosityDisplay("ERROR: In Commands() - Numerical value argument incorrect (negative number).\n");
					UserErrorDisplay("ERROR - Your time argument is a negative number.\nPlease try again with a number between 0 and 2 billion.\n");

					return;
				}
			}
		}

		// Only display prompt when command ran without arguments
		if (dFrequency <= 0 && dDuration <= 0) {
			CentreColouredText(" ___BEEP___ ", 1);

			std::cout << "\n\n";
			dFrequency = NumInputld("Please input frequency in Hertz (0 to exit): > ");
			if (dFrequency <= 0) {
				Exiting();
				return;
			}
			dDuration = NumInputld("Please input duration in seconds (0 to exit): > ");
			if (dDuration <= 0) {
				Exiting();
				return;
			}
		}
		

		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("Beep is outputting...") << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Run the MultimediaEngine::BeepSound() function to output beep.
		MultimediaEngine meBeep;
		meBeep.BeepSound(dFrequency, (dDuration * 1000));

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Beep output operation complete.") << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// MessageBox
	else if (sCommand == "messagebox" || sCommand == "20") {
		std::string sCaption = "";
		std::string sText = "";
		int nButton = 0;
		int nIcon = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				MessageBoxHelp();
				return;
			}
			else if (cCommandArgs[i] == 't') {
				if (sStringDataCommandArgs[i] != "") {
					sText = sStringDataCommandArgs[i];
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of text argument found.\nPlease make sure that's there, and try again.\n");

					return;
				}

			}
			else if (cCommandArgs[i] == 'c') { 
				if (sStringDataCommandArgs[i] != "") {
					sCaption = sStringDataCommandArgs[i];
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of caption text argument found.\nPlease make sure that's there, and try again.\n");

					return;
				}
			}
			else if (cCommandArgs[i] == 'i') {
				// Uses sStringCommandArgs because the only arguments in this function are string-based
				if (sStringDataCommandArgs[i] != "") {
					nIcon = MessageBoxIconSwitch(sStringDataCommandArgs[i]);
					if (nIcon == 1) return;
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of icon argument found.\nPlease make sure that's there, and try again.\n");

					return;
				}
			}
			else if (cCommandArgs[i] == 'b') {
				if (sStringDataCommandArgs[i] != "") {
					nButton = MessageBoxButtonSwitch(sStringDataCommandArgs[i]);
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of button argument found.\nPlease make sure that's there, and try again.\n");

					return;
				}
			}
		}

		if (sCaption == "" && sText == "" && nButton == 0 && nIcon == 0) {
			CentreColouredText(" ___MESSAGEBOX___ ", 1);
			std::cout << '\n';

			// Prompts
			// Icon Selection
			OptionSelectEngine oseMsgBox;
			oseMsgBox.nSizeOfOptions = 4;
			std::string sOptionsIcon[] = {
				"Error",
				"Question Mark",
				"Warning",
				"Information 'I'"
			};
			oseMsgBox.sOptions = sOptionsIcon;
			switch (oseMsgBox.OptionSelect("Please select what icon you want for the message box:", " ICON SELECTION ")) {
			case -1:
				Exiting();
				return;
			case 1:
				nIcon = 16;
				break;
			case 2:
				nIcon = 32;
				break;
			case 3:
				nIcon = 48;
				break;
			case 4:
				nIcon = 64;
				break;
			default:
				UserErrorDisplay("An unknown error occured while processing your icon argument.\nPlease try again later.\n");
				return;
			}

			// Button Selection
			oseMsgBox.nSizeOfOptions = 7;
			std::string sOptionsButton[] = {
				"OK",
				"OK + Cancel",
				"Abort + Retry + Ignore",
				"Yes + No + Cancel",
				"Yes + No",
				"Retry + Cancel",
				"Cancel + Try + Continue"
			};
			oseMsgBox.sOptions = sOptionsButton;
			nButton = oseMsgBox.OptionSelect("Please select the button layout for the message box:", " BUTTON SELECTION ") - 1;
			// Because -1 - 1 = -2, so exit
			if (nButton == -2) { 
				Exiting();
				return;
			}

			// MessageBox Text
			sText = StrInput("Please input the text that you want in the message box (0 to exit): > ");
			std::cout << '\n';
			if (sText == "0") {
				Exiting();
				return;
			}

			// MessageBox Caption Text
			sCaption = StrInput("Please input the caption text that you want in the message box (0 to exit): > ");
			std::cout << '\n';
			if (sCaption == "0") {
				Exiting();
				return;
			}
		}

		// Display message box
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nDisplaying messagebox...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (MessageBoxA(NULL, sText.c_str(), sCaption.c_str(), nButton | nIcon) == false) {
			// An error occured
			VerbosityDisplay("In Commands() - ERROR: Possible unknown messagebox return value from OptionSelectEngine::OptionSelect(), or standard WIN32 Function Library error.\n");
			UserErrorDisplay("An error occured while displaying the message box.\nPlease try again later.\n");
		}
		else {
			// Success
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Messagebox successfully displayed!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return;
	}

	// Copy
	else if (sCommand == "copy" || sCommand == "21") {

		int nFlagOverwrite = static_cast<int>(std::filesystem::copy_options::none);
		int nFlagDirectoryCopy = static_cast<int>(std::filesystem::copy_options::none);
		std::string sFileToCopyPath = "";
		std::string sDestinationPath = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CopyHelp();
				return;
			}
			else if (cCommandArgs[i] == 'o') {
				nFlagOverwrite = static_cast<int>(std::filesystem::copy_options::overwrite_existing);
			}
			else if (cCommandArgs[i] == 'd') {
				nFlagDirectoryCopy = static_cast<int>(std::filesystem::copy_options::recursive);
			}

			if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[1] == "") {
					// Error message
					VerbosityDisplay("In Commands() - ERROR: Vital argument not found.\n");
					UserErrorDisplay("ERROR: You need to have both the file location AND destination file directories included in your arguments.\nSee \"copy -h\" for more info.\n");

					return;
				}

				sFileToCopyPath = sStringDataCommandArgs[0];
				sDestinationPath = sStringDataCommandArgs[1];
			}
		}

		// User Interface for filepath
		if (sFileToCopyPath == "") {
			CentreColouredText(" ___COPY___ ", 1);
			std::cout << wordWrap("\nThis command copies files or folder contents recursively, from one location to another destination location.\n");
			colour(LBLU, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Input 0 to exit, and \"*open\" without quotes to use the Windows File Dialogue.\n\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			sFileToCopyPath = StrInput("Please input the path to the file/folder that is to be copied: > ");
			if (sFileToCopyPath == "0") {
				Exiting();
				return;
			}
		}

		if (sFileToCopyPath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue(nFlagDirectoryCopy == 0 ? "Select a File To Copy" : "Select a Folder to Copy Contents From", (bool)nFlagDirectoryCopy);
			sFileToCopyPath = FileCopyDialogue.GetRetrievedPathName();
			if (sFileToCopyPath == "") {
				Exiting();
				return;
			}
		}

		// User Interface for destination path
		if (sDestinationPath == "") {
			sDestinationPath = StrInput("Please input the path to the directory to copy the file(s) to: > ");
			if (sDestinationPath == "0") {
				Exiting();
				return;
			}
		}

		if (sDestinationPath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue("Select the Destination Path for File Copy", true);
			sDestinationPath = FileCopyDialogue.GetRetrievedPathName();
			if (sDestinationPath == "") {
				Exiting();
				return;
			}
		}

		// Remove quotes if there are any, in case of copy from File Explorer
		// In other words, check for any speechmarks that might accidentally get passed to copy operation
		if (sFileToCopyPath[0] == '\"') {
			size_t nFirstMarkPos = sFileToCopyPath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sFileToCopyPath.find('\"', nFirstMarkPos) - 1;
			sFileToCopyPath = sFileToCopyPath.substr(nFirstMarkPos, nFinalMarkPos);
		}
		if (sDestinationPath[0] == '\"') {
			size_t nFirstMarkPos = sDestinationPath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sDestinationPath.find('\"', nFirstMarkPos) - 1;
			sDestinationPath = sDestinationPath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		// Copy files/folder contents
		std::cout << wordWrap("\nCopying file(s)...\n");
		std::error_code ecTestZone;
		try {
			std::filesystem::copy_options CopyOptions = static_cast<std::filesystem::copy_options>(nFlagOverwrite) | static_cast<std::filesystem::copy_options>(nFlagDirectoryCopy);
			std::filesystem::copy(sFileToCopyPath, sDestinationPath, CopyOptions, ecTestZone);
		}
		
		// Catch bad memory allocation to avoid exception
		catch (const std::bad_alloc&) {
			VerbosityDisplay("In Commands(): ERROR - Memory allocation failed when copying using std::filesystem::copy (std::bad_alloc).\n");
			UserErrorDisplay("ERROR - Failed to allocate memory before copy operation. Please try again later.\n");

			return;
		}

		// Error codes output
		if (ecTestZone.value() != 0) {
			if (ecTestZone == std::errc::file_exists) {
				VerbosityDisplay("In Commands(): ERROR - File exists in the destination location already. -o flag not specified, so copy failed. STDC++ error details: " + ecTestZone.message() + " (std::errc::file_exists).\n");
				UserErrorDisplay("Sorry, but the file exists in the copy location already. Please try again later.\n");
			}
			else if (ecTestZone == std::errc::permission_denied) {
				VerbosityDisplay("In Commands(): ERROR - No sufficient permissions available for file access. STDC++ error details: " + ecTestZone.message() + " (std::errc::permission_denied).\n");
				UserErrorDisplay("Sorry, but there aren't any sufficient permissions to access the file. Please try again with elevated permissions.\n");
			}
			else if (ecTestZone == std::errc::is_a_directory) {
				VerbosityDisplay("In Commands(): ERROR - Source argument is a directory, and -d flag not specified, so copy failed. STDC++ error details: " + ecTestZone.message() + " (std::errc::is_a_directory).\n");
				UserErrorDisplay("Sorry, but the specified source argument is a directory, not a file.\nIf you want to copy the contents of a directory, use the -d argument.\nPlease try again later.\n");
			}
			else if (ecTestZone == std::errc::io_error) {
				VerbosityDisplay("In Commands(): ERROR - Unknown I/O error occured when copying. STDC++ error details: " + ecTestZone.message() + " (std::errc::io_error).\n");
				UserErrorDisplay("Sorry, but an unknown I/O error occured when copying.\nThis could possibly relate to losing access to the source file or destination directory, or even a hardware error.\nPlease try again later.\n");
			}
			else if (ecTestZone == std::errc::no_such_file_or_directory) {
				VerbosityDisplay("In Commands(): ERROR - No such file or directory exists in either the source or destination argument paths. STDC++ error details: " + ecTestZone.message() + " (std::errc::no_such_file_or_directory).\n");
				UserErrorDisplay("Sorry, but the specified source filepath or destination directory path does not exist.\nPlease check the specified arguments and try again later.\n");
			}
			else {
				// Unknown error
				VerbosityDisplay("In Commands(): ERROR - Unknown error when copying file. STDC++ error details: " + ecTestZone.message() + " (Error Code " + std::to_string(ecTestZone.value()) + ").\n");
				UserErrorDisplay("Sorry, but an unknown error of code " + std::to_string(ecTestZone.value()) + " occured when copying. Please try again later.\n");
			}
		}
		else {
			// Copy operation success message
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Copy operation successful!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	
		return;
	}

	// CopyFile
	else if (sCommand == "copyfile" || sCommand == "22") {

		std::string sOriginalFilePath = "";
		std::string sDestinationFilePath = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CopyFileHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[1] != "") {
					sOriginalFilePath = sStringDataCommandArgs[0];
					sDestinationFilePath = sStringDataCommandArgs[1];
				}
				else {
					// Error message
					VerbosityDisplay("In Commands() - ERROR: Vital argument not found.\n");
					UserErrorDisplay("ERROR: You need to have both the file location AND destination file directories included in your arguments.\nSee \"copyfile -h\" for more info.\n");
					
					return;
				}
			}
		}
		
		// Output title when user input
		if (sOriginalFilePath == "" || sDestinationFilePath == "") {
			CentreColouredText(" ___COPYFILE___ ", 1);
			std::cout << "\n\n";
			colour(LBLU, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Type \"*open\" without quotes to use the Windows File Dialogue to find necessary copy files.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Prompts
		if (sOriginalFilePath == "") {
			sOriginalFilePath = StrInput("Please input directory of original file (0 to exit): > ");
			if (sOriginalFilePath == "0") {
				Exiting();
				return;
			}
		}

		if (sOriginalFilePath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue("Select a File to Copy Contents From");
			sOriginalFilePath = FileCopyDialogue.GetRetrievedPathName();
			if (sOriginalFilePath == "") {
				Exiting();
				return;
			}
		}

		if (sDestinationFilePath == "") {
			sDestinationFilePath = StrInput("Please input directory of new destination file (0 to exit): > ");
			if (sDestinationFilePath == "0") {
				Exiting();
				return;
			}
		}

		if (sDestinationFilePath == "*open") {
			// Use the Windows File Dialogue
			std::cout << wordWrap("Opening the Windows File Dialogue Box...\n");
			FileOpenGUIEngine FileCopyDialogue;
			FileCopyDialogue.FileOpenDialogue("Select a File to Copy Contents From");
			sDestinationFilePath = FileCopyDialogue.GetRetrievedPathName();
			if (sDestinationFilePath == "") {
				Exiting();
				return;
			}
		}

		// Check for any speechmarks that might accidentally get passed to copy operation
		if (sOriginalFilePath[0] == '\"') {
			size_t nFirstMarkPos = sOriginalFilePath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sOriginalFilePath.find('\"', nFirstMarkPos) - 1;
			sOriginalFilePath = sOriginalFilePath.substr(nFirstMarkPos, nFinalMarkPos);
		}
		if (sDestinationFilePath[0] == '\"') {
			size_t nFirstMarkPos = sDestinationFilePath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sDestinationFilePath.find('\"', nFirstMarkPos) - 1;
			sDestinationFilePath = sDestinationFilePath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		// Copy file
		VerbosityDisplay("Copying file " + sOriginalFilePath + " to " + sDestinationFilePath + "...");
		std::cout << "Copying file...\n";
		if (!CopyFileA(sOriginalFilePath.c_str(), sDestinationFilePath.c_str(), false)) {
			VerbosityDisplay("In Commands() - ERROR: Existing file when copying to file directory detected. File copy operation has failed. GetLastError() error code: " + std::to_string(GetLastError()) + "\n");
			UserErrorDisplay("An error occured while copying the file.\nPossibly the original file is nonexistent?\n");
		}
		else {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("File successfully copied!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return;
	}

	// TextInfo
	else if (sCommand == "textinfo" || sCommand == "23") {
		std::string sText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				TextInfoHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				// Assign sText to sStringDataCommandArgs[0] to be used after the argument checking
				sText = sStringDataCommandArgs[0];
			}
		}

		// if not assigned by argument
		if (sText == "") {
			CentreColouredText(" ___TEXTINFO___ ", 1);
			std::cout << "\n\n";

			sText = StrInput("Please input the text string for the info (0 to exit): > ");
			if (sText == "0") {
				// Exit
				Exiting();
				return;
			}
		}
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nReading text and finalising data...\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		//
		// Check string for spaces, '.', and so on
		//

		int nNumOfWords = 0, nNumOfSentences = 0, nNumOfLetters = 0;
		// Add a space so the last word gets counted
		sText += ' ';

		// Count spaces, words, sentences
		for (int i = 0; i < sText.length(); i++) {
			// Spaces/Words
			if (sText[i] == ' ') {
				if (i - 1 > 0) {
					if (sText[i - 1] != ' ') nNumOfWords++;
				}
			}
			// Sentences
			else if (sText[i] == '.' || sText[i] == '?' || sText[i] == '!') nNumOfSentences++;
			// Letters
			else if (std::isalpha(sText[i])) nNumOfLetters++;
		}
		if (nNumOfSentences == 0) nNumOfSentences++; // because technically, it's one sentence

		// Display results
		colourSubheading();
		std::cout << "Results:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\n\nNumber of characters: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << sText.length() - 1 << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Number of letters: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nNumOfLetters << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Number of words: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nNumOfWords << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Number of sentences: ");
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << nNumOfSentences << "\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// ConfigAction
	else if (sCommand == "configaction" || sCommand == "24") {
		int nOption = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++)
		{
			if (cCommandArgs[i] == 'h') 
			{
				ConfigActionHelp();
				return;
			}
			else if (sStringOptionCommandArgs[0] == "readconfigfile") {
				nOption = 1;
			}
			else if (sStringOptionCommandArgs[0] == "writeconfigfile") {
				nOption = 2;
			}
			else if (sStringOptionCommandArgs[0] == "createconfigfile") {
				nOption = 3;
			}
			else if (sStringOptionCommandArgs[0] == "displayconfigobj") {
				nOption = 4;
			}
			else if (sStringOptionCommandArgs[0] == "displayconfigfile") {
				nOption = 5;
			}
		}

		// User-end UI if no arguments used
		if (nOption == 0) {
			OptionSelectEngine oseConfigAction;
			oseConfigAction.nSizeOfOptions = 5;
			std::string sOptions[] = {
				"Read from Configuration File to Memory",
				"Write from Memory to Configuration File",
				"Create new Configuration File",
				"Display Main Configuration Object Contents",
				"Display Configuration File Contents"
			};
			oseConfigAction.sOptions = sOptions;

			nOption = oseConfigAction.OptionSelect("Please select what you would like to interact with in the Configuration File System:", " ___CONFIGACTION___ ");
		}

		switch (nOption) {
		case 1:
			if (ConfigObjMain.ReadConfigFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Function has returned TRUE. No error has occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << "Function has returned FALSE. An error occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			break;

		case 2:
			if (ConfigObjMain.WriteConfigFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Function has returned TRUE. No error has occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << "Function has returned FALSE. An error occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			break;

		case 3:
			if (ConfigObjMain.CreateConfigFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Function has returned TRUE. No error has occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << "Function has returned FALSE. An error occured.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			break;

		case 4:
			std::cout << '\n';
			colourSubheading();
			std::cout << "Contents of Main Configuration Object:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n" << ConfigObjMain.GetConfigObjectContents() << '\n';

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Main configuration object contents output complete!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			break;

		case 5:
			std::cout << '\n';
			colourSubheading();
			std::cout << "Contents of Configuration File:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n" << ConfigObjMain.GetConfigFileContents();

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Configuration file contents output complete!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			break;

		case -1:
			Exiting();
			return;

		default:
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			break;
		}

		return;
	}

	// BeepSounds
	else if (sCommand == "beepsounds" || sCommand == "25") {
		bool bArgumentExecuted = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				BeepSoundsHelp();
				return;
			}
			else if (sStringOptionCommandArgs[i] == "missionimpossible") {
				RandomColourOutput("Playing Mission Impossible Theme...");
				std::cout << '\n';
				MissionImpossibleTheme();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "happybirthday") {
				RandomColourOutput("Playing Happy Birthday Song...");
				std::cout << '\n';
				HappyBirthdaySong();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "supermario") {
				RandomColourOutput("Playing Super Mario Theme...");
				std::cout << '\n';
				SuperMarioTheme();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "dundundun") {
				RandomColourOutput("Playing DunDunDun Sound...");
				std::cout << '\n';
				DunDunDunSound();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "imperialmarch") {
				RandomColourOutput("Playing Star Wars Imperial March Song...");
				std::cout << '\n';
				StarWarsImperialMarch();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "tetris") {
				RandomColourOutput("Playing Tetris Theme Song...");
				std::cout << '\n';
				TetrisTheme();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "dramatic") {
				RandomColourOutput("Playing A Dramatic Song...");
				std::cout << '\n';
				DramaticSong();
				bArgumentExecuted = true;
			}
			else if (sStringOptionCommandArgs[i] == "rickroll") {
				RandomColourOutput("Playing RickRoll Song...");
				std::cout << '\n';
				RickRollSong();
				bArgumentExecuted = true;
			}

		}

		// Something already executed in this command
		if (bArgumentExecuted == true) return;

		OptionSelectEngine oseBeepSounds;

		oseBeepSounds.nSizeOfOptions = 8;
		std::string sOptions[] = {
			"Mission Impossible Theme",
			"Happy Birthday Song",
			"Super Mario Theme",
			"DunDunDun Sound",
			"Star Wars Imperial March Song",
			"Tetris Theme Song",
			"A Dramatic Song",
			"RickRoll Song"
		};
		oseBeepSounds.sOptions = sOptions;

		int nChoice = oseBeepSounds.OptionSelect("Please select which beep-sound you would like to output:", " ___BEEP SOUNDS___ ");
		std::cout << '\n';
		
		switch (nChoice) {
		case 1:
			RandomColourOutput("Playing Mission Impossible Theme...");
			std::cout << '\n';
			MissionImpossibleTheme();
			break;
		case 2:
			RandomColourOutput("Playing Happy Birthday Song...");
			std::cout << '\n';
			HappyBirthdaySong();
			break;
		case 3:
			RandomColourOutput("Playing Super Mario Theme...");
			std::cout << '\n';
			SuperMarioTheme();
			break;
		case 4:
			RandomColourOutput("Playing DunDunDun Sound...");
			std::cout << '\n';
			DunDunDunSound();
			break;
		case 5:
			RandomColourOutput("Playing Star Wars Imperial March Song...");
			std::cout << '\n';
			StarWarsImperialMarch();
			break;
		case 6:
			RandomColourOutput("Playing Tetris Theme Song...");
			std::cout << '\n';
			TetrisTheme();
			break;
		case 7:
			RandomColourOutput("Playing A Dramatic Song...");
			std::cout << '\n';
			DramaticSong();
			break;
		case 8:
			RandomColourOutput("Playing RickRoll Song...");
			std::cout << '\n';
			RickRollSong();
			break;
		case -1:
			Exiting();
			return;
		default:
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
			Exiting();
			return;
		}

		return;
	}

	// RickRoll
	else if (sCommand == "rickroll" || sCommand == "26") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				RickRollHelp();
				return;
			}
		}

		// Rickroll
		// Props to Hell's Channel for keeping this youtube link alive!
		ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=z4JJ270xx98", 0, 0, SW_HIDE);

		return;
	}

	// ShellExecute
	else if (sCommand == "shellexecute" || sCommand == "27") {

		std::string sCommandText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ShellExecuteHelp();
				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sCommandText = sStringDataCommandArgs[0];
			}
		}

		// User Interface
		if (sCommandText == "") {
			CentreColouredText("___SHELLEXECUTE___", 1);
			std::cout << "\n\n";

			sCommandText = StrInput("Please input your desired CMD command to run (0 to exit): > ");

			// Exit on 0
			if (sCommandText == "0") {
				Exiting();
				return;
			}
		}

		// Display messages and execute command
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Executing command...\n\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Execute command
		system(sStringDataCommandArgs[0].c_str());

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nCommand execution successful!\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Hacker
	else if (sCommand == "hacker" || sCommand == "28") {

		// 1 for display, 2 for typing
		int nChoice = 0;
		// For custom file hacker type
		std::string sFileName = "";
		// Speed of characters
		uint64_t nOutputSpeed = 0;
		// Start immediately and skip messages
		bool bStartImmediately = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				HackerHelp();
				return;
			}
			else if (cCommandArgs[i] == 'i') {
				// Set start immediately to true
				bStartImmediately = true;
			}
			
			if (sStringOptionCommandArgs[i] == "display") {
				nChoice = 1;
			}
			else if (sStringOptionCommandArgs[i] == "type") {
				// Firstly, validate string to be a number
				// Don't check empty strings
				if (sStringDataCommandArgs[i] != "")
				{
					if (isNumberull(sStringDataCommandArgs[i]) == false) {
						colour(RED, ConfigObjMain.sColourGlobalBack);
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR: The speed argument given is not a number.\nPlease try again later, or see 'hacker -h' for more details.\n");
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
						return;
					}
					else nOutputSpeed = std::stoull(sStringDataCommandArgs[i]);
				}

				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "typecustom") {
				sFileName = sStringDataCommandArgs[i];

				// If statements for safety
				if (i + 1 < 128) {
					// Firstly, validate string to be a number
					// Don't check empty strings
					if (sStringDataCommandArgs[i + 1] != "") 
					{
						if (isNumberull(sStringDataCommandArgs[i + 1]) == false) {
							colour(RED, ConfigObjMain.sColourGlobalBack);
							VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
							UserErrorDisplay("ERROR: The speed argument given is not a number.\nPlease try again later, or see 'hacker -h' for more details.\n");
							colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
							return;
						}
						else nOutputSpeed = std::stoull(sStringDataCommandArgs[i + 1]);
					}
				}

				nChoice = 3;
			}
		}

		// User interface
		if (nChoice == 0) {
			OptionSelectEngine oseHacker;
			oseHacker.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Hacker Display",
				"Hacker Type",
				"Hacker Type (Custom File)"
			};
			oseHacker.sOptions = sOptions;

			nChoice = oseHacker.OptionSelect("Please select what type of hacker experience you want:", " ___HACKER___ ");

			if (nChoice == -1) {
				Exiting();
				return;
			}
		}
		else {
			CentreColouredText(" ___HACKER___ ", 1);
			std::cout << '\n';
		}

		// Display
		if (nChoice == 1) {

			// Display prompt if start immediately is false
			if (bStartImmediately == false) {
				// Warn user on how to stop before starting
				std::cout << wordWrap("\nThe program will output random numbers in green text to simulate a hacking-like environment.\nYou can press any key in the middle of the operation to stop.")
					<< wordWrap("\n\nPress any key to begin, or ESC to exit...\n");

				// 27 is ESC key
				if (_getch() == 27) {
					Exiting();
					return;
				}
			}

			// Set colour to light green - hacking colour
			colour(LGRN, ConfigObjMain.sColourGlobalBack);

			// Loop for outputting random numbers
			while (!_kbhit()) {
				std::cout << RandNum(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()) << ' ';
			}

			// Clear keyboard buffer to erase key from buffer
			ClearKeyboardBuffer();

			std::cout << "\n\n";
			Exiting();
			return;
		}

		// Typing
		else if (nChoice == 2) {
			
			if (bStartImmediately == false) {
				std::cout << wordWrap("\nWelcome to Hacker Type!\nThis will allow you to type like a hacker and impress your friends.\nThe idea was taken from https://www.hackertyper.net/. Type with any random keys to output text, and ESC to exit.\n\n");

				if (nOutputSpeed == 0) {
					nOutputSpeed = PositiveNumInputull("Please input desired character output speed (default is 3) (0 to exit): > ");
					if (nOutputSpeed <= 0) {
						Exiting();
						return;
					}
				}
			}
			else nOutputSpeed = 3; // Default

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Starting...\n\n";

			HackerTyper(nOutputSpeed);
			return;
		}

		// Typing with custom file
		else if (nChoice == 3) {

			if (bStartImmediately == false) {
				std::cout << wordWrap("\nWelcome to Hacker Type with Custom File support!\nThis will allow you to type like a hacker and impress your friends.\nThe idea was taken from https://www.hackertyper.net/. Type with any random keys to output text, and ESC to exit.\n\n");
			}

			if (sFileName == "") {
				sFileName = StrInput("Please input the filepath for the custom file (0 to exit): > ");
				if (sFileName == "0") {
					Exiting();
					return;
				}
			}
			
			if (bStartImmediately == false) {
				std::cout << '\n';

				if (nOutputSpeed == 0) {
					nOutputSpeed = PositiveNumInputull("Please input desired character output speed (default is 3) (0 to exit): > ");
					if (nOutputSpeed <= 0) {
						Exiting();
						return;
					}
				}
			}
			else nOutputSpeed = 3; // Default

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Starting...\n\n";

			HackerTyperFile(sFileName, nOutputSpeed);
			return;
		}

		// Error occured
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return;
	}

	// Calculator
	else if (sCommand == "calculator" || sCommand == "29") {

		// Declare variables
		bool bWorkingOut = false;
		bool bWorkingOutArgumentSet = false;
		bool bUseEuropeanMathNotation = false;
		std::string sCalculationInput = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CalculatorHelp();
				return;
			}
			else if (cCommandArgs[i] == 'w') {
				// Set switch to true
				bWorkingOut = true;

				bWorkingOutArgumentSet = true;
			}
			else if (cCommandArgs[i] == 'n') {
				// Set switch to false
				bWorkingOut = false;

				bWorkingOutArgumentSet = true;
			}
			else if (cCommandArgs[i] == 'e') {
				// Set EU Math Notation switch to true
				bUseEuropeanMathNotation = true;
			}
			
			if (sStringDataCommandArgs[i] != "") {
				sCalculationInput = sStringDataCommandArgs[i];
			}
		}

		// Only output title if bWorkingOutArgumentSet is true AND sCalculationInput has nothing, OR if bWorkingOutArgumentSet is false AND sCalculationInput has nothing.
		if ((bWorkingOutArgumentSet == true && sCalculationInput == "") || (bWorkingOutArgumentSet == false && sCalculationInput == "")) {
			CentreColouredText(" ___CALCULATOR___ ", 1);
			std::cout << "\n\n";
		}

		// No working out is default
		if (bWorkingOutArgumentSet == false && sCalculationInput != "") 
			bWorkingOut = false;
		// If the working out wasn't user-set
		else if (bWorkingOutArgumentSet == false) {
			bWorkingOut = YesNoInput("Would you like the calculator to display working out steps? [y/n] > ");
			std::cout << '\n';
		}

		// Start the Calculation Algorithm
		CalculationAlgorithm caCalculator;
		caCalculator.bDisplayWorkingOutProcess = bWorkingOut;
		caCalculator.UseEuropeanNotation(bUseEuropeanMathNotation);
		
		// Before loop, check if calculation string was brought in as an argument
		if (sCalculationInput != "") {

			// Calculate answer using SafeCalculate
			long double dCalculatedVal = caCalculator.SafeCalculate(sCalculationInput);

			// Output depending on if error occured
			if (caCalculator.GetLastCalculationErrorValue() > 0) {
				colour(LRED, ConfigObjMain.sColourGlobalBack);
				std::cout << " " << caCalculator.GetLastCalculationErrorInfo();
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n See 'calculator -h' for more info.\n";
			}
			else {
				std::cout << " Calculated Answer: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);

				// Output result
				if (bUseEuropeanMathNotation) {
					std::cout << FormatValueForEuropeanNotation(dCalculatedVal) << "\n";
				}
				else {
					// Send all floating-point information and formatting information to stringstream
					std::ostringstream ossFinalAns;
					ossFinalAns << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 - GetWholeNumberDigitLength(dCalculatedVal) - 1) << dCalculatedVal;

					std::cout << EradicateTrailingZeroes(ossFinalAns.str()) << "\n";
				}

				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

			return;
		}

		// Loop calculator, with exit possibility
		while (sCalculationInput != "exit") {
			sCalculationInput = StrInput("Input calculation (type \"exit\" to exit): > ");

			// Exit on exit input
			if (sCalculationInput == "exit") {
				Exiting();
				break;
			}
			else std::cout << '\n';

			// Calculate answer using SafeCalculate
			long double dCalculatedVal = caCalculator.SafeCalculate(sCalculationInput);

			// Output depending on if error occured
			if (caCalculator.GetLastCalculationErrorValue() > 0) {
				colour(LRED, ConfigObjMain.sColourGlobalBack);
				std::cout << " " << caCalculator.GetLastCalculationErrorInfo();
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n See 'calculator -h' for more info.\n\n";
			}
			else {
				std::cout << " Calculated Answer: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);

				// Open stringstream
				std::ostringstream ossFinalAns;
				// Send all floating-point information and formatting information
				ossFinalAns << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 - GetWholeNumberDigitLength(dCalculatedVal) - 1) << dCalculatedVal;

				// Finally, output result
				if (bUseEuropeanMathNotation) {
					std::cout << FormatValueForEuropeanNotation(dCalculatedVal) << "\n\n";
				}
				else {
					std::cout << EradicateTrailingZeroes(ossFinalAns.str()) << "\n\n";
				}

				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		return;
	}

	// Logoff
	else if (sCommand == "logoff" || sCommand == "30") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				LogoffHelp();
				return;
			}
		}

		// Log off
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Logging-off process initiated.\nLogging off...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		ExitWindowsEx(EWX_LOGOFF, SHTDN_REASON_MINOR_ENVIRONMENT);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Log-off successful.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Shutdown
	else if (sCommand == "shutdown" || sCommand == "31") {
		unsigned long int nTimeBeforeShutdown = 10;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ShutdownHelp();
				return;
			}
			else if (cCommandArgs[i] == 'c') {
				// Abort system shutdown
				AbortSystemShutdownA(NULL);
				
				// Output success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Shutdown successfully aborted.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				return;
			}
			else if (cCommandArgs[i] == 't') {
				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberul(sStringDataCommandArgs[0]) == false) {
						UserErrorDisplay("ERROR - Time argument is not a number.\nPlease try again later, or see 'shutdown -h' for more details.\n");

						return;
					}
					else nTimeBeforeShutdown = std::stoul(sStringDataCommandArgs[0]);
				}
				else {
					UserErrorDisplay("ERROR - No time argument found.\nPlease try again later, or see 'shutdown -h' for more details.\n");

					return;
				}
			}
		}

		InitiateSystemShutdownExA(NULL, (LPSTR)"User decided to shut down the computer through the ZeeTerminal program.", nTimeBeforeShutdown, false, false, SHTDN_REASON_MINOR_ENVIRONMENT);
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Computer will shut down in " << nTimeBeforeShutdown << " seconds.\nExecute 'shutdown -c' to abort.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Reboot
	else if (sCommand == "reboot" || sCommand == "restart" || sCommand == "32") {
		unsigned long int nTimeBeforeReboot = 10;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				RebootHelp();
				return;
			}
			else if (cCommandArgs[i] == 'c') {
				// Abort system shutdown
				AbortSystemShutdownA(NULL);

				// Output success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Reboot successfully aborted.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				return;
			}
			else if (cCommandArgs[i] == 't') {
				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberul(sStringDataCommandArgs[0]) == false) {
						UserErrorDisplay("ERROR - Time argument is not a number.\nPlease try again later, or see 'reboot -h' for more details.\n");

						return;
					}
					else nTimeBeforeReboot = std::stoul(sStringDataCommandArgs[0]);
				}
				else {
					UserErrorDisplay("ERROR - No time argument found.\nPlease try again later, or see 'reboot -h' for more details.\n");

					return;
				}
			}
		}

		InitiateSystemShutdownExA(NULL, (LPSTR)"User decided to reboot the computer through the ZeeTerminal program.", nTimeBeforeReboot, false, true, SHTDN_REASON_MINOR_ENVIRONMENT);
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Computer will reboot in " << nTimeBeforeReboot << " seconds.\nExecute 'reboot -c' to abort.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Hibernate
	else if (sCommand == "hibernate" || sCommand == "33") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				HibernateHelp();
				return;
			}
		}

		// Hibernate
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Hibernate process initiated.\nHibernating...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		SetSuspendState(true, false, true);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Hibernation successful.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;

	}

	// ResetExpl
	else if (sCommand == "resetexpl" || sCommand == "34") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ResetExplHelp();
				return;
			}
		}

		// Reset explorer.exe
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Resetting explorer.exe...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (ResetExpl() == true) {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "Explorer.exe reset successful!\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else {
			UserErrorDisplay("Explorer.exe reset failed.\nSee the Verbosity Messages for more info (you can enable them in the settings).\n");
		}

		return;
	}

	// MemTest
	else if (sCommand == "memtest" || sCommand == "35") {

		int nChoice = 0;
		uint64_t nNumOfPasses = 0; // -b: 100, -l: 10, -e: 2
		bool bKeypressBeforeDeallocation = false;
		bool bUseFullMemory = false;
		bool bSuccess = true;
		bool bMultiThreaded = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {

			if (cCommandArgs[i] == 'h') {
				MemTestHelp();
				return;
			}
			else if (cCommandArgs[i] == 'f') {
				nChoice = 1;
			}
			else if (cCommandArgs[i] == 'k') {
				bKeypressBeforeDeallocation = true;
			}
			else if (cCommandArgs[i] == 'a') {
				bUseFullMemory = true;
			}
			else if (cCommandArgs[i] == 'm') {
				bMultiThreaded = true;
			}
			else if (cCommandArgs[i] == 'b') {

				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR - Passes argument is not a number.\nPlease try again later, or see 'memtest -h' for more details.\n");

						return;
					}
					else nNumOfPasses = std::stoull(sStringDataCommandArgs[0]);
				}

				nChoice = 2;

			}
			else if (cCommandArgs[i] == 'l') {

				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR - Passes argument is not a number.\nPlease try again later, or see 'memtest -h' for more details.\n");

						return;
					}
					else nNumOfPasses = std::stoull(sStringDataCommandArgs[0]);
				}

				nChoice = 4;
			}
			else if (cCommandArgs[i] == 'e') {

				// Check if argument is a number
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == false) {
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
						UserErrorDisplay("ERROR - Passes argument is not a number.\nPlease try again later, or see 'memtest -h' for more details.\n");

						return;
					}
					else nNumOfPasses = std::stoull(sStringDataCommandArgs[0]);
				}

				nChoice = 6;
			}
		}

		// User Interface
		if (nChoice == 0) {
			OptionSelectEngine oseMemtest;
			oseMemtest.nSizeOfOptions = 7;
			std::string sOptions[] = {
				"Simple fill up and deallocate memory",
				"Fill up memory and perform binary search",
				"Fill up memory and perform binary search (Multithreaded)",
				"Fill up memory and perform linear check search",
				"Fill up memory and perform linear check search (Multithreaded)",
				"Fill up memory and perform extended linear check search",
				"Fill up memory and perform extended linear check search (Multithreaded)",
			};
			oseMemtest.sOptions = sOptions;

			nChoice = oseMemtest.OptionSelect("Please select how you would like to test your computer's memory:", " ___MEMTEST___ ");

			if (nChoice == -1) {
				// Exit
				Exiting();
				return;
			}
		}

		// Multithreaded options setter
		if (nChoice == 3) {
			bMultiThreaded = true;
			nChoice = 2;
		}
		else if (nChoice == 5) {
			bMultiThreaded = true;
			nChoice = 4;
		}
		else if (nChoice == 7) {
			bMultiThreaded = true;
			nChoice = 6;
		}

		// Simple fill up and deallocate memory
		if (nChoice == 1) {
			CentreColouredText(" ___MEMTEST SIMPLE ALLOCATE & DEALLOCATE___ ", 1);

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nStarting a simple fill-up and memory deallocation process...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteFillUpDeallocate;
			mteFillUpDeallocate.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteFillUpDeallocate.FillMemoryToMaximum(bKeypressBeforeDeallocation);
		}

		// Fill up memory and perform x binary searches
		else if (nChoice == 2) 
		{
			CentreColouredText(" ___MEMTEST BINARY SEARCH___ ", 1);

			// When not inputted as an argument
			if (nNumOfPasses == 0) {
				std::cout << "\n\n";
				colourHighlight();
				std::cout << wordWrap("Welcome to the Binary Search Memory Test!");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n\nThis will fill up the memory on your computer and perform binary search tests on it.\n");
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("NOTE: You can stop the test at any time by pressing any key in the duration of the test.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (bMultiThreaded == true) {
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("NOTE: This test will run with multithreading. Beware of CPU throttling and temperatures.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				std::cout << '\n';
				nNumOfPasses = PositiveNumInputull("Please input the number of binary search passes (100 is default, 0 to exit): > ");

				if (nNumOfPasses <= 0) {
					Exiting();
					return;
				}
			}

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nStarting a memory fill-up and binary search test...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteBinarySearch;
			mteBinarySearch.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteBinarySearch.PerformBinarySearchOnMemory(nNumOfPasses, bMultiThreaded);
		}

		// Fill up memory and perform x linear check searches
		else if (nChoice == 4) 
		{
			CentreColouredText(" ___MEMTEST LINEAR CHECK SEARCH___ ", 1);

			// When not inputted as an argument
			if (nNumOfPasses == 0) {
				std::cout << "\n\n";
				colourHighlight();
				std::cout << wordWrap("Welcome to the Linear Check Search Memory Test!");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n\nThis will fill up the memory on your computer and perform linear check search tests on it.\n");
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("NOTE: This test may take some time.\nNOTE: You can stop the test at any time by pressing any key during the test.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (bMultiThreaded == true) {
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("NOTE: This test will run with multithreading. Beware of CPU throttling and temperatures.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				std::cout << '\n';
				
				nNumOfPasses = PositiveNumInputull("Please input the number of linear check search passes (10 is default, 0 to exit): > ");

				if (nNumOfPasses <= 0) {
					Exiting();
					return;
				}
			}

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nStarting a memory fill-up and linear check search test...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteLinearSearch;
			mteLinearSearch.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteLinearSearch.PerformLinearSearchOnMemory(nNumOfPasses, bMultiThreaded);
		}

		// Fill up memory and perform x extended linear check searches
		else if (nChoice == 6) 
		{
			CentreColouredText(" ___MEMTEST EXTENDED LINEAR CHECK SEARCH___ ", 1);

			// When not inputted as an argument
			if (nNumOfPasses == 0) {
				std::cout << "\n\n";
				colourHighlight();
				std::cout << wordWrap("Welcome to the Extended Linear Check Search Memory Test!");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n\nThis will fill up the memory on your computer and perform extended linear check search tests on it.")
					<< wordWrap("\nThis won't only comprise of checking digits only (like the non-extended test), but also performing operations on memory, before reiterating to the next memory block.\n");
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("NOTE: This test may take a lot of time.\nNOTE: You can stop the test at any time by pressing any key during the test.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (bMultiThreaded == true) {
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << wordWrap("NOTE: This test will run with multithreading. Beware of CPU throttling and temperatures.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				std::cout << '\n';
				nNumOfPasses = PositiveNumInputull("Please input the number of extended linear check search passes (2 is default, 0 to exit): > ");

				if (nNumOfPasses <= 0) {
					Exiting();
					return;
				}
			}

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nStarting a memory fill-up and extended linear check search test...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			MemoryTestEngine mteLinearSearch;
			mteLinearSearch.bUseTotalPhysicalCapacity = bUseFullMemory;
			bSuccess = mteLinearSearch.PerformExtendedLinearSearchOnMemory(nNumOfPasses, bMultiThreaded);
		}

		// Failed, unknown return value
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR: An unknown error occured. Please try again later.\n");

			return;
		}

		if (bSuccess == true) {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("Memory Test or Allocation & Deallocation Complete!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return;
	}

	// RandCol
	else if (sCommand == "randcol" || sCommand == "36") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				RandColHelp();
				return;
			}
		}

		std::cout << "Setting random colours...\n";

		// Calculate random numbers
		ConfigObjMain.sColourGlobal = NumberToColour(RandNum(16, 1));
		ConfigObjMain.sColourGlobalBack = NumberToColour(RandNum(16, 1));
		
		// Write new values to config file
		ConfigObjMain.WriteConfigFile();

		// Finally, set colours
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Random colours successfully set!") << '\n';

		return;
	}

	// Pause
	else if (sCommand == "pause" || sCommand == "37") {

		bool bEnterKeypressLimit = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				PauseHelp();
				return;
			}
			else if (cCommandArgs[i] == 'e') {
				bEnterKeypressLimit = true;
			}
		}

		if (bEnterKeypressLimit == false) {
			std::cout << "Press any key to continue...";
			_getch();
			std::cout << '\n';
		}
		else {
			std::cout << "Press ENTER to continue...: "; // Use the colon character, similar to Powershell
			std::cin.get();
		}

		return;
	}

	// CommandNum
	else if (sCommand == "commandnum" || sCommand == "38") {
		
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CommandNumHelp();
				return;
			}
		}

		// Output number of inputted commands
		std::cout << '\n';
		colourSubheading();
		std::cout << wordWrap("Since the start of the session, including this command, you have inputted:") << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << wordWrap("\nNumber of total commands: " + std::to_string(nNumOfInputtedCommands) + '\n');
		std::cout << wordWrap("Number of commands that were genuine and registered: " + std::to_string(nNumOfSuccessfulInputtedCommands) + '\n');
		std::cout << wordWrap("Number of commands that were unsuccessful and undefined: " + std::to_string(nNumOfInputtedCommands - nNumOfSuccessfulInputtedCommands) + '\n');

		return;
	}

	// SlowChar
	else if (sCommand == "slowchar" || sCommand == "39") {

		bool bUseRandomColours = false;
		std::string sText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				SlowCharHelp();
				return;
			}
			else if (cCommandArgs[i] == 'r') {
				bUseRandomColours = true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sText = sStringDataCommandArgs[0];
			}
		}

		// User Interface
		if (sText == "") {
			CentreColouredText(" ___SLOWCHAR___ ", 1);

			sText = StrInput("\n\nPlease input the text that you want to be outputted slowly (0 to exit): > ");
			if (sText == "0") {
				Exiting();
				return;
			}
			else std::cout << '\n';
		}

		// Output slow characters depending on colours
		std::cout << "Slow Character Text:\n";
		if (bUseRandomColours == true) {
			SlowCharColourful(sText, false);
		}
		else {
			slowcharfn(true, sText);
		}

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nOutput successful!\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// ReverseText
	else if (sCommand == "reversetext" || sCommand == "40") {

		bool bUseSlowChar = false;
		std::string sText = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				ReverseTextHelp();
				return;
			}
			else if (cCommandArgs[i] == 's') {
				bUseSlowChar = true;
			}
			else if (sStringDataCommandArgs[0] != "") {
				sText = sStringDataCommandArgs[0];
			}
		}

		if (sText == "") {
			CentreColouredText(" ___REVERSETEXT___ ", 1);

			sText = StrInput("\n\nPlease input text that you want to output in reverse (0 to exit): > ");
			if (sText == "0") {
				Exiting();
				return;
			}
		}

		// Output text in reverse
		std::cout << "Reversed Text:\n\n";
		std::reverse(sText.begin(), sText.end());
		if (bUseSlowChar == true) {
			slowcharfn(true, sText);
		}
		else {
			std::cout << sText;
		}
		
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nOutput successful!\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		
		return;
	}

	// Notes
	else if (sCommand == "notes" || sCommand == "41") {

		// Declare necessary variables
		int nChoice = 0;
		std::string sNotesText = "";
		uint64_t nNotesLine = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				NotesHelp();
				return;
			}
			else if (cCommandArgs[i] == 'a') {
				if (sStringDataCommandArgs[0] != "") {
					sNotesText = sStringDataCommandArgs[0];
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of note text argument found.\nPlease make sure that's there, and try again.\nSee \"notes -h\" for more info.\n");

					return;
				}

				nChoice = 6;
			}
			else if (cCommandArgs[i] == 'r') {
				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == true) {
						nNotesLine = std::stoull(sStringDataCommandArgs[0]) - 1;
						if (nNotesLine > NotesMain.GetCurrentNotesCount() - 1) {
							// Line number too large
							VerbosityDisplay("In Commands() - ERROR: String-based number argument is too large/small in correlation to number of notes currently in notes array.\n");
							UserErrorDisplay("ERROR - Line number is too large/small, and is accessing a nonexistent note line. Please change the argument, and try again.\nSee \"notes -h\" for more info.\n");

							return;
						}
					}
					else {
						// Not a number or it is negative
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument, or argument was negative.\n");
						UserErrorDisplay("ERROR - Line number is not a number, or it is negative. Please change the argument, and try again.\nSee \"notes -h\" for more info.\n");

						return;
					}
				}
				else {
					// Last note indication
					nNotesLine = NotesMain.GetCurrentNotesCount() - 1;
				}

				nChoice = 7;
			}
			else if (cCommandArgs[i] == 'm') {

				if (sStringDataCommandArgs[0] != "") {
					if (isNumberull(sStringDataCommandArgs[0]) == true) {
						nNotesLine = std::stoull(sStringDataCommandArgs[0]) - 1;
					}
					else {
						// Not a number or it is negative
						VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument, or argument was negative.\n");
						UserErrorDisplay("ERROR - Line number is not a number, or it is negative. Please change the argument, and try again.\nSee \"notes -h\" for more info.\n");

						return;
					}
				}
				else {
					// Last note indication
					nNotesLine = NotesMain.GetCurrentNotesCount() - 1;
				}

				// Notes text
				if (sStringDataCommandArgs[1] != "") {
					sNotesText = sStringDataCommandArgs[1];
				}
				else {
					VerbosityDisplay("ERROR: In Commands() - Vital argument not found.\n");
					UserErrorDisplay("ERROR - No form of note text argument found.\nPlease make sure that's there, and try again.\nSee \"notes -h\" for more info.\n");

					return;
				}

				nChoice = 8;
			}
			else if (cCommandArgs[i] == 'e') {
				nChoice = 1;
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 2;
			}
			else if (cCommandArgs[i] == 'c') {
				nChoice = 3;
			}
			else if (cCommandArgs[i] == 'u') {
				nChoice = 4;
			}
			else if (cCommandArgs[i] == 'f') {
				nChoice = 5;
			}
		}

		// User Interface
		if (nChoice == 0) {
			OptionSelectEngine oseNotes;
			oseNotes.nSizeOfOptions = 5;
			std::string sOptions[] = {
				"Edit Notes",
				"Output All Notes",
				"Clear All Notes",
				"Update Memory Notes with File Notes",
				"Update File Notes with Memory Notes"
			};
			oseNotes.sOptions = sOptions;

			nChoice = oseNotes.OptionSelect("Please select what you would like to do to the current notes setup:", " ___NOTES___ ");

			if (nChoice == -1) {
				Exiting();
				return;
			}
		}

		// Add sNotesText
		else if (nChoice == 6) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Adding new note...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			if (NotesMain.AddNoteToArray(NotesMain.GetCurrentNotesCount(), sNotesText)) {
				if (NotesMain.WriteToNotesFile()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Note addition successful!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and save notes.\n");
					UserErrorDisplay("ERROR - Failed to save new added notes. Exiting anyway...\n");

					return;
				}

				return;
			}
			else {
				UserErrorDisplay("Note addition failed. Possibly a bug.\n");

				return;
			}
		}

		// Remove nNoteLine
		else if (nChoice == 7) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Removing note...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Modify
			if (NotesMain.AddNoteToArray(nNotesLine, ""))
			{
				if (NotesMain.WriteToNotesFile()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Removal successful!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and save notes.\n");
					UserErrorDisplay("ERROR - Failed to remove the notes from the notes file. Exiting anyway...\n");

					return;
				}
			}
			else {
				UserErrorDisplay("Removal failed. Possibly because no notes currently exist?\n");

				return;
			}

			return;
		}

		// Modify note nNoteLine
		else if (nChoice == 8) {

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "Modifying note with argument text...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Modify
			if (NotesMain.AddNoteToArray(nNotesLine, sNotesText))
			{
				if (NotesMain.WriteToNotesFile()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "Modifying successful!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and save notes.\n");
					UserErrorDisplay("ERROR - Failed to save modified notes. Exiting anyway...\n");

					return;
				}

				return;
			}
			else {
				UserErrorDisplay("Modifying failed. Possibly the note line is too high?\n");

				return;
			}

			return;
		}


		/* Main User Interface parts */
		//
		// Notes Editor
		if (nChoice == 1)
		{
			NotesSystemUI NotesUI;
			NotesUI.NotesEditor();
			return;
		}

		// Notes Viewer
		else if (nChoice == 2) {
			NotesSystemUI NotesUI;
			NotesUI.NotesViewer();
			return;
		}

		// Clear Notes
		else if (nChoice == 3) {

			std::cout << '\n';
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			if (YesNoInput("WARNING: ALL NOTES WILL BE LOST WHEN CLEARED, BOTH ON MEMORY AND ON STORAGE.\nAre you absolutely sure you want to continue? [y for yes, n for no]: > "))
			{
				// Clear all notes - confirmed
				if (NotesMain.ClearAllNotes()) {
					colour(LGRN, ConfigObjMain.sColourGlobalBack);
					std::cout << "All notes have been successfully cleared!\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
				else {
					UserErrorDisplay("ERROR - Failed to clear notes on file, but notes on memory has been fully cleared.\nThis is an unknown error. Please try again later.\n");
				}
			}
			else {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Note-clearing cancelled.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}

		}

		// Update notes array with notes file
		else if (nChoice == 4) {

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Updating Memory Notes (Notes Array)...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			if (NotesMain.ReadFromNotesFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("Memory notes (notes array) has successfully been updated with the Notes File's contents!\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				UserErrorDisplay("ERROR - Memory notes (notes array) has failed to update with the Notes File's contents.\nSee the Verbosity Messages for more info (settings?)\n");
			}

			return;
		}

		// Update notes file with notes array
		else if (nChoice == 5) {

			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Updating Notes File...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			if (NotesMain.WriteToNotesFile()) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("The Notes file has successfully been updated with the Memory notes' (notes array's) contents!\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else {
				UserErrorDisplay("ERROR - The Notes File has failed to update with the Memory notes (notes array) contents.\nSee the Verbosity Messages for more info (settings?)\n");
			}

			return;
		}

		// Error
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");

			return;
		}
	}

	// FileParse
	else if (sCommand == "fileparse" || sCommand == "42") {
		std::string sFilePath = "";
		bool bExitOnCompletion = false;

		// Do not run command if fileparse mode is already on and running
		if (bRunningFromScriptOrArgCommand) {
			UserErrorDisplay("ERROR - FileParse is already running, and another script cannot be run while this one is running.\nPlease try again when not running from a script.\n");
			return;
		}

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				FileParseHelp();
				return;
			}
			else if (cCommandArgs[i] == 'e') {
				bExitOnCompletion = true;
			}

			if (sStringOptionCommandArgs[i] == "exit") {
				bExitOnCompletion = true;
			}

			if (sStringDataCommandArgs[0] != "") {
				sFilePath = sStringDataCommandArgs[0];
			}
		}

		if (sFilePath == "") {
			CentreColouredText(" ___FILEPARSE___ ", 1);
			std::cout << '\n';

			colour(NumberToColour(RandNum(15, 1)), ConfigObjMain.sColourGlobalBack);
			slowcharfn(true, "Welcome to FileParse!");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << "This is where you can run scripts on ZeeTerminal, where commands can be automatically executed.\n\n";

			sFilePath = StrInput("Please input filepath for custom script (0 to exit, '*open' to open file dialogue): > ");

			// Exit on 0
			if (sFilePath == "0") {
				Exiting();
				return;
			}
		}

		// Windows File Dialogue command
		if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "\nOpening with the Windows File Dialogue...\n";
			FileOpenGUIEngine ReadCommand;
			ReadCommand.FileOpenDialogue("Open a Script File to Execute");
			sFilePath = ReadCommand.GetRetrievedPathName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return;
			}
		}

		// Initialise FileParse system
		if (!InitialiseFileParse(sFilePath, bExitOnCompletion)) {
			UserErrorDisplay("ERROR - An error occured while initialising the FileParse System. Possibly a nonexistent file path?\n");
			return;
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Executing FileParse Script...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		bLastCommandWasFileParse = true; // because this command IS the FileParse command.
		return;
	}

	// Disp
	else if (sCommand == "disp" || sCommand == "43") {
		bool bDispSettingChoice = false;
		bool bDispSettingChoiceArgument = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				DispHelp();
				return;
			}
			else if (cCommandArgs[i] == 'y') {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = true;
			}
			else if (cCommandArgs[i] == 'n') {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = false;
			}

			if (sStringOptionCommandArgs[i] == "on") {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = true;
			}
			else if (sStringOptionCommandArgs[i] == "off") {
				bDispSettingChoiceArgument = true;
				bDispSettingChoice = false;
			}
		}

		if (!bDispSettingChoiceArgument) {
			OptionSelectEngine oseDisp;
			oseDisp.nSizeOfOptions = 2;
			std::string sOptions[] = {
				"DISP On (Default)",
				"DISP Off"
			};
			oseDisp.sOptions = sOptions;

			int nChoice = 
				oseDisp.OptionSelect("This command allows you to turn command interface output on or off.\n"
									"The command interface is the starting screen where the \"Command: > \" text is shown.\n"
									"This also, when executing scripts, disables outputting the command that is about to run.\n\n"
									"Please select what you would like to set the DISP switch to:", " ___DISP___ ");

			if (nChoice == 1) {
				bDispSettingChoice = true;
			}
			else if (nChoice == 2) {
				bDispSettingChoice = false;
			}
			else if (nChoice == -1) {
				Exiting();
				return;
			}
			else {
				// Unknown error
				VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
				UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
				return;
			}
		}

		// Set bDisp switch
		bDisp = bDispSettingChoice;

		// Output success message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "DISP has successfully been switched ";
		if (bDisp == true) {
			std::cout << "on.\n";
		}
		else std::cout << "off.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// SysInfo
	else if (sCommand == "sysinfo" || sCommand == "44") {
		SystemInfo siSysInfo;

		CentreColouredText(" ___SYSINFO___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				// Execute help function, exit
				SysInfoHelp();
				return;
			}
		}

		// Display system info //
		std::cout << wordWrap("\nBelow is some system information about this computer:\n\n");

		// OS Name
		std::cout << wordWrap("OS Name: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetOSName()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << wordWrap("OS Build Info: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetOSBuildInfo()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// System memory
		std::cout << wordWrap("Total System Memory: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(EradicateTrailingZeroes(std::to_string(siSysInfo.GetSysMemorySizeInGiB()))) << " GiB\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// System virtual memory
		std::cout << wordWrap("Total System Virtual Memory: "); 
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(EradicateTrailingZeroes(std::to_string(siSysInfo.GetSysVirtualMemorySizeInGiB()))) << " GiB\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// System page file size
		std::cout << wordWrap("System Page File Size: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(EradicateTrailingZeroes(std::to_string(siSysInfo.GetSysPageSizeInGiB()))) << " GiB\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// CPU name
		std::cout << wordWrap("CPU Model Name: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetCPUModelName()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Cpu cores
		std::cout << wordWrap("CPU Logical Core Count: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(std::to_string(siSysInfo.GetCPUCoreCount())) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Cpu architecture
		std::cout << wordWrap("CPU Architecture: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetCPUArchitectureAsName()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Lowest memory address
		std::cout << wordWrap("Lowest Accessible Memory Address: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetLowestAccessibleMemoryAddress()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Highest memory address
		std::cout << wordWrap("Highest Accessible Memory Address: ");
		colour(LBLU, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap(siSysInfo.GetHighestAccessibleMemoryAddress()) << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Einstein
	else if (sCommand == "einstein" || sCommand == "45") {

		bool bSlowcharOutput = false;
		bool bRandColourOutput = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				EinsteinHelp();
				return;
			}
			else if (cCommandArgs[i] == 's') {
				bSlowcharOutput = true;
			}
			else if (cCommandArgs[i] == 'c') {
				bRandColourOutput = true;
			}
		}

		// Output depending on request
		std::string sQuote = "\"" + GetEinsteinQuote(RandNum(50, 1)) + "\"";
		if (bSlowcharOutput && bRandColourOutput) {
			SlowCharColourful(sQuote, false);
		}
		else if (bSlowcharOutput && !bRandColourOutput) {
			slowcharfn(false, sQuote);
		}
		else if (bRandColourOutput && !bSlowcharOutput) {
			RandomColourOutput(sQuote);
		}
		else {
			std::cout << wordWrap(sQuote);
		}

		std::cout << "\n";
		colour(NumberToColour(RandNum(15, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "- Albert Einstein\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Edison
	else if (sCommand == "edison" || sCommand == "46") {

		bool bSlowcharOutput = false;
		bool bRandColourOutput = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				EdisonHelp();
				return;
			}
			else if (cCommandArgs[i] == 's') {
				bSlowcharOutput = true;
			}
			else if (cCommandArgs[i] == 'c') {
				bRandColourOutput = true;
			}
		}

		// Output depending on request
		std::string sQuote = "\"" + GetEdisonQuote(RandNum(50, 1)) + "\"";
		if (bSlowcharOutput && bRandColourOutput) {
			SlowCharColourful(sQuote, false);
		}
		else if (bSlowcharOutput && !bRandColourOutput) {
			slowcharfn(false, sQuote);
		}
		else if (bRandColourOutput && !bSlowcharOutput) {
			RandomColourOutput(sQuote);
		}
		else {
			std::cout << wordWrap(sQuote);
		}

		std::cout << "\n";
		colour(NumberToColour(RandNum(15, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "- Thomas Edison\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Tesla
	else if (sCommand == "tesla" || sCommand == "47") {

		bool bSlowcharOutput = false;
		bool bRandColourOutput = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				TeslaHelp();
				return;
			}
			else if (cCommandArgs[i] == 's') {
				bSlowcharOutput = true;
			}
			else if (cCommandArgs[i] == 'c') {
				bRandColourOutput = true;
			}
		}

		// Output depending on request
		std::string sQuote = "\"" + GetTeslaQuote(RandNum(50, 1)) + "\"";
		if (bSlowcharOutput && bRandColourOutput) {
			SlowCharColourful(sQuote, false);
		}
		else if (bSlowcharOutput && !bRandColourOutput) {
			slowcharfn(false, sQuote);
		}
		else if (bRandColourOutput && !bSlowcharOutput) {
			RandomColourOutput(sQuote);
		}
		else {
			std::cout << wordWrap(sQuote);
		}

		std::cout << "\n";
		colour(NumberToColour(RandNum(15, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "- Nikola Tesla\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Cow
	else if (sCommand == "cow" || sCommand == "48") {

		std::string sText = "";
		std::string sRandomColour = ConfigObjMain.sColourGlobal;
		int nChoice = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CowHelp();
				return;
			}
			else if (cCommandArgs[i] == 'c') {
				sRandomColour = NumberToColour(RandNum(16, 1));
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 1;
			}

			if (sStringOptionCommandArgs[i] == "quote") {
				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "saytext") {
				if (sStringDataCommandArgs[i] == "") {
					VerbosityDisplay("ERROR: In Commands() - Could not detect any argument string after option.\n");
					UserErrorDisplay("ERROR - No text data argument found. Please check for a text argument, and try again.\nType \"cow -h\" for more info.\n");
					return;
				}
				else {
					sText = sStringDataCommandArgs[i];
					nChoice = 3;
				}
			}
		}

		if (nChoice == 0) {
			OptionSelectEngine oseAnimal;
			oseAnimal.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Output cow",
				"Output cow with quote",
				"Output cow with custom text"
			};
			oseAnimal.sOptions = sOptions;

			nChoice = oseAnimal.OptionSelect("Please select how you would like to output a cow:", " ___COW___ ");
		}

		if (nChoice == 1) {
			OutputCow("", sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 2) {
			int nRandQuoteSet = std::roundl(RandNum(2, 0));
			if (nRandQuoteSet == 2) {
				sText = GetTeslaQuote(RandNum(50, 1));
			}
			else if (nRandQuoteSet == 1) {
				sText = GetEdisonQuote(RandNum(50, 1));
			}
			else if (nRandQuoteSet == 0) {
				sText = GetEinsteinQuote(RandNum(50, 1));
			}

			OutputCow(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 3) {
			if (sText == "") {
				sText = StrInput("Please input desired custom text for the cow to output: > ");
			}

			OutputCow(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == -1) {
			Exiting();
			return;
		}
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return;
	}

	// Cat
	else if (sCommand == "cat" || sCommand == "49") {
		std::string sText = "";
		std::string sRandomColour = ConfigObjMain.sColourGlobal;
		int nChoice = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CatHelp();
				return;
			}
			else if (cCommandArgs[i] == 'c') {
				sRandomColour = NumberToColour(RandNum(16, 1));
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 1;
			}

			if (sStringOptionCommandArgs[i] == "quote") {
				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "saytext") {
				if (sStringDataCommandArgs[i] == "") {
					VerbosityDisplay("ERROR: In Commands() - Could not detect any argument string after option.\n");
					UserErrorDisplay("ERROR - No text data argument found. Please check for a text argument, and try again.\nType \"cat -h\" for more info.\n");
					return;
				}
				else {
					sText = sStringDataCommandArgs[i];
					nChoice = 3;
				}
			}
		}

		if (nChoice == 0) {
			OptionSelectEngine oseAnimal;
			oseAnimal.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Output cat",
				"Output cat with quote",
				"Output cat with custom text"
			};
			oseAnimal.sOptions = sOptions;

			nChoice = oseAnimal.OptionSelect("Please select how you would like to output a cat:", " ___CAT___ ");
		}

		if (nChoice == 1) {
			OutputCat("", sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 2) {
			int nRandQuoteSet = std::roundl(RandNum(2, 0));
			if (nRandQuoteSet == 2) {
				sText = GetTeslaQuote(RandNum(50, 1));
			}
			else if (nRandQuoteSet == 1) {
				sText = GetEdisonQuote(RandNum(50, 1));
			}
			else if (nRandQuoteSet == 0) {
				sText = GetEinsteinQuote(RandNum(50, 1));
			}

			OutputCat(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 3) {
			if (sText == "") {
				sText = StrInput("Please input desired custom text for the cat to output: > ");
			}

			OutputCat(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == -1) {
			Exiting();
			return;
		}
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return;
	}
	   
	// Bunny
	else if (sCommand == "bunny" || sCommand == "50") {
		std::string sText = "";
		std::string sRandomColour = ConfigObjMain.sColourGlobal;
		int nChoice = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				BunnyHelp();
				return;
			}
			else if (cCommandArgs[i] == 'c') {
				sRandomColour = NumberToColour(RandNum(16, 1));
			}
			else if (cCommandArgs[i] == 'o') {
				nChoice = 1;
			}

			if (sStringOptionCommandArgs[i] == "quote") {
				nChoice = 2;
			}
			else if (sStringOptionCommandArgs[i] == "saytext") {
				if (sStringDataCommandArgs[i] == "") {
					VerbosityDisplay("ERROR: In Commands() - Could not detect any argument string after option.\n");
					UserErrorDisplay("ERROR - No text data argument found. Please check for a text argument, and try again.\nType \"bunny -h\" for more info.\n");
					return;
				}
				else {
					sText = sStringDataCommandArgs[i];
					nChoice = 3;
				}
			}
		}

		if (nChoice == 0) {
			OptionSelectEngine oseAnimal;
			oseAnimal.nSizeOfOptions = 3;
			std::string sOptions[] = {
				"Output bunny",
				"Output bunny with quote",
				"Output bunny with custom text"
			};
			oseAnimal.sOptions = sOptions;

			nChoice = oseAnimal.OptionSelect("Please select how you would like to output a bunny:", " ___BUNNY___ ");
		}

		if (nChoice == 1) {
			OutputBunny("", sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 2) {
			int nRandQuoteSet = std::roundl(RandNum(2, 0));
			if (nRandQuoteSet == 2) {
				sText = GetTeslaQuote(RandNum(50, 1));
			}
			else if (nRandQuoteSet == 1) {
				sText = GetEdisonQuote(RandNum(50, 1));
			}
			else if (nRandQuoteSet == 0) {
				sText = GetEinsteinQuote(RandNum(50, 1));
			}

			OutputBunny(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == 3) {
			if (sText == "") {
				sText = StrInput("Please input desired custom text for the bunny to output: > ");
			}

			OutputBunny(sText, sRandomColour, ConfigObjMain.sColourGlobalBack);
		}
		else if (nChoice == -1) {
			Exiting();
			return;
		}
		else {
			VerbosityDisplay("In Commands() - ERROR: Unknown return value from OptionSelectEngine::OptionSelect().\n");
			UserErrorDisplay("ERROR - Unknown error occured. Please try again later.\n");
		}

		return;
	}

	else if (sCommand == "test") {
		
	}

	// Unknown command - fail
	else {
		colour(RED, ConfigObjMain.sColourGlobalBack);
		std::cout << "Unknown command ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\"' << sCommandInputRAW << "\"";
		colour(LRED, ConfigObjMain.sColourGlobalBack);
		std::cout << ".\nPlease make sure you have inputted a listed command, and try again.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Log the failed command if enabled
		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging) {
			LogFileMain.AddLogLine("Command execution [" + sCommand + "] failed. Command invalid or not found.", 3);
		}

		// Decrement number of successful commands, as it would have been incremented before entering this function
		nNumOfSuccessfulInputtedCommands--;
		return;
	}

	return;
}
