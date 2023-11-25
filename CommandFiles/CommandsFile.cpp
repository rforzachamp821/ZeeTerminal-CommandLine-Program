// External function definitions
void					ResetColour();
std::string				wordWrap(std::string, long long int, long long int);
void					CentreColouredText(std::string, short int);
void					colourSubheading();
bool					isNumberld(const std::string);
bool					isNumberll(const std::string);
bool					isNumberl(const std::string);
bool					isNumberi(const std::string);
bool					isNumberull(const std::string);
bool					isNumberul(const std::string);
long double				NumInputld(std::string);
long long int			NumInputll(std::string);
long int				NumInputl(std::string);
int						NumInputi(std::string);
bool					SetWindowTitle(std::string);
void					slowcharCentredFn(bool, std::string);
void					slowcharfn(bool, std::string);
void					SlowCharColourful(std::string, bool);
std::string				CentreText(std::string);
void					SetCursorAttributes();
void					RandomColourOutput(std::string);
long double				RandNum(long double, long double);
void					UserErrorDisplay(std::string);
uint64_t				PositiveNumInputull(std::string);
unsigned long int		PositiveNumInputul(std::string);

#include "Settings.cpp"
#include "CPUStress.cpp"
#include "CommandFileAssets.cpp"
#include "CalculationAlgorithm.cpp"


// External variable definitions
extern std::string				sCommandInputRAW;
extern std::string				sStringOptionCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
                                                                         // on multi-argument commands.
extern std::string				sStringDataCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
                                                                       // on multi-argument commands.
