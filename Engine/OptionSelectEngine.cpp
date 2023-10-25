
// DEPENDANCIES
void VerbosityDisplay(std::string);
void DirectionsDisplay(std::string);
void colour(std::string, std::string);
void colourHighlight();
void SetCursorPosition(int, int);
void CentreColouredText(std::string, short int);
void cls();


extern ConfigFileSystem ConfigObjMain;
extern bool bConsoleBugGCSBI;

//
// ZT OptionSelectEngine - Class for OptionSelect function, allows for easy debugging too.
//
class OptionSelectEngine {
public:
	int nSizeOfOptions = 0;
	std::string* sOptions {};

	OptionSelectEngine() {
		// Display only when verbose messages are turned on
		VerbosityDisplay("New OptionSelectEngine Object Created.\n");
		// Set values to default
		int nSizeOfOptions = 0;
	}

	~OptionSelectEngine() {
		// Display verbose destructor message
		VerbosityDisplay("OptionSelectEngine Object has been destroyed.\n");
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
		int nEndingCursorHeight = 0;
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
		bool bReiterated = false;
		int nIndexIncrease = 3; // 0 for decrease, 1 for increase, 2 for starting position, 3 for ending position
		while (true) {

			// Get terminal height
			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			nWindowHeight = csbiOptionSelect.srWindow.Bottom - csbiOptionSelect.srWindow.Top;

			/*Check if cursor is on the lowest row of the terminal window
			NOTE: THIS IS A WORKAROUND FOR THE WINDOWS TERMINAL GetConsoleScreenBufferInfo() BUG.
				  THIS MAY ONLY BE TEMPORARY.
			*///////////////////////////////////////////////////////////
			if (bConsoleBugGCSBI == true) {
				if (csbiOptionSelect.dwCursorPosition.Y == nWindowHeight && bReiterated == true) {
					cls();
					// Display centred title
					CentreColouredText(sTitle, 1);
					// Display prompt message for selection options
					std::cout << "\n" << sPrompt << "\n\n";

					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					nStartingRow = csbiOptionSelect.dwCursorPosition.Y;

					// Set bReiterated to false to tell the next while loop to redraw options
					bReiterated = false;
				}
			}

			// 80 is ascii for down arrow
			if (nKey == 80 || nKey == 115) {
				nIndex++;
				nIndexIncrease = 1;
			}
			// 72 is ascii for up arrow
			else if (nKey == 72 || nKey == 119) {
				nIndex--;
				nIndexIncrease = 0;
			}

			// if statements to prevent overspill of nIndex
			if (nIndex > nNumberOfOptions) {
				nIndex = 1;
				nIndexIncrease = 2;
			}
			else if (nIndex < 1) {
				nIndex = nNumberOfOptions;
				nIndexIncrease = 3;
			}

			// 1. Using nIndex, create buffer with >> first, then sOptions[nIndex - 1], then <<
			sHighlightBuffer = ">> " + sOptions[nIndex - 1] + " <<";

			// 2. Get length of sBuffer. Put into nHighlightBuffer
			size_t nHighlightBuffer = sHighlightBuffer.length();

			// Only redraw options on first load - CPU optimisation, reduces flickering
			if (bReiterated == false) 
			{			
				// 3. for loop
				for (int i = 0; i < nNumberOfOptions; i++) {
					// Set cursor position
					SetCursorPosition(0, (nStartingRow + i + 1));

					// Mitigation for a terminal colour bug on older-style Windows terminals (specifically Conhost.exe)
					if (i <= 0) {
						GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
						std::cout << std::setw(csbiOptionSelect.srWindow.Right - csbiOptionSelect.srWindow.Left) << std::cout.fill(' ') << '\r';
					}
					else {
						// 4. Measure size of sOptions[i] and make equal number of spaces, then go to the beginning of the line
						std::cout << std::setw(sOptions[i].length() + 6) << std::cout.fill(' ') << '\r'; // + 6 because ">> " and " <<" combined are 6 chars
					}

					// 5. Output option
					if (i == (nIndex - 1)) {
						colourHighlight();
						std::cout << sHighlightBuffer;

						// Put index height into nIndexHeight for ESC keypress and nIndex-only redraw
						GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
						nIndexHeight = csbiOptionSelect.dwCursorPosition.Y;
					}
					else std::cout << sOptions[i];

					// Reset to default colour
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					std::cout << "\n";
				}

				if (ConfigObjMain.bDisplayDirections) {
					// Add newlines for DirectionsDisplay
					std::cout << "\n\n";

					// Add directions on how to use using DirectionsDisplay()
					DirectionsDisplay("Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit.");
				}

			}
			else // Only draw the new index option after first draw - CPU optimisation, reduces flickering
			{
				// 1. Go to index highlight height
				SetCursorPosition(0, nIndexHeight);

				// 2. Output spaces depending on previous nIndex option
				if (nIndexIncrease == 1)
					std::cout << std::setw(sOptions[nIndex - 2].length() + 6) << std::cout.fill(' ') << '\r' << sOptions[nIndex - 2];
				else if (nIndexIncrease == 0) {
					std::cout << std::setw(sOptions[nIndex].length() + 6) << std::cout.fill(' ') << '\r' << sOptions[nIndex];
				}
				else if (nIndexIncrease == 2) {
					std::cout << std::setw(sOptions[nNumberOfOptions - 1].length() + 6) << std::cout.fill(' ') << '\r' << sOptions[nNumberOfOptions - 1];
				}
				else if (nIndexIncrease == 3) {
					std::cout << std::setw(sOptions[0].length() + 6) << std::cout.fill(' ') << '\r' << sOptions[0];
				}
					
				// 3. Go to nIndex + nStartingRow
				SetCursorPosition(0, nIndex + nStartingRow);

				// 4. Output new sHighlightBuffer
				colourHighlight();
				std::cout << sHighlightBuffer;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// 5. Put index height into nIndexHeight for ESC keypress and next nIndex-only redraw
				GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
				nIndexHeight = csbiOptionSelect.dwCursorPosition.Y;

				// 6. Put cursor on the ending cursor height to make it work like normal whole-screen redraw
				SetCursorPosition(0, nEndingCursorHeight);
			}


			bool bIsEnter = false;
			// While loop to skip next code on wrong input, CPU optimisation
			while (true) {
				// Set nEndingCursorHeight to cursor height at this point
				GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
				nEndingCursorHeight = csbiOptionSelect.dwCursorPosition.Y;

				// Exit if ESC was pressed (from previous non-reiteration)
				if (nKey == 27) {
					// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					SetCursorPosition(0, nIndexHeight);
					colour(LWHT, GRAY);
					std::cout << sHighlightBuffer;
					SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

					// Set colour back to default and exit
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					return -1;
				}

				// Exit if ENTER was pressed (from previous non-iteration around the ms console bug)
				else if (nKey == 13) {
					bIsEnter = true;

					break;
				}
				

				// Get input
				nKey = _getch();
				if (nKey == 80 || nKey == 72 || nKey == 119 || nKey == 115) {
					break;
				}
				// Enter key
				else if (nKey == 13) {
					// Break if ESC pressed immediately, without any reiterations - for consoles with windows terminal bug #14774
					if (bReiterated == false && bConsoleBugGCSBI == true) break;

					bIsEnter = true;
				}
				// exit with code -1 if ESC is pressed
				else if (nKey == 27) {

					// Break if ESC pressed immediately, without any reiterations - for consoles with windows terminal bug #14774
					if (bReiterated == false && bConsoleBugGCSBI == true) break;

					// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					SetCursorPosition(0, nIndexHeight);
					colour(LWHT, GRAY);
					std::cout << sHighlightBuffer;
					SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

					// Set colour back to default and exit
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					return -1;
				}
				else continue;
			}

			// Exit on enter keypress
			if (bIsEnter == true) break;

			bReiterated = true;
		}

		// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
		GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
		SetCursorPosition(0, nIndexHeight);
		colour(LWHT, GRAY);
		std::cout << sHighlightBuffer;
		SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

		// Set colour back to default and exit
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return nIndex;
	}

};