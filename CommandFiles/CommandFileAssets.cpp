//
// CommandFileAssets.cpp - Contains assets for the commands in CommandsFile.cpp.
//
#include "../Core/ZeeTerminalCore.h"
#include "../Engine/MultimediaEngine/MultimediaEngine.h"
#include "CommandsFiles\Commands.h"
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

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
					if (colconv::ValidateColourStringsWin32() == false) {
						bValidColours = false;
					}
				}
				else if (RGBPreset[nOption - 1].CheckIfAnsiPreset() == true) {
					if (colconv::ValidateColourStringsANSI() == false) {
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
	// Output title
	CentreColouredText(" ___HELP___ ", 1);
	std::cout << "\n\n";

	// Output subheading and information about commands to display help commands under
	colourSubheading();
	std::cout << wordWrap("___LIST OF COMMANDS___") << NOULINE_STR;
	colour(LCYN, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n\nTo see more info about a command, type in \"<command> -h\". Put the command in the place of <command> here.\n\n");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Output help commands
	std::cout <<
		"[1] Help\t\t[16] Stopwatch\t\t[31] Shutdown\t\t[46] Edison\t[61] Converter\n"
		"[2] Exit\t\t[17] Read\t\t[32] Reboot\t\t[47] Tesla\t[62] RandNum\n"
		"[3] Tutorial\t\t[18] Timer\t\t[33] Hibernate\t\t[48] Cow\n"
		"[4] Echo\t\t[19] Beep\t\t[34] ResetExpl\t\t[49] Cat\n"
		"[5] CLS\t\t\t[20] MessageBox\t\t[35] MemTest\t\t[50] Bunny\n"
		"[6] DevTools\t\t[21] Copy\t\t[36] RandCol\t\t[51] Game\n"
		"[7] CPUStress\t\t[22] CopyFile\t\t[37] Pause\t\t[52] FileCryptor\n"
		"[8] Colour\t\t[23] TextInfo\t\t[38] CommandNum\t\t[53] Delete\n"
		"[9] Settings\t\t[24] ConfigAction\t[39] SlowChar\t\t[54] Factorial\n"
		"[10] Title\t\t[25] BeepSounds\t\t[40] ReverseText\t[55] CalcQuadratic\n"
		"[11] Date\t\t[26] RickRoll\t\t[41] Notes\t\t[56] Y2038\n"
		"[12] ColourNumbers\t[27] ShellExecute\t[42] FileParse\t\t[57] PiOutput\n"
		"[13] MediaPlayer\t[28] Hacker\t\t[43] Disp\t\t[58] Spam\n"
		"[14] AudioPlayer\t[29] Calculator\t\t[44] SysInfo\t\t[59] FAQ\n"
		"[15] TTS\t\t[30] Logoff\t\t[45] Einstein\t\t[60] About\n"

		"\nMore will be added soon!\n";

	// Exit
	return;
}

// About - A function that displays all about and copyright information for ZeeTerminal,
//         using the ScreenNavigate engine.
//
void About(bool bFromTutorial) {
	ScreenNavigateEngine sneAbout;

	sneAbout.nSizeOfScreens = 2;
	std::string sScreens[] =
	{
		"___ABOUT THIS PROGRAM___\n\nThis is the ZeeTerminal Commandline Program, Build v" + std::string(ZT_VERSION) + ".\n" +
		"This is a public stable release build of ZeeTerminal, with an entirely new engine and components.\nThis program is made in C++, with a few very small parts of C." +
		"\n\nThis program uses the DirectShow API in the MediaPlayer command, licensed by Microsoft Corp. (c) Microsoft Corp.\n\n" +
		"This program uses the BASS API in the AudioPlayer command, licensed by Un4Seen Developments. (c) Un4Seen Developments.\n\n" +
		"This program uses the CarDodge game v0.6.0, accessible in the Game command. CarDodge is licensed under RZVelocity64 with the MIT License. For more information, visit the archived repo: https://github.com/rzvelocity64/CarDodge\n\n"
		"\nZeeTerminal is licensed under the MIT License. The license and credits can be viewed on Page 4.\n\n"
		"  _____        _____                   _             _ \n"
		" |__  /___  __|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |\n"
		"   / // _ \\/ _ \\| |/ _ \\ '__| '_ \\` _ \\| | '_ \\ / _\\` |\n"
		"  / /|  __/  __/| |  __/ |  | | | | | | | | | | (_| | |\n"
		" /____\\___|\\___||_|\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|\n"
		"                                                       ",

		"___LICENSE AND CREDITS___\n\n"
		"Massive thank-you to my dad, Hazem, for assisting with this project, including with the logo design, name, high-level component ideas, and lots of heads-up messages along the way.\n\n"
		"ZeeTerminal is licensed under the MIT License. Below is the license info:\n\nCopyright (c) 2025 RZVelocity64.\n\n"
		"Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal"
		" in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell"
		" copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n"
		"The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\n"
		"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
		"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
		"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\n"
	};

	sneAbout.sScreens = sScreens;
	
	// Set custom direction text when coming from tutorial
	if (bFromTutorial) {
		sneAbout.SetDirectionsText("Press the 'A' key or left arrow key to move left.\nPress the 'D' key or right arrow key to move right.\nPress ESC to exit the About command and continue with the tutorial.");
	}

	// Call sneAbout.ScreenNavigate for screen strings set.
	sneAbout.ScreenNavigate(" ___ABOUT___ ");

	return;
}

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

	sleep(1000);
	slowcharfn(true, "\nDid you notice how when you typed in 'help', the Help command executed?\nWhen executing commands, type the name of the command and press ENTER to execute it, just like you did to execute the Help command.\n"
		"Use the Help command to get a reference of all the commands in the terminal.");

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

// DevTools - A function for accessing developer tools.
// These can include test interfaces and functionality testers.
void DevTools(short int nToolNum) {

	// Colour Tester
	if (nToolNum == 1) {
		CentreColouredText(" ___COLOUR TESTER___ ", 1);
		std::cout << wordWrap("\n\nNote that ANSI colour escape sequences may not be interpreted correctly or at all on older terminals, such as Windows 7.\n\n");

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
		// Reset background to previous colours
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		std::cout << "Press ESC to exit...\n";
		while (true) {
			// _kbhit() to exit on ESC keypress
			if (_kbhit()) {
				if (_getch() == 27) break;
			}
			sleep(10);
		}

		return;
	}

	// Beep Sound Test
	else if (nToolNum == 2) {
		CentreColouredText(" ___BEEP SOUND TEST___ ", 1);

		std::cout << '\n';
		colourSubheading();
		slowcharCentredFn(false, "This is a tester for the 'Beep()' function in Windows.");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << NOULINE_STR << std::endl;
		std::cout << wordWrap("ZeeTerminal will output a pitch of sound that increases by 100hz every second, until 22000hz.") << "\n\n";
		colour(MAG, LYLW);
		std::cout << wordWrap("You can press ESC to exit in the middle of the test.");
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
			// output and colour the hertz value
			std::cout << "Outputting ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << i << " hz...";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			Beep(i, 1000);
			// stop if kbhit is true and ESC key was pressed
			if (_kbhit() && _getch() == 27) {
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
		char cTemp[nArgArraySize];
		for (int i = 0; i < nArgArraySize; i++) {
			cTemp[i] = ' ';
		}
		commands::Commands11To20("colournumbers", cTemp, "");

		std::cout << "\nPress ESC to exit...\n";
		while (true) {
			// _kbhit() to exit on ESC keypress
			if (_kbhit()) {
				if (_getch() == 27) break;
			}
			sleep(10);
		}


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
		for (int i = 0;; i++) {
			sOptions.push_back(StrInput("Please input your desired string for Option " + std::to_string(i + 1) + " (0 to finish input, -1 to exit entirely): > "));
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
			sScreens.push_back(StrInput("Please input your desired string for Screen " + std::to_string(i + 1) + " (0 to finish, -1 to exit entirely) : > "));
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
		// Output title, headings
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
		uint64_t nNumOfColumns = PositiveNumInputull("\nPlease input how many columns you would like to create (0 to exit): > ");
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

		// Exit on ESC keypress
		std::cout << "Press ESC to exit...\n";
		while (true) {
			if (_kbhit()) {
				if (_getch() == 27) break;
			}
			sleep(10);
		}

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
		std::cout << wordWrap("You can press the ESC key in the middle of the stopwatch run to stop it.");
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


		while (true) {
			// _kbhit() to exit on ESC keypress
			if (_kbhit()) {
				if (_getch() == 27) break;
			}
			
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

		std::cout << NOULINE_STR << wordWrap("\n\nYou can test any ANSI escape code here. Everything will be reset after exiting the sandbox (by typing in 0 or \"zero\").\nSome older terminals, e.g Windows 7 terminals, cannot interpret ANSI escape codes properly, therefore this may not produce intended results on those systems.");
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
		std::cout << wordWrap("You can press ESC to exit in the middle of the test.");
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

// A switch-case function for the ColourBackground function.
bool ColourBackgroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable) {
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
		ConfigObjMain.WriteConfigFile();
		return false;
	}

	ConfigObjMain.WriteConfigFile();

	return true;
}

// A switch-case function for the ColourForeground function.
bool ColourForegroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable)
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
		ConfigObjMain.WriteConfigFile();
		return false;
	}

	ConfigObjMain.WriteConfigFile();

	return true;
}

// A function that gives an interface to modify the global foreground colour of the terminal.
void ColourForeground(int nChoice = 0) {

	// Execute menu if wrong argument input or no argument
	if (nChoice <= 0 || nChoice > 17) {
		OptionSelectEngine oseColourFore;
		oseColourFore.nSizeOfOptions = 17;
		std::string sOptions[] = {
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
			"Bright White (DEFAULT)",
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

	// Apply foreground colour
	if (ColourForegroundSwitch(&nChoice, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal)) {
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Foreground colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	return;
}

// A function that gives an interface to modify the global background colour of the terminal.
void ColourBackground(int nChoice = 0) {

	// Execute menu if wrong argument input or no argument
	if (nChoice <= 0 || nChoice > 17) {
		OptionSelectEngine oseColourBack;
		oseColourBack.nSizeOfOptions = 17;
		std::string sOptions[] = {
			"Black (DEFAULT)",
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
			"Bright White",
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

	// Set background colour
	if (!ColourBackgroundSwitch(&nChoice, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal)) {
		return;
	}
	else {
		// Apply colours to whole screen
		cls();

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << CentreText("Background colour successfully set!") << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	return;
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

// Mission Impossible Theme Song in Beeps
//
void MissionImpossibleTheme() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(932, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(1047, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(699, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(740, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(932, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(1047, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	sleep(300);
	bExitEarly = meSong.BeepSound(699, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(740, 150, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(932, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587, 1200, true);
	if (bExitEarly == false) return;
	sleep(75);
	bExitEarly = meSong.BeepSound(932, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(554, 1200, true);
	if (bExitEarly == false) return;
	sleep(75);
	bExitEarly = meSong.BeepSound(932, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(784, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523, 1200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(466, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523, 150, true);
	if (bExitEarly == false) return;

	return;
}

// Happy Birthday Song in Beep Sounds
//
void HappyBirthdaySong() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(1059.274, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1059.274, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1188.995, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1059.274, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1413.961, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1334.601, 950, true);
	if (bExitEarly == false) return;

	bExitEarly = meSong.BeepSound(1059.274, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1059.274, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1188.995, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1059.274, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1587.117, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1413.961, 950, true);
	if (bExitEarly == false) return;

	bExitEarly = meSong.BeepSound(1059.274, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1059.274, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(2118.547, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1781.479, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1413.961, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1334.601, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1188.995, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1887.411, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1887.411, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1781.479, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1413.961, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1587.117, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1413.961, 900, true);
	if (bExitEarly == false) return;

	return;
}

// Super Mario Theme Song in Beep Sounds
//
void SuperMarioTheme() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(660, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(510, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(770, 550, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 575, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(510, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 400, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(320, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(480, 330, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(450, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(860, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(700, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(520, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(580, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(480, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(510, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 400, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(320, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(480, 330, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(450, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(860, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(700, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(520, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(580, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(480, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(720, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(680, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(620, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(650, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(570, 220, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(720, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(680, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(620, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(650, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1020, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1020, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1020, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(720, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(680, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(620, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(650, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(570, 420, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(585, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(550, 420, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 360, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(720, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(680, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(620, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(650, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(570, 220, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(720, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(680, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(620, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(650, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1020, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1020, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1020, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(720, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(680, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(620, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(650, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(570, 420, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(585, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(550, 420, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 360, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(580, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 600, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(580, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 550, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(870, 325, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(760, 600, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(580, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(500, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(430, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 600, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(510, 100, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(660, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(770, 550, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(380, 575, true);
	if (bExitEarly == false) return;

	return;
}

// DunDunDun song in Beep Sounds
//
void DunDunDunSound() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(1568, 250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1568, 250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1568, 250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1245, 1250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1397, 250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1397, 250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1397, 250, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1175, 1250, true);
	if (bExitEarly == false) return;

	return;
}

// Star Wars Imperial March Theme in Beep Sounds
//
void StarWarsImperialMarch() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(440, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(349, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(349, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 1000, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(415, 500, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(349, 350, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 1000, true);
	if (bExitEarly == false) return;

	return;
}

// Pac-Man Theme Song in Beep Sounds
//
void TetrisTheme() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(370, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(370, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(329.6, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(329.6, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(370, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(370, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(329.6, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(329.6, 300, true);
	if (bExitEarly == false) return;
	sleep(500);
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.2, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659.2, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(587.3, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.2, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(370, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(370, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(440, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(493.9, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(392, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(329.6, 200, true);
	if (bExitEarly == false) return;
	sleep(150);
	bExitEarly = meSong.BeepSound(329.6, 800, true);
	if (bExitEarly == false) return;

	return;
}

// Dramatic Song in Beep Sounds
//
void DramaticSong() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1175, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(988, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1175, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(1109, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(988, 200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(740, 200, true);
	if (bExitEarly == false) return;

	return;
}

// RickRoll Song in Beep Sounds
//
void RickRollSong() {
	MultimediaEngine meSong;
	bool bExitEarly = true;

	bExitEarly = meSong.BeepSound(523.25, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659.25, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 900, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(880.00, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 1200, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.25, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(880.00, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(880.00, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 1000, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.25, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 450, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659.25, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.25, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 150, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 600, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(659.25, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(587.33, 125, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.25, 600, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(523.25, 300, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(783.99, 600, true);
	if (bExitEarly == false) return;
	bExitEarly = meSong.BeepSound(698.46, 1000, true);
	if (bExitEarly == false) return;

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


	std::cout << "       ||----W |\n"
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

	std::cout << "       _ _ /  ^ ^\n"
		<< "     /    \\  =>X<=\n"
		<< "   /|      |   /\n"
		<< "   \\|     /__| |\n"
		<< "     \\_____\\ \\__\\\n";
}

// HackerTyper - Traditional hacker-typer using a snippet of the linux kernel source code
// Parameters: nSpeed - The speed of the character output in characters.
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
// Parameters: sFilePath - The file path for the custom file to be used.
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
		VerbosityDisplay("ERROR: In HackerTyperFile() - Test file stream failed to open file path. Incorrect filepath, lack of permissions, bad memory, etc could be the culprit.\n");
		UserErrorDisplay("ERROR - File does not exist. Please ensure the filepath that has been used exists, the permissions are there and there is enough system memory, and try again later.\n");
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
// Parameters: None
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
// Parameters: dNumber - The number to check and use.
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
// Parameters: sString - The string to perform the eradication on.
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
// Parameters: dValue - The number to format.
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

// GetNumPrimeFactorsAsString - Get the prime factors of a specified integer argument and return them as a string in this format: "<n>, <n>, <n>"...
// Parameters: nNumToUse - The number to calculate the prime factors of.
// Return Values: std::string containing the prime factors of nNumToUse, as a string.
//
std::string GetNumPrimeFactorsAsString(uint64_t nNumToUse) {
	std::string sPrimeFactorStr = "";

	// Repeat until square root of nNumToUse
	for (uint64_t i = 2; i * i <= nNumToUse; ++i) {

		// Check if divisible by i
		while (nNumToUse % i == 0) {
			// Add prime factor to string with space
			sPrimeFactorStr += std::to_string(i) + ", ";
			// Divide by i to move on to next prime factor
			nNumToUse /= i;
		}
	}

	// nNumToUse has been divided all the way, do not forget about it
	if (nNumToUse > 1) {
		// Add prime factor to string with space
		sPrimeFactorStr += std::to_string(nNumToUse) + ", ";
	}

	// There should be an unnecessary extra ", " at the end of the string - remove it
	sPrimeFactorStr.erase(sPrimeFactorStr.length() - 2, 2);

	// Return string
	return sPrimeFactorStr;
}

// GetNumFactorsAsString - Get the factors of a specified integer argument and return it as a string in this format: "<n>, <n>, <n>"...
// Parameters: nNumToUse - The number to calculate the factors of.
// Return Values: std::string containing the factors of nNumToUse, as a string.
//
std::string GetNumFactorsAsString(uint64_t nNumToUse) {
	std::string sFactorsStr = "";

	// Iterate until number with increment of 1 (brute-force technique)
	for (uint64_t i = 1; i <= nNumToUse; i++) {
		if (nNumToUse % i == 0) {
			// Add number to string
			sFactorsStr += std::to_string(i) + ", ";
		}
	}

	// There should be an unnecessary extra ", " at the end of the string - remove it
	sFactorsStr.erase(sFactorsStr.length() - 2, 2);

	return sFactorsStr;
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