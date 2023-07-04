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
	std::cout << "THIS IS THE WINDOWS TERMINAL NEW WINDOW\n";
}
else std::cout << "THIS IS THE OLD CONHOST WINDOW\n";
return 0;