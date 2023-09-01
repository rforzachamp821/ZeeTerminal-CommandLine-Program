#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <thread>
#include <atomic>
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
#include "Engine\ScreenNavigateEngine.cpp"
#include "Engine\OptionSelectEngine.cpp"
#include "Engine\TableEngine.cpp"
#include "Engine\RGBColourPreset-System.cpp"
#include "Engine\MultimediaEngine.cpp"
#include "Engine\FileOpenGUIEngine.cpp"
#include "CommandFiles\CommandsFile.cpp"


#pragma comment(lib, "winmm.lib") // To access MMSYSTEM libs

// Runtime variables
RGBColourPresetSystem RGBPreset[3]; // Possibly [5] in a future update?
bool bConsoleBugGCSBI = false; // WindowsTerminal Bug PR#14774 Workaround
std::string sCommandInputRAW = "";
std::string sStringCommandArgs[128]; // Made global because you can't pass an std::string array into a function, therefore Commands() wouldn't work properly
									 // on multi-argument commands.

// Settings
bool bAnsiVTSequences = true;
bool bDisplayDirections = true;
bool bDisplayVerboseMessages = false; // TRUE for debugging; temporary and not for final release'
bool bRandomColoursOnStartup = false;
bool bShowCursor = true;
bool bWordWrapToggle = true;
bool bCursorBlink = true;
bool bTermCustomThemeSupport = false;

int nSlowCharSpeed = 45;
int nCursorShape = 5; // TYPES are: block blinking (1), block steady (2), underline blinking (3), underline steady (4), bar blinking (5), bar steady (6)

std::string sColourGlobal = LWHT;
std::string sColourGlobalBack = BLK;

std::string sColourHighlight = LWHT;
std::string sColourHighlightBack = BLU;

std::string sColourTitle = BLK;
std::string sColourTitleBack = LCYN;

std::string sColourSubheading = LWHT;
std::string sColourSubheadingBack = MAG;



// Sets cursor attributes automatically when called
void SetCursorAttributes() {

	// Can't do without ANSI VT sequences
	if (bAnsiVTSequences) {
		// Set cursor shape
		std::cout << "\x1b[" << nCursorShape << " q";

		// Set cursor blink
		if (bCursorBlink == true) {
			std::cout << "\x1b[?12h";
		}
		else std::cout << "\x1b[?12l";

		// Set cursor visibility
		if (bShowCursor == true) {
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
		if (bShowCursor == true) {
			cciAttribSet.bVisible = true;
		}
		else cciAttribSet.bVisible = false;

		// Set final cursor info
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cciAttribSet);
	}

	return;
}

// Sets the colour and background colour
void colour(std::string sColourForegroundChoice, std::string sColourBackgroundChoice) {
	if (bAnsiVTSequences) {

		// Foreground
		std::cout << "\x1b[38;2;" << sColourForegroundChoice << "m";

		// Support for transparency in Windows Terminal; black is usually default background colour so will be default here
		if (sColourBackgroundChoice == BLK && bTermCustomThemeSupport) {
			std::cout << "\x1b[49m";
			return;
		}

		// Background
		std::cout << "\x1b[48;2;" << sColourBackgroundChoice << "m";
	}

	// Windows Console API - activated when no ANSI support is detected and is a fallback (16-colours)
	else {

		// Check for bugs
		// 
		// Check for bug in foreground input
		for (int i = 0; i < sColourForegroundChoice.length() - 1; i++) {
			// Check if it's a number; there may be a bug
			if (!isdigit(sColourForegroundChoice[i])) {
				VerbosityDisplay("Platform ERROR - Failed to change foreground colour due to bug detection.\n");
				return;
			}
		}

		// Check for bug in background input
		for (int i = 0; i < sColourBackgroundChoice.length() - 1; i++) {
			// Check if it's a number; there may be a bug
			if (!isdigit(sColourBackgroundChoice[i])) {
				VerbosityDisplay("Platform ERROR - Failed to change background colour due to bug detection.\n");
				return;
			}
		}

		// Now, modify the background input choice 
		int nBackgroundColourFinal = std::stoi(sColourBackgroundChoice) * 16; // WINAPI works on a 16 colour system
		int nForegroundColourFinal = std::stoi(sColourForegroundChoice);

		// Finally, add the colours and set the colour
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), nBackgroundColourFinal + nForegroundColourFinal);
	}
	
	return;
}

// colourHighlight - Sets the colour from value inside nColourHighlight(Back).
void colourHighlight() 
{
	// Use the default colour function; custom solution not needed
	colour(sColourHighlight, sColourHighlightBack);
	return;
}

// Be sure to change back to no underline AND no bold when done
void colourTitle() 
{
	// Use the default colour function; custom solution not needed
	colour(sColourTitle, sColourTitleBack);
	if (bAnsiVTSequences) std::cout << "\x1b[" << ULINE << "m";

	return;
}

// Be sure to change back to no underline when done
void colourSubheading() 
{
	// Use the default colour function; custom solution not needed
	colour(sColourSubheading, sColourSubheadingBack);
	if (bAnsiVTSequences) std::cout << "\x1b[" << ULINE << "m";

	return;
}

// Function to put console to sleep so makes programming job easier
void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

// Function to choose random number
int randnum(long long int max, long long int min) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [min, max]

	long long int randnum = dist(rng);
	return randnum;
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
void clearkeebbuf() {
	while (_kbhit()) {
		_getch();
	}
	return;
}

// Function to set console cursor position
void SetCursorPosition(int x, int y) {
	
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
	if (bWordWrapToggle == false) return text;

	// Get console window size
	CONSOLE_SCREEN_BUFFER_INFO csbiWordWrap;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiWordWrap);
	width = csbiWordWrap.srWindow.Right - csbiWordWrap.srWindow.Left + 1;

	size_t lastSpace = -1;
	for (size_t i = 0; i < text.length(); i++) {
		if (text[i] == '\n') {
			counter = 0;
			lastSpace = -1;
		}
		else if (text[i] == '\t') { // tabstop is usually 8 spaces; might be dynamic in future
			counter += 8;
		}
		else if (counter == width) {
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
void DirectionsDisplay(std::string sPrompt) {
	if (bDisplayDirections == true && bAnsiVTSequences == true) {
		colour(CYN, sColourGlobalBack);
		std::cout << "\x1b[" << ULINE << "m" << (sPrompt) << "\x1b[" << NOULINE << "m" << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
	}
	else if (bDisplayDirections == true && bAnsiVTSequences == false) {
		colour(CYN, sColourGlobalBack);
		std::cout << (sPrompt) << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
	}
	return;
}

// Function to display verbosity messages at specific times
void VerbosityDisplay(std::string sPrompt) {
	if (bDisplayVerboseMessages == true && bAnsiVTSequences == true) {
		colour(GRAY, BLK);
		std::cerr << "Verbose Message: " << sPrompt << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
	}
	else if (bDisplayVerboseMessages == true && bAnsiVTSequences == false) {
		colour(GRAY, BLK);
		std::cerr << "Verbose Message: " << sPrompt << std::endl;
		colour(sColourGlobal, sColourGlobalBack);
	}
	return;
}

// Function to output stuff for converters and calculators
long double num(std::string sPrompt) {
	long double num;

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, sColourGlobalBack);
		std::cin >> num;
		colour(sColourGlobal, sColourGlobalBack);

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect. Please try again.\n");
			colour(sColourGlobal, sColourGlobalBack);
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
std::string str(std::string sPrompt) {
	std::string string;

	// Prompt
	std::cout << wordWrap(sPrompt);
	colour(LYLW, sColourGlobalBack);
	getline(std::cin, string);
	colour(sColourGlobal, sColourGlobalBack);

	return string;
}

// YesNo - allows for y/n input
bool YesNo(std::string sPrompt) {
	char cInput;

	while (true) {
		std::cout << wordWrap(sPrompt);
		colour(LYLW, sColourGlobalBack);
		std::cin >> cInput;
		colour(sColourGlobal, sColourGlobalBack);
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			colour(RED, sColourGlobalBack);
			std::cerr << wordWrap("Your input was incorrect. Please try again.\n");
			colour(sColourGlobal, sColourGlobalBack);
			continue;
		}
		else {
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		}
	}
	if (cInput == 'y' || cInput == 'Y') return true; else return false;
}

// WindowTitleSet - Function to set title for the console window.
// Arguments: sTitle for the title string.
bool WindowTitleSet(std::string sTitle) {
	if (bAnsiVTSequences) {
		// Use ANSI VT sequences if they work on current terminal
		std::cout << "\x1b]0;" << sTitle << "\x1b\x5c";
	}
	else {
		// Use Windows SetConsoleTitleA if ANSI VT sequences don't work on current terminal window
		if (SetConsoleTitleA(sTitle.c_str())) {
			return true;
		}
		else return false;
	}

	return true;
}

// Clear screen function (Flushes screen buffer)
void cls() {

	// Using ANSI escape codes to clear the screen is a lot faster and cross-platform
	if (bAnsiVTSequences == true) {
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

// CentreColouredText - Takes in a title string and outputs it centred to the console with padding in relation to the console window size.
// Arguments: sText is for the string input, nTypeOfText is for the type of text (title (1), subheaing (2), etc).
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
	colour(sColourGlobal, sColourGlobalBack);
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
	colour(sColourGlobal, sColourGlobalBack);

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
			sleep(nSlowCharSpeed);
			std::cout << sText[i];
		}
		// In case a key was pressed while operation was commencing
		clearkeebbuf();
		return;
	}

	// Firstly, output string of spaces
	std::cout << std::string((nWidth - sText.length()) / 2, ' ');
	// Then output the string itself like slowcharfn()
	for (int i = 0; i <= sText.length(); i++) {
		sleep(nSlowCharSpeed);
		std::cout << sText[i];
	}
	// Output newline if call says so
	if (bNewLine) std::cout << std::endl;
	// In case a key was pressed while operation was commencing
	clearkeebbuf();
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
		sleep(nSlowCharSpeed);
		std::cout << sSlowchar[i];
	}
	// In case a key was pressed while operation was commencing
	clearkeebbuf();
	colour(sColourGlobal, sColourGlobalBack);

	return;
}

