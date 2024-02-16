// A function to check for a specific bug affecting CONSOLE_SCREEN_BUFFER_INFO::dwCursorPosition
// positioning reports, in the new Windows Terminal and OpenConsole.exe.
bool ConsoleWTBugCheck()
{
	// Firstly, clear screen
	cls();

	// Get console size
	HANDLE hTest = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiTest;
	GetConsoleScreenBufferInfo(hTest, &csbiTest);
	int nConsoleHeight = csbiTest.srWindow.Bottom - csbiTest.srWindow.Top;

	// Spam enters until a few more than console bottom
	std::cout << std::string('\n', nConsoleHeight + 1);

	// Get the console cursor position after that
	GetConsoleScreenBufferInfo(hTest, &csbiTest);
	int nVerticalCPosition = csbiTest.dwCursorPosition.Y;
	cls();

	if (nVerticalCPosition <= nConsoleHeight) {
		return true; // THIS IS THE WINDOWS TERMINAL NEW WINDOW
	}
	else {
		return false; // THIS IS THE OLD CONHOST WINDOW
	}
}