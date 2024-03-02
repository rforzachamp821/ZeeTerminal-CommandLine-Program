
//
// ZeeTerminal Main and Shared Engine Components
/***
 *      _____        _____                   _             _
 *     |__  /___  __|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |
 *       / // _ \/ _ \| |/ _ \ '__| '_ ` _ \| | '_ \ / _` | |
 *      / /|  __/  __/| |  __/ |  | | | | | | | | | | (_| | |
 *     /____\___|\___||_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_|
 * 
 */
// (c) Ryan Zorkot, 2023. Licensed under MIT.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include <limits>
#include <conio.h>
#include "Definitions.h" // Defined first to prevent min()/max() conflict with std::numeric_limits<T>::max/min()
#include <math.h>
#include <Windows.h>
#include <mmsystem.h>
#include <random>
#include <shobjidl.h>
#include <powrprof.h>
#include <codecvt>
#include <filesystem>
#include "Engine\TerminalDefaultAttributes.cpp"
#include "Engine\RGBColourPreset-System.cpp"
#include "Engine\ConfigFile-System.cpp"
#include "Engine\SystemInfo.cpp"
#include "Engine\LogFile-System.cpp"
#include "Engine\FileParse-System.cpp"
#include "Engine\ScreenNavigateEngine.cpp"
#include "Engine\OptionSelectEngine.cpp"
#include "Engine\TableEngine.cpp"
#include "Engine\MultimediaEngine.cpp"
#include "Engine\FileOpenGUIEngine.cpp"
#include "Engine\MemoryTestEngine.cpp"
#include "Engine\NotesSystem.cpp"
#include "CommandFiles\CommandsFile.cpp"


#pragma comment(lib, "winmm.lib") // To access MMSYSTEM libs
#pragma comment(lib, "powrprof.lib") // To access power profile libs

// Runtime variables
bool					bAnsiVTSequences = true;
bool					bConfigAndLogSystemsInitialised = false; // Switch to symbolise that the config and log systems have been initialised
bool					bDisp = true; // Switch for showing the start command screen ("Command: > "), similar to CMD's @echo off. 
std::string				sCommandInputRAW = "";
std::string				sStringOptionCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
                                                                 // on multi-argument commands.
std::string				sStringDataCommandArgs[nArgArraySize]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
                                                               // on multi-argument commands.
uint64_t				nNumOfInputtedCommands = 0; // Counter for number of inputted commands since the start of the ZeeTerminal session.
uint64_t				nNumOfSuccessfulInputtedCommands = 0; // Counter for number of successful inputted commands since the start of the ZeeTerminal session.

std::string				sLastColourFore = ""; // Last set colour of any kind - foreground
std::string				sLastColourBack = ""; // Last set colour of any kind - background

TerminalDefaultAttributes	DefaultAttributesObj;
RGBColourPresetSystem	RGBPreset[3]; // Possibly [5] in a future update?
ConfigFileSystem		ConfigObjMain; // Configuration Object
LogFileSystem			LogFileMain; // LogFile System Object
NotesSystem				NotesMain; // Notes Object


// Sets cursor attributes automatically when called
inline void SetCursorAttributes() {

	// Can't do without ANSI VT sequences
	if (bAnsiVTSequences) {
		// Set cursor shape
		std::cout << "\x1b[" << ConfigObjMain.nCursorShape << " q";

		// Set cursor blink
		if (ConfigObjMain.bCursorBlink == true) {
			std::cout << "\x1b[?12h";
		}
		else std::cout << "\x1b[?12l";

		// Set cursor visibility
		if (ConfigObjMain.bShowCursor == true) {
			std::cout << "\x1b[?25h";
		}
		else std::cout << "\x1b[?25l";

	}

	// Non-ANSI terminals
	else {
		// Set cursor visibility using the WIN32 Console API
		CONSOLE_CURSOR_INFO cciAttribSet;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cciAttribSet);

		// Set variables
		if (ConfigObjMain.bShowCursor == true) {
			cciAttribSet.bVisible = true;
		}
		else cciAttribSet.bVisible = false;

		// Set final cursor info
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cciAttribSet);
	}

	return;
}

// Sets the colour and background colour
inline void colour(std::string sColourForegroundChoice, std::string sColourBackgroundChoice) {

	// Set colours to their respective last colours
	sLastColourFore = sColourForegroundChoice;
	sLastColourBack = sColourBackgroundChoice;

	if (bAnsiVTSequences) {

		// Maintain a readable contrast if the setting is set to true
		if (ConfigObjMain.bAutoReadableContrast == true) {
			// To keep contrast good
			if (sColourForegroundChoice == sColourBackgroundChoice) {
				if (sColourBackgroundChoice == BLK
					|| sColourBackgroundChoice == RED
					|| sColourBackgroundChoice == GRN
					|| sColourBackgroundChoice == YLW
					|| sColourBackgroundChoice == BLU
					|| sColourBackgroundChoice == MAG
					|| sColourBackgroundChoice == CYN)
				{
					sColourForegroundChoice = LWHT;
				}
				else if (sColourBackgroundChoice == GRAY
					|| sColourBackgroundChoice == LRED
					|| sColourBackgroundChoice == LGRN
					|| sColourBackgroundChoice == LYLW
					|| sColourBackgroundChoice == LBLU
					|| sColourBackgroundChoice == LMAG
					|| sColourBackgroundChoice == LCYN
					|| sColourBackgroundChoice == LWHT
					|| sColourBackgroundChoice == WHT)
				{
					sColourForegroundChoice = BLK;
				}
			}

			// Colour relationship
			if (sColourBackgroundChoice == LWHT && sColourForegroundChoice == LYLW) {
				sColourForegroundChoice = BLK;
			}
			else if (sColourBackgroundChoice == LYLW && sColourForegroundChoice == LWHT) {
				sColourForegroundChoice = BLK;
			}
			else if (sColourBackgroundChoice == LWHT && sColourForegroundChoice == LGRN) {
				sColourForegroundChoice = BLK;
			}
			else if (sColourBackgroundChoice == LGRN && sColourForegroundChoice == LWHT) {
				sColourForegroundChoice = BLK;
			}
		}

		// Foreground
		std::cout << "\x1b[38;2;" << sColourForegroundChoice << "m";

		// Support for transparency in Windows Terminal; black is usually default background colour so will be default here
		if (sColourBackgroundChoice == BLK && ConfigObjMain.bTermCustomThemeSupport) {
			std::cout << "\x1b[49m";
			return;
		}

		// Background
		std::cout << "\x1b[48;2;" << sColourBackgroundChoice << "m";
	}

	// Windows Console API - activated when no ANSI support is detected and is a fallback (16-colours)
	else {

		int nBackgroundColourFinal = 0;
		int nForegroundColourFinal = 0;

		// Now, modify the background input choice 
		// Check for number
		if (isNumberi(sColourForegroundChoice, false) && isNumberi(sColourBackgroundChoice, false)) {
			nBackgroundColourFinal = std::stoi(sColourBackgroundChoice);
			nForegroundColourFinal = std::stoi(sColourForegroundChoice);
		}
		else {
			// Check failed, do not change colour; stream error message to std::cerr without using colours (to prevent forkbomb)
			std::cerr << wordWrap("ERROR: In colour() - Invalid WIN32 colour argument(s) detected. The arguments must be numbers as strings only."
				"\nArguments: sColourForegroundChoice: <" + sColourForegroundChoice + ">, sColourBackgroundChoice: <" + sColourBackgroundChoice + ">.\n");
			return;
		}

		// Maintain a readable contrast if the setting is set to true
		if (ConfigObjMain.bAutoReadableContrast == true) 
		{
			if (nBackgroundColourFinal == nForegroundColourFinal) {
				if (nBackgroundColourFinal < 7) {
					nForegroundColourFinal = 15; // Bright White
				}
				else if (nBackgroundColourFinal > 7 || nBackgroundColourFinal == 7) {
					nForegroundColourFinal = 0; // Black
				}
			}

			// Colour relationship
			if (nBackgroundColourFinal == 15 && nForegroundColourFinal == 14) {
				nForegroundColourFinal = 0; // Black due to similarity with yellow and white
			}
			else if (nBackgroundColourFinal == 14 && nForegroundColourFinal == 15) {
				nForegroundColourFinal = 0; // Black due to similarity with yellow and white
			}
			else if (nBackgroundColourFinal == 15 && nForegroundColourFinal == 10) {
				nForegroundColourFinal = 0; // Black due to similarity with green and white
			}
			else if (nBackgroundColourFinal == 10 && nForegroundColourFinal == 15) {
				nForegroundColourFinal = 0; // Black due to similarity with green and white
			}
		}

		nBackgroundColourFinal *= 16; // WINAPI works on a 16 colour system

		// Finally, add the colours and set the colour
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (nBackgroundColourFinal + nForegroundColourFinal));
	}

	return;
}

