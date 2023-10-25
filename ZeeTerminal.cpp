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
#include <codecvt>
#include <powrprof.h>
#include "Engine\RGBColourPreset-System.cpp"
#include "Engine\ConfigFile-System.cpp"
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
RGBColourPresetSystem	RGBPreset[3]; // Possibly [5] in a future update?
bool					bConsoleBugGCSBI = false; // WindowsTerminal Bug PR#14774 Workaround
bool					bAnsiVTSequences = true;
std::string				sCommandInputRAW = "";
std::string				sStringCommandArgs[128]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
									             // on multi-argument commands.
const int				nArgArraySize = 128; // Array size for all argument arrays
unsigned long long int	nNumOfInputtedCommands = 0; // Counter for number of inputted commands since the start of the ZeeTerminal session.
unsigned long long int	nNumOfSuccessfulInputtedCommands = 0; // Counter for number of successful inputted commands since the start of the ZeeTerminal session.

std::string				sLastColourFore = ""; // Last set colour of any kind - foreground
std::string				sLastColourBack = ""; // Last set colour of any kind - background

ConfigFileSystem		ConfigObjMain; // Configuration Object
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

		// Now, modify the background input choice 
		int nBackgroundColourFinal = std::stoi(sColourBackgroundChoice);
		int nForegroundColourFinal = std::stoi(sColourForegroundChoice);

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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), nBackgroundColourFinal + nForegroundColourFinal);
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
long double RandNum(long double max, long double min) {
	std::random_device dev;
	std::mt19937_64 rng(dev());
	std::uniform_int_distribution<std::mt19937_64::result_type> dist(min, max); // distribution in range [min, max]

	return dist(rng);
}

// Converter from wide string to string
std::string ws2s(const std::wstring &wstr) {
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

// Checks whether std::string argument is a string or not
bool isNumber(const std::string sNumberTest) {
	// Not a number as there's nothing in the string
	if (sNumberTest.length() <= 0) return false;

	// Check if all digits are numbers
	for (size_t i = 0; i < sNumberTest.length(); i++) {
		// skip character if it's a decimal point
		if (sNumberTest[i] == '.') continue;
		else if (isdigit(sNumberTest[i]) == false) return false;
	}

	// Test if above stold() range
	try {
		long double nRangeTest = std::stold(sNumberTest);
	}
	catch (const std::out_of_range& oorIsNumber) {
		VerbosityDisplay("Exception caught - Number is too high/low (out of range).");
		return false;
	}

	return true;
}

// Function to clear keyboard buffer
void ClearKeyboardBuffer() {
	while (_kbhit()) {
		_getch();
	}
	return;
}

// Function to set console cursor position
inline void SetCursorPosition(int x, int y) {
	
	COORD CursorPos{};
	CursorPos.X = x;
	CursorPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);
}

