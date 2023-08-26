
// DEPENDANCIES
void VerbosityDisplay(std::string);
void DirectionsDisplay(std::string);
void colour(std::string, std::string);
void colourHighlight();
void SetCursorPosition(int, int);
void CentreColouredText(std::string, short int);
void cls();

extern std::string sColourGlobal;
extern std::string sColourGlobalBack;
extern bool bDisplayDirections;
extern bool bConsoleBugGCSBI;

//
// TAG3 OptionSelectEngine - Class for OptionSelect function, allows for easy debugging too.
//
class OptionSelectEngine {
public:
	int nSizeOfOptions = 0;
	std::string* sOptions {};

	OptionSelectEngine() {
		// Display only when verbose messages are turned on
		VerbosityDisplay("New OptionSelectEngine Object Created.");
		// Set values to default
		int nSizeOfOptions = 0;
	}

	~OptionSelectEngine() {
		// Display verbose destructor message
		VerbosityDisplay("OptionSelectEngine Object has been destroyed.");
	}

	// OptionSelect - A selection UI that allows for easy arrow-key OR W/S-key navigation.
	// 
	// Pressing ESC leads to returning code -1, and the index of the option when ENTER is pressed is returned otherwise.
	int OptionSelect(std::string sPrompt, std::string sTitle) {
		int nNumberOfOptions = 0;
		int nIndex = 1;
		char nKey = 0;
		int nWindowHeight = 0;
		int nIndexHeight = 0;
		std::string sHighlightBuffer = "";
		CONSOLE_SCREEN_BUFFER_INFO csbiOptionSelect;
		HANDLE hOptionSelect = GetStdHandle(STD_OUTPUT_HANDLE);

		// Count the number of options
		for (int i = 0; i < nSizeOfOptions; i++) {
			if (sOptions[i] != "") nNumberOfOptions++;
		}

		// Output a newline to prevent errors with overwriting cells of text
		std::cout << '\n';
		// Display centred title
		CentreColouredText(sTitle, 1);
		// Display prompt message for selection options
		std::cout << "\n" << sPrompt << "\n\n";

		// Get correct row position into nStartingRow
		GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
		int nStartingRow = csbiOptionSelect.dwCursorPosition.Y;


		// 13 is ascii for ENTER key
		while (nKey != 13) {

			// Get terminal height
			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			nWindowHeight = csbiOptionSelect.srWindow.Bottom - csbiOptionSelect.srWindow.Top;

			/*Check if cursor is on the lowest row of the terminal window
			NOTE: THIS IS A WORKAROUND FOR THE WINDOWS TERMINAL GetConsoleScreenBufferInfo() BUG.
				  THIS MAY ONLY BE TEMPORARY.
			*///////////////////////////////////////////////////////////
			if (bConsoleBugGCSBI == true) {
				if (csbiOptionSelect.dwCursorPosition.Y == nWindowHeight) {
					cls();
					// Display centred title
					CentreColouredText(sTitle, 1);
					// Display prompt message for selection options
					std::cout << "\n" << sPrompt << "\n\n";

					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					nStartingRow = csbiOptionSelect.dwCursorPosition.Y;
				}
			}

			// 80 is ascii for down arrow
			if (nKey == 80 || nKey == 115) nIndex++;
			// 72 is ascii for up arrow
			else if (nKey == 72 || nKey == 119) nIndex--;

			// if statements to prevent overspill of nIndex
			if (nIndex > nNumberOfOptions) nIndex = 1;
			else if (nIndex < 1) nIndex = nNumberOfOptions;

			// 1. Using nIndex, create buffer with >> first, then sOptions[nIndex - 1], then <<
			sHighlightBuffer = ">> " + sOptions[nIndex - 1] + " <<";
			// 2. Get length of sBuffer. Put into nHighlightBuffer
			int nHighlightBuffer = sHighlightBuffer.length();
			// 3. for loop
			for (int i = 0; i < nNumberOfOptions; i++) {
				// Set cursor position
				SetCursorPosition(0, (nStartingRow + i + 1));
				// 4. Measure size of sOptions[i] and make equal number of spaces, then go to the beginning of the line
				std::cout << std::setw(sOptions[i].length() + 6) << std::cout.fill(' ') << '\r'; // + 6 because ">> " and " <<" combined are 6 chars
				// 5. Output option
				if (i == (nIndex - 1)) {
					colourHighlight();
					std::cout << sHighlightBuffer;

					// Put index height into nIndexHeight for ESC keypress
					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					nIndexHeight = csbiOptionSelect.dwCursorPosition.Y;
				}
				else std::cout << sOptions[i];
				// Reset to default colour
				colour(sColourGlobal, sColourGlobalBack);
				std::cout << "\n";
			}
			if (bDisplayDirections) {
				// Add newlines for DirectionsDisplay
				std::cout << "\n\n";
				// Add directions on how to use using DirectionsDisplay()
				DirectionsDisplay("Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit.");
			}

			// while loop to skip next code on wrong input, CPU optimisation
			while (true) {
				// Get input
				nKey = _getch();
				if (nKey == 80 || nKey == 72 || nKey == 119 || nKey == 115 || nKey == 13) {
					break;
				}
				// exit with code -1 if ESC is pressed
				else if (nKey == 27) {
					// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					SetCursorPosition(0, nIndexHeight);
					colour(LWHT, GRAY);
					std::cout << sHighlightBuffer;
					SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

					// Set colour back to default and exit
					colour(sColourGlobal, sColourGlobalBack);
					return -1;
				}
				else continue;
			}

		}

		// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
		GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
		SetCursorPosition(0, nIndexHeight);
		colour(LWHT, GRAY);
		std::cout << sHighlightBuffer;
		SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

		// Set colour back to default and exit
		colour(sColourGlobal, sColourGlobalBack);
		return nIndex;
	}
};