// colourHighlight - Sets the colour from value inside nColourHighlight(Back).
inline void colourHighlight()
{
	// Use the default colour function; custom solution not needed
	colour(ConfigObjMain.sColourHighlight, ConfigObjMain.sColourHighlightBack);
	return;
}

// Be sure to change back to no underline AND no bold when done
inline void colourTitle()
{
	// Use the default colour function; custom solution not needed
	colour(ConfigObjMain.sColourTitle, ConfigObjMain.sColourTitleBack);
	if (bAnsiVTSequences) std::cout << "\x1b[" << ULINE << "m";

	return;
}

// Be sure to change back to no underline when done
inline void colourSubheading()
{
	// Use the default colour function; custom solution not needed
	colour(ConfigObjMain.sColourSubheading, ConfigObjMain.sColourSubheadingBack);
	if (bAnsiVTSequences) std::cout << "\x1b[" << ULINE << "m";

	return;
}

// Function to put console to sleep so makes programming job easier
// Measures in milliseconds
inline void sleep(long long int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// Function to choose random number
long double RandNum(long double max, long double min) 
{
	std::random_device rdRandNum;
	std::mt19937_64 mtRandNumGen(rdRandNum());

	// distribution in range [min, max]
	std::uniform_real_distribution<> dist(min, max);

	return dist(mtRandNumGen);
}

// LogWindowsEvent - Logs an event of choice on the Windows Event Log Database.
// Arguments: vsEventDataArray - Vector array of event data strings to forward to the event report.
//            dwBinaryDataSize - The size of the lpBinaryData argument. Set this to 0 if no binary data will be included.
//            lpBinaryData - Binary data to forward to the event report.
// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
// 
bool LogWindowsEvent(std::vector<std::string> vsEventDataArray, DWORD dwBinaryDataSize, LPVOID lpBinaryData)
{
	// Create handle around ZeeTerminal source
	HANDLE hEventSource = RegisterEventSourceA(NULL, "ZeeTerminal");
	size_t nEventDataArraySize = vsEventDataArray.size();

	// Convert std::string array to LPCSTR
	LPCSTR* lpEventData = new LPCSTR[nEventDataArraySize];
	// Use for loop
	for (size_t i = 0; i < nEventDataArraySize; i++) {
		lpEventData[i] = vsEventDataArray[i].c_str();
	}

	// Report the event to event log
	if (!ReportEventA(hEventSource, EVENTLOG_ERROR_TYPE, 0, 0, NULL, nEventDataArraySize, dwBinaryDataSize, lpEventData, lpBinaryData)) {
		VerbosityDisplay("In LogWindowsEvent(): ERROR - Failed to report event on ReportEventA function. Error code " + std::to_string(GetLastError()) + ": " + std::system_category().message(GetLastError()) + ".\n");
		return false;
	}

	// Uninitialise and exit
	DeregisterEventSource(hEventSource);
	delete[] lpEventData;

	return true;
}

// OutputBoxWithText - Outputs a box outline, with text inside.
//                   - The box is drawn to the maximum text width, and if that is too big, it's drawn to the terminal width.
// Arguments: sText - The text to be boxed.
//            sColourOutlineFore - The foreground colour for the outline. 
//            sColourOutlineBack - The background colour for the outline.
//            sColourTextFore - The foreground colour for the text.
//            sColourTextBack - The background colour for the text.
// Return Values: None
//
void OutputBoxWithText(std::string sText, std::string sColourOutlineFore, std::string sColourOutlineBack, std::string sColourTextFore, std::string sColourTextBack) 
{
	CONSOLE_SCREEN_BUFFER_INFO csbiDirections;
	int nBoxWidth = 0;
	std::vector<std::string> sLines = {};
	std::string sBuffer = "";

	// Use a for loop to check for box width, height, line length and contents, etc
	for (int i = 0, nCounter = 0; i < sText.length(); i++, nCounter++) {
		if (sText[i] == '\n') {

			// Early check for line size
			if (nBoxWidth < nCounter) {
				// Get current terminal width
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiDirections);

				// Check for oversized line length
				if (csbiDirections.srWindow.Right - csbiDirections.srWindow.Left - 3 > nCounter) {
					nBoxWidth = nCounter;
				}
				else {
					nBoxWidth = csbiDirections.srWindow.Right - csbiDirections.srWindow.Left - 3;

					// Create new lines
					// Get change between box width and counter to determine number of lines
					int nNumOfLines = ((nCounter - nBoxWidth) / nBoxWidth) + 1;

					// Append new lines to vector
					for (int j = 0; j <= nNumOfLines; j++) {

						// Get line
						sLines.push_back(sBuffer.substr(0, nBoxWidth));

						// Erase line from string
						sBuffer.erase(0, nBoxWidth);
					}

					// Reset counter
					nCounter = 0;

					// Reset buffer
					sBuffer = "";

					continue;
				}

			}

			// Reset counter
			nCounter = 0;

			// Push accumulated buffer contents into vector
			sLines.push_back(sBuffer);

			// Reset buffer
			sBuffer = "";

			continue;
		}

		if (nBoxWidth < nCounter) {
			// Get current terminal width
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiDirections);

			// Check for oversized line length
			if (csbiDirections.srWindow.Right - csbiDirections.srWindow.Left - 3 > nCounter) {
				nBoxWidth = nCounter;
			}
			else {
				nBoxWidth = csbiDirections.srWindow.Right - csbiDirections.srWindow.Left - 3;
			}
		}

		sBuffer += sText[i];
	}

	// Check for line size - determines final box width
	int nBufferLength = sBuffer.length();
	if (nBoxWidth < nBufferLength) {
		// Get current terminal width
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiDirections);

		// Check for oversized line length
		if (csbiDirections.srWindow.Right - csbiDirections.srWindow.Left - 3 > nBufferLength) {
			nBoxWidth = nBufferLength;
			if (sBuffer != "") sLines.push_back(sBuffer);
		}
		else {
			nBoxWidth = csbiDirections.srWindow.Right - csbiDirections.srWindow.Left - 3;

			// Create new lines
			// Get change between box width and counter to determine number of lines
			int nNumOfLines = ((nBufferLength - nBoxWidth) / nBoxWidth) + 1;

			// Append new lines to vector
			for (int j = 0; j <= nNumOfLines; j++) {

				// Get line
				sLines.push_back(sBuffer.substr(0, nBoxWidth));

				// Erase line from string
				sBuffer.erase(0, nBoxWidth);
			}

			// Reset buffer
			sBuffer = "";
		}
	}
	else sLines.push_back(sBuffer);


	// to support 1 asterisk and 1 whitespace on each side of the text
	nBoxWidth += 4;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiDirections);
	if (csbiDirections.srWindow.Right - csbiDirections.srWindow.Left + 1 < nBoxWidth) {
		nBoxWidth = csbiDirections.srWindow.Right - csbiDirections.srWindow.Left + 1;
	}


	// Firstly, output box top
	colour(sColourOutlineFore, sColourOutlineBack);
	std::cout << std::string(nBoxWidth, '=');

	// Secondly, output text with appropriate padding using for loop to reiterate through line vector
	std::cout << '\n';
	for (int i = 0; i < sLines.size(); i++) {
		sBuffer = sLines[i];
		for (int j = 0; j < nBoxWidth - sLines[i].length() - 4; j++) { // -4 as the box width was first incremented by 4 before this
			sBuffer += ' '; // Add space
		}

		// Output padding
		colour(sColourOutlineFore, sColourOutlineBack);
		std::cout << "* ";
		colour(sColourTextFore, sColourTextBack);

		// Output line and spaces
		std::cout << sBuffer;

		// Output padding
		colour(sColourOutlineFore, sColourOutlineBack);
		std::cout << " *\n";
	}

	// Finally, output box bottom
	colour(sColourOutlineFore, sColourOutlineBack);
	std::cout << std::string(nBoxWidth, '=');

	std::cout << '\n';
	colour(sColourTextFore, sColourTextBack);

	return;
}