// wordWrap - Adds line/word wrapping to a string, based on the console window width.
//
// This takes in an std::string as an argument, and returns another std::string with the word wrapping in the string.
std::string wordWrap(std::string text) {
	int width = 0;
	std::string result = "";
	long long int counter = 0;

	// Cannot do word wrapping if disabled
	if (ConfigObjMain.bWordWrapToggle == false) return text;

	// Get console window size
	CONSOLE_SCREEN_BUFFER_INFO csbiWordWrap;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiWordWrap);
	width = csbiWordWrap.srWindow.Right - csbiWordWrap.srWindow.Left + 1;

	size_t lastSpace = -1;
	for (size_t i = 0; i < text.length(); i++) {

		// Counter mods
		if (text[i] == '\n') {
			counter = 0;
			lastSpace = -1;
		}
		else if (text[i] == '\t') {
			// tabstop is usually 8 spaces; might be dynamic in future
			counter += 8;
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

// Function to display extra help information for specific commands
inline void DirectionsDisplay(std::string sPrompt) {
	if (ConfigObjMain.bDisplayDirections == true && bAnsiVTSequences == true) {
		colour(CYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\x1b[" << ULINE << "m" << (sPrompt) << "\x1b[" << NOULINE << "m" << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	else if (ConfigObjMain.bDisplayDirections == true && bAnsiVTSequences == false) {
		colour(CYN, ConfigObjMain.sColourGlobalBack);
		std::cout << (sPrompt) << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	return;
}

// Function to display verbose messages at specific times
inline void VerbosityDisplay(std::string sPrompt) {
	if (ConfigObjMain.bDisplayVerboseMessages == true) {
		colour(GRAY, BLK);
		std::cerr << "Verbose Message: " << sPrompt << std::endl;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	return;
}

// Function to display error messages at specific times
inline void UserErrorDisplay(std::string sError) {

	// Output user-space error in red text with word wrapping
	colour(RED, ConfigObjMain.sColourGlobalBack);
	std::cerr << wordWrap(sError) << std::endl;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// Function to output stuff for converters and calculators
long double NumInput(std::string sPrompt) {
	long double num;

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::cin >> num;
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

	return num;
}

// Function to assist with string output by preventing reuse of code
std::string StrInput(std::string sPrompt) {
	std::string string;

	// Prompt
	std::cout << wordWrap(sPrompt);
	colour(LYLW, ConfigObjMain.sColourGlobalBack);
	getline(std::cin, string);
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return string;
}

// YesNo - allows for y/n input
bool YesNo(std::string sPrompt) {
	char cInput;

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
	if (cInput == 'y' || cInput == 'Y') return true; else return false;
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

// Clear screen function (Flushes screen buffer)
void cls() {

	// Using ANSI escape codes to clear the screen is a lot faster and cross-platform
	if (bAnsiVTSequences == true) {
		std::cout << "\033c"; // fully clear the scrollback buffer
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
			HANDLE v1 = GetStdHandle(0xFFFFFFF5);
			SetConsoleCursorPosition(v1, v6.dwCursorPosition);
		}
		return;
	}
	return;

}

// Function that outputs text with random colours 
void RandomColourOutput(std::string sText) {

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
		std::cout << sText;
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
	if (bAnsiVTSequences) {
		std::cout << "\x1b[" << NOULINE << "m\x1b[" << NOBOLD << "m";
	}
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
		for (int i = 0; i <= sText.length(); i++) {
			sleep(ConfigObjMain.nSlowCharSpeed);
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
		sleep(ConfigObjMain.nSlowCharSpeed);
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
		sleep(ConfigObjMain.nSlowCharSpeed);
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
		sleep(ConfigObjMain.nSlowCharSpeed);
	}

	// Finish off with newline
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << '\n';
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
inline void ResetColour() {

	// Reset all RGB to default
	ConfigObjMain.sColourGlobal = LWHT;
	ConfigObjMain.sColourGlobalBack = BLK;
	// Output reset message
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << "\x1b[" << RESETALL << "m\nColours have been reset to default.\n";

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

// A function to check for a specific bug affecting CONSOLE_SCREEN_BUFFER_INFO::dwCursorPosition
// positioning reports, in the new Windows Terminal and OpenConsole.exe.
bool ConsoleWTBugCheck() {
	// Get console size
	HANDLE hTest = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiTest;
	GetConsoleScreenBufferInfo(hTest, &csbiTest);
	int nConsoleHeight = csbiTest.srWindow.Bottom - csbiTest.srWindow.Top;

	// Spam enters until a few more than console bottom
	for (int i = 0; i <= (nConsoleHeight + 4); i++) {
		std::cout << '\n';
	}

	// Get the console cursor position after that
	GetConsoleScreenBufferInfo(hTest, &csbiTest);
	int nVerticalCPosition = csbiTest.dwCursorPosition.Y;
	cls();

	if (nVerticalCPosition <= nConsoleHeight) {
		return true;
	}
	else {
		return false;
	}
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


		// Set colour definitions with RGB ANSI
		// Standard colours
		BLK = "0;0;0";
		RED = "230;0;0";
		GRN = "22;198;12";
		YLW = "231;186;0";
		BLU = "0;0;255";
		MAG = "136;23;152";
		CYN = "58;150;221";
		WHT = "215;215;215";

		// Bright colours
		GRAY = "118;118;118";
		LRED = "251;96;127";
		LGRN = "0;255;0";
		LYLW = "255;255;0";
		LBLU = "59;120;255";
		LMAG = "180;0;158";
		LCYN = "97;214;214";
		LWHT = "255;255;255";

		// Check if previous colours were ANSI RGB codes - if not, reset to default and update
		if (
			ConfigObjMain.sColourGlobal.find(';') == std::string::npos
			|| ConfigObjMain.sColourGlobalBack.find(';') == std::string::npos
			|| ConfigObjMain.sColourHighlight.find(';') == std::string::npos
			|| ConfigObjMain.sColourHighlightBack.find(';') == std::string::npos
			|| ConfigObjMain.sColourSubheadingBack.find(';') == std::string::npos
			|| ConfigObjMain.sColourTitle.find(';') == std::string::npos
			|| ConfigObjMain.sColourTitleBack.find(';') == std::string::npos
			)
		{
			// Reset definitions of colours to new values
			ConfigObjMain.sColourGlobal = LWHT;
			ConfigObjMain.sColourGlobalBack = BLK;

			ConfigObjMain.sColourHighlight = LWHT;
			ConfigObjMain.sColourHighlightBack = BLU;

			ConfigObjMain.sColourTitle = BLK;
			ConfigObjMain.sColourTitleBack = LCYN;

			ConfigObjMain.sColourSubheading = LWHT;
			ConfigObjMain.sColourSubheadingBack = MAG;

			ConfigObjMain.WriteConfigFile();
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

		// Set colour definitions to support the older Windows Console API
		// Standard colours
		BLK = "0";
		BLU = "1";
		GRN = "2";
		CYN = "3";
		RED = "4";
		MAG = "5";
		YLW = "6";
		WHT = "7";

		// Bright colours
		GRAY = "8";
		LBLU = "9";
		LGRN = "10";
		LCYN = "11";
		LRED = "12";
		LMAG = "13";
		LYLW = "14";
		LWHT = "15";

		// Check if previous colours were WIN32 numbers - if not, reset to default and update
		if (
			ConfigObjMain.sColourGlobal.find(';') != std::string::npos
			|| ConfigObjMain.sColourGlobalBack.find(';') != std::string::npos
			|| ConfigObjMain.sColourHighlight.find(';') != std::string::npos
			|| ConfigObjMain.sColourHighlightBack.find(';') != std::string::npos
			|| ConfigObjMain.sColourSubheadingBack.find(';') != std::string::npos
			|| ConfigObjMain.sColourTitle.find(';') != std::string::npos
			|| ConfigObjMain.sColourTitleBack.find(';') != std::string::npos
			) 
		{
			// Reset definitions of colours to new values
			ConfigObjMain.sColourGlobal = LWHT;
			ConfigObjMain.sColourGlobalBack = BLK;

			ConfigObjMain.sColourHighlight = LWHT;
			ConfigObjMain.sColourHighlightBack = BLU;

			ConfigObjMain.sColourTitle = BLK;
			ConfigObjMain.sColourTitleBack = LCYN;

			ConfigObjMain.sColourSubheading = LWHT;
			ConfigObjMain.sColourSubheadingBack = MAG;

			ConfigObjMain.WriteConfigFile();
		}

	}

	return;
}

// Function to manage startup tasks
void ProgramInitialisation() 
{
	// Set random colours if random colours on startup are enabled
	if (ConfigObjMain.bRandomColoursOnStartup == true) {
		// Can't do without ANSI VT Sequences
		if (bAnsiVTSequences) {
			// Pick random foreground colour
			int nRandForeground = RandNum(16, 1);
			ColourForegroundSwitch(&nRandForeground, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);

			// Pick random background colour
			int nRandBackground = RandNum(16, 1);
			ColourBackgroundSwitch(&nRandBackground, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);
		}

		// Set colours to the whole screen
		cls();
	}

	// Check for Virtual Terminal (ANSI) Sequence Support
	if (EnableVTMode() == false) {
		// Disable ANSI virtual terminal sequences
		bAnsiVTSequences = false;

		VerbosityDisplay("This terminal cannot do Virtual Terminal Sequences.\nThis session will use the WIN32 API fallback colour set for operation.\n");

		// Set the colours
		ColourTypeSwitch();

		// Clear screen to set screen buffer to black colour
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		cls();
	}
	else {
		// Keep ANSI VT sequences enabled
		bAnsiVTSequences = true;

		// Set the colours
		ColourTypeSwitch();

		// Clear screen to set screen buffer to black colour
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		cls();

		VerbosityDisplay("This terminal has Virtual Terminal Sequences support.\nThis session will run with colour support.\n");
	}

	// Check for existence of bug PR#14774 in console window
	if (ConsoleWTBugCheck()) {
		// Enable workaround
		bConsoleBugGCSBI = true;

		VerbosityDisplay("This console window has bug PR#14774 on the Windows Terminal GitHub. A workaround will be used throughout program operation.");
		std::cout << "\n\n";
	}
	else {
		// Keep workaround disabled
		bConsoleBugGCSBI = false;

		VerbosityDisplay("This console window does not have bug PR#14774 on the Windows Terminal GitHub, and its workaround will not be used.");
		std::cout << "\n\n";
	}

	// Set console cursor attributes
	SetCursorAttributes();

	// Set shutdown privileges
	if (!EnableShutdownPrivileges()) VerbosityDisplay("Failed to enable shutdown privileges. Restart and shutdown commands may not work.\n");

	// Set window title to 'ZeeTerminal'
	SetWindowTitle("ZeeTerminal");

	// Update Notes Array (Memory Notes) from notes file
	VerbosityDisplay("Updating Notes Array (Memory Notes) from Notes file, using NotesSystem::ReadFromNotesFile()...\n");
	NotesMain.ReadFromNotesFile();

	// Finally, close away all of the initialisation messages with cls()
	cls();

	return;
}

// Main function for running platform
int main(int argc, char* argv[]) 
{
	std::string sCommandInput = "";
	std::string sCommand = "";
	std::string sCommandArgsBuffer = "";
	char sCommandInputArgs[128] = {};

	// Get the program ready, sort out environment
	std::cout << "Getting ready...\n";
	// Initialise main() variables
	// sCommandInputArgs and sStringCommandArgs
	for (int i = 0; i < nArgArraySize; i++) {
		sCommandInputArgs[i] = ' ';
		sStringCommandArgs[i] = "";
	}

	// Initialise everything else in program
	ProgramInitialisation();

	colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);

	if (bAnsiVTSequences == true) std::cout << "\x1b[" << BLINK << 'm';
	slowcharfn(true, "Welcome to ZeeTerminal!");

	// Alert new user about the existence of a short tutorial
	if (ConfigObjMain.GetFileAgeInfo() == true) {
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		slowcharfn(true, "\nIt looks like you haven't used this application before.");

		if (YesNo("\nWould you like a short tutorial on how to use it? ['y' for yes, 'n' for no]: > ")) {
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
	if (bAnsiVTSequences) std::cout << "\x1b[" << NOBLINK << "m";
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

	while (true) 
	{
		// Set colours to default
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Prompt and get input
		std::cout << "Command: > ";
		colour(LYLW, ConfigObjMain.sColourGlobalBack);
		std::getline(std::cin, sCommandInput);
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Optimisation for no input
		if (sCommandInput == "") {
			continue;
		}
		else {
			// Initialise sCommandInputArgs to make all spaces
			for (int i = 0; i < nArgArraySize; i++) {
				sCommandInputArgs[i] = ' ';
				sStringCommandArgs[i] = "";
			}
		}

		// Copy command from sCommandInput into sCommand until space
		std::istringstream sCommandInputIn(sCommandInput);

		// For loop to start checking from after any spaces inputted by the user
		for (int i = 0; i < sCommandInput.length(); i++) {
			std::getline(sCommandInputIn, sCommand, ' ');
			if (sCommand != "") break;
		}

		// Optimisation for spaces
		if (sCommand == "") {
			continue;
		}

		// Put raw input into sCommandInputRAW (done now to prevent overwrite before making sCommand lowercase)
		sCommandInputRAW = sCommand;

		// Make all letters inside sCommand lowercase
		for (int i = 0; i < sCommand.length(); i++) {
			sCommand[i] = std::tolower(sCommand[i]);
		}

		// Optimisation for exit command (doesn't need to be in Commands())
		if (sCommand == "exit" || sCommand == "0") {
			nNumOfInputtedCommands++;
			nNumOfSuccessfulInputtedCommands++;
			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nHave a good day/night!\n";
			colour(RED, ConfigObjMain.sColourGlobalBack);
			slowcharfn(false, "Exiting...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return 0;
		}

		// Copy the rest of the stringstream contents into sCommandArgsBuffer
		std::getline(sCommandInputIn, sCommandArgsBuffer, '\n');

		// Copy new sCommandArgsBuffer string to another string, as it will be modified
		const std::string sCommandArgsBufferRAW = sCommandArgsBuffer + " ";

		/* The following will be based on parsing sCommandArgsBuffer for the actual arguments. */
		// Copy the string arguments into sStringCommandArgs with correct formatting
		sCommandArgsBuffer += " ";
		sCommandArgsBuffer = " " + sCommandArgsBuffer;
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

					sStringCommandArgs[i] = sCommandArgument;

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
					sStringCommandArgs[i] = sCommandArgsBuffer.substr(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);

					// Erase substring from argument buffer
					// 
					// 1 is subtracted so the first quotation is removed as well, 
					// and 1 is added on the last marker here so the ending quotation gets purged
					sCommandArgsBuffer.erase(nFirstMarkerPos-1, (nLastMarkerPos+1) - (nFirstMarkerPos-1));
				}
			}
		}

		// Copy the letter after a dash into sCommandInputArgs
		for (size_t i = 0, j = 0; i < sCommandArgsBuffer.length() && j < nArgArraySize; i++) {
			if (i > 0) {
				// Character after must not be a space to prevent conflict with string parser 
				if (sCommandArgsBuffer[i - 1] != '-' && sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					sCommandInputArgs[j] = std::tolower(sCommandArgsBuffer[i + 1]);
					j++;
				}
			}
			else {
				// This time, just remove the check for sCommandArgsBuffer[i - 1] to prevent OOR exception
				if (sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					sCommandInputArgs[j] = std::tolower(sCommandArgsBuffer[i + 1]);
					j++;
				}
			}

		}

		// Finally, call commands function
		nNumOfInputtedCommands++;
		nNumOfSuccessfulInputtedCommands++;
		Commands(sCommand, sCommandInputArgs, sCommandArgsBufferRAW);
		std::cout << '\n';

		// Reset all command processing variables to defaults
		sCommand = "";
		sCommandArgsBuffer = "";
		sCommandInput = "";
		sCommandInputRAW = "";
	}

	return 0;

}