// Function for outputting characters slowly
void slowcharfn(bool nline, std::string sSlowchar) {
	size_t size = 0;

	// Add word wrapping
	sSlowchar = wordWrap(sSlowchar);
	size = sSlowchar.size();
	for (int i = 0; i <= size; i++) {
		sleep(nSlowCharSpeed);
		std::cout << sSlowchar[i];
	}

	if (nline == true) {
		std::cout << std::endl;
	}

	// In case a key was pressed while operation was commencing
	clearkeebbuf();

	return;
}

// A function to display an exiting message without typing too much.
void Exiting() {
	colour(YLW, sColourGlobalBack);
	std::cout << "\nExiting...\n";
	colour(sColourGlobal, sColourGlobalBack);
	return;
}

// A function designated for resetting the global colours.
void ResetColour() {

	// Reset all RGB to default
	sColourGlobal = LWHT;
	sColourGlobalBack = BLK;
	// Output reset message
	colour(sColourGlobal, sColourGlobalBack);
	std::cout << "\x1b[" << RESETALL << "m\nColours have been reset to default.\n";

	return;
}

// A function that checks for VT Terminal Sequence support, and enables them if support is there
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
		RED = "255;0;0";
		GRN = "22;198;12";
		YLW = "231;186;0";
		BLU = "0;0;255";
		MAG = "136;23;152";
		CYN = "58;150;221";
		WHT = "242;242;242";

		// Bright colours
		GRAY = "118;118;118";
		LRED = "231;72;86";
		LGRN = "0;255;0";
		LYLW = "255;255;0";
		LBLU = "59;120;255";
		LMAG = "180;0;158";
		LCYN = "97;214;214";
		LWHT = "255;255;255";

		// Reset definitions of colours to new values
		sColourGlobal = LWHT;
		sColourGlobalBack = BLK;

		sColourHighlight = LWHT;
		sColourHighlightBack = BLU;

		sColourTitle = BLK;
		sColourTitleBack = LCYN;

		sColourSubheading = LWHT;
		sColourSubheadingBack = MAG;
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

		// Reset definitions of colours to new values
		sColourGlobal = LWHT;
		sColourGlobalBack = BLK;

		sColourHighlight = LWHT;
		sColourHighlightBack = BLU;

		sColourTitle = BLK;
		sColourTitleBack = LCYN;

		sColourSubheading = LWHT;
		sColourSubheadingBack = MAG;
	}

	return;
}