// Converter from wide string to string
std::string ws2s(const std::wstring& wstr) {
	// Use UTF-8 for this
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

// Converter from string to wide string
std::wstring s2ws(const std::string& str) {
	// Use UTF-8 for this
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;

	return converterX.from_bytes(str);
}

// Converter from boolean to string ("true" or "false")
std::string BoolToString(const bool bValue) 
{
	// Convert to respective strings
	switch (bValue) {
	case true:
		return "True";
		break;
	case false:
		return "False";
		break;
	default:
		return "Failed";
		break;
	}

	// If switch wasn't exited, return failed (there's no way this could've happened in a normal scenario)
	return "failed";
}

// Checks whether std::string argument is a number or not - long double
bool isNumberld(const std::string sNumberTest) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// Check for negative at the beginning if i is 0

		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (sNumberTest[i] == '-' && i == 0) {
			// Allowed, since i is at the beginning of the string
			continue;
		}
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stold() range
	try {
		long double nRangeTest = std::stold(sNumberTest);
	}
	catch (const std::out_of_range&) {
		VerbosityDisplay("In isNumberld(): Exception caught - Number is too high/low (out of range).");
		return false;
	}
	catch (const std::invalid_argument&) {
		VerbosityDisplay("In isNumberld(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
		return false;
	}

	return true;
}

// Checks whether std::string argument is a number or not - 64-bit integer
bool isNumberll(const std::string sNumberTest) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (sNumberTest[i] == '-' && i == 0) {
			// Allowed, since i is at the beginning of the string
			continue;
		}
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stoll() range
	try {
		long long int nRangeTest = std::stoll(sNumberTest);
	}
	catch (const std::out_of_range&) {
		VerbosityDisplay("In isNumberll(): Exception caught - Number is too high/low (out of range).");
		return false;
	}
	catch (const std::invalid_argument&) {
		VerbosityDisplay("In isNumberll(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
		return false;
	}

	return true;
}

// Checks whether std::string argument is a number or not - 32-bit integer
bool isNumberl(const std::string sNumberTest) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (sNumberTest[i] == '-' && i == 0) {
			// Allowed, since i is at the beginning of the string
			continue;
		}
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stoll() range
	try {
		long int nRangeTest = std::stol(sNumberTest);
	}
	catch (const std::out_of_range&) {
		VerbosityDisplay("In isNumberl(): Exception caught - Number is too high/low (out of range).");
		return false;
	}
	catch (const std::invalid_argument&) {
		VerbosityDisplay("In isNumberl(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
		return false;
	}

	return true;
}

// Checks whether std::string argument is a number or not - integer
// bSetErrorsAsVerbose - Any errors that occur are set as verbose when this is TRUE, else the messages are streamed to std::cerr.
bool isNumberi(const std::string sNumberTest, bool bSetErrorsAsVerbose) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (sNumberTest[i] == '-' && i == 0) {
			// Allowed, since i is at the beginning of the string
			continue;
		}
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stoi() range
	try {
		int nRangeTest = std::stoi(sNumberTest);
	}
	catch (const std::out_of_range&) {
		if (bSetErrorsAsVerbose) VerbosityDisplay("In isNumberi(): Exception caught - Number is too high/low (out of range).");
		else std::cerr << wordWrap("In isNumberi(): Exception caught - Number is too high/low (out of range).\n");
		return false;
	}
	catch (const std::invalid_argument&) {
		if (bSetErrorsAsVerbose) VerbosityDisplay("In isNumberi(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
		else std::cerr << wordWrap("In isNumberi(): Exception caught - Argument cannot be converted whatsoever (invalid argument).\n");
		return false;
	}

	return true;
}

// Checks whether std::string argument is a number or not - unsigned 64-bit integer
bool isNumberull(const std::string sNumberTest) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stoll() range
	try {
		uint64_t nRangeTest = std::stoull(sNumberTest);
	}
	catch (const std::out_of_range&) {
		VerbosityDisplay("In isNumberull(): Exception caught - Number is too high/low (out of range).");
		return false;
	}
	catch (const std::invalid_argument&) {
		VerbosityDisplay("In isNumberull(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
		return false;
	}

	return true;
}

// Checks whether std::string argument is a number or not - unsigned 32-bit integer
bool isNumberul(const std::string sNumberTest) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stoll() range
	try {
		unsigned long int nRangeTest = std::stoul(sNumberTest);
	}
	catch (const std::out_of_range&) {
		VerbosityDisplay("In isNumberul(): Exception caught - Number is too high/low (out of range).");
		return false;
	}
	catch (const std::invalid_argument&) {
		VerbosityDisplay("In isNumberul(): Exception caught - Argument cannot be converted whatsoever (invalid argument).");
		return false;
	}

	return true;
}

// Function to clear keyboard buffer
void ClearKeyboardBuffer() {
	while (_kbhit()) {
		_getch_nolock(); // faster than _getch() - not thread-safe but this function is meant to be single-threaded
	}
	return;
}

// Function to set console cursor position
inline void SetCursorPosition(int x, int y) {
	COORD CursorPos{};
	CursorPos.X = x;
	CursorPos.Y = y;
	if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos)) {
		// Don't display on windows terminal VT bug
		bool bHideMessage = false;
		if (CheckIfCursorExceedScreenBufferHeight()) {
			bHideMessage = true;
		}

		VerbosityDisplay("In SetCursorPosition(): ERROR - Failed to set console cursor position with error code " + std::to_string(GetLastError()) + ".\n", 10000, bHideMessage);
	}

	return;
}

// wordWrap - Adds line/word wrapping to a string, based on the console window width.
//
// This takes in an std::string as an argument, and returns another std::string with the word wrapping in the string.
std::string wordWrap(std::string text, long long int nCustomStartCounter, long long int nCustomWidth) {
	std::string result = "";
	long long int counter = nCustomStartCounter;

	// Cannot do word wrapping if disabled
	if (ConfigObjMain.bWordWrapToggle == false) return text;

	// Get console window size
	CONSOLE_SCREEN_BUFFER_INFO csbiWordWrap;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiWordWrap);
	long long int width = csbiWordWrap.srWindow.Right - csbiWordWrap.srWindow.Left + 1;
	if (nCustomWidth > 0) width = nCustomWidth;


	if (counter < 0) {
		// Set counter to the cursor X position, due to the fact that it shouldn't be 
		// assumed that word wrapping will start from the very beginning of a line
		counter = csbiWordWrap.dwCursorPosition.X;
	}

	size_t lastSpace = -1;
	for (size_t i = 0; i < text.length(); i++) {

		// Counter mods
		if (text[i] == '\n') {
			counter = -1;
			lastSpace = -1;
		}
		else if (text[i] == '\t') {

			// tabstop is usually 8 spaces; might be dynamic in future
			size_t nNumOfSpacesForTab = 8 - (counter % 8);
			if (nNumOfSpacesForTab == 0) nNumOfSpacesForTab = 8;
			counter += nNumOfSpacesForTab;
		}

		// Counter check
		if (counter >= width) {
			if (lastSpace != -1) {
				result[lastSpace] = '\n';
				counter = i - lastSpace - 1;
			}
			else {
				result += '\n';
				counter = 0;
			}
		}
		if (text[i] == ' ') {
			lastSpace = result.length();
		}

		result += text[i];

		counter++;
	}
	return result;
}

// Function to display extra help information for specific commands for user's sake
void DirectionsDisplay(std::string sPrompt) 
{
	if (ConfigObjMain.bDisplayDirections == true) 
	{
		// Output directions
		OutputBoxWithText(sPrompt, LRED, ConfigObjMain.sColourGlobalBack, GRN, ConfigObjMain.sColourGlobalBack);
	}

	return;
}

// Function to display verbose messages at specific times
inline void VerbosityDisplay(std::string sPrompt, int nObjectID, bool bForceDontDisplayMessage, bool bForceDontLog) {
	if (ConfigObjMain.bDisplayVerboseMessages == true && bForceDontDisplayMessage == false) {
		colour(GRAY, BLK);
		std::cerr << "Verbose Message: " << sPrompt << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	// Only log when systems initialised, logging enabled, force-disable logging disabled and verbose logging enabled
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bVerboseMessageLogging && !bForceDontLog) {
		LogFileMain.AddLogLine(sPrompt, 1, nObjectID);
	}

	return;
}

// Function to display error messages at specific times
inline void UserErrorDisplay(std::string sError, int nObjectID) {

	// Output user-space error in red text with word wrapping
	colour(RED, ConfigObjMain.sColourGlobalBack);
	std::cerr << wordWrap(sError);
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserSpaceErrorLogging) {
		LogFileMain.AddLogLine(sError, 2, nObjectID);
	}

	return;
}

