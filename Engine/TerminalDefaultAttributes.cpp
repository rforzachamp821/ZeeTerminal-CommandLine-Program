//
// TerminalDefaultAttributes.cpp - File containing the TerminalDefaultAttributes class.
//


// TerminalDefaultAttributes - Class containing functions and structures that are able to store default terminal attributes and values.
//
class TerminalDefaultAttributes {
private:
	CONSOLE_SCREEN_BUFFER_INFO	csbiBufferAttribBeforeExec; // Object that describes what screen buffer attributes were set before program execution
	DWORD						dwConsoleModeBeforeExec; // Variable that contains all original console mode attributes before execution
	CONSOLE_CURSOR_INFO			cciCursorAttribBeforeExec; // Object that describes what cursor attributes were set before program execution

	// Function to set most terminal attributes to how they were before after ZeeTerminal execution
	inline void ResetTerminalAttributesToDefault() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Set console text attributes to default
		SetConsoleTextAttribute(hConsole, csbiBufferAttribBeforeExec.wAttributes);
		// Set console mode to default
		SetConsoleMode(hConsole, dwConsoleModeBeforeExec);
		// Set console cursor attributes to default
		SetConsoleCursorInfo(hConsole, &cciCursorAttribBeforeExec);
	}

	inline void InitialiseStructures() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Initialise all structures early
		GetConsoleMode(hConsole, &dwConsoleModeBeforeExec);
		GetConsoleScreenBufferInfo(hConsole, &csbiBufferAttribBeforeExec);
		GetConsoleCursorInfo(hConsole, &cciCursorAttribBeforeExec);
	}

public:

	// Constructor
	TerminalDefaultAttributes() {
		// Initialise all structures and variables, as a 'default' scheme.
		InitialiseStructures();
	}

	// Destructor
	~TerminalDefaultAttributes() {
		// As the name of this class suggests, reset terminal attributes to defaults.
		ResetTerminalAttributesToDefault();
	}

};