extern RGBColourPresetSystem	RGBPreset[3];
extern ConfigFileSystem			ConfigObjMain;
extern NotesSystem				NotesMain;
extern bool						bAnsiVTSequences;

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
		bInput = YesNo("Is this program called ZeeTerminal? [y/n] > ");
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
		bInput = YesNo("Are you asleep right now? [y/n] > ");
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

			// Load colours and variables from objects based on nOption - 1 (OptionSelect returns based on 1, not 0)
			ConfigObjMain.sColourGlobal = RGBPreset[nOption - 1].sColourPresetForeground;
			ConfigObjMain.sColourGlobalBack = RGBPreset[nOption - 1].sColourPresetBackground;
			// Set colours
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			// Clear screen to set new colours to whole screen
			cls();
			// Warn user that default colours will be set if the preset hasn't been initialised by user
			if (RGBPreset[nOption - 1].bSetByUser == false) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("Warning: This preset is an empty, undefined preset with default colours, so default colours will be set.") << std::endl;
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

				if (!YesNo(wordWrap("Are you sure you want to overwrite these values? [y/n] > "))) {
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
			if (YesNo("Would you like to proceed? [y/n] > ")) {
				// Set all RGBPreset objects to default values
				for (int i = 0; i <= 2; i++) {
					RGBPreset[i].bSetByUser = false;
					RGBPreset[i].sColourPresetBackground = "0;0;0";
					RGBPreset[i].sColourPresetForeground = "255;255;255";
					RGBPreset[i].sPresetName = "EMPTY_PRESET";
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
		"___LIST OF COMMANDS___\n\nTo see more about a command, type in \"<command> -h\". This will work for all commands, except: echo and title.\n\n[1] Help\n[2] Exit\n[3] Tutorial\n[4] Echo\n[5] CLS\n[6] DevTools\n[7] CPUStress\n[8] Colour\n[9] Settings\n[10] Title\n[11] Date\n[12] ColourNumbers\n[13] MediaPlayer\n[14] AudioPlayer\n[15] TTS\n[16] Stopwatch\n[17] Read\n[18] Timer\n[19] Beep\n[20] Copy\n[21] MessageBox\n[22] TextInfo\n[23] ConfigAction\n[24] BeepSounds\n[25] RickRoll\n[26] ShellExecute\n[27] Hacker\n[28] Calculator\n[29] Logoff\n[30] Shutdown\n[31] Reboot (or Restart)\n[32] Hibernate\n[33] ResetExpl\n[34] MemTest\n[35] RandCol\n[36] Pause\n[37] CommandNum\n[38] SlowChar\n[39] ReverseText\n[40] Notes\n\nMore will be added soon!\n",

		"___FREQUENTLY ASKED QUESTIONS___\n\n"
		"1) I can't see the terminal text. How can I zoom in?\n  1a) You can zoom in, of course. Press and hold the Ctrl button and scroll with the mouse to your desired text size.\n"
		"\n\n2) The error messages shown aren't detailed enough. How do I get better-quality error messages?\n  2a) To get better quality error messages, just enable the Verbosity Messages setting in the Settings command.\n"
		"\n\n3) I'm using the Windows 7 terminal. How do I scroll up and down in the terminal without using the mouse?\n  3a) To scroll up and down with the mouse, press Alt + Space and then the keys 'E' and 'L', and then scroll with the up/down arrow keys. Use the PageUp/PageDown keys to scroll full pages in the terminal.\n",

		"___ABOUT THIS PROGRAM___\n\nThis is the ZeeTerminal Commandline Program, Build " + std::string(ZT_VERSION) + ".\n" +
		"This is an early alpha build of ZeeTerminal, with an entirely new engine and components.\nThis program is made in C++, with a few very small parts of C." +
		"\n\nThis program uses the DirectShow API in the MediaPlayer command, which is licensed by Microsoft Corporation. (c) Microsoft Corporation.\n\n" +
		"This program uses the BASS API in the AudioPlayer command, which is licensed by Un4Seen Developments. (c) Un4seen Developments.\n\n" +
		"\n(c) Ryan Zorkot, 2023. ZeeTerminal is licensed under the MIT License. The license and credits can be viewed on Page 4.\n\n"
		"  _____        _____                   _             _ \n"
		" |__  /___  __|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |\n"
		"   / // _ \\/ _ \\| |/ _ \\ '__| '_ \\` _ \\| | '_ \\ / _\\` |\n"
		"  / /|  __/  __/| |  __/ |  | | | | | | | | | | (_| | |\n"
		" /____\\___|\\___||_|\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|\n"
		"                                                       ",

		"___LICENSE AND CREDITS___\n\n"
		"Massive thank-you to my dad, Hazem Zorkot, for assisting with this project, including with the logo design, name, high-level component ideas, and lots of heads-up messages along the way.\n\n"
		"ZeeTerminal is licensed under the MIT License. Below is the license info:\n\nCopyright (c) 2023 Ryan Zorkot\n\n"
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

			if (i != (nNumOfRows - 1)) {
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

	// Help
	if (sCommand == "help" || sCommand == "1") {
		
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			// help message
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___HELP___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Lists all possible commands in ZeeTerminal.")
					<< wordWrap("\n- Displays some frequently asked questions with answers.")
					<< wordWrap("\n- Displays information about the program, such as copyright information, credits and basic program information.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: help -h\n\n");

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
				CentreColouredText(" ___TUTORIAL___ ", 1);
				
				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- This command starts a short tutorial on how to use ZeeTerminal.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: tutorial -h\n\n");
				
				return;
			}
		}

		// Start the tutorial
		if (YesNo("Are you sure you want to start the tutorial? [y/n] > ")) {
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
				CentreColouredText(" ___CLS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- This command clears the terminal window. Nothing more, nothing less.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: cls -h\n\n");

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
				CentreColouredText(" ___DEVTOOLS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Provides an interface to access a set of developer tools that are designed to test the features of ZeeTerminal.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.")
					<< wordWrap("\n -1\tAutomatically starts Colour Tester.")
					<< wordWrap("\n -2\tAutomatically starts Beep Sound Test.")
					<< wordWrap("\n -3\tAutomatically starts Colour Numbers.")
					<< wordWrap("\n -4\tAutomatically starts OptionSelectEngine Tester.")
					<< wordWrap("\n -5\tAutomatically starts ScreenNavigateEngine Tester.")
					<< wordWrap("\n -6\tAutomatically starts TableEngine Tester.")
					<< wordWrap("\n -7\tAutomatically starts High-Res Nanosecond Stopwatch.")
					<< wordWrap("\n -8\tAutomatically starts ANSI VT Testing Environment.")
					<< wordWrap("\n -9\tAutomatically starts MMSYSTEM API Sound Test.")
					<< wordWrap("\n\nExample: devtools -6") << "\n\n";

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
		CentreColouredText("CPUStress can stress or benchmark your CPU in multiple different ways.", 2);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Stresses your CPU and can be used for stability checks and throttling tests.")
					<< wordWrap("\n- Can benchmark your CPU to see performance metrics.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.")
					<< wordWrap("\n -1 <rnum>\tStarts the Single Core benchmarker. You can optionally set your reiterations in place of <rnum>.")
					<< wordWrap("\n -2 <rnum>\tStarts the Multi Core benchmarker. You can optionally set your reiterations in place of <rnum>.")
					<< wordWrap("\n -3\t\tStarts the Single Core stress test.")
					<< wordWrap("\n -4\t\tStarts the Multi Core stress test.")
					<< wordWrap("\n\nExample: cpustress -1 120000") << "\n\n";

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
		bool bArgExecuted = false;
		bool bForeExecuted = false;
		bool bBackExecuted = false;

		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___COLOUR___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What it does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Adjusts the foreground colour of the terminal (text).")
					<< wordWrap("\n- Adjusts the background colour of the terminal.")
					<< wordWrap("\n- Edit and apply custom RGB colour presets.")
					<< wordWrap("\n- Resets colours to default at request.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n\n -h\t\tDisplays this help message.")
					<< wordWrap("\n -f <colournum>\tAdjusts foreground colour. Put colour number in place of <colournum>.")
					<< wordWrap("\n -b <colournum>\tAdjusts background colour. Put desired colour number in place of <colournum>.")
					<< wordWrap("\n -r\t\tResets colours to default values (excluding RGB colour profiles).")
					<< wordWrap("\n\nExample: colour -f 3 -b 7 ") << "\n\n";
				std::cout << wordWrap("NOTE: You can get the colour numbers by executing the \"ColourNumbers\" command.") << "\n\n";

				return;
			}
			else if (cCommandArgs[i] == 'f') {

				// Can't run background editing twice in the same command
				if (bForeExecuted == true) continue;

				if (isNumberi(sStringDataCommandArgs[i]) == true) {
					ColourForeground(std::stoi(sStringDataCommandArgs[i]));
				}
				else {
					// Can't process a non-number
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured while processing your foreground argument. Make sure your argument syntax is correct, and try again.\nSee \"colour -h\" for more info.\n");
					Exiting();
					return;
				}

				bArgExecuted = true;
				bForeExecuted = true;
			}
			else if (cCommandArgs[i] == 'b') {

				// Can't run background editing twice in the same command
				if (bBackExecuted == true) continue;

				// Check if argument is a number
				if (isNumberi(sStringDataCommandArgs[i]) == true) {
					ColourBackground(std::stoi(sStringDataCommandArgs[i]));
				}
				else {
					// Can't process a non-number
					VerbosityDisplay("In Commands() - ERROR: Could not detect numerical value in string-based number argument.\n");
					UserErrorDisplay("An error occured while processing your background argument. Make sure your argument syntax is correct, and try again.\nSee \"colour -h\" for more info.\n");
					Exiting();
					return;
				}

				bArgExecuted = true;
				bBackExecuted = true;
			}
			else if (cCommandArgs[i] == 'r') {
				// Reset colours prompt
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nTHIS WILL RESET ALL SET COLOURS TO DEFAULT VALUES.\nRGB Colour presets will NOT be affected.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (YesNo(wordWrap("Are you sure you would like to proceed? [y/n] > "))) {
					// Reset colours and update the config file with new colours
					ResetColour();
					ConfigObjMain.WriteConfigFile();
					cls(); // To apply default colours to whole terminal screen
				}

				return;
			}
		}

		// Exit if argument previously executed - there is no need to do it again
		if (bArgExecuted == true) return;

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
			std::cout << '\n';
			int nChoiceFirst = oseColour.OptionSelect("Please choose the colour that you want to change below:", " ___COLOUR___ ");

			if (nChoiceFirst == 1) {
				ColourForeground();
			}
			else if (nChoiceFirst == 2) {
				ColourBackground();
			}
			else if (nChoiceFirst == 3) {
				RGBColourPresets();
			}
			else if (nChoiceFirst == 4) {
				// Reset colours prompt
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nTHIS WILL RESET ALL SET COLOURS TO DEFAULT VALUES.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				if (YesNo(wordWrap("Are you sure you would like to proceed? [y/n] > "))) {
					// Reset colours and update config file with new colours
					ResetColour();
					ConfigObjMain.WriteConfigFile();
					cls(); // To apply default colours to whole terminal screen
				}
				else {
					colour(YLW, ConfigObjMain.sColourGlobalBack);
					std::cout << "\nAborted...\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}
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
				CentreColouredText(" ___SETTINGS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What it does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- The Settings command allows you to adjust common settings in the terminal, such as colour settings, verbosity and direction messages, and ANSI settings.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for the Settings command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n --highlightfore <num>\t\tModifies the highlight foreground colour. Set your colour number in place of <num>.")
					<< wordWrap("\n --highlightback <num>\t\tModifies the highlight background colour. Set your colour number in place of <num>.")
					<< wordWrap("\n --titlefore <num>\t\tModifies the title foreground colour. Set your colour number in place of <num>.")
					<< wordWrap("\n --titleback <num>\t\tModifies the title background colour. Set your colour number in place of <num>.")
					<< wordWrap("\n --subheadingfore <num>\t\tModifies the subheading foreground colour. Set your colour number in place of <num>.")
					<< wordWrap("\n --subheadingback <num>\t\tModifies the subheading background colour. Set your colour number in place of <num>.")
					<< wordWrap("\n --verbose <toggle>\t\tToggles verbose messages. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --directions <toggle>\t\tToggles direction messages. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --ansi <toggle>\t\tToggles ANSI VT sequences. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --wordwrap <toggle>\t\tToggles word wrapping. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --cursorblink <toggle>\t\tToggles cursor blinking. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --showcursor <toggle>\t\tToggles cursor visibility. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --cursorstyle <style>\t\tSets the style of the cursor. Set the style (block, underline, bar) in place of <style>.")
					<< wordWrap("\n --slowcharspeed <num>\t\tSets the speed of SlowChar. Set the speed in place of <num>.")
					<< wordWrap("\n --randcolstartup <toggle>\tToggles random colours on startup. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --customtheme <toggle>\t\tToggles terminal custom theme support. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --autocontrast <toggle>\tToggles auto-readable colour contrast. Set either true/t or false/f in place of <toggle>.")
					<< wordWrap("\n --tempconfigdir <dir>\t\tSets a temporary custom configuration file directory. Pass the directory in place of <dir>.")
					<< wordWrap("\n\nExample: settings --titlefore 1")
					<< wordWrap("\n\nNote: You can get colour numbers by executing the \"ColourNumbers\" command.") << "\n\n";
				 
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
						UserErrorDisplay("An error occured. Your setting option seems to be incorrect. Make sure it's either 'block', 'underline', or 'bar'. Type \"settings -h\" for more info.");
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
					UserErrorDisplay("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again. Type \"settings -h\" for more info.");
					return;
				}

				return;
			}

		}

		OptionSelectEngine oseSettings;
		oseSettings.nSizeOfOptions = 9;
		std::string sOptions[] = {
			"Highlight Colour Settings",
			"Title Colour Settings",
			"Subheading Colour Settings",
			"Disable/Enable Verbose Messages",
			"Disable/Enable Direction Messages",
			"Disable/Enable ANSI",
			"Disable/Enable Word Wrapping",
			"Cursor Settings",
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
			// Take title input
			std::string sTitle = StrInput("Please input your desired title (256 characters max): > ");
			// Set window title using WindowTitleSet engine function
			if (SetWindowTitle(sTitle)) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Setting console window title succeeded!\n";
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
				CentreColouredText(" ___DATE___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- This command displays the time and date in 24 hour time. Nothing more, nothing less.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\n")
					<< wordWrap("Example: date -h\n\n");

				return;

			}
		}

		CentreColouredText(" ___DATE___ ", 1);
		std::cout << '\n';

		time_t currentTime = time(0);
		struct tm localTime {};

		time(&currentTime);
		localtime_s(&localTime, &currentTime);

		std::cout << "Local Date: ";
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

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- This command displays the colour numbers for all default colours. Nothing more, nothing less.\n\n");
				
				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\n")
					<< wordWrap("Example: colournumbers -h\n\n");
				
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

		std::wstring wsFilePath;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___MEDIA PLAYER___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does: " << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Can play media and audio of specific types.")
					<< wordWrap("\n- Can view images of specific types.\n")
					<< wordWrap("\n- Supported file formats: WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, MP3 (Only MPEG Audio Layer-3 codec), JPG and BMP.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command: " << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.")
					<< wordWrap("\n <FILE>\tOpens a file for playback/viewing. Put the exact filepath in place of <FILE>.\n\nExample: mediaplayer \"C:\\Media\\media test.mp3\"\n\n")
					<< wordWrap("\nNOTE: You need to use quotes like shown in the example to use a filename with ANY spaces.\nNOTE: Type in \"*open\" without quotes in place of the file argument to use the Windows File Dialogue to open a file.\n\n");

				return;
			}
			else if (sStringDataCommandArgs[0] != "") {

				std::string sFilePath = sStringDataCommandArgs[0];

				std::cout << '\n';
				CentreColouredText(" ___MEDIA PLAYER___ ", 1);
				std::cout << '\n';

				// Check if the start of the first argument has a speechmark; 
				// if there is one, use filepath from the start to the ending speechmark (if there is one)
				if (sStringDataCommandArgs[0] == "*open") {
					std::cout << "Opening with the Windows File Dialogue...\n\n";
					FileOpenGUIEngine MediaPlayer;
					MediaPlayer.FileOpenDialogue("Open a Media File to Play");
					sFilePath = MediaPlayer.GetFileName();
					// Cancelled
					if (sFilePath == "") {
						Exiting();
						return;
					}
				}
				else sFilePath = sStringDataCommandArgs[0];

				VerbosityDisplay("Executing media file using MediaPlayer: \"" + sFilePath + "\"...\n");

				MultimediaEngine meArgInterface;

				meArgInterface.DShowMultimediaPlayer(s2ws(sFilePath));

				return;
			}
		}

		CentreColouredText(" ___MEDIA PLAYER___ ", 1);

		// Information
		std::cout << "\n\n";
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
		else if (wsFilePath == L"*open") {
			std::cout << "Opening with the Windows File Dialogue...\n\n";
			FileOpenGUIEngine MediaPlayer;
			MediaPlayer.FileOpenDialogue("Open a Media File to Play");
			wsFilePath = s2ws(MediaPlayer.GetFileName());
			// Cancelled
			if (wsFilePath == L"") {
				Exiting();
				return;
			}
		}

		// Execute multimedia player with the inputted file path
		MultimediaEngine meMediaPlayer;
		meMediaPlayer.DShowMultimediaPlayer(wsFilePath);

		return;

	}

	// AudioPlayer
	else if (sCommand == "audioplayer" || sCommand == "14") {

		CentreColouredText("___AUDIO PLAYER___", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Plays a wide range of popular audio formats, such as FLAC and MP3, in an easy-to-use interface.\n- This is newer than the MediaPlayer, which uses an older DirectShow API.\n- Uses the BASS Audio API, so requires DLLs to be in the same directory as ZeeTerminal.\n- Audio formats supported: MP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n <file>\tSpecify the file to use. Put the filepath in place of <file>.\n\nExample: audioplayer \"C:\\Users\\Public\\Music\\Kalimba.mp3\"\n\nNOTE: Use quotes for ANY filename with spaces inside of it, like the example.\nNOTE: Type in \"*open\" without quotes to use the Windows File Dialogue to open a file.\n\n");

				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[0] == "*open") {
					std::cout << "Opening with the Windows File Dialogue...\n\n";
					// Open with the FileOpen GUI Engine
					FileOpenGUIEngine AudioPlayer;
					AudioPlayer.FileOpenDialogue("Open an Audio File to Play");
					// Cancelled
					if (AudioPlayer.GetFileName() == "") {
						Exiting();
						return;
					}
					
					MultimediaEngine meArgInterface;
					meArgInterface.BASSAudioPlayer(AudioPlayer.GetFileName());

					return;
				}

				std::cout << '\n';

				VerbosityDisplay("Executing audio file using AudioPlayer: \"" + sStringDataCommandArgs[0] + "\"...\n");

				MultimediaEngine meArgInterface;

				meArgInterface.BASSAudioPlayer(sStringDataCommandArgs[0]);

				return;
			}
		}

		// Information
		std::cout << "\n";
		colourSubheading();
		std::cout << wordWrap("The following file formats are supported:") << NOULINE_STR;
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nMP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC\n\nType \"*open\" without quotes to use the Windows File Dialogue to open an audio file.\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Prompt
		std::string sFilePath = StrInput("Enter your desired audio file path (0 to exit): > ");
		std::cout << '\n';

		// Exit on 0
		if (sFilePath == "0") {
			Exiting();
			return;
		}
		// Open the file dialogue on *open
		else if (sFilePath == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "Opening with the Windows File Dialogue...\n\n";
			FileOpenGUIEngine AudioPlayer;
			AudioPlayer.FileOpenDialogue("Open an Audio File to Play");
			sFilePath = AudioPlayer.GetFileName();
			// Cancelled
			if (sFilePath == "") {
				Exiting();
				return;
			}
		}

		MultimediaEngine meAudioPlayer;
		meAudioPlayer.BASSAudioPlayer(sFilePath);

		return;

	}

	// TTS
	else if (sCommand == "tts" || sCommand == "15") {
		
		// Arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___TEXT TO SPEECH___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does: " << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Takes in input and outputs it with a human-like voice through the speaker.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command: " << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n <MSG>\tInput text to be said by the computer. Put text in place of <MSG>.\n\n")
					<< wordWrap("Example: tts \"The quick brown fox jumps over the lazy dog.\"\n\n")
					<< wordWrap("Note: If the text contains any spaces, put it in speech marks like the example, or it will not work.\n\n");

				return;
			}
			else if (sStringDataCommandArgs[0] != "") {

				std::string sText = sStringDataCommandArgs[0];

				// Check for speechmarks; if so, remove them so they don't get pronounced
				if (sStringDataCommandArgs[0][0] == '"' && sStringDataCommandArgs[0][sStringDataCommandArgs[0].length() - 1] == '"') {
					sText = sStringDataCommandArgs[0].substr(1, (sStringDataCommandArgs[0].length() - 2));
				}
				else sText = sStringDataCommandArgs[0];

				VerbosityDisplay("TTS starting with text \"" + sText + "\"...\n");

				// Output message
				colour(GRN, ConfigObjMain.sColourGlobalBack);
				std::cout << CentreText("Outputting TTS Message...") << '\n';

				// Execute text-to-speech
				MultimediaEngine meTTS;
				meTTS.TTSOutput(s2ws(sText));

				// Output success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << CentreText("TTS Message successfully outputted!") << '\n';
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				return;
			}
		}

		CentreColouredText(" ___TEXT-TO-SPEECH___ ", 1);

		std::cout << "\n";
		CentreColouredText("Text To Speech takes in text and outputs it through the speakers in a human-like voice.", 2);
		std::cout << "\n\n";

		// Take input
		std::string sText = StrInput("Please input your desired text (0 to exit): > ");
		if (sText == "0") {
			Exiting();
			return;
		}

		// Output using MultimediaEngine::TTS() //
		// Output message
		colour(GRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("Outputting TTS Message...") << '\n';

		MultimediaEngine meTTS;
		VerbosityDisplay("Outputting \"" + sText + "\" as TTS...\n");
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

		// arguments interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___STOPWATCH___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does: " << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Allows for the use for a simple stopwatch, that measures the time in seconds.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command: " << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n -i\tStarts the stopwatch immediately on command execution.\n\nExample: stopwatch -i\n\n");

				return;
			}
			else if (cCommandArgs[i] == 'i') {
				bSkipStartScreen = true;
			}
		}

		CentreColouredText(" ___STOPWATCH___ ", 1);
		std::cout << '\n';
		CentreColouredText("This is a simple stopwatch that measures the time in seconds.", 2);
		
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
		return;
	}

	// Read
	else if (sCommand == "read" || sCommand == "17") {

		CentreColouredText(" ___READ___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Reads the contents and characters of a file and outputs them to the screen.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n <file>\tThe file that will be used to read from. Put file directory in place of <file>.\n\nNOTE: You can use \"*open\" without quotes as the filename argument to use the Windows File Dialogue to get a file.\n\n")
					<< wordWrap("Example: read \"C:\\Users\\Public\\file.txt\"\n\n");

				return;
			}
			else if (sStringDataCommandArgs[0] != "") {

				// Firstly, test if file is actually real
				std::ifstream fileTestIn;

				std::string sText = sStringDataCommandArgs[0];
				// Check if the start of the first argument has a speechmark and if File Dialogue was requested; 
				// if there is one, use text from the start to the ending speechmark (if there is one)
				if (sStringDataCommandArgs[0] == "*open") {
					// Open with the FileOpen GUI Engine
					std::cout << "Opening with the Windows File Dialogue...\n\n";
					FileOpenGUIEngine ReadCommand;
					ReadCommand.FileOpenDialogue("Open a File to Read");
					sText = ReadCommand.GetFileName();
					// Cancelled
					if (sText == "") {
						Exiting();
						return;
					}
				}
				else if (sText[0] == '\"') {
					size_t nFinalMarkPos = sText.find('\"', 1);
					sText = sText.substr(1, nFinalMarkPos - 1);
				}
				else sText = sStringDataCommandArgs[0];

				fileTestIn.open(sText);
				if (fileTestIn.fail()) {
					VerbosityDisplay("In Commands() - ERROR: Unknown directory/file detected. Read operation failed.\n");
					colour(RED, ConfigObjMain.sColourGlobalBack);
					UserErrorDisplay("ERROR - The directory or file doesn't exist. Please try again with a directory/file that exists.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

					fileTestIn.close();
					Exiting();
					return;
				}
				fileTestIn.close();

				// Open a new stream for reading
				std::ifstream fileIn(sText, std::ios::binary);
				std::string* sFileContents = new std::string; // In case of big file
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

				delete sFileContents;
				return;
			}
		}

		CentreColouredText("This command outputs all contents of a file.", 2);
		std::cout << "\n\n";
		std::string sInput = StrInput("Please input file directory (0 to exit, \"*open\" without quotes to use the Windows File Dialogue): > ");
		if (sInput == "0") {
			Exiting();
			return;
		}
		// Open the file dialogue on *open
		else if (sInput == "*open") {
			// Open with the FileOpen GUI Engine
			std::cout << "Opening with the Windows File Dialogue...\n\n";
			FileOpenGUIEngine ReadCommand;
			ReadCommand.FileOpenDialogue("Open a File to Read");
			sInput = ReadCommand.GetFileName();
			// Cancelled
			if (sInput == "") {
				Exiting();
				return;
			}
		}
		else std::cout << '\n';

		// Firstly, test if file is actually real
		std::ifstream fileTestIn;

		// Check if the start of the first argument has a speechmark; 
		// if there is one, use text from the start to the ending speechmark (if there is one)
		if (sInput[0] == '\"') {
			size_t nFirstMarkPos = sInput.find("\"", 0) + 1;
			size_t nFinalMarkPos = sInput.find('\"', nFirstMarkPos) - 1;
			sInput = sInput.substr(nFirstMarkPos, nFinalMarkPos);
		}

		fileTestIn.open(sInput);
		if (fileTestIn.fail()) {
			VerbosityDisplay("In Commands() - ERROR: Unknown directory/file detected. Read operation failed.\n");
			UserErrorDisplay("ERROR - The directory or file doesn't exist. Please try again with a directory/file that exists.\n");

			fileTestIn.close();
			Exiting();
			return;
		}
		fileTestIn.close();

		// Open a new stream for reading
		std::ifstream fileIn(sInput, std::ios::binary);
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

		CentreColouredText(" ___TIMER___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Provides access to a highly accurate countdown timer that takes time in seconds.\n- You can press any key to exit the timer while in operation.\n\n");
				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n <time>\tAllows to pass the time in seconds as an argument. Put the number of seconds in place of <time>.\n\nExample: timer 45\n\n");

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
			CentreColouredText("This is a highly accurate countdown timer that takes time in seconds.", 2);
			std::cout << "\n\n";
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

		return;

	}

	// Beep
	else if (sCommand == "beep" || sCommand == "19") {

		long double dFrequency = 0;
		long double dDuration = 0;

		CentreColouredText(" ___BEEP___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Allows for outputting a constant beep sound at a variable frequency and duration.\n- The frequency is measured in Hertz, and the duration is measured in SECONDS.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n <freq>\tSpecify the frequency as an argument. Input your frequency number in place of <freq>.\n <time>\tSpecify the time as an argument. Input your time number in place of <time>.\n\nExample: beep 500 1 (syntax: beep <freq> <time>)\n\n");

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
			CentreColouredText("This allows for outputting a sound at a specified frequency for a specified amount of time.", 2);
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

		CentreColouredText(" ___MESSAGEBOX___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Allows for creating a custom message box.\n- Customisations include text, caption, icon and buttons.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -t <text>\tText for the message box. Set the text in place of <text>.")
					<< wordWrap("\n -c <caption>\tCaption for the message box. Set the caption in place of <caption>.\n -i <icon>\tIcon for the message box. Set either: info, warning, error, or question, in place of <icon>.")
					<< wordWrap("\n -b <button>\tButtons for the message box. Set either: ok, okcancel, abortretryignore, yesnocancel, yesno, retrycancel, or canceltrycontinue, in place of <button>.\n\nExample: messagebox -t \"Test Text\" -c \"Test Caption\" -b ok")
					<< wordWrap("\n\nNOTE: Use speechmarks like the example when using text that contains spaces.\n\n");

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
			CentreColouredText("This allows for creating a message box with custom icons, buttons, text and caption text.", 2);
			std::cout << "\n\n";

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
		CentreColouredText(" ___COPY___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Copies an existing file to a new file.\n- This uses a directory of the source file, and the directory of the new file (NOT folder).\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n <source>\tThe original file to be copied to another file. Put the file directory in place of <source>.\n <dest>\t\tThe file directory of the new file. Put the file directory in place of <dest>.")
					<< wordWrap("\n\nExample: copy \"C:\\test\\a file.txt\" C:\\Users\\newfile.txt")
					<< wordWrap("\n\nNOTE: For any directory with spaces, use quotes like in the example.\nNOTE: You must have both the source and the destination directories when using them as arguments.\nNOTE: Read this article for information on the different forms of filepaths: ");
				
				colour(LBLU, ConfigObjMain.sColourGlobalBack);
				std::cout << "https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#fully-qualified-vs-relative-paths" << '\n';
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				return;

			}
			else if (sStringDataCommandArgs[0] != "") {
				if (sStringDataCommandArgs[1] != "") {
					std::string sOriginalFilePath = sStringDataCommandArgs[0];
					std::string sDestinationFilePath = sStringDataCommandArgs[1];

					// Copy file
					VerbosityDisplay("Copying file " + sOriginalFilePath + " to " + sDestinationFilePath + "...");
					std::cout << "Copying file...\n";

					if (!CopyFileA(sOriginalFilePath.c_str(), sDestinationFilePath.c_str(), true)) {
						// Output existing file message
						VerbosityDisplay("In Commands() - ERROR: Existing file when copying to file directory detected. Copy operation has failed.\n");
						colour(RED, ConfigObjMain.sColourGlobalBack);
						UserErrorDisplay("An error occured while copying the file.\nPossibly either the original file is nonexistent or the file already exists in the destination location.\n");
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					}
					else {
						// Success
						colour(LGRN, ConfigObjMain.sColourGlobalBack);
						std::cout << CentreText("File successfully copied!") << '\n';
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					}
					std::cout << '\n';
				}
				else {
					// Error message
					VerbosityDisplay("In Commands() - ERROR: Vital argument not found.\n");
					colour(RED, ConfigObjMain.sColourGlobalBack);
					UserErrorDisplay("ERROR: You need to have both the file location AND destination file directories included in your arguments.\nSee \"copy -h\" for more info.\n");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				}

				return;
			}
		}

		CentreColouredText("This command copies a file from one location to another.", 2);
		std::cout << "\n\n";

		// Prompts
		std::string sOrigPath = StrInput("Please input directory of original file (0 to exit): > ");
		if (sOrigPath == "0") {
			Exiting();
			return;
		}
		std::string sDestPath = StrInput("Please input directory of new destination file (0 to exit): > ");
		if (sDestPath == "0") {
			Exiting();
			return;
		}

		// Check for any speechmarks that might accidentally get passed to copy operation
		if (sOrigPath[0] == '\"') {
			size_t nFirstMarkPos = sOrigPath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sOrigPath.find('\"', nFirstMarkPos) - 1;
			sOrigPath = sOrigPath.substr(nFirstMarkPos, nFinalMarkPos);
		}
		if (sDestPath[0] == '\"') {
			size_t nFirstMarkPos = sDestPath.find("\"", 0) + 1;
			size_t nFinalMarkPos = sDestPath.find('\"', nFirstMarkPos) - 1;
			sDestPath = sDestPath.substr(nFirstMarkPos, nFinalMarkPos);
		}

		// Copy file
		VerbosityDisplay("Copying file " + sOrigPath + " to " + sDestPath + "...");
		std::cout << "Copying file...\n";
		if (!CopyFileA(sOrigPath.c_str(), sDestPath.c_str(), true)) {
			VerbosityDisplay("In Commands() - ERROR: Existing file when copying to file directory detected. Copy operation has failed.\n");
			UserErrorDisplay("An error occured while copying the file.\nPossibly either the original file is nonexistent or the file already exists in the destination location.\n");
		}
		else {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("File successfully copied!") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		return;
	}

	// TextInfo
	else if (sCommand == "textinfo" || sCommand == "22") {
		std::string sText = "";

		CentreColouredText(" ___TEXTINFO___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Displays information about a string of text.\n- This can include words, sentences, letters, characters, etc.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n <text>\tThe text to be used for the command. Put the text in place of <text>.")
					<< wordWrap("\n\nExample: textinfo \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes for text with any spaces in it like the example, or the text may not be read properly.\n\n");

				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				// Assign sText to sStringDataCommandArgs[0] to be used after the argument checking
				sText = sStringDataCommandArgs[0];
			}
		}

		// if not assigned by argument
		if (sText == "") {

			CentreColouredText("This allows for displaying information about a string of text.", 2);
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
	else if (sCommand == "configaction" || sCommand == "23") {
		int nOption = 0;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++)
		{
			if (cCommandArgs[i] == 'h') 
			{
				std::cout << '\n';
				CentreColouredText(" ___CONFIGACTION___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Contains options to interact with the ZeeTerminal Configuration File System.\n- You can manually read, write, create and display config files/objects with this command.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n --readconfigfile\tReads from the currently-pointed configuration file\n --writeconfigfile\tWrites to the currently-pointed-to configuration file.")
					<< wordWrap("\n --createconfigfile\tCreates a configuration file to the same file directory as user-set location, or default location as fallback.\n --displayconfigobj\tDisplays contents of the main configuration object in memory.")
					<< wordWrap("\n --displayconfigfile\tDisplays contents of currently-pointed-to configuration file.\n\nExample: configaction --readconfigfile\n\n");

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
	else if (sCommand == "beepsounds" || sCommand == "24") {
		bool bArgumentExecuted = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___BEEPSOUNDS___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Provides an interface to play different themes, songs and sounds with beeps.\n- This uses the MMSYSTEM API to play beep sounds.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n --misssionimpossible\tPlays a small snippet of the Mission Impossible theme song.")
					<< wordWrap("\n --happybirthday\tPlays the Happy Birthday song.\n --supermario\t\tPlays the Super Mario Theme Song.\n --dundundun\t\tPlays a 'dun dun dun dun' sound.")
					<< wordWrap("\n --imperialmarch\tPlays the Star Wars Imperial March song.\n\nExample: beepsounds --missionimpossible\n\n");

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

		}

		// Something already executed in this command
		if (bArgumentExecuted == true) return;

		OptionSelectEngine oseBeepSounds;

		oseBeepSounds.nSizeOfOptions = 5;
		std::string sOptions[] = {
			"Mission Impossible Theme",
			"Happy Birthday Song",
			"Super Mario Theme",
			"DunDunDun Sound",
			"Star Wars Imperial March Song"
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
	else if (sCommand == "rickroll" || sCommand == "25") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				std::cout << '\n';
				CentreColouredText(" ___RICKROLL___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Rickrolls a ZeeTerminal user (a decade-old meme).\n- This only works when the user is online.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: rickroll -h\n\n");

				return;
			}
		}

		// Rickroll
		// Props to Hell's Channel for keeping this youtube link alive!
		ShellExecuteA(0, 0, "https://www.youtube.com/watch?v=z4JJ270xx98", 0, 0, SW_HIDE);

		return;
	}

	// ShellExecute
	else if (sCommand == "shellexecute" || sCommand == "26") {

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText("___SHELLEXECUTE___", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Forwards and executes commands in the Windows Command Prompt.\n- You can perform actions such as opening a specific file or performing an operation of sorts.\n- Use when you know what you are doing.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n <command>\tCommand to execute. Put the desired command in place of <command>.\n\nExample: ShellExecute \"ipconfig -a\"")
					<< wordWrap("\n\nNOTE: Use quotes whenever there are spaces in the command, like the example.\n\n");

				return;
			}
			else if (sStringDataCommandArgs[0] != "") {
				CentreColouredText("___SHELLEXECUTE___", 1);
				std::cout << '\n';

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
		}

		CentreColouredText("___SHELLEXECUTE___", 1);
		std::cout << "\n";
		CentreColouredText("This allows for the execution of CMD shell commands from ZeeTerminal.", 2);
		std::cout << "\n\n";

		std::string sCommandText = StrInput("Please input your desired CMD command to run (0 to exit): > ");

		// Exit on 0
		if (sCommandText == "0") {
			Exiting();
			return;
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
	else if (sCommand == "hacker" || sCommand == "27") {

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

				CentreColouredText(" ___HACKER___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Displays text of random numbers to make the computer look like it's processing a hacking script.\n- Allows you to type like a hacker, with the ability to use a custom file to do so.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -i\t\tStart immediately, with default settings when no argument is given.\n --display\tStarts the hacking text part of this command.\n --type\t\tStarts the hacker typing part of this command.\n --typecustom\tStarts the hacker typing part of this command, with custom file output abilities.\n <speed>\tSpeed of output characters for 'type' and 'typecustom' arguments. Must be a number.\n <filepath>\tCustom filepath argument for 'typecustom' argument. Must be a valid filepath.")
					<< wordWrap("\n\nSyntax for '--type' argument:\t\t type <speed>\nSyntax for '--typecustom' argument:\t typecustom <filepath> <speed> (In order)")
					<< wordWrap("\n\nExample: hacker --type\n\n");

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
	else if (sCommand == "calculator" || sCommand == "28") {

		// Declare variables
		bool bWorkingOut = false;
		bool bWorkingOutArgumentSet = false;
		std::string sCalculationInput = "";

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {

				CentreColouredText("___CALCULATOR___", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Calculates a string-based calculation, using the BIDMAS order of operations.\n- Supports up to a theoretical 18 trillion characters per calculation string.\n- Supports all BIDMAS operations, trigonometric functions, mathematical constants and square/cube roots.\n- Can display how the answer was worked out.\n\n");
				
				colourSubheading();
				std::cout << "___Syntax___:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Type in any symbol or function from the following in your calculation input:\n\n");

				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << "___BASIC MATHEMATICAL OPERATORS___";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n\t --> '/': Division\n\t --> '*': Multiplication\n\t --> '+': Addition\n\t --> '-': Subtraction\n\t --> '^': To the power of\n\n";

				colour(LBLU, ConfigObjMain.sColourGlobalBack);
				std::cout << "___SQUARE/CUBE ROOT AND TRIGONOMETRY___";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap(std::string("\n\t --> 'sqrt(n)': Square Root function, where n is the desired number\n\t --> 'cbrt(n)': Cube Root function, where n is the desired number\n\t --> 'sin(n)': Sine function, where n is the desired number")
					+ "\n\t --> 'cos(n)': Cosine function, where n is the desired number\n\t --> 'tan(n)': Tangent function, where n is the desired number\n\t --> 'asin(n)': Arc Sine function, where n is the desired number"
					+ "\n\t --> 'acos(n)': Arc Cosine function, where n is the desired number\n\t --> 'atan(n)': Arc Tangent function, where n is the desired number\n\n");

				colour(GRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "___MATHEMATICAL CONSTANTS___";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n\t --> '(pi)': The PI number constant.\n\t --> '(e)': The Euler's number constant.\n\n";

				colour(LMAG, ConfigObjMain.sColourGlobalBack);
				std::cout << "___OTHER___";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n\t --> '(ans)': The 'Ans' user-space variable (last calculated answer)\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n -w\tMakes calculator display working out steps.\n -n\tMakes calculator NOT display working out steps.\n <calc>\tCalculation as an argument. Input your calculation in place of <calc>.")
					<< wordWrap("\n\nExample: calculator (10+5^2)((5*-2)+9-3^3)/2\n\n");

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
			
			if (sStringDataCommandArgs[i] != "") {
				sCalculationInput = sStringDataCommandArgs[i];
			}
		}

		CentreColouredText(" ___CALCULATOR___ ", 1);
		std::cout << "\n";
		CentreColouredText("This allows for advanced BIDMAS calculations to be computed fully offline, with trigonometry and more.", 2);
		std::cout << "\n\n";

		// If the working out wasn't user-set
		if (bWorkingOutArgumentSet == false) {
			bWorkingOut = YesNo("Would you like the calculator to display working out steps? [y/n] > ");
			std::cout << '\n';
		}


		// Start the Calculation Algorithm
		CalculationAlgorithm caCalculator;
		caCalculator.bDisplayWorkingOutProcess = bWorkingOut;
		
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
				std::cout << std::setprecision(16) << dCalculatedVal << "\n";
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
				std::cout << std::setprecision(16) << dCalculatedVal << "\n\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		return;
	}

	// Logoff
	else if (sCommand == "logoff" || sCommand == "29") {
		
		CentreColouredText(" ___LOGOFF___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Logs off the current user from the computer.\n- Initiating the logoff process happens immediately and on command.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: logoff -h\n\n");

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
	else if (sCommand == "shutdown" || sCommand == "30") {
		unsigned long int nTimeBeforeShutdown = 10;

		CentreColouredText(" ___SHUTDOWN___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Shuts down the computer that ZeeTerminal is running on.\n- It can be set to trigger after a certain amount of time.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -t <time>\tA time argument for shutdown in seconds. Put time argument in place of <time>. Must be a number.\n -c\t\tCancel any pending shutdown operations.")
					<< wordWrap("\n\nExample: shutdown -t 5\n\n");

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
	else if (sCommand == "reboot" || sCommand == "restart" || sCommand == "31") {
		unsigned long int nTimeBeforeReboot = 10;

		CentreColouredText(" ___REBOOT___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Reboots the computer that ZeeTerminal is running on.\n- It can be set to trigger after a certain amount of time.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -t <time>\tA time argument for reboot in seconds. Put time argument in place of <time>. Must be a number.\n -c\t\tCancel any pending reboot operations.")
					<< wordWrap("\n\nExample: reboot -t 5\n\n");

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
	else if (sCommand == "hibernate" || sCommand == "32") {

		CentreColouredText(" ___HIBERNATE___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Hibernates the computer that ZeeTerminal is running on.\n- Initiating the hibernate process is immediate and on command.\n- Hibernation will NOT work if hibernation is disabled on the computer running ZeeTerminal.\n\n");

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: hibernate -h\n\n");

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
	else if (sCommand == "resetexpl" || sCommand == "33") {

		CentreColouredText(" ___RESETEXPL___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Resets explorer.exe on the system running ZeeTerminal.\n- The reset process executes immediately and on command.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: resetexpl -h\n\n");

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
	else if (sCommand == "memtest" || sCommand == "34") {

		int nChoice = 0;
		uint64_t nNumOfPasses = 0; // -b: 100, -l: 10, -e: 2
		bool bKeypressBeforeDeallocation = false;
		bool bUseFullMemory = false;
		bool bSuccess = true;
		bool bMultiThreaded = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {

			if (cCommandArgs[i] == 'h') {
				
				CentreColouredText(" ___MEMTEST___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Checks your computer's memory to see if any issues arise with it.\n- The way this is done is by filling up the computer's memory and assigning each byte of memory with a specific value.")
					<< wordWrap("\n- There are 2 methods of checking: A quick round of x binary searches using randomly calculated numbers, and a slower x-pass linear search that checks every cell of assigned memory for the correct value (x being no. of passes).")
					<< wordWrap("\n- Any program/system crash or completely unexpected behaviour in this test probably means that the memory is faulty.\n- It is recommended that all programs and background tasks are closed before any memory tests are run.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -f\t\tSimply fill up and allocate the system memory, and then deallocate.\n -b <passes>\tPerform binary searches on allocated memory. Put number of passes in place of <passes>.")
					<< wordWrap("\n -l <passes>\tPerform linear check searches on allocated memory. Put number of passes in place of <passes>.\n -e <passes>\tPerform extended linear check searches on allocated memory. Put number of passes in place of <passes>.\n -k\t\tRequire a keypress before memory deallocation, with the -f option. Default is false.")
					<< wordWrap("\n -m\t\tUse multithreading. May increase performance but can increase CPU temperatures.\n -a\t\tUse all the memory available on the host system, rather than just the default available memory. May not work with systems that have paging disabled.\n\nExample: memtest -k -l 6\n\n");

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
	else if (sCommand == "randcol" || sCommand == "35") {

		CentreColouredText(" ___RANDCOL___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Picks randomised colours from the colour numbers, and sets them as default.\n- Make sure you set a colour preset for your current colours before running this command, so you don't lose them.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: randcol -h\n\n");

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
	else if (sCommand == "pause" || sCommand == "36") {

		bool bEnterKeypressLimit = false;

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___PAUSE___ ", 1);
				std::cout << '\n';

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Pauses the operation of ZeeTerminal and resumes on any user keypress.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n -e\tRequire an ENTER keypress only, instead of any key being allowed.\n\nExample: pause -h\n\n");

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
			std::cout << "Press ENTER to continue...:"; // Use the colon character, similar to Powershell
			std::cin.get();
		}

		return;
	}

	// CommandNum
	else if (sCommand == "commandnum" || sCommand == "37") {

		CentreColouredText(" ___COMMANDNUM___ ", 1);
		std::cout << '\n';
		
		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Displays the number of inputted commands since the startup of the current ZeeTerminal session.\n- Also displays the number of successful and unsuccessful commands.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: commandnum -h\n\n");

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
	else if (sCommand == "slowchar" || sCommand == "38") {

		bool bUseRandomColours = false;
		std::string sText = "";

		CentreColouredText(" ___SLOWCHAR___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Takes in text and outputs it in a slow character manner.\n- You can choose to output in random colours, as well.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n -r\tOutput slow character text in random colours.\n <text>\tThe text to be used for the command. Put text in place of <text>.")
					<< wordWrap("\n\nExample: slowchar -r \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes, like in the example, for any text that contains spaces.\n\n");

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
			sText = StrInput("\nPlease input the text that you want to be outputted slowly (0 to exit): > ");
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
	else if (sCommand == "reversetext" || sCommand == "39") {

		bool bUseSlowChar = false;
		std::string sText = "";

		CentreColouredText(" ___REVERSETEXT___ ", 1);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {

				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Outputs text that is inputted in reverse.\n- Can be outputted with a slow character effect.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n -s\tOutputs reverse text with a slow character effect.\n <text>\tThe text to be outputted in reverse. Put the desired text in place of <text>.")
					<< wordWrap("\n\nExample: reversetext -s \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes, like in the example, for any text argument that contains spaces.\n\n");

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
			sText = StrInput("\nPlease input text that you want to output in reverse (0 to exit): > ");
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
	else if (sCommand == "notes" || sCommand == "40") {

		// Declare necessary variables
		int nChoice = 0;
		std::string sNotesText = "";
		uint64_t nNotesLine = 0;

		CentreColouredText(" ___NOTES___ ", 1);
		std::cout << '\n';
		CentreColouredText("Allows for the management and creation of custom notes.", 2);
		std::cout << '\n';

		// Arguments Interface
		for (int i = 0; i < nArgArraySize; i++) {
			if (cCommandArgs[i] == 'h') {
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n- Allows the taking-down and saving of notes that can be accessed from this program.\n- The notes are saved on memory and on a file in the same directory as ZeeTerminal.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n -a <note>\t\tAdd a note. Put the desired note in place of <note>.\n -r <linenum>\t\tRemove a note indicated by <linenum> from the notes. Put the line number in place of <linenum>. Cannot be less than 1 or more than the number of saved notes. If there is no line number argument, the last line will be removed.")
					<< wordWrap("\n -e\t\t\tEdit all notes in notes array.\n -m <linenum> <text>\tModify a note indicated by the line number. Put the line number in place of <linenum>, or leave it blank to modify the last line. Put the desired note text in place of <text>.\n -o\t\t\tOutput all notes that are saved.\n -c\t\t\tClear all notes, permanently.\n -u\t\t\tUpdate the Notes array (memory notes) with the Notes file. This will take effect immediately.\n -f\t\t\tUpdate the Notes file with the Notes array (memory notes). This will take effect immediately.")
					<< wordWrap("\n\nExample: notes -a \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes, like the example, for any text that contains spaces.\n\n");

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

			nChoice = oseNotes.OptionSelect("Please select what you would like to do to the current notes setup:", "");

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
			// Create new file if nonexistent
			if (NotesMain.ReadFromNotesFile() == false) {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\nNo notes file detected. Creating new file...\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Attempt to write to notes file
				if (!NotesMain.WriteToNotesFile()) {
					VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and create notes file.\n");
					UserErrorDisplay("ERROR - Failed to create notes file. This notes session will save to memory only.\n");

					return;
				}
			}

			// Interface
			std::cout << "\n";
			colourSubheading();
			std::cout << "Welcome to the Notes Editor!" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nThis is where you can edit your notes.\n\n");

			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Use the following shortcuts to make changes quicker:");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n -> ^exit or nothing inputted - Exit and save.\n -> ^prev - Modify the previous note line.\n -> ^<num> - Modify a note line of a specific number. Put the number in place of <num>.\n\n");

			std::string sNoteBuffer = "";

			bool bIteratorChange = false;
			size_t nPreviousIterator = 0;
			for (size_t i = NotesMain.GetCurrentNotesCount(); i < NotesMain.GetMaxNotesArraySize(); i++) {
				std::cout << "Note ";
				colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
				std::cout << i + 1;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << ": > ";
				sNoteBuffer = StrInput("");

				// Shortcut check
				if (sNoteBuffer == "^exit" || sNoteBuffer == "") {
					colour(YLW, ConfigObjMain.sColourGlobalBack);
					std::cout << "Saving and exiting...\n";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

					if (!NotesMain.WriteToNotesFile()) {
						VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and save notes.\n");
						UserErrorDisplay("ERROR - Failed to save notes. Exiting anyway...\n");

						return;
					}

					return;
				}
				else if (sNoteBuffer == "^prev") {
					bIteratorChange = true;
					nPreviousIterator = i;
					i -= 2;
					if (i <= -1) {
						bIteratorChange = false;
						i = nPreviousIterator;
						nPreviousIterator = 0;
						NotesMain.AddNoteToArray(i, sNoteBuffer);
						// Save notes
						NotesMain.WriteToNotesFile();
					}
					else continue; // to avoid write to notes array
				}
				else if (sNoteBuffer.find("^") == 0) {
					// Possibly a number - search until the end of a string
					std::string sNumberCandidate = sNoteBuffer.substr(1, std::string::npos);
					if (isNumberull(sNumberCandidate)) {
						bIteratorChange = true;
						nPreviousIterator = i;
						i = std::stoull(sNumberCandidate);

						if (i < 1 || i > NotesMain.GetCurrentNotesCount()) {
							i = nPreviousIterator;
							nPreviousIterator = 0;
							bIteratorChange = false;
							NotesMain.AddNoteToArray(i, sNoteBuffer);
							// Save notes
							NotesMain.WriteToNotesFile();
						}
						else {
							i -= 2;
							continue; // to avoid write to notes aray
						}
					}
				}

				// Add note to note array
				NotesMain.AddNoteToArray(i, sNoteBuffer);
				// Save notes
				NotesMain.WriteToNotesFile();

				// For iterator change
				if (bIteratorChange) {
					bIteratorChange = false;
					i = nPreviousIterator - 1;
					nPreviousIterator = 0;
				}
			}
		}

		// Notes Viewer
		else if (nChoice == 2) {

			colourSubheading();
			std::cout << "Notes saved in memory:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n";
			std::stringstream ssMemoryNotes(NotesMain.GetMemoryNotes());

			// Don't do for loop if there aren't any notes
			if (ssMemoryNotes.str() == "") {
				std::cout << "No notes are saved on memory.\n";
			}
			else {
				for (int i = 0; !ssMemoryNotes.eof(); i++) {
					std::string sNoteBuffer = "";

					// Get a line up to next newline
					std::getline(ssMemoryNotes, sNoteBuffer, '\n');
					if (ssMemoryNotes.eof()) break; // break on end of stream

					// Output line with line number appended
					std::cout << "Note ";
					colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
					std::cout << i + 1;
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					std::cout << ": " << sNoteBuffer << "\n";
				}
			}
			std::cout << "\n";

			colourSubheading();
			std::cout << "Notes saved in file:" << NOULINE_STR;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\n";
			std::stringstream ssFileNotes(NotesMain.GetFileNotes());

			if (ssFileNotes.str() == "") {
				std::cout << "No notes are saved on the Notes file.\n";
			}
			else {
				for (int i = 0; !ssFileNotes.eof(); i++) {
					std::string sNoteBuffer = "";

					// Get a line up to next newline
					std::getline(ssFileNotes, sNoteBuffer, '\n');
					if (ssFileNotes.eof()) break; // break on end of stream

					// Output line with line number appended
					std::cout << "Note ";
					colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
					std::cout << i + 1;
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					std::cout << ": " << sNoteBuffer << "\n";
				}
			}

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nAll notes outputted.\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Clear Notes
		else if (nChoice == 3) {

			std::cout << '\n';
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			if (YesNo("WARNING: ALL NOTES WILL BE LOST WHEN CLEARED, BOTH ON MEMORY AND ON STORAGE.\nAre you absolutely sure you want to continue? [y for yes, n for no]: > "))
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

	// Unknown command - fail
	else {
		colour(RED, ConfigObjMain.sColourGlobalBack);
		std::cout << "Unknown command ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\"' << sCommandInputRAW << "\"";
		colour(LRED, ConfigObjMain.sColourGlobalBack);
		std::cout << ".\nPlease make sure you have inputted a listed command, and try again.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Decrement number of successful commands, as it would have been incremented before entering this function
		nNumOfSuccessfulInputtedCommands--;
		return;
	}

	return;
}