// Function to handle +/- number input - long double
long double NumInputld(std::string sPrompt) {
	long double num;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputld(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> num;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputld(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// Function to handle +/- number input - long long int
long long int NumInputll(std::string sPrompt) {
	long long int num;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputll(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> num;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputll(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// Function to handle +/- number input - long int
long int NumInputl(std::string sPrompt) {
	long int num;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputl(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> num;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputl(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// Function to handle +/- number input - int
int NumInputi(std::string sPrompt) {
	int num;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputi(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> num;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In NumInputi(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// Function to handle only positive number input - uint64_t
uint64_t PositiveNumInputull(std::string sPrompt) {
	uint64_t num = 0;
	std::string sInput = "";
	bool bSuccess = true;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In PositiveNumInputull(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		// Reset variables on next iteration
		bSuccess = true;

		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> sInput;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		
		// Convert string input for integer into unsigned 64-bit integer, while checking for correct input AND negative number
		// Check if number
		if (isNumberull(sInput) == false) {
			bSuccess = false;
		}

		// Convert to number
		if (bSuccess == true) {
			num = std::stoull(sInput);
		}

		if (std::cin.fail() || num < 0 || bSuccess == false) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In PositiveNumInputull(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// Function to handle only positive number input - unsigned long int
unsigned long int PositiveNumInputul(std::string sPrompt) {
	unsigned long int num = 0;
	std::string sInput = "";
	bool bSuccess = true;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In PositiveNumInputul(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		// Reset variables on next iteration
		bSuccess = true;

		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> sInput;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Convert string input for integer into unsigned 64-bit integer, while checking for correct input AND negative number
		// Check if number
		if (isNumberul(sInput) == false) {
			bSuccess = false;
		}

		// Convert to number
		if (bSuccess == true) {
			num = std::stoul(sInput);
		}

		if (std::cin.fail() || num < 0 || bSuccess == false) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect, or the number inputted was too high/low. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In PositiveNumInputul(): Input session end with return value: " + std::to_string(num) + ".", 4);
	}

	return num;
}

// Function to assist with string output by preventing reuse of code
std::string StrInput(std::string sPrompt) {
	std::string string;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In StrInput(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	// Prompt
	std::cout << wordWrap(sPrompt);
	colour(LYLW, ConfigObjMain.sColourGlobalBack);
	getline(std::cin, string);
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In StrInput(): Input session end with return value: {" + string + "}.", 4);
	}

	return string;
}

// YesNoInput - allows for y/n input
bool YesNoInput(std::string sPrompt) {
	char cInput;

	// Add log line
	if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
		LogFileMain.AddLogLine("In YesNoInput(): Input session begin with prompt: {" + sPrompt + "}.", 4);
	}

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> cInput;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect. Please try again.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}
	if (cInput == 'y' || cInput == 'Y') {
		// Add log line
		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
			LogFileMain.AddLogLine("In YesNoInput(): Input session end with return value: TRUE.", 4);
		}
		return true;
	}
	else {
		// Add log line
		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bUserInputInfoLogging) {
			LogFileMain.AddLogLine("In YesNoInput(): Input session end with return value: FALSE.", 4);
		}
		return false;
	}

	// Unknown error, just post TRUE
	return true;
}

// SetWindowTitle - Function to set title for the console window.
// Arguments: sTitle for the title string.
bool SetWindowTitle(std::string sTitle) {
	if (bAnsiVTSequences) {
		if (sTitle.length() > 256) {
			VerbosityDisplay("ERROR: In SetWindowTitle() - String argument incorrect due to ANSI 256 max string char limit for title.\n");
		}

		// Use ANSI VT sequences if they work on current terminal
		std::cout << "\x1b]0;" << sTitle << "\x1b\x5c";
	}
	else {
		// Use Windows SetConsoleTitleA if ANSI VT sequences don't work on current terminal window
		if (SetConsoleTitleA(sTitle.c_str())) {
			return true;
		}
		else {
			VerbosityDisplay("ERROR: In SetWindowTitle() - String argument incorrect due to Win32 API 256 max string char limit for title.\n");
			return false;
		}
	}

	return true;
}

// Clear screen function (Flushes whole screen buffer)
void cls() {

	// Using ANSI escape codes to clear the screen is a lot faster and cross-platform
	if (bAnsiVTSequences == true) {
		std::cout << "\033c"; // fully clear the scrollback buffer
		// As everything was reset, set everything back to normal
		// Cursor attributes
		SetCursorAttributes();

		colour(sLastColourFore, sLastColourBack); // Set colours to last set colour
		std::cout << "\033[2J\033[1;1H";
		return;
	}
	else {
		// If ANSI escape codes cannot be used, just do the classical method
		HANDLE h;
		CHAR_INFO v3;
		COORD v4;
		SMALL_RECT v5;
		CONSOLE_SCREEN_BUFFER_INFO v6;

		if ((h = (HANDLE)GetStdHandle(0xFFFFFFF5), (unsigned int)GetConsoleScreenBufferInfo(h, &v6)))
		{
			v5.Right = v6.dwSize.X;
			v5.Bottom = v6.dwSize.Y;
			v3.Char.UnicodeChar = 32;
			v4.Y = -v6.dwSize.Y;
			v3.Attributes = v6.wAttributes;
			v4.X = 0;
			*(DWORD*)&v5.Left = 0;
			ScrollConsoleScreenBufferW(h, &v5, 0, v4, &v3);
			v6.dwCursorPosition = { 0 };
			SetCursorPosition(v6.dwCursorPosition.X, v6.dwCursorPosition.Y);
		}
		return;
	}
	return;

}

// Function that outputs text with random colours 
void RandomColourOutput(std::string sText) {

	// Add word wrapping
	sText = wordWrap(sText);

	// j is for string check, i is for colour indicator
	// for loop
	for (int i = 1, j = 0; j < sText.size(); j++, i++) 
	{
		// Colour indicator going past 16 will give an error
		if (i > 16) i = 1;

		if (NumberToColour(i) == ConfigObjMain.sColourGlobalBack && !ConfigObjMain.bAutoReadableContrast) {
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else colour(NumberToColour(i), ConfigObjMain.sColourGlobalBack);

		// Output with colour
		std::cout << sText[j];
	}

	return;
}

// CentreColouredText - Takes in a title string and outputs it centred to the console with padding in relation to the console window size.
// Arguments: sText is for the string input, nTypeOfText is for the type of text (title (1), subheading (2), etc).
void CentreColouredText(std::string sText, short int nTypeOfText) {
	// Work out width
	int nWidth = 0;
	// Get console window size
	CONSOLE_SCREEN_BUFFER_INFO csbiCentreCT;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiCentreCT);
	// Assign window width to nWidth
	nWidth = csbiCentreCT.srWindow.Right - csbiCentreCT.srWindow.Left + 1;

	// Check to prevent memory overspill
	if (sText.length() >= (nWidth + 1)) {
		
		// Output with correct colour
		if (nTypeOfText == 1) colourTitle();
		else if (nTypeOfText == 2) colourSubheading();

		// Word wrapping because text is longer than display width, so word wrapping is necessary
		std::cout << wordWrap(sText); 
		
		// Reset underline and bold
		std::cout << NOULINE_STR << NOBOLD_STR;

		// Default colour
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return;
	}

	// Output string of spaces first with default colour
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap(std::string((nWidth - sText.length()) / 2, ' ')); 

	// Then output the string itself, with correct colour
	if (nTypeOfText == 1) colourTitle();
	else if (nTypeOfText == 2) colourSubheading();
	std::cout << sText;

	// Reset underline and bold
	std::cout << NOULINE_STR << NOBOLD_STR;

	// Default colour
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// CentreText - Takes in a string and outputs it with padding in relation to the console window size.
std::string CentreText(std::string sText) {
	// Work out width
	int nWidth = 0;
	// Get console window size
	CONSOLE_SCREEN_BUFFER_INFO csbiCentreText;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiCentreText);
	// Assign window width to nWidth
	nWidth = csbiCentreText.srWindow.Right - csbiCentreText.srWindow.Left + 1;

	// Check to prevent memory overspill
	if (sText.length() >= (nWidth + 1)) return sText;

	return wordWrap(std::string((nWidth - sText.length()) / 2, ' ') + sText);
}

// slowcharCentredFn - Takes in a string and outputs it centred to the console with padding in relation to the console window size.
// Arguments: sText is for string input, bNewLine is for adding a newline after the output.
void slowcharCentredFn(bool bNewLine, std::string sText) {
	// Work out width
	int nWidth = 0;
	// Get console window size
	CONSOLE_SCREEN_BUFFER_INFO csbiCentreCT;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiCentreCT);
	// Assign window width to nWidth
	nWidth = csbiCentreCT.srWindow.Right - csbiCentreCT.srWindow.Left + 1;

	// Check to prevent memory overspill
	if (sText.length() >= (nWidth + 1)) {
		sText = wordWrap(sText);

		for (int i = 0; i <= sText.length(); i++) {
			// Pause for a couple of milliseconds to make output slow
			if (i > 0) {
				// Space backtrack for word wrapping detection
				if (not (sText[i - 1] == ' ' && sText[i] == ' ')) {
					sleep(ConfigObjMain.nSlowCharSpeed);
				}
			}
			else {
				sleep(ConfigObjMain.nSlowCharSpeed);
			}

			std::cout << sText[i];
		}
		// In case a key was pressed while operation was commencing
		ClearKeyboardBuffer();
		return;
	}

	// Firstly, output string of spaces
	std::cout << std::string((nWidth - sText.length()) / 2, ' ');
	// Then output the string itself like slowcharfn()
	for (int i = 0; i <= sText.length(); i++) {
		sleep(ConfigObjMain.nSlowCharSpeed);
		std::cout << sText[i];
	}
	// Output newline if call says so
	if (bNewLine) std::cout << std::endl;
	// In case a key was pressed while operation was commencing
	ClearKeyboardBuffer();
	return;
}

// Function for outputting characters slowly with the same colour
void slowcolourfn(std::string nColourFore, std::string nColourBack, std::string sSlowchar) {
	size_t size = 0;
	// Add word wrapping
	sSlowchar = wordWrap(sSlowchar);
	// Get size of sSlowChar
	size = sSlowchar.size();
	colour(nColourFore, nColourBack);
	for (int i = 0; i <= size; i++) {

		// Pause for a couple of milliseconds to make output slow
		if (i > 0) {
			// Space backtrack for word wrapping detection
			if (not (sSlowchar[i - 1] == ' ' && sSlowchar[i] == ' ')) {
				sleep(ConfigObjMain.nSlowCharSpeed);
			}
		}
		else {
			sleep(ConfigObjMain.nSlowCharSpeed);
		}

		std::cout << sSlowchar[i];
	}
	// In case a key was pressed while operation was commencing
	ClearKeyboardBuffer();
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// Function for outputting characters slowly
void slowcharfn(bool nline, std::string sSlowchar) {
	size_t size = 0;

	// Add word wrapping
	sSlowchar = wordWrap(sSlowchar);
	size = sSlowchar.size();
	for (int i = 0; i <= size; i++) {

		if (i > 0) {
			// Space backtrack for word wrapping detection
			if (not (sSlowchar[i - 1] == ' ' && sSlowchar[i] == ' ')) {
				sleep(ConfigObjMain.nSlowCharSpeed);
			}
		}
		else {
			sleep(ConfigObjMain.nSlowCharSpeed);
		}

		std::cout << sSlowchar[i];
	}

	if (nline == true) {
		std::cout << std::endl;
	}

	// In case a key was pressed while operation was commencing
	ClearKeyboardBuffer();

	return;
}

// Function for outputting characters with random colours
void SlowCharColourful(std::string sText, bool bIncludeBackground) {

	// Add word wrapping
	sText = wordWrap(sText);

	// Repeat output with random colour each time
	for (int i = 0; i < sText.size(); i++) 
	{
		// Get random colour number
		int nRandomNumber = RandNum(16, 1);

		if (bIncludeBackground == true) {
			// Create another background random number
			int nRandomNumberBack = RandNum(16, 1);

			// Set background and foreground colours to random
			colour(NumberToColour(nRandomNumber), NumberToColour(nRandomNumberBack));
		}
		else {
			// Set foreground colour to the random number
			colour(NumberToColour(nRandomNumber), ConfigObjMain.sColourGlobalBack);
		}

		// Output a character
		std::cout << sText[i];

		// Pause for a couple of milliseconds to make output slow
		if (i > 0) {
			// Space backtrack for word wrapping detection
			if (not (sText[i - 1] == ' ' && sText[i] == ' ')) {
				sleep(ConfigObjMain.nSlowCharSpeed);
			}
		}
		else {
			sleep(ConfigObjMain.nSlowCharSpeed);
		}
	}

	// Finish off with newline
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << '\n';
	ClearKeyboardBuffer();
	return;
}

// A function to display an exiting message without typing too much.
inline void Exiting() {
	colour(YLW, ConfigObjMain.sColourGlobalBack);
	std::cout << "\nExiting...\n";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	return;
}

// A function designated for resetting the global colours.
inline void ResetColour() 
{
	// Reset all RGB to default
	ConfigObjMain.sColourGlobal = LWHT;
	ConfigObjMain.sColourGlobalBack = BLK;

	// Optional reset-everything command for ANSI VT Sequence-supporting terminals
	if (bAnsiVTSequences) {
		std::cout << "\x1b[" << RESETALL << "m";
	}

	// Output reset message with default colours
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << "\nColours have been reset to default.\n";

	return;
}

// A function that checks for VT Terminal Sequence support, enables them if support is there
// and disables them if support isn't there. Returns true/false respectively, too.
bool EnableVTMode()
{
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	dwMode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

// A function to enable shutdown privileges for commands that require them.
// Returns false if they couldn't be enabled, but returns true otherwise.
bool EnableShutdownPrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	bool bSuccess = true;

	// Get a token for the current process
	bSuccess = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	if (bSuccess == false) return bSuccess; // Failed

	// Lookup the LUID for the shutdown privilege
	bSuccess = LookupPrivilegeValueW(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	if (bSuccess == false) return bSuccess; // Failed

	tkp.PrivilegeCount = 1; // Set the number of privileges to change
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Enable the shutdown privilege

	// Adjust the token privileges
	bSuccess = AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (bSuccess == false) return bSuccess; // Failed

	// Close the token handle
	bSuccess = CloseHandle(hToken);
	if (bSuccess == false) return bSuccess; // Failed

	// Privileges enabled
	VerbosityDisplay("Shutdown Privileges have been successfully enabled.\n");

	return bSuccess;
}

// Check if cursor exceeds the maximum set screen buffer height
// Returns TRUE if this is the case, otherwise FALSE is returned.
// the cls() function is recommended to be called after this function if TRUE is returned,
// as the terminal buffer may need to be reset.
//
bool CheckIfCursorExceedScreenBufferHeight() 
{
	// Get console screen buffer info - have all data ready before check
	CONSOLE_SCREEN_BUFFER_INFO csbiCursorScreenBufCheck;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiCursorScreenBufCheck);

	// Check by comparing set screen buffer height with cursor height
	if (csbiCursorScreenBufCheck.dwCursorPosition.Y >= csbiCursorScreenBufCheck.dwSize.Y - 1) {
		return true;
	}
	else return false;
}

// Switch colours depending on ANSI or WIN32 fallback support
void ColourTypeSwitch()
{
	// Read config file for next check
	ConfigObjMain.ReadConfigFile();

	// Change to ANSI colour variety
	if (bAnsiVTSequences == true) 
	{
		// Set reset definitions
		NOULINE_STR = "\x1b[24m";
		NOBOLD_STR = "\x1b[22m";
		NOBLINK_STR = "\x1b[25m";
		NOSTRIKE_STR = "\x1b[29m";
		
		// Set formatting definitions
		ULINE_STR = "\x1b[4m";
		BOLD_STR = "\x1b[1m";
		BLINK_STR = "\x1b[5m";
		STRIKE_STR = "\x1b[9m";


		// Set colour definitions with RGB ANSI
		// Standard colours
		BLK = BLK_ANSI;
		BLU = BLU_ANSI;
		GRN = GRN_ANSI;
		CYN = CYN_ANSI;
		RED = RED_ANSI;
		MAG = MAG_ANSI;
		YLW = YLW_ANSI;
		WHT = WHT_ANSI;

		// Bright colours
		GRAY = GRAY_ANSI;
		LBLU = LBLU_ANSI;
		LGRN = LGRN_ANSI;
		LCYN = LCYN_ANSI;
		LRED = LRED_ANSI;
		LMAG = LMAG_ANSI;
		LYLW = LYLW_ANSI;
		LWHT = LWHT_ANSI;

		// Check if previous colours were ANSI RGB codes - if not, reset to default and update
		if (
			ConfigObjMain.sColourGlobal.find(';') == std::string::npos
			|| ConfigObjMain.sColourGlobalBack.find(';') == std::string::npos
			|| ConfigObjMain.sColourHighlight.find(';') == std::string::npos
			|| ConfigObjMain.sColourHighlightBack.find(';') == std::string::npos
			|| ConfigObjMain.sColourSubheading.find(';') == std::string::npos
			|| ConfigObjMain.sColourSubheadingBack.find(';') == std::string::npos
			|| ConfigObjMain.sColourTitle.find(';') == std::string::npos
			|| ConfigObjMain.sColourTitleBack.find(';') == std::string::npos
			)
		{
			// Reset definitions of colours to new values
			ConfigObjMain.sColourGlobal = Win32ToAnsiColours(ConfigObjMain.sColourGlobal);
			if (ConfigObjMain.sColourGlobal == "") ConfigObjMain.sColourGlobal = LWHT;

			ConfigObjMain.sColourGlobalBack = Win32ToAnsiColours(ConfigObjMain.sColourGlobalBack);
			if (ConfigObjMain.sColourGlobalBack == "") ConfigObjMain.sColourGlobalBack = BLK;

			ConfigObjMain.sColourHighlight = Win32ToAnsiColours(ConfigObjMain.sColourHighlight);
			if (ConfigObjMain.sColourHighlight == "") ConfigObjMain.sColourHighlight = LWHT;

			ConfigObjMain.sColourHighlightBack = Win32ToAnsiColours(ConfigObjMain.sColourHighlightBack);
			if (ConfigObjMain.sColourHighlightBack == "") ConfigObjMain.sColourHighlightBack = BLU;

			ConfigObjMain.sColourTitle = Win32ToAnsiColours(ConfigObjMain.sColourTitle);
			if (ConfigObjMain.sColourTitle == "") ConfigObjMain.sColourTitle = BLK;

			ConfigObjMain.sColourTitleBack = Win32ToAnsiColours(ConfigObjMain.sColourTitleBack);
			if (ConfigObjMain.sColourTitleBack == "") ConfigObjMain.sColourTitleBack = LCYN;

			ConfigObjMain.sColourSubheading = Win32ToAnsiColours(ConfigObjMain.sColourSubheading);
			if (ConfigObjMain.sColourSubheading == "") ConfigObjMain.sColourSubheading = LWHT;

			ConfigObjMain.sColourSubheadingBack = Win32ToAnsiColours(ConfigObjMain.sColourSubheadingBack);
			if (ConfigObjMain.sColourSubheadingBack == "") ConfigObjMain.sColourSubheadingBack = MAG;
		}

		// Check validity of ANSI colours - to prevent errors in colour system
		if (ValidateColourStringsANSI() == false) {
			VerbosityDisplay("In ColourTypeSwitch(): ERROR - ValidateColourStringsANSI() exited and reported one or more ConfigObjMain.sColour values being incorrect. One or more of these values have been reset to defaults.");
		}
	}

	// Use fallback WIN32 API colour variety
	else 
	{
		// Set reset definitions to nothing- they will not be needed
		NOULINE_STR = "";
		NOBOLD_STR = "";
		NOBLINK_STR = "";
		NOSTRIKE_STR = "";

		// Set formatting definitions to nothing- they will not be needed
		ULINE_STR = "";
		BOLD_STR = "";
		BLINK_STR = "";
		STRIKE_STR = "";

		// Set colour definitions to support the older Windows Console API
		// Standard colours
		BLK = BLK_WIN32;
		BLU = BLU_WIN32;
		GRN = GRN_WIN32;
		CYN = CYN_WIN32;
		RED = RED_WIN32;
		MAG = MAG_WIN32;
		YLW = YLW_WIN32;
		WHT = WHT_WIN32;

		// Bright colours
		GRAY = GRAY_WIN32;
		LBLU = LBLU_WIN32;
		LGRN = LGRN_WIN32;
		LCYN = LCYN_WIN32;
		LRED = LRED_WIN32;
		LMAG = LMAG_WIN32;
		LYLW = LYLW_WIN32;
		LWHT = LWHT_WIN32;

		// Check if previous colours were WIN32 numbers - if not, reset to default and update
		if (
			ConfigObjMain.sColourGlobal.find(';') != std::string::npos
			|| ConfigObjMain.sColourGlobalBack.find(';') != std::string::npos
			|| ConfigObjMain.sColourHighlight.find(';') != std::string::npos
			|| ConfigObjMain.sColourHighlightBack.find(';') != std::string::npos
			|| ConfigObjMain.sColourSubheading.find(';') != std::string::npos
			|| ConfigObjMain.sColourSubheadingBack.find(';') != std::string::npos
			|| ConfigObjMain.sColourTitle.find(';') != std::string::npos
			|| ConfigObjMain.sColourTitleBack.find(';') != std::string::npos
			) 
		{
			// Reset definitions of colours to new values
			ConfigObjMain.sColourGlobal = AnsiToWin32Colours(ConfigObjMain.sColourGlobal);
			if (ConfigObjMain.sColourGlobal == "") ConfigObjMain.sColourGlobal = LWHT;

			ConfigObjMain.sColourGlobalBack = AnsiToWin32Colours(ConfigObjMain.sColourGlobalBack);
			if (ConfigObjMain.sColourGlobalBack == "") ConfigObjMain.sColourGlobalBack = BLK;

			ConfigObjMain.sColourHighlight = AnsiToWin32Colours(ConfigObjMain.sColourHighlight);
			if (ConfigObjMain.sColourHighlight == "") ConfigObjMain.sColourHighlight = LWHT;

			ConfigObjMain.sColourHighlightBack = AnsiToWin32Colours(ConfigObjMain.sColourHighlightBack);
			if (ConfigObjMain.sColourHighlightBack == "") ConfigObjMain.sColourHighlightBack = BLU;

			ConfigObjMain.sColourTitle = AnsiToWin32Colours(ConfigObjMain.sColourTitle);
			if (ConfigObjMain.sColourTitle == "") ConfigObjMain.sColourTitle = BLK;

			ConfigObjMain.sColourTitleBack = AnsiToWin32Colours(ConfigObjMain.sColourTitleBack);
			if (ConfigObjMain.sColourTitleBack == "") ConfigObjMain.sColourTitleBack = LCYN;

			ConfigObjMain.sColourSubheading = AnsiToWin32Colours(ConfigObjMain.sColourSubheading);
			if (ConfigObjMain.sColourSubheading == "") ConfigObjMain.sColourSubheading = LWHT;

			ConfigObjMain.sColourSubheadingBack = AnsiToWin32Colours(ConfigObjMain.sColourSubheadingBack);
			if (ConfigObjMain.sColourSubheadingBack == "") ConfigObjMain.sColourSubheadingBack = MAG;
		}

		// Check validity of WIN32 colours - to prevent errors in colour system
		if (ValidateColourStringsWin32() == false) {
			VerbosityDisplay("In ColourTypeSwitch(): ERROR - ValidateColourStringsWin32() exited and reported one or more ConfigObjMain.sColour values being incorrect. One or more of these values have been reset to defaults.");
		}
	}

	// Finally, write to config file
	ConfigObjMain.WriteConfigFile();

	return;
}

// Function to manage startup tasks
void ProgramInitialisation() 
{
	// Set random colours if random colours on startup are enabled
	if (ConfigObjMain.bRandomColoursOnStartup == true) {

		// Pick random foreground colour
		int nRandForeground = (int)RandNum(16, 1);
		ColourForegroundSwitch(&nRandForeground, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);

		// Pick random background colour
		int nRandBackground = (int)RandNum(16, 1);
		ColourBackgroundSwitch(&nRandBackground, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);
	}

	// Check for Virtual Terminal (ANSI) Sequence Support
	if (EnableVTMode() == false) {
		// Disable ANSI virtual terminal sequences - do not refer to the configuration file
		bAnsiVTSequences = false;

		// Set the colours
		ColourTypeSwitch();

		VerbosityDisplay("This terminal cannot do Virtual Terminal Sequences.\nThis session will use the WIN32 API fallback colour set for operation.\n");
	}
	else {
		// Use user-set setting in the configuration file
		bAnsiVTSequences = ConfigObjMain.bAnsiVTSequences;

		// Set the colours
		ColourTypeSwitch();

		VerbosityDisplay("This terminal has Virtual Terminal Sequences support.\nThis session will run with ANSI RGB colour support.\n");
	}

	// Set colours to global colours that have just been retrieved from config file
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Set console cursor attributes
	SetCursorAttributes();

	// Set shutdown privileges
	if (!EnableShutdownPrivileges()) VerbosityDisplay("Failed to enable shutdown privileges. Restart and shutdown commands may not work.\n");

	// Set window title to 'ZeeTerminal'
	SetWindowTitle("ZeeTerminal");

	// Finally, close away all of the initialisation messages by clearing the screen (non-ANSI terminals fully clear the whole buffer)
	if (bAnsiVTSequences) {
		std::cout << "\033[2J\033[1;1H";
	}
	else {
		cls();
	}

	return;
}

// Main function for running platform
int main(int argc, char* argv[]) 
{
	std::string sCommandInput = "";
	std::string sCommand = "";
	std::string sCommandArgsBuffer = "";
	char cCommandInputArgs[nArgArraySize] = {};
	bool bRunCommandLoopOnce = false; // Run the command loop once, should only be used for singular command arguments

	// Get the program ready, sort out environment
	std::cout << "Getting ready...\n";
	// Initialise main() variables
	// cCommandInputArgs and sStringCommandArgs
	for (int i = 0; i < nArgArraySize; i++) {
		cCommandInputArgs[i] = ' ';
		sStringDataCommandArgs[i] = "";
		sStringOptionCommandArgs[i] = "";
	}

	// Initialise everything else in program
	ProgramInitialisation();

	// Arguments to ZeeTerminal session
	if (argc > 1) {
		std::string sArgv[2];
		sArgv[0] = argv[0];
		sArgv[1] = argv[1];


		if (sArgv[1] == "-c") 
		{
			// The command argument is nonexistent and wasn't found because the argument count is only 2 (the program and the '-c') - post error.
			if (argc <= 2) {
				UserErrorDisplay("ERROR - No command argument found with option -c. Please check that a command argument is after the -c argument, and try again.\n");
				return 0;
			}

			// vsFileParseCommands is used as bRunningFromScriptOrArgCommand will be set to TRUE, so the parser would just read the first value like FileParse.
			// The program would terminate right after the first command as bRunCommandLoopOnce will be set to TRUE, therefore no invalid memory access error should occur.
			vsFileParseCommands.clear();
			vsFileParseCommands.push_back(argv[2]);
			bRunningFromScriptOrArgCommand = true;
			bRunCommandLoopOnce = true; // One command from argument will end the terminal operation

		}
		else if (sArgv[1] == "-h" || sArgv[1] == "--help") {
			// Output help message for user
			std::cout << "___ZeeTerminal Help___\n\n__Syntax__:\nFor running a script: ZeeTerminal.exe <script filepath>\nFor running a singular command: ZeeTerminal.exe -c <command>\n\n"
				<< "If you would like to run a script OR command where either contains space characters, use quotation marks (\"\").\n --> For example: ZeeTerminal.exe \"C:\\Users\\Public\\A Test Script.txt\"\n\n"
				<< "__Possible Arguments__:\n  -->  '-h'  OR  '--help'\tDisplays this help message.\n  -->  -c\t\t\tUse this argument to interpret the next string as a command.\n\n"
				<< "__Examples__:\n -->  ZeeTerminal.exe -c \"echo Hello, World!\"\n -->  ZeeTerminal.exe -c devtools\n -->  ZeeTerminal.exe TestScript.txt\n -->  ZeeTerminal.exe \"Random Directory\\A Test Script.txt\"\n\n";

			// Exit after that - nothing else needs to be run
			return 0;
		}
		else {
			// Initialise FileParse system with first argument - if failed, the function will uninitialise properly immediately.
			if (!InitialiseFileParse(sArgv[1], true)) {
				UserErrorDisplay("ERROR - An error occured while initialising the FileParse System. Possibly a nonexistent file path?\n");
				return 0;
			}
		}
	}

	// If an argument was given, messages that usually would appear when a user is using it should not be displayed.
	// This is indicated by the boolean below:
	//
	if (bRunningFromScriptOrArgCommand == false)
	{
		colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);

		if (bAnsiVTSequences == true) std::cout << BLINK_STR;
		slowcharfn(true, "Welcome to ZeeTerminal!");
		if (bAnsiVTSequences == true) std::cout << NOBLINK_STR;

		// Alert new user about the existence of a short tutorial
		// Helps with new users to get familiar with the program
		if (ConfigObjMain.GetFileAgeInfo() == true) {
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			// Sleep statements to keep user calm
			sleep(500);
			slowcharfn(true, "\nIt looks like you haven't used this application before.");
			sleep(100);

			if (YesNoInput("\nWould you like a short tutorial on how to use it? ['y' for yes, 'n' for no]: > ")) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Sure!\n\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				Tutorial();
			}
			else {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Alright, got it.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "\nPress ENTER to begin...\n";
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		// Help message
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "[Type ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\"Help\" ";
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "to get all commands.]\n[Type ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\"Tutorial\"";
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << " to get a tutorial on how to use the program.]\n\n";
	}


	size_t nFileParseIterator = 0;
	while (true) 
	{
		// Reset all command processing variables to defaults
		sCommand = "";
		sCommandArgsBuffer = "";
		sCommandInput = "";
		sCommandInputRAW = "";

		// Set colours to default
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// The below if-statement is present because after the user-initiated command execution that activates FileParse is complete, the nFileParseIterator variable is incremented.
		// The nFileParseIterator variable incrementing is unwanted as no command from the actual file has been read yet, so it's essentially skipping the first line of the file,
		// hence the nFileParseIterator variable is set to 0 again and the bLastCommandWasFileParse variable is set to false.
		//
		if (bLastCommandWasFileParse && nFileParseIterator >= 1) {
			bLastCommandWasFileParse = false;
			nFileParseIterator = 0;
		}

		// Output 'command' if the display boolean is true
		if (bDisp == true) {
			// Prompt and get input
			std::cout << "Command: > ";
		}

		// Different input methods depending on running off script or actual user wanting to input
		// From script
		if (bRunningFromScriptOrArgCommand == true) {
			// Display command if wanted
			if (bDisp == true) {
				colour(LYLW, ConfigObjMain.sColourGlobalBack);
				std::cout << vsFileParseCommands[nFileParseIterator] << '\n';
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			// Send the next parsed command to command input
			sCommandInput = vsFileParseCommands[nFileParseIterator];
		}
		// From actual user input
		else {
			// Get input from std::cin
			colour(LYLW, ConfigObjMain.sColourGlobalBack);
			std::getline(std::cin, sCommandInput, '\n');
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Optimisation for no input
		if (sCommandInput == "") {
			if (bRunningFromScriptOrArgCommand) {
				// Do nothing - This shouldn't be triggered but is there to prevent crashes
				// if there actually is a bug in the FileParse system.
			}
			else {
				continue;
			}
		}
		else {
			// Initialise cCommandInputArgs to make all spaces
			for (int i = 0; i < nArgArraySize; i++) {
				cCommandInputArgs[i] = ' ';
				sStringDataCommandArgs[i] = "";
				sStringOptionCommandArgs[i] = "";
			}
		}

		// Copy command from sCommandInput into sCommand until space
		//
		// Create stringstream
		std::istringstream sCommandInputIn(sCommandInput);

		// For loop to start checking from after any spaces inputted by the user
		for (int i = 0; i < sCommandInput.length() && !sCommandInputIn.eof(); i++) {
			std::getline(sCommandInputIn, sCommand, ' ');
			if (sCommand != "") break;
		}

		// For loop to find and remove tabs in the command string - these are unwanted, especially if they're used for intentation such as within a script
		while (true) {
			// Find next tab character
			size_t nTabLocation = sCommand.find('\t');
			// if nothing found, break out of the loop
			if (nTabLocation == std::string::npos) break;
			// Erase/remove the tab character
			sCommand.erase(nTabLocation, 1);
		}

		// Optimisation for spaces
		if (sCommand == "") {
			if (bRunCommandLoopOnce) {
				break; // No command, so just leave
			}
			else if (bRunningFromScriptOrArgCommand) {
				// Do nothing - This shouldn't be triggered but is there to prevent crashes
				// if there actually is a bug in the FileParse system.
			}
			else {
				continue; // Normal method - skip everything below
			}
		}

		// Put raw input into sCommandInputRAW (done now to prevent overwrite before making sCommand lowercase)
		sCommandInputRAW = sCommand;

		// Make all letters inside sCommand lowercase
		for (int i = 0; i < sCommand.length(); i++) {
			sCommand[i] = std::tolower(sCommand[i]);
		}

		// Optimisation for exit command (doesn't need to be in Commands())
		if (sCommand == "exit" || sCommand == "0" || sCommand == "2") {
			nNumOfInputtedCommands++;
			nNumOfSuccessfulInputtedCommands++;
			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nHave a good day/night!\n";
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			slowcharfn(false, "Exiting...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Don't exit the terminal when exiting on script completion is disabled - just terminate FileParse and set up everything back to normal.
			if (!bExitOnScriptCompletion && bRunningFromScriptOrArgCommand) 
			{
				// Add log line
				if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging) {
					LogFileMain.AddLogLine("Exit command executed. Exiting on completion disabled and running from script, so FileParse uninitialisation initiated.", 3);
				}

				UninitialiseFileParse();
				nFileParseIterator = 0; // zero out counter and stop counting
				bRunningFromScriptOrArgCommand = false;
				bRunCommandLoopOnce = false;

				// Display success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << CentreText("___FileParse Script successfully executed!___") << "\n\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Now that FileParse has been shut off and terminated, running the continue line on the loop should be safe.
				continue;
			}
			else {
				// Add log line
				if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging) {
					LogFileMain.AddLogLine("Exit command executed. Exiting on completion enabled or user executed the command, so exit process initiated.", 3);
				}

				break; // exit terminal command loop
			}
		}

		// Copy the rest of the stringstream contents into sCommandArgsBuffer
		std::getline(sCommandInputIn, sCommandArgsBuffer, '\n');

		// Copy new sCommandArgsBuffer string to another string, as it will be modified
		const std::string sCommandArgsBufferRAW = sCommandArgsBuffer + " ";

		/* The following will be based on parsing sCommandArgsBuffer for the actual arguments. */
		// Copy the string option arguments into sStringOptionCommandArgs with correct formatting
		sCommandArgsBuffer += " ";
		sCommandArgsBuffer = " " + sCommandArgsBuffer;
		for (size_t nDashPos = 0, nSpacePos = 0, i = 0; i < 128; i++, nDashPos = 0, nSpacePos = 0)
		{
			// Firstly, check which type of string syntax is first (lower is closer to beginning)
			//
			if (sCommandArgsBuffer.find("--\"", 0) > sCommandArgsBuffer.find("--", 0))
			{
				// Anything with -- at the beginning
				if (sCommandArgsBuffer.find("--", 0) != std::string::npos)
				{
					// Get next occurence of " --"
					nDashPos = sCommandArgsBuffer.find("--", 0);
					// Get occurence of ' ' after nDashPos new location
					nSpacePos = sCommandArgsBuffer.find(" ", nDashPos + 2);

					/* Check for confliction with --" */
					//
					std::string sTest = sCommandArgsBuffer.substr((nDashPos + 2), nSpacePos - (nDashPos + 2));

					// For loop uses struct so declaration of multiple variables in for loop is possible
					//
					for (struct { size_t j = 0; bool bAlreadyErased = false; } loop; loop.j < sTest.length(); loop.j++)
					{
						if (sTest[loop.j] == '\"') {
							break;
						}
						else {

							// Only read and erase string if first time passing by the line of code
							if (loop.bAlreadyErased == false) {
								// Copy from after the dashes to the next space
								sStringOptionCommandArgs[i] = sCommandArgsBuffer.substr((nDashPos + 2), nSpacePos - (nDashPos + 2));

								// Erase the found string from the argument buffer to remove it from plain sight from parser
								sCommandArgsBuffer.erase(nDashPos, nSpacePos - (nDashPos));

								loop.bAlreadyErased = true;
							}
						}
					}
				}

			}
			else
			{
				// Anything with --" at the beginning
				if (sCommandArgsBuffer.find("--\"", 0) != std::string::npos)
				{
					nDashPos = sCommandArgsBuffer.find("--\"", 0);
					// Get next occurence of '"'
					nSpacePos = sCommandArgsBuffer.find("\"", nDashPos + 3);
					// Use space as fallback if there is no other speechmark
					if (nSpacePos == std::string::npos) nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

					// Copy from after the dashes to the next space/speechmark
					sStringOptionCommandArgs[i] = sCommandArgsBuffer.substr((nDashPos + 3), nSpacePos - (nDashPos + 3));

					// Erase the found string from the argument buffer to remove it from plain sight from parser
					sCommandArgsBuffer.erase(nDashPos, nSpacePos + 1 - nDashPos);

				}

			}

		}

		// Copy the string data arguments into sStringDataCommandArgs with correct formatting
		for (size_t nFirstMarkerPos = 0, nLastMarkerPos = 0, i = 0, nViableSpacePos = 0; i < nArgArraySize; i++, nFirstMarkerPos = 0, nLastMarkerPos = 0, nViableSpacePos = 0)
		{
			// Check for next viable space location
			while (true) 
			{
				// a. Find next raw space location
				nViableSpacePos = sCommandArgsBuffer.find(" ", nViableSpacePos);

				// b. Check if raw space location is at end of string
				if (nViableSpacePos == std::string::npos || nViableSpacePos == sCommandArgsBuffer.find_last_of(" ", sCommandArgsBuffer.length())) break;

				// c. Increment nViableSpacePos to not just run in loops when checking space location
				nViableSpacePos++;

				// d. Check next character for any conflictions; if after the space is good, exit
				if (sCommandArgsBuffer[nViableSpacePos] != ' ' && sCommandArgsBuffer[nViableSpacePos] != '-' && sCommandArgsBuffer[nViableSpacePos] != '\"') {
					nViableSpacePos--;
					break;
				}
			}

			// Check what string argument type is first, and then check that first so everything in the array is in order
			if (sCommandArgsBuffer.find(" ", nViableSpacePos) < sCommandArgsBuffer.find("\"", 0)) 
			{
				if (sCommandArgsBuffer.find(" ", nViableSpacePos) != std::string::npos)
				{
					// Check for space argument first
					//
					// Check for first space
					nFirstMarkerPos = sCommandArgsBuffer.find(" ", nViableSpacePos) + 1;

					// Check for last space
					nLastMarkerPos = sCommandArgsBuffer.find(" ", nFirstMarkerPos);

					// Create new substring from these marking points
					std::string sCommandArgument = sCommandArgsBuffer.substr(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);

					sStringDataCommandArgs[i] = sCommandArgument;

					// Erase substring from arugment buffer
					sCommandArgsBuffer.erase(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);
				}
			}
			else
			{
				if (sCommandArgsBuffer.find("\"", 0) != std::string::npos)
				{
					// Check for quotation argument first
					//
					// Check for first quotation mark
					nFirstMarkerPos = sCommandArgsBuffer.find("\"", 0) + 1;

					// Check for last quotation mark
					nLastMarkerPos = sCommandArgsBuffer.find("\"", nFirstMarkerPos);

					// Create new substring from these marking points
					sStringDataCommandArgs[i] = sCommandArgsBuffer.substr(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);

					// Erase substring from argument buffer
					// 
					// 1 is subtracted so the first quotation is removed as well, 
					// and 1 is added on the last marker here so the ending quotation gets purged
					sCommandArgsBuffer.erase(nFirstMarkerPos-1, (nLastMarkerPos+1) - (nFirstMarkerPos-1));
				}
			}
		}

		// Copy the letter after a dash into cCommandInputArgs
		for (size_t i = 0, j = 0; i < sCommandArgsBuffer.length() && j < nArgArraySize; i++) {
			if (i > 0) {
				// Character after must not be a space to prevent conflict with string parser 
				if (sCommandArgsBuffer[i - 1] != '-' && sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					cCommandInputArgs[j] = std::tolower(sCommandArgsBuffer[i + 1]);
					j++;
				}
			}
			else {
				// This time, just remove the check for sCommandArgsBuffer[nFileParseIterator - 1] to prevent OOR exception
				if (sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					cCommandInputArgs[j] = std::tolower(sCommandArgsBuffer[i + 1]);
					j++;
				}
			}

		}

		// Add a log line for command execution
		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging)
		{
			// Get number of char args
			size_t nCharArraySize = 0;
			for (; nCharArraySize < nArgArraySize && cCommandInputArgs[nCharArraySize] != ' '; nCharArraySize++) {}

			// Get number of data string args
			size_t nDataStringArraySize = 0;
			for (; nDataStringArraySize < nArgArraySize && sStringDataCommandArgs[nDataStringArraySize] != ""; nDataStringArraySize++) {}

			// Get number of option string args
			size_t nOptionStringArraySize = 0;
			for (; nOptionStringArraySize < nArgArraySize && sStringOptionCommandArgs[nOptionStringArraySize] != ""; nOptionStringArraySize++) {}

			// Add log line
			LogFileMain.AddLogLine("Executing command [" + sCommand + "] with "
				+ std::to_string(nCharArraySize) + " character arguments, "
				+ std::to_string(nOptionStringArraySize) + " option string arguments, and "
				+ std::to_string(nDataStringArraySize) + " data string arguments (User Input: [" + sCommandInput + "]).", 3);
		}

		// Finally, call commands function
		//
		nNumOfInputtedCommands++;
		nNumOfSuccessfulInputtedCommands++;
		Commands(sCommand, cCommandInputArgs, sCommandArgsBufferRAW);
		std::cout << '\n';

		// Exit on argument command completion OR exit on script completion (line position check and if exiting after script completion is enabled)
		if (bRunCommandLoopOnce == true || (nFileParseIterator >= vsFileParseCommands.size() - 1 && bExitOnScriptCompletion == true)) {
			break;
		}

		// If not exiting on script completion, just uninitialise everything related to the FileParse system and continue as normal
		else if (nFileParseIterator >= vsFileParseCommands.size() - 1 && bExitOnScriptCompletion == false) {
			UninitialiseFileParse();
			nFileParseIterator = 0; // zero out counter and stop counting
			bRunningFromScriptOrArgCommand = false;
			bRunCommandLoopOnce = false;

			// Display success message
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("___FileParse Script successfully executed!___") << "\n\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Increment if running from script
		if (bRunningFromScriptOrArgCommand) nFileParseIterator++;
	}

	return 0;
}