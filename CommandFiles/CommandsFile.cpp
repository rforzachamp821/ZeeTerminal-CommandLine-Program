#include "Settings.cpp"
#include "CPUStress.cpp"
#include "CommandFileAssets.cpp"

// External function definitions
void ResetColour();
std::string wordWrap(std::string);
void CentreColouredText(std::string, short int);
void colourSubheading();
bool isNumber(const std::string);
bool WindowTitleSet(std::string);
void slowcharCentredFn(bool, std::string);
void slowcharfn(bool, std::string);
std::string CentreText(std::string);
void SetCursorAttributes();

// External variable definitions
extern std::string sCommandInputRAW;
extern RGBColourPresetSystem RGBPreset[3];
extern std::string sColourGlobal;
extern std::string sColourGlobalBack;

void Commands(const std::string, char*, std::string*, const std::string);
void help();


// Tutorial function
void Tutorial() {
	std::string sInput;
	cls();
	slowcolourfn(LBLU, sColourGlobalBack, "Using this terminal is very straightforward, and all terminals are similar in some way.");
	slowcolourfn(GRN, sColourGlobalBack, "\nFirstly, let's begin with the normal terminal screen:\n\n");
	slowcolourfn(sColourGlobal, sColourGlobalBack, "Command: > \n\n");
	slowcolourfn("255;165;0", sColourGlobalBack, "The 'Help' command tells us what commands are in this terminal.\n");
	
	// Input 'help' to continue
	while (true) {
		slowcolourfn(sColourGlobal, sColourGlobalBack, "Type in \"Help\" to see what happens: > ");
		sInput = str("");
		if (sInput == "Help" || sInput == "help") {
			bool bPreviousHelpMsg = bDisplayDirections;
			bDisplayDirections = true; // only temporary; gets put back to normal next 2 lines
			help();
			bDisplayDirections = bPreviousHelpMsg;
			break;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "Please try again.\n";
		}
	}
	slowcharfn(true, "\nThat previous command also taught you how to use the ScreenNavigate engine.\nYou can move left and right between 'screens' to scroll through information that is in the command.\n");
	
	// OptionSelect Engine Tutorial
	slowcolourfn(GRN, sColourGlobalBack, "\nNow is the next step, the OptionSelect engine.\nThis will teach you how to select options in this terminal.\n");
	OptionSelectEngine oseTutorial;
	oseTutorial.nSizeOfOptions = 3;
	std::string sOptions[] = {
		"Option 1",
		"Option 2",
		"Option 3"
	};
	oseTutorial.sOptions = sOptions;

	bool bPreviousHelpMsg = bDisplayDirections;
	bDisplayDirections = true; // only temporary; gets put back to normal afterwards

	// Start option 1
	int nOption1 = 0;
	while (nOption1 != 1) {
		nOption1 = oseTutorial.OptionSelect("Please select Option 1 from the set of options:", "___OPTIONSELECT TUTORIAL___");
		switch (nOption1) {
		case 1:
			colour(LGRN, sColourGlobalBack);
			std::cout << "That is correct!\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case 2:
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case 3:
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case -1:
			// Put help messages setting back to original value
			bDisplayDirections = bPreviousHelpMsg;
			Exiting();

			return;
		default:
			colour(RED, sColourGlobalBack);
			std::cout << "An unknown error occured. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		}
	}

	// Start option 3
	int nOption3 = 0;
	while (nOption3 != 3) {
		nOption3 = oseTutorial.OptionSelect("Please select Option 3 from the set of options:", "___OPTIONSELECT TUTORIAL___");
		switch (nOption3) {
		case 1:
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case 2:
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case 3:
			colour(LGRN, sColourGlobalBack);
			std::cout << "That is correct!!\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case -1:
			// Put help messages setting back to original value
			bDisplayDirections = bPreviousHelpMsg;
			Exiting();

			return;
		default:
			colour(RED, sColourGlobalBack);
			std::cout << "An unknown error occured. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		}
	}

	// Start option 2
	int nOption2 = 0;
	while (nOption2 != 2) {
		nOption2 = oseTutorial.OptionSelect("Please select Option 2 from the set of options:", "___OPTIONSELECT TUTORIAL___");
		switch (nOption2) {
		case 1:
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case 2:
			colour(LGRN, sColourGlobalBack);
			std::cout << "That is correct!!!\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case 3:
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		case -1:
			// Put help messages setting back to original value
			bDisplayDirections = bPreviousHelpMsg;
			Exiting();

			return;
		default:
			colour(RED, sColourGlobalBack);
			std::cout << "An unknown error occured. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		}
	}
	// Put help messages setting back to original value
	bDisplayDirections = bPreviousHelpMsg;

	// Yes/No prompt tutorial
	slowcolourfn(GRN, sColourGlobalBack, "OptionSelectEngine tutorial finished, now for the final tutorial: the Yes/No prompt.\n\n");
	slowcharfn(true, "Yes/No prompts are really important, as they manage the most important terminal functions.");
	slowcolourfn("255;165;0", sColourGlobalBack, "\nThey require you to input the letter 'y' (for yes) or the letter 'n' (for no).\n");
	slowcharfn(true, "\nHere is a yes/no prompt. Answer 'y' for this:\n");

	// The yes prompt
	bool bInput = false;
	while (bInput != true) {
		bInput = YesNo("Is this program called TerminalAppGen3? [y/n] > ");
		if (bInput == true) {
			colour(LGRN, sColourGlobalBack);
			std::cout << "Well done!\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect input. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
		}
	}

	// The no prompt
	slowcharfn(true, "Here is another yes/no prompt. Answer 'n' for this:\n");
	while (bInput != false) {
		bInput = YesNo("Is this program called TerminalAppGen3? [y/n] > ");
		if (bInput == false) {
			colour(LGRN, sColourGlobalBack);
			std::cout << "Well done!\nCongratulations, you have finished the tutorial!\n";
			colour(sColourGlobal, sColourGlobalBack);
			break;
		}
		else {
			colour(RED, sColourGlobalBack);
			std::cout << "Incorrect input. Please try again.\n";
			colour(sColourGlobal, sColourGlobalBack);
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
		colour(YLW, sColourGlobalBack);
		std::cout << wordWrap("Sorry, but changing RGB foreground colours from arguments has been locked in development for a future update.") << "\nExiting...\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}



	if (nChoice == 17) {
		short int nRed = 0, nGreen = 0, nBlue = 0;
		int nRGBForegroundColour[3] = { 255,255,255 };

		colour(YLW, sColourGlobalBack);
		std::cout << '\n' << wordWrap("Warning: Although supported program-wide, RGB is still a new and possibly unstable colour method for TerminalApp Gen 3. Be prepared for bugs and issues.")
			<< std::endl;
		colour(LCYN, sColourGlobalBack);
		std::cout << wordWrap("Type in a negative number to exit.") << "\n\n";
		colour(sColourGlobal, sColourGlobalBack);


		// Red value
		while (true) {
			nRGBForegroundColour[0] = num("Please type in Red value: > ");
			if (nRGBForegroundColour[0] > 255) {
				colour(YLW, sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(sColourGlobal, sColourGlobalBack);
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
			nRGBForegroundColour[1] = num("Please type in Green value: > ");
			if (nRGBForegroundColour[1] > 255) {
				colour(YLW, sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(sColourGlobal, sColourGlobalBack);
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
			nRGBForegroundColour[2] = num("Please type in Blue value: > ");
			if (nRGBForegroundColour[2] > 255) {
				colour(YLW, sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(sColourGlobal, sColourGlobalBack);
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
			sColourGlobal =
				std::to_string(nRGBForegroundColour[0]) + ';' +
				std::to_string(nRGBForegroundColour[1]) + ';' +
				std::to_string(nRGBForegroundColour[2]);

			// Output finishing message
			colour(LGRN, sColourGlobalBack);
			std::cout << CentreText("Foreground colour successfully set!") << std::endl;
			colour(sColourGlobal, sColourGlobalBack);
		}

		return;
	}
	else if (nChoice == -1) {
		Exiting();
		return;
	}

	ColourForegroundSwitch(&nChoice, &sColourGlobalBack, &sColourGlobal);

	colour(LGRN, sColourGlobalBack);
	std::cout << CentreText("Foreground colour successfully set!") << std::endl;
	colour(sColourGlobal, sColourGlobalBack);
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
		colour(YLW, sColourGlobalBack);
		std::cout << wordWrap("Sorry, but changing RGB background colours from arguments has been locked in development for a future update.") << "\nExiting...\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}


	if (nChoice == 17) {
		short int nRed = 0, nGreen = 0, nBlue = 0;
		int nRGBBackgroundColour[3] = { 0,0,0 };

		colour(YLW, sColourGlobalBack);
		std::cout << '\n' << wordWrap("Warning: Although supported program-wide, RGB is still a new and possibly unstable colour method for TerminalApp Gen 3. Be prepared for bugs and issues.")
			<< std::endl;
		colour(LCYN, sColourGlobalBack);
		std::cout << wordWrap("Type in a negative number to exit.") << "\n\n";
		colour(sColourGlobal, sColourGlobalBack);


		// Red value
		while (true) {
			nRGBBackgroundColour[0] = num("Please type in Red value: > ");
			if (nRGBBackgroundColour[0] > 255) {
				colour(YLW, sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(sColourGlobal, sColourGlobalBack);
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
			nRGBBackgroundColour[1] = num("Please type in Green value: > ");
			if (nRGBBackgroundColour[1] > 255) {
				colour(YLW, sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(sColourGlobal, sColourGlobalBack);
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
			nRGBBackgroundColour[2] = num("Please type in Blue value: > ");
			if (nRGBBackgroundColour[2] > 255) {
				colour(YLW, sColourGlobalBack);
				std::cout << "You cannot use numbers above 255.\nPlease try again.\n";
				colour(sColourGlobal, sColourGlobalBack);
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
			// Load values into sColourGlobalBack
			sColourGlobalBack =
				std::to_string(nRGBBackgroundColour[0]) + ';' +
				std::to_string(nRGBBackgroundColour[1]) + ';' +
				std::to_string(nRGBBackgroundColour[2]);

			// Output finishing message
			colour(LGRN, sColourGlobalBack);
			std::cout << CentreText("Background colour successfully set!") << std::endl;
			colour(sColourGlobal, sColourGlobalBack);
		}

		return;
	}
	else if (nChoice == -1) {
		Exiting();
		return;
	}

	ColourBackgroundSwitch(&nChoice, &sColourGlobalBack, &sColourGlobal);

	colour(LGRN, sColourGlobalBack);
	std::cout << CentreText("Background colour successfully set!") << std::endl;
	colour(sColourGlobal, sColourGlobalBack);
	return;
}

// A function to give an interface to modify and load RGB colour presets.
void RGBColourPresets() {
	OptionSelectEngine oseRGBPresets;

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

		if (nOption == 1) {
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

			// Load colours and variables from objects based on nOption
			sColourGlobal = RGBPreset[nOption - 1].sColourPresetForeground;
			sColourGlobalBack = RGBPreset[nOption - 1].sColourPresetBackground;
			// Warn user that default colours will be set if the preset hasn't been initialised by user
			if (RGBPreset[nOption - 1].bSetByUser == false) {
				colour(YLW, sColourGlobalBack);
				std::cout << wordWrap("Warning: This preset is an empty, undefined preset with default colours, so default colours will be set.") << std::endl;
			}
			colour(LGRN, sColourGlobalBack);
			std::cout << CentreText("RGB Preset successfully loaded!") << std::endl;
			colour(sColourGlobal, sColourGlobalBack);
		}
		else if (nOption == 2) {
			std::string sOptions[] = {
				"Preset Slot 1",
				"Preset Slot 2",
				"Preset Slot 3"
			};
			oseRGBPresets.sOptions = sOptions;

			// Display save options
			nOption = oseRGBPresets.OptionSelect("Please select which option you would like to save the current colour settings to:", " ___SAVE TO RGB PRESET___ ");
			if (nOption == -1) {
				Exiting();
				continue;
			}

			std::string sPresetName = str("Please input a name for Preset " + std::to_string(nOption) + ": > ");

			// Display overwrite message if preset was set by user already
			if (RGBPreset[nOption - 1].bSetByUser == true) {
				colour(YLW, sColourGlobalBack);
				std::cout << wordWrap("This RGB preset (" + RGBPreset[nOption - 1].sPresetName + ") already is user-defined and has user-set values.") << std::endl;

				if (!YesNo(wordWrap("Are you sure you want to overwrite these values? [y/n] > "))) {
					colour(LGRN, sColourGlobalBack);
					std::cout << "Aborted.\n";
					colour(sColourGlobal, sColourGlobalBack);

					continue;
				}
			}

			// Initialise colours and variables in objects based on runtime terminal colours and nOption
			RGBPreset[nOption - 1].sPresetName = sPresetName;
			RGBPreset[nOption - 1].sColourPresetForeground = sColourGlobal;
			RGBPreset[nOption - 1].sColourPresetBackground = sColourGlobalBack;
			// Show that object has been edited and initialised by user's consent
			RGBPreset[nOption - 1].bSetByUser = true;
			colour(LGRN, sColourGlobalBack);
			std::cout << CentreText("RGB Preset successfully saved!") << std::endl;
			colour(sColourGlobal, sColourGlobalBack);

		}
		else if (nOption == 3) {
			colour(YLW, sColourGlobalBack);
			std::cout << wordWrap("WARNING: ALL PRESETS MADE BY THE USER WILL BE DESTROYED AND INITIALISED TO DEFAULT VAULES.") << std::endl;
			if (YesNo("Would you like to proceed? [y/n] > ")) {
				// Set all RGBPreset objects to default values
				for (int i = 0; i <= 2; i++) {
					RGBPreset[i].bSetByUser = false;
					RGBPreset[i].sColourPresetBackground = "0;0;0";
					RGBPreset[i].sColourPresetForeground = "255;255;255";
					RGBPreset[i].sPresetName = "EMPTY_PRESET";
					VerbosityDisplay("RGBPreset " + std::to_string((i + 1)) + " has been set to default values.");
				}
				colour(LGRN, sColourGlobalBack);
				std::cout << "All presets have successfully been set to default values.\n";
				colour(sColourGlobal, sColourGlobalBack);
			}
			else {
				colour(LGRN, sColourGlobalBack);
				std::cout << "Preset deletion aborted.\n";
				colour(sColourGlobal, sColourGlobalBack);
			}
		}
		else if (nOption == -1) {
			Exiting();
			return;
		}
	}

	return;
}

// A function that displays all help info for the terminal.
void help() {
	ScreenNavigateEngine sneHelp;

	sneHelp.nSizeOfScreens = 3;
	std::string sScreens[] =
	{
		"___LIST OF COMMANDS___\n\n[1] Help\n[2] Exit\n[3] Tutorial\n[4] DevTools\n[5] CPUStress\n[6] Colour\n[7] Settings\n[8] Title\n[9] Date\n[10] ColourNumbers\n[11] MediaPlayer\n[12] TTS\n[13] Stopwatch\n\nMore will be added soon!\n",

		"___FREQUENTLY ASKED QUESTIONS___\n\n"
		"1) I can't see the terminal text. How can I zoom in?\n  1a) You can zoom in, of course. Press and hold the Ctrl button and scroll with the mouse to your desired text size.\n",

		"___ABOUT THIS PROGRAM___\n\nThis is a TerminalAppGen3 Alpha Build.\n" +
		wordWrap("This is an early alpha build of TerminalAppGen3, with an entirely new engine and components.") +
		"\n(c) Ryan Zorkot 2023. Protected by the MIT License.\n"
	};

	sneHelp.sScreens = sScreens;

	// Call sneHelp.ScreenNavigate for screen strings set.
	sneHelp.ScreenNavigate(" ___HELP___ ");

	return;
}

// DevTools - A function for accessing developer tools.
// These can include test interfaces and functionality testers.
void DevTools(short int nToolNum) {

	// Colour Tester
	if (nToolNum == 1) {
		CentreColouredText(" ___Colour Tester___ ", 1);
		std::cout << "\n\n";

		// Firstly, output all default colours
		// Foreground
		colourSubheading();
		std::cout << "Default Foreground Colours" << NOULINE_STR << "\n\n";
		colour(sColourGlobal, sColourGlobalBack);
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
		colour(sColourGlobal, sColourGlobalBack);
		for (int i = 40; i <= 47; i++) {
			std::cout << "\x1b[" << i << "mThis is background ANSI escape code colour <" << i << ">. 1234567890\n";
		}
		for (int i = 100; i <= 107; i++) {
			std::cout << "\x1b[" << i << "mThis is background ANSI escape code colour <" << i << ">. 1234567890 (Light)\n";
		}
		// Reset background
		std::cout << "\x1b[49m\n";

		return;
	}

	// Beep Sound Test
	else if (nToolNum == 2) {
		CentreColouredText(" ___BEEP SOUND TEST___ ", 1);

		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(true, "This is a tester for the 'Beep' function in Windows.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << NOULINE_STR << std::endl << wordWrap("TerminalAppGen3 will output a pitch of sound that increases by 100hz every second, until 22000hz.") << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press any key to exit in the middle of the test.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << '\n' << wordWrap("Press any key to begin the test, or ESC to exit...\n");
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
				colour(YLW, sColourGlobalBack);
				std::cout << "\nBeep Sound Test stopped.\n";
				clearkeebbuf();
				colour(sColourGlobal, sColourGlobalBack);
				return;
			}
		}

		std::cout << std::endl << CentreText("Beep Sound Test completed successfully.");
		return;
	}

	// ColourNumbers
	else if (nToolNum == 3) {
		// Execute the ColourNumbers command from the Command function
		char cTemp[3] = { ' ', ' ', ' ' };
		std::string sTemp = "";
		Commands("colournumbers", cTemp, &sTemp, "");

		return;
	}

	// OptionSelectEngine Tester
	else if (nToolNum == 4) {
		CentreColouredText(" ___OPTIONSELECT ENGINE TESTER___ ", 1);
		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(true, "This allows you to test the OptionSelect Engine that is in this program.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << NOULINE_STR << "\n\n";

		int nNumOfOptions = num("Please input how many options you would like to input (0 to exit): > ");
		if (nNumOfOptions <= 0) {
			Exiting();
			return;
		}

		// Use a vector as it has a dynamic array structure
		std::vector<std::string> sOptions;

		// Input all options up to nNumOfOptions
		for (int i = 0; i < nNumOfOptions; i++) {
			sOptions.push_back(str("Please input your desired string for Option " + std::to_string(i+1) + " (0 to exit): > "));
			if (sOptions[i] == "0") {
				Exiting();
				return;
			}
		}

		colour(GRN, sColourGlobalBack);
		std::cout << "\nNow for everything else...\n";
		colour(sColourGlobal, sColourGlobalBack);
		// Get title, prompt
		std::string sTitle = str("Please input your desired title for the window (0 to exit): > ");
		if (sTitle == "0") {
			Exiting();
			return;
		}
		std::string sPrompt = str("Please input your desired prompt for the window (0 to exit): > ");
		if (sPrompt == "0") {
			Exiting();
			return;
		}

		// Create an OptionSelectEngine object and assign accumulated data to members
		OptionSelectEngine oseTester;
		oseTester.nSizeOfOptions = nNumOfOptions;
		std::string* sOptionsArr = sOptions.data();
		oseTester.sOptions = sOptionsArr;

		// Call the display function
		oseTester.OptionSelect(sPrompt, sTitle);

		// Completed message
		colour(LGRN, sColourGlobalBack);
		std::cout << '\n' << CentreText("OptionSelectEngine Tester Completed Successfully!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}

	// ScreenNavigateEngine Tester
	else if (nToolNum == 5) {
		CentreColouredText(" ___SCREENNAVIGATE ENGINE TESTER___ ", 1);
		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(true, "This allows you to test the ScreenNavigate Engine that is in this program.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << NOULINE_STR << "\n\n";

		int nNumOfScreens = num("Please input how many screens you would like to input (0 to exit): > ");
		if (nNumOfScreens <= 0) {
			Exiting();
			return;
		}

		// Use a vector as it has a dynamic array structure
		std::vector<std::string> sScreens;

		// Input all screens up to nNumOfScreens
		for (int i = 0; i < nNumOfScreens; i++) {
			sScreens.push_back(str("Please input your desired string for Screen " + std::to_string(i+1) + " (0 to exit) : > "));
			if (sScreens[i] == "0") {
				Exiting();
				return;
			}
		}

		// Get title, prompt
		colour(GRN, sColourGlobalBack);
		std::cout << "\nNow for everything else...\n";
		colour(sColourGlobal, sColourGlobalBack);
		std::string sTitle = str("Please input your desired title for the window (0 to exit): > ");
		if (sTitle == "0") {
			Exiting();
			return;
		}

		// Create a ScreenNavigateEngine object and assign accumulated data to members
		ScreenNavigateEngine sneTester;
		sneTester.nSizeOfScreens = nNumOfScreens;
		std::string* sScreensArr = sScreens.data();
		sneTester.sScreens = sScreensArr;

		// Call the display function
		sneTester.ScreenNavigate(sTitle);

		// Completed message
		colour(LGRN, sColourGlobalBack);
		std::cout << '\n' << CentreText("ScreenNavigateEngine Tester Completed Successfully!") << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
	}

	// TableEngine Tester
	else if (nToolNum == 6) {
		CentreColouredText(" ___TABLE-ENGINE TESTER___ ", 1);
		std::cout << std::endl;
		colourSubheading();
		slowcharCentredFn(true, "This allows you to test the Table Engine that is in this program.");
		colour(sColourGlobal, sColourGlobalBack);

		std::cout << NOULINE_STR << "\n\n" << wordWrap("This engine's main purpose is for making tables.") << "\n";
		// Get rows and columns from user for next for loop
		int nNumOfRows = num("\nPlease input how many rows you would like to create (0 to exit): > ");
		if (nNumOfRows <= 0) {
			Exiting();
			return;
		}
		int nNumOfColumns = num("\nPlease input now many columns you would like to create (0 to exit): > ");
		if (nNumOfColumns <= 0) {
			Exiting();
			return;
		}

		// Input rows
		TableEngine teTester;
		for (int i = 0; i < nNumOfRows; i++) {
			std::vector<std::string> nRow;
			// Take all members of 1 row from user
			for (int j = 0; j < nNumOfColumns; j++) {
				nRow.push_back(str("Please input table member " + std::to_string(j + 1) + "/" + std::to_string(nNumOfColumns) + " for row " + std::to_string(i + 1) + "/" + std::to_string(nNumOfRows) + " (input 0 to exit): > "));
				if (nRow[j] == "0") {
					Exiting();
					return;
				}
			}

			if (i != (nNumOfRows - 1)) {
				colour(LGRN, sColourGlobalBack);
				std::cout << "\nMoving to next row..." << std::endl;
				colour(sColourGlobal, sColourGlobalBack);
			}
			else {
				colour(LGRN, sColourGlobalBack);
				std::cout << '\n' << CentreText("Generating table...") << "\n\n";
				colour(sColourGlobal, sColourGlobalBack);
			}
			// Send in another row using TableEngine::addRow()
			teTester.addRow(nRow);
		}

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
		slowcharCentredFn(true, "This is a CPU-intensive, nanosecond-accurate stopwatch that uses CPU ticks for the time.");
		colour(sColourGlobal, sColourGlobalBack);

		// Prompt to start
		std::cout << NOULINE_STR << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press any key in the middle of the stopwatch run to stop the time.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << "\n\n" << wordWrap("Press any key to start the stopwatch, or ESC to exit...");
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
			colour(LCYN, sColourGlobalBack);
			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\r";
			colour(sColourGlobal, sColourGlobalBack);
		}

		// Output final stopwatch time after keyboard press
		clearkeebbuf();
		colour(GRN, sColourGlobalBack);
		std::cout << "\n\nTimer stopped.";
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << "\nFinal stopwatch time: ";
		colour(LCYN, sColourGlobalBack);
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << " nanoseconds.\n";

		return;
	}

	// ANSI VT Testing Environment
	else if (nToolNum == 8) {
		std::string sANSI;
		CentreColouredText(" ___ANSI VT TESTING ENVIRONMENT___ ", 1);
		std::cout << std::endl;
		colourSubheading();
		slowcharCentredFn(true, "This is a sandbox-style testing enviroment for ANSI (VT) escape codes.");
		colour(sColourGlobal, sColourGlobalBack);

		std::cout << NOULINE_STR << "\n\n" << wordWrap("You can test any ANSI escape code here. Everything will be reset after exiting the sandbox (by typing in 0 or \"zero\").");
		colour(LBLU, sColourGlobalBack);
		std::cout << '\n' << wordWrap("You can get a list of ANSI VT escape codes here: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences") << "\n\n";
		colour(sColourGlobal, sColourGlobalBack);

		while (true) {
			sANSI = str("Please input your ANSI escape code, excluding \\x1b (ESC) and the '[' after it (0 or \"zero\" to exit): > ");
			if (sANSI == "0" || sANSI == "zero") {
				Exiting();
				std::cout << "\x1b[" << RESETALL << "m" << RESETEVERYTHING_STR << "\033c";
				// Set console cursor attributes
				SetCursorAttributes();
				// Set colour
				colour(sColourGlobal, sColourGlobalBack);
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
		slowcharCentredFn(true, "This is a sound test similar to the Beep Sound Test, but by interacting directly with drivers.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << NOULINE_STR << "\n\n" << wordWrap("TerminalAppGen3 will output a pitch of sound that starts at 20hz and increases by 100hz every second, until 22000hz.") << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press any key to exit in the middle of the test.");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << '\n' << wordWrap("Press any key to begin the test, or ESC to exit now...") << '\n';
		char cKey = _getch();
		if (cKey == 27) {
			Exiting();
			return;
		}
		else std::cout << '\n';


		HWAVEOUT* hWaveOut = new HWAVEOUT;
		WAVEFORMATEX* wfx = new WAVEFORMATEX;
		wfx->wFormatTag = WAVE_FORMAT_PCM;
		wfx->nChannels = 1;
		wfx->nSamplesPerSec = 44100;
		wfx->nAvgBytesPerSec = 44100 * 2;
		wfx->nBlockAlign = 2;
		wfx->wBitsPerSample = 16;
		wfx->cbSize = 0;

		waveOutOpen(&*hWaveOut, WAVE_MAPPER, &*wfx, 0, 0, CALLBACK_NULL);

		const int bufferSize = 44100 * 2;
		short buffer[bufferSize];

		for (int i = 20; i <= 22000; i += 100)
		{
			std::cout << "Outputting " << i << "hz...\r";
			for (int j = 0; j < bufferSize / sizeof(short); j++)
			{
				double t = (double)j / (double)wfx->nSamplesPerSec;
				double freq = i + t * 37.0;
				buffer[j] = (short)(32767.0 * sin(2.0 * M_PI * freq * t));
			}

			WAVEHDR whdr;
			whdr.lpData = (LPSTR)buffer;
			whdr.dwBufferLength = bufferSize;
			whdr.dwFlags = 0;

			waveOutPrepareHeader(*hWaveOut, &whdr, sizeof(whdr));
			waveOutWrite(*hWaveOut, &whdr, sizeof(whdr));
			while ((whdr.dwFlags & WHDR_DONE) == 0)
				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			waveOutUnprepareHeader(*hWaveOut, &whdr, sizeof(whdr));

			// Leave when keyboard key pressed
			if (_kbhit()) {
				colour(YLW, sColourGlobalBack);
				std::cout << "\n\nMMSYSTEM API Sound Test stopped.\n";
				waveOutClose(*hWaveOut);
				clearkeebbuf();
				colour(sColourGlobal, sColourGlobalBack);
				delete hWaveOut;
				delete wfx;
				return;
			}
		}

		// Close stream and output success message
		waveOutClose(*hWaveOut);
		colour(LGRN, sColourGlobalBack);
		std::cout << std::endl << CentreText("Beep Sound Test completed successfully.");
		colour(sColourGlobal, sColourGlobalBack);
		// Clear heap
		delete hWaveOut;
		delete wfx;

		return;
	}

	return;
}



// Commands function - all command interfaces/start menus will go here
void Commands(const std::string sCommand, char* cCommandArgs, std::string* sStringCommandArgs, const std::string sCommandArgsBuffer = "") {

	// Help
	if (sCommand == "help") {

		// Arguments Interface
		for (int i = 0; i < 128; i++) {
			// help message
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___HELP___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- Lists all possible commands in TerminalApp Gen3.") << '\n'
					<< wordWrap("- Displays some frequently asked questions with answers.") << '\n'
					<< wordWrap("- Displays information about the program, such as copyright information, credits and basic program information.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);

				std::cout << '\n' << wordWrap("-h\tDisplays this help message.") << "\n\n";

				return;
			}
		}

		help();
		return;
	}

	// Tutorial
	else if (sCommand == "tutorial") {

		// Arguments Interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___TUTORIAL___ ", 1);
				
				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- This command starts a short tutorial on how to use the terminal.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" -h\tDisplays this help message.") << "\n\n"
					<< wordWrap("Example: tutorial -h") << "\n\n";
				
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
	else if (sCommand == "echo") {

		// Output what is after echo
		if (sCommandArgsBuffer != " ") {
			std::cout << sCommandArgsBuffer << std::endl;
			return;
		}
		// Output what user wants to input within echo
		else {
			std::string sEcho = str("Input what you would like me to output: > ");
			// Output the input
			std::cout << sEcho << std::endl;
			return;
		}

		return;
	}

	// CLS
	else if (sCommand == "cls") {

		// Arguments Interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___CLS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("This command clears the terminal window. Nothing more, nothing less.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("-h\tDisplays this help message.") << "\n\n";

				return;
			}
		}

		cls();
		return;
	}

	// DevTools
	else if (sCommand == "devtools") {

		// Arguments
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___DEVTOOLS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("This command provides an interface to access a set of developer tools that YOU can use if you're building your own program.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" -h\tDisplays this help message.") << '\n'
					<< wordWrap(" -1\tAutomatically starts Colour Tester.") << '\n'
					<< wordWrap(" -2\tAutomatically starts Beep Sound Test.") << '\n'
					<< wordWrap(" -3\tAutomatically starts Colour Numbers.") << '\n'
					<< wordWrap(" -4\tAutomatically starts OptionSelectEngine Tester.") << '\n'
					<< wordWrap(" -5\tAutomatically starts ScreenNavigateEngine Tester.") << '\n'
					<< wordWrap(" -6\tAutomatically starts TableEngine Tester.") << '\n'
					<< wordWrap(" -7\tAutomatically starts High-Res Nanosecond Stopwatch.") << '\n'
					<< wordWrap(" -8\tAutomatically starts ANSI VT Testing Environment.") << '\n'
					<< wordWrap(" -9\tAutomatically starts MMSYSTEM API Sound Test.") << "\n\n"
					<< wordWrap("Example: devtools -6 ") << "\n\n";

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
				colour(RED, sColourGlobalBack);
				std::cout << "An unknown error occured. Please try again.\n";
				Exiting();
				break;
			}
		}

		return;
	}

	// CPUStress
	else if (sCommand == "cpustress") {

		// Arguments Interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___CPUSTRESS___ ", 1);
				
				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- Stresses your CPU and can be used for stability checks and throttling tests.") << '\n'
					<< wordWrap("- Can benchmark your CPU to see performance metrics.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" -h\t\tDisplays this help message.") << '\n'
					<< wordWrap(" -1 --<rnum>\tStarts the Single Core benchmarker. You can optionally set your reiterations in place of <rnum>.") << '\n'
					<< wordWrap(" -2 --<rnum>\tStarts the Multi Core benchmarker. You can optionally set your reiterations in place of <rnum>.") << '\n'
					<< wordWrap(" -3\t\tStarts the Single Core stress test.") << '\n'
					<< wordWrap(" -4\t\tStarts the Multi Core stress test.") << "\n\n"
					<< wordWrap("Example: cpustress -1 --120000") << "\n\n";

				return;

			}
			else if (cCommandArgs[i] == '1') {
				// First, check if it's a number
				if (isNumber(sStringCommandArgs[0]) == true) {
					CpuBenchmark(1, std::stoll(sStringCommandArgs[0]));
				}
				else CpuBenchmark(1, -1);

				return;
			}
			else if (cCommandArgs[i] == '2') {
				if (isNumber(sStringCommandArgs[0]) == true) {
					CpuBenchmark(2, std::stoll(sStringCommandArgs[0]));
				}
				else CpuBenchmark(2, -1);

				return;
			}
			else if (cCommandArgs[i] == '3') {
				CpuStressTest(1, true);
				return;
			}
			else if (cCommandArgs[i] == '4') {
				CpuStressTest(2, true);
				return;
			}
		}

		OptionSelectEngine CpuStress;

		// Starting page
		CentreColouredText(" ___CPUSTRESS___ ", 1);
		std::cout << '\n';
		slowcharCentredFn(true, "CPUStress can stress or benchmark your CPU in multiple different ways.");

		while (true) {

			std::cout << '\n';
			CentreColouredText("You can stop a test at any time by pressing a key on the keyboard.", 2);
			std::cout << "\n\n";

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
				CpuBenchmark(1);
			}
			else if (nChoice == 2) {
				CpuBenchmark(2);
			}
			else if (nChoice == 3) {
				CpuStressTest(1);
			}
			else if (nChoice == 4) {
				CpuStressTest(2);
			}
			else if (nChoice == -1) {
				Exiting();
				return;
			}
		}

		return;
	}

	// Colour
	else if (sCommand == "colour") {
		bool bArgExecuted = false;
		bool bForeExecuted = false;
		bool bBackExecuted = false;

		// Arguments interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___COLOUR___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What it does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- Adjusts the foreground colour of the terminal (text).") << '\n'
					<< wordWrap("- Adjusts the background colour of the terminal.") << '\n'
					<< wordWrap("- Edit and apply custom RGB colour presets.") << '\n'
					<< wordWrap("- Resets colours to default at request.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" -h\t\t\tDisplays this help message.") << '\n'
					<< wordWrap(" -f --<colournum>\tAdjusts foreground colour. Put colour number in place of <colournum>.") << '\n'
					<< wordWrap(" -b --<colournum>\tAdjusts background colour. Put desired colour number in place of <colournum>.") << '\n'
					<< wordWrap(" -r\t\t\tResets colours to default values (excluding RGB colour profiles).") << "\n\n"
					<< wordWrap("Example: colour -f --3 -b --7 ") << "\n\n";
				std::cout << wordWrap("Note: You can get the colour numbers by executing the \"ColourNumbers\" command.") << "\n\n";

				return;
			}
			else if (cCommandArgs[i] == 'f') {
				
				// Can't run background editing twice in the same command
				if (bForeExecuted == true) continue;

				// Find the argument from argument buffer find first 2 dashes after it, and find next space
				int n = sCommandArgsBuffer.find("-f");
				int nDashPos = sCommandArgsBuffer.find("--", n);
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				// std::string::npos symbolises an error
				if (nDashPos != std::string::npos && nSpacePos != std::string::npos) {
					std::string sForegroundArg = sCommandArgsBuffer.substr(nDashPos + 2, nSpacePos - (nDashPos + 2));
					if (isNumber(sForegroundArg) == true) {
						ColourForeground(std::stoi(sForegroundArg));
					}
					else {
						// Can't process a non-number
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured while processing your foreground argument. Make sure your argument syntax is correct, and try again.")
							<< "\nType \"colour -h\" for more info.\nExiting...\n";
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					// Can't find any argument
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured while finding any foreground argument in your input. Make sure you have an argument after the colour setting choice, and try again.")
						<< "\nType \"colour -h\" for more info.\nExiting...\n";
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				bArgExecuted = true;
				bForeExecuted = true;
			}
			else if (cCommandArgs[i] == 'b') {

				// Can't run background editing twice in the same command
				if (bBackExecuted == true) continue;

				// Find the argument from argument buffer find first 2 dashes after it, and find next space
				int n = sCommandArgsBuffer.find("-b");
				int nDashPos = sCommandArgsBuffer.find("--", n);
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos != std::string::npos && nSpacePos != std::string::npos) {
					std::string sBackgroundArg = sCommandArgsBuffer.substr(nDashPos + 2, nSpacePos - (nDashPos + 2));
					// Check if argument is a number
					if (isNumber(sBackgroundArg) == true) {
						ColourBackground(std::stoi(sBackgroundArg));
					}
					else {
						// Can't process a non-number
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured while processing your background argument. Make sure your argument syntax is correct, and try again.") 
							<< "\nType \"colour -h\" for more info.\nExiting...\n";
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					// Can't find any argument
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured while finding any background argument in your input. Make sure you have an argument after the colour setting choice, and try again.") 
						<< "\nType \"colour -h\" for more info.\nExiting...\n";
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				bArgExecuted = true;
				bBackExecuted = true;
			}
			else if (cCommandArgs[i] == 'r') {
				// Reset colours prompt
				colour(YLW, sColourGlobalBack);
				std::cout << "\nTHIS WILL RESET ALL SET COLOURS TO DEFAULT VALUES.\n";
				colour(sColourGlobal, sColourGlobalBack);
				if (YesNo(wordWrap("Are you sure you would like to proceed? [y/n] > "))) {
					// Only reset colours when VT sequences are available- non-VT terminals remain white on black.
					if (bAnsiVTSequences == true) {
						ResetColour();
					}
					else std::cout << "\nColours are already defaulted for your terminal.\n";
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
				colour(YLW, sColourGlobalBack);
				std::cout << "\nTHIS WILL RESET ALL SET COLOURS TO DEFAULT VALUES.\n";
				colour(sColourGlobal, sColourGlobalBack);
				if (YesNo(wordWrap("Are you sure you would like to proceed? [y/n] > "))) {
					// Only reset colours when VT sequences are available- non-VT terminals remain white on black.
					if (bAnsiVTSequences == true) {
						ResetColour();
					}
					else std::cout << "\nColours are already defaulted for your terminal.\n";
				}
				else {
					colour(YLW, sColourGlobalBack);
					std::cout << "\nAborted...\n";
					colour(sColourGlobal, sColourGlobalBack);
				}
			}
			else if (nChoiceFirst == -1) {
				Exiting();
				break;
			}
		}

		return;
	}

	// Settings
	else if (sCommand == "settings") {

		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___SETTINGS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What it does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- The Settings command allows you to adjust common settings in the terminal, such as colour settings, verbosity and direction messages, and ANSI settings.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for the Settings command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" --highlightfore --<num>\tModifies the highlight foreground colour. Set your colour number in place of <num>.") << '\n'
					<< wordWrap(" --highlightback --<num>\tModifies the highlight background colour. Set your colour number in place of <num>.") << '\n'
					<< wordWrap(" --titlefore --<num>\t\tModifies the title foreground colour. Set your colour number in place of <num>.") << '\n'
					<< wordWrap(" --titleback --<num>\t\tModifies the title background colour. Set your colour number in place of <num>.") << '\n'
					<< wordWrap(" --subheadingfore --<num>\tModifies the subheading foreground colour. Set your colour number in place of <num>.") << '\n'
					<< wordWrap(" --subheadingback --<num>\tModifies the subheading background colour. Set your colour number in place of <num>.") << '\n'
					<< wordWrap(" --verbose -t/f\t\t\tToggles verbose messages. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --directions -t/f\t\tToggles direction messages. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --ansi -t/f\t\t\tToggles ANSI VT sequences. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --wordwrap -t/f\t\tToggles word wrapping. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --cursorblink -t/f\t\tToggles cursor blinking. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --showcursor -t/f\t\tToggles cursor visibility. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --cursorstyle --<style>\tSets the style of the cursor. Set the style (block, underline, bar) in place of <style>.") << '\n'
					<< wordWrap(" --slowcharspeed --<num>\tSets the speed of SlowChar. Set the speed in place of <num>.") << '\n'
					<< wordWrap(" --randcolstartup -t/f\t\tToggles random colours on startup. Set either true (-t) or false (-f) in place of -t/f.") << '\n'
					<< wordWrap(" --customtheme -t/f\t\tToggles terminal custom theme support. Set either true (-t) or false (-f) where t/f is.") << "\n\n"
					<< wordWrap("Example: --titlefore --1") << "\n\n"
					<< wordWrap("Note: You can get colour numbers by executing the \"ColourNumbers\" command.") << "\n\n";

				return;
			}
			else if (sStringCommandArgs[0] == "highlightfore") {
				// Get argument position
				int nArgPos = sCommandArgsBuffer.find("--highlightfore") + 2;
				// Get dashes position after argument
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				// Get space position to copy as argument to function
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				// if statement to see if dash or space was found
				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) 
				{
					// Check if argument is a number, post error message if not and call function if yes
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						HighlightColourSettings(1, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)));
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				return;
			}
			else if (sStringCommandArgs[0] == "highlightback") {
				int nArgPos = sCommandArgsBuffer.find("--highlightback") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						HighlightColourSettings(2, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)));
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				
				return;
			}
			else if (sStringCommandArgs[0] == "titlefore") {
				int nArgPos = sCommandArgsBuffer.find("--titlefore") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						TitleColourSettings(1, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)));
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				return;
			}
			else if (sStringCommandArgs[0] == "titleback") {
				int nArgPos = sCommandArgsBuffer.find("--titleback") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos-2 != std::string::npos && nSpacePos != std::string::npos) {
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						TitleColourSettings(2, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)));
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				return;
			}
			else if (sStringCommandArgs[0] == "subheadingfore") {
				int nArgPos = sCommandArgsBuffer.find("--subheadingfore") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						SubheadingColourSettings(1, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)));
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}
				return;
			}
			else if (sStringCommandArgs[0] == "subheadingback") {
				int nArgPos = sCommandArgsBuffer.find("--subheadingback") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						SubheadingColourSettings(2, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)));
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "verbose") {
				int nArgPos = sCommandArgsBuffer.find("--verbose") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						VerboseMessagesSettings(1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						VerboseMessagesSettings(2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "directions") {
				int nArgPos = sCommandArgsBuffer.find("--directions") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						DirectionMessagesSettings(1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						DirectionMessagesSettings(2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "ansi") {
				int nArgPos = sCommandArgsBuffer.find("--ansi") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						AnsiSettings(1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						AnsiSettings(2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "wordwrap") {
				int nArgPos = sCommandArgsBuffer.find("--wordwrap") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						WordWrapSettings(1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						WordWrapSettings(2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "cursorblink") {
				int nArgPos = sCommandArgsBuffer.find("--cursorblink") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						CursorSettings(1, 1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						CursorSettings(1, 2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "showcursor") {
				int nArgPos = sCommandArgsBuffer.find("--showcursor") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						CursorSettings(2, 0, 1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						CursorSettings(2, 0, 2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "cursorstyle") {
				int nArgPos = sCommandArgsBuffer.find("--cursorstyle") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "block") {
						CursorSettings(3, 0, 0, 1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "underline") {
						CursorSettings(3, 0, 0, 2);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "bar") {
						CursorSettings(3, 0, 0, 3);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's either '--block', '--underline', or '--bar'.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "slowcharspeed") {
				int nArgPos = sCommandArgsBuffer.find("--slowcharspeed") + 2;
				int nDashPos = sCommandArgsBuffer.find("--", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (isNumber(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos))) {
						OtherSettings(1, std::stoi(sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos)), true);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's a number and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "randcolstartup") {
				int nArgPos = sCommandArgsBuffer.find("--randcolstartup") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						OtherSettings(2, 0, true, 1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						OtherSettings(2, 0, true, 2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
					return;
				}

				return;
			}
			else if (sStringCommandArgs[0] == "customtheme") {
				int nArgPos = sCommandArgsBuffer.find("--customtheme") + 2;
				int nDashPos = sCommandArgsBuffer.find(" -", nArgPos) + 2;
				int nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

				if (nDashPos - 2 != std::string::npos && nSpacePos != std::string::npos) {
					if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "t") {
						OtherSettings(3, 0, true, 0, 1);
					}
					else if (sCommandArgsBuffer.substr(nDashPos, nSpacePos - nDashPos) == "f") {
						OtherSettings(3, 0, true, 0, 2);
					}
					else {
						colour(RED, sColourGlobalBack);
						std::cout << wordWrap("An error occured. Your setting option seems to be incorrect. Make sure it's \"-t\" or \"-f\" and try again.") << std::endl
							<< wordWrap("Type \"settings -h\" for more info.");
						colour(sColourGlobal, sColourGlobalBack);
						return;
					}
				}
				else {
					colour(RED, sColourGlobalBack);
					std::cout << wordWrap("An error occured. It seems like no option was found. Check your syntax, make sure an option is present and try again.") << std::endl
						<< wordWrap("Type \"settings -h\" for more info.");
					colour(sColourGlobal, sColourGlobalBack);
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
				colour(RED, sColourGlobalBack);
				std::cout << "An error occured. Please try again later.\n";
				colour(sColourGlobal, sColourGlobalBack);
				break;
			}
		}

		return;
	}

	// Title
	else if (sCommand == "title") {

		if (sCommandArgsBuffer == " ") {
			// Take title input
			std::string sTitle = str("Please input your desired title: > ");
			// Set window title using WindowTitleSet engine function
			if (WindowTitleSet(sTitle)) {
				colour(LGRN, sColourGlobalBack);
				std::cout << "Setting console window title succeeded!\n";
				colour(sColourGlobal, sColourGlobalBack);
			}
			else {
				colour(RED, sColourGlobalBack);
				std::cout << wordWrap("Setting console window title failed!\nPlease check if your title is too long. It cannot be longer than 256 characters.\n");
				colour(sColourGlobal, sColourGlobalBack);
			}
		}
		else {
			if (WindowTitleSet(sCommandArgsBuffer)) {
				colour(LGRN, sColourGlobalBack);
				std::cout << wordWrap("Setting console window title succeeded!\n");
				colour(sColourGlobal, sColourGlobalBack);
			}
			else {
				colour(RED, sColourGlobalBack);
				std::cout << wordWrap("Setting console window title failed!\nPlease check if your title is too long. It cannot be longer than 256 characters.\n");
				colour(sColourGlobal, sColourGlobalBack);
			}
		}

		return;
	}

	// Date
	else if (sCommand == "date") {

		// Arguments interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___DATE___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- This command displays the time and date in 24 hour time. Nothing more, nothing less.") << "\n\n";

				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" -h\tDisplays this help message.") << "\n\n"
					<< wordWrap("Example: date -h") << "\n\n";

				return;

			}
		}

		time_t currentTime = time(0);
		struct tm localTime {};

		time(&currentTime);
		localtime_s(&localTime, &currentTime);

		std::cout << "Local Date: ";
		colour(LCYN, sColourGlobalBack);
		std::cout << localTime.tm_mday << "/" << (localTime.tm_mon + 1) << "/" << (localTime.tm_year + 1900); 
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << " (DD/MM/YYYY)\n";
		std::cout << "Local Time: ";
		colour(LCYN, sColourGlobalBack);
		std::cout << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << "\n";
		colour(sColourGlobal, sColourGlobalBack);

		return;
	}

	// ColourNumbers
	else if (sCommand == "colournumbers") {

		// Arguments Interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___COLOURNUMBERS___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does:" << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap("- This command displays the colour numbers for all default colours. Nothing more, nothing less.") << "\n\n";
				
				colourSubheading();
				std::cout << "Possible arguments for this command:" << NOULINE_STR << '\n';
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n' << wordWrap(" -h\tDisplays this help message.") << "\n\n"
					<< wordWrap("Example: colournumbers -h") << "\n\n";
				
				return;
			}
		}

		// Display all colours in the colour array inside Settings.cpp
		std::cout << '\n';
		colourSubheading();
		std::cout << "Colour numbers are below:" << NOULINE_STR;
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << '\n';

		for (int i = 0; i < 16; i++) {
			std::cout << '[' << (i + 1) << "] "<< sOptionsColour[i] << "\n";
		}
		std::cout << std::endl << wordWrap("The colour number for each colour is in between the square brackets.") << std::endl;

		return;
	}

	// MediaPlayer
	else if (sCommand == "mediaplayer") {

		std::wstring wsFilePath;

		// Arguments Interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___MEDIA PLAYER___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does: " << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n';
				std::cout << wordWrap("- Can play media and audio of specific types.") << '\n'
					<< wordWrap("- Can view images of specific types.") << '\n'
					<< wordWrap("- Supported file formats: WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, MP3 (Only MPEG Audio Layer-3 codec), JPG and BMP.") << "\n\n";

				std::cout << '\n';
				colourSubheading();
				std::cout << "Possible arguments for this command: " << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << '\n';
				std::cout << wordWrap(" -h\t\tDisplays this help message.") << '\n'
					<< wordWrap(" --<FILE>\tOpens a file for playback/viewing. Put the exact filepath in place of <FILE>.\n\nExample: mediaplayer --\"C:\\Media\\media test.mp3\"\n\n")
					<< wordWrap("Note: You need to use quotes like shown in the example to use a filename with ANY spaces.\n\n");

				return;
			}
			else if (sStringCommandArgs[0] != " ") {

				std::string sFilePath = sCommandArgsBuffer;

				// Check if the start of the first argument has a speechmark; 
				// if there is one, use filepath from the start to the ending speechmark (if there is one)
				if (sStringCommandArgs[0][0] == '\"') {
					int nFirstMarkPos = sFilePath.find("--\"", 0) + 3;
					int nFinalMarkPos = sFilePath.find('\"', nFirstMarkPos) - 3;
					sFilePath = sFilePath.substr(nFirstMarkPos, nFinalMarkPos); 
					VerbosityDisplay("Executing file " + sFilePath + "...\n");
				}
				else sFilePath = sStringCommandArgs[0];

				CA2W ca2w(sFilePath.c_str());
				MultimediaEngine meArgInterface;

				std::wstring wsPath;
				wsPath = ca2w;
				meArgInterface.MultimediaPlayer(wsPath);

				return;
			}
		}

		CentreColouredText(" ___MEDIA PLAYER___ ", 1);

		// Information
		colourSubheading();
		std::cout << wordWrap("\n\nThe following file formats are supported:\n") << NOULINE_STR;
		colour(LCYN, sColourGlobalBack);
		std::cout << wordWrap("WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, MP3(Only MPEG Audio Layer - 3 codec), JPG, BMP\n\n");
		colour(sColourGlobal, sColourGlobalBack);

		// Prompt
		std::cout << "Enter your desired audio/video/image file path (0 to exit): > ";
		colour(LYLW, sColourGlobalBack);
		std::getline(std::wcin, wsFilePath);
		colour(sColourGlobal, sColourGlobalBack);

		// Exit on 0
		if (wsFilePath == L"0") {
			Exiting();
			return;
		}

		// Execute multimedia player with the inputted file path
		MultimediaEngine meMediaPlayer;
		meMediaPlayer.MultimediaPlayer(wsFilePath);

		return;

	}

	// TTS
	else if (sCommand == "tts") {
		
		// Arguments interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___TEXT TO SPEECH___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does: " << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << wordWrap("\n- Takes in input and outputs it with a human-like voice through the speaker.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command: " << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << wordWrap("\n -h\t\tDisplays this help message.\n --<MSG>\tInput text to be said by the computer. Put text in place of <MSG>.\n\n")
					<< wordWrap("Example: tts --\"The quick brown fox jumps over the lazy dog.\"\n\n")
					<< wordWrap("Note: If the text contains any spaces, put it in speech marks like the example, or it will not work.\n\n");

				return;
			}
			else if (sStringCommandArgs[0] != " ") {

				std::string sText = sCommandArgsBuffer;

				// Check if the start of the first argument has a speechmark; 
				// if there is one, use text from the start to the ending speechmark (if there is one)
				if (sStringCommandArgs[0][0] == '\"') {
					int nFirstMarkPos = sText.find("--\"", 0) + 3;
					int nFinalMarkPos = sText.find('\"', nFirstMarkPos) - 3;
					sText = sText.substr(nFirstMarkPos, nFinalMarkPos);
					VerbosityDisplay("Outputting \"" + sText + "\" as TTS...\n");
				}
				else sText = sStringCommandArgs[0];

				CA2W ca2w(sText.c_str());
				std::wstring wsFinalText;
				wsFinalText = ca2w;

				// Execute text-to-speech
				MultimediaEngine meTTS;
				meTTS.TTSOutput(wsFinalText);

				return;
			}
		}

		CentreColouredText(" ___TEXT-TO-SPEECH___ ", 1);

		std::cout << "\n\n";
		colourSubheading();
		slowcharCentredFn(true, "Text To Speech takes in text and outputs it through the speakers in a human-like voice.\n");
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << NOULINE_STR;

		// Take input
		std::string sText = str("Please input your desired text (0 to exit): > ");
		if (sText == "0") {
			Exiting();
			return;
		}

		CA2W ca2w(sText.c_str());

		// Pass to wstring
		std::wstring wsText;
		wsText = ca2w;

		// Output using MultimediaEngine::TTS()
		MultimediaEngine meTTS;
		VerbosityDisplay("Outputting \"" + sText + "\" as TTS...\n");
		meTTS.TTSOutput(wsText);

		return;
	}

	// Stopwatch
	else if (sCommand == "stopwatch") {

		bool bSkipStartScreen = false;

		// Arugments interface
		for (int i = 0; i < 128; i++) {
			if (cCommandArgs[i] == 'h') {
				CentreColouredText(" ___STOPWATCH___ ", 1);

				std::cout << '\n';
				colourSubheading();
				std::cout << "What this command does: " << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << wordWrap("\n- Allows for the use for a simple stopwatch. Nothing more, nothing less.\n\n");

				colourSubheading();
				std::cout << "Possible arguments for this command: " << NOULINE_STR;
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << wordWrap("\n -h\tDisplays this help message.\n -i\tStarts the stopwatch immediately on command execution.\n\nExample: stopwatch -i\n\n");

				return;
			}
			else if (cCommandArgs[i] == 'i') {
				bSkipStartScreen = true;
				break;
			}
		}

		CentreColouredText(" ___STOPWATCH___ ", 1);
		std::cout << '\n';
		CentreColouredText("This is a simple stopwatch that measures the time in milliseconds.", 2);
		
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
			colour(YLW, sColourGlobalBack);
			std::cout << "\n\nTest starting immediately...\n";
			colour(sColourGlobal, sColourGlobalBack);
		}

		// Start stopwatch
		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		std::cout << '\n';
		while (!_kbhit()) {
			end = std::chrono::steady_clock::now();
			std::cout << "Time: ";
			colour(LCYN, sColourGlobalBack);
			std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			colour(sColourGlobal, sColourGlobalBack);
			std::cout << " milliseconds...\r";
		}

		// Assume keyboard has been pressed
		colour(GRN, sColourGlobalBack);
		std::cout << "\n\nKeyboard pressed.\n";
		colour(sColourGlobal, sColourGlobalBack);

		// Output final time
		std::cout << "Final time: ";
		colour(LCYN, sColourGlobalBack);
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		colour(sColourGlobal, sColourGlobalBack);
		std::cout << " milliseconds.\n\n";

		clearkeebbuf();
		return;
	}

	// Unknown command - fail
	else {
		colour(RED, sColourGlobalBack);
		std::cout << "Unknown command ";
		colour(LCYN, sColourGlobalBack);
		std::cout << '\"' << sCommandInputRAW << "\"";
		colour(LRED, sColourGlobalBack);
		std::cout << ".\nPlease make sure you have inputted a listed command, and try again.\n";
		colour(sColourGlobal, sColourGlobalBack);
		return;
	}
	return;
}