// Function to manage startup tasks
void ProgramInitialisation() {
	// Set random colours if random colours on startup are enabled
	if (bRandomColoursOnStartup == true) {
		// Can't do without ANSI VT Sequences
		if (bAnsiVTSequences) {
			// Pick random foreground colour
			int nRandForeground = randnum(16, 1);
			ColourForegroundSwitch(&nRandForeground, &sColourGlobalBack, &sColourGlobal);

			// Pick random background colour
			int nRandBackground = randnum(16, 1);
			ColourBackgroundSwitch(&nRandBackground, &sColourGlobalBack, &sColourGlobal);
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
		colour(sColourGlobal, sColourGlobalBack);

		cls();
	}
	else {
		// Keep ANSI VT sequences enabled
		bAnsiVTSequences = true;

		// Set the colours
		ColourTypeSwitch();

		// Clear screen to set screen buffer to black colour
		colour(sColourGlobal, sColourGlobalBack);
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

	// Set window title to 'TerminalAppGen3'
	WindowTitleSet("TerminalApp Gen 3");

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
	for (int i = 0; i < 128; i++) {
		sCommandInputArgs[i] = ' ';
		sStringCommandArgs[i] = " ";
	}

	// Initialise everything else in program
	ProgramInitialisation();

	colour(LBLU, sColourGlobalBack);

	if (bAnsiVTSequences == true) std::cout << "\x1b[" << BLINK << 'm';
	slowcharfn(true, "Welcome to TerminalApp Gen 3!");

	colour(LGRN, sColourGlobalBack);
	std::cout << "\nPress ENTER to begin...\n";
	if (bAnsiVTSequences) std::cout << "\x1b[" << NOBLINK << "m";
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');

	// Help message
	colour(YLW, sColourGlobalBack);
	std::cout << "[Type ";
	colour(LCYN, sColourGlobalBack);
	std::cout << "\"Help\" ";
	colour(YLW, sColourGlobalBack);
	std::cout << "to get all commands.]\n[Type ";
	colour(LCYN, sColourGlobalBack);
	std::cout << "\"Tutorial\"";
	colour(YLW, sColourGlobalBack);
	std::cout << " to get a tutorial on how to use the terminal.]\n";

	// Set colours to default
	colour(sColourGlobal, sColourGlobalBack);

	while (true) {

		// Prompt and get input
		std::cout << "\nCommand: > ";
		colour(LYLW, sColourGlobalBack);
		std::getline(std::cin, sCommandInput);
		colour(sColourGlobal, sColourGlobalBack);

		// Optimisation for no input
		if (sCommandInput == "") {
			continue;
		}
		else {
			// Initialise sCommandInputArgs to make all spaces
			for (int i = 0; i < 128; i++) {
				sCommandInputArgs[i] = ' ';
				sStringCommandArgs[i] = " ";
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
			colour(GRN, sColourGlobalBack);
			std::cout << "\nHave a good day/night!\n";
			colour(RED, sColourGlobalBack);
			slowcharfn(false, "Exiting...\n");
			colour(sColourGlobal, sColourGlobalBack);
			return 0;
		}

		// Copy the rest of the stringstream contents into sCommandArgsBuffer
		std::getline(sCommandInputIn, sCommandArgsBuffer, '\n');

		// Copy new sCommandArgsBuffer string to another string, as it will be modified
		const std::string sCommandArgsBufferRAW = sCommandArgsBuffer + " ";

		/* The following will be based on parsing sCommandArgsBuffer for the actual arguments. */
		// Copy the string arguments into sStringCommandArgs with correct formatting
		sCommandArgsBuffer += " ";
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
								sStringCommandArgs[i] = sCommandArgsBuffer.substr((nDashPos + 2), nSpacePos - (nDashPos + 2));

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
					sStringCommandArgs[i] = sCommandArgsBuffer.substr((nDashPos + 3), nSpacePos - (nDashPos + 3));

					// Erase the found string from the argument buffer to remove it from plain sight from parser
					sCommandArgsBuffer.erase(nDashPos, nSpacePos - nDashPos);

				}

			}

		}

		// Copy the letter after a dash into sCommandInputArgs
		for (size_t i = 0, j = 0; i < sCommandArgsBuffer.length(); i++) {
			if (i > 0) {
				// Character after must not be a space to prevent conflict with string parser 
				if (sCommandArgsBuffer[i - 1] != '-' && sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					sCommandInputArgs[j] = sCommandArgsBuffer[i + 1];
					j++;
				}
			}
			else {
				// This time, just remove the check for sCommandArgsBuffer[i - 1] to prevent OOR exception
				if (sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					sCommandInputArgs[j] = sCommandArgsBuffer[i + 1];
					j++;
				}
			}

		}

		// Finally, call commands function
		Commands(sCommand, sCommandInputArgs, sCommandArgsBufferRAW);

		// Reset all command processing variables to defaults
		// sCommandInputArgs and sStringCommandInputArgs
		for (int i = 0; i < 128; i++) {
			sCommandInputArgs[i] = ' ';
			sStringCommandArgs[i] = " ";
		}
		sCommand = "";
		sCommandArgsBuffer = "";
		sCommandInput = "";
		sCommandInputRAW = "";
	}

	return 0;

}