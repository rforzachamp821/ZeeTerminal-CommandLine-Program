//
// OptionSelectEngine.cpp - Contains everything to do with the OptionSelect engine, including its class.
//

std::string NumberToColour(int);

extern ConfigFileSystem ConfigObjMain;
extern LogFileSystem LogFileMain;
extern bool bAnsiVTSequences;

//
// ZT OptionSelectEngine - Class for OptionSelect function, allows for easy debugging too.
//
class OptionSelectEngine 
{
private:
	// Object ID
	int nObjectID;
protected:

	// Directions text to forward to DirectionsDisplay()
	std::string sDirectionsText = "Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit.";

	// The indicator string for options
	const std::string sOptionIndicator = "~| "; 

	// DisplayOptionsIndicator - Displays the options indicator at calltime.
	// Arguments: sColour - The foreground colour to display for the options indicator, in RGB units.
	// Return values: None
	//
	void DisplayOptionsIndicator(std::string sColour) {
		// 1. Set colour
		colour(sColour, ConfigObjMain.sColourGlobalBack);
		// 2. Display indicator
		std::cout << sOptionIndicator;
		// 3. Set colours back to normal and exit
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		return;
	}

	// SimpleOptionSelect - A simple selection UI that allows for easy number-typing input.
	// 
	// Pressing ESC (exit) leads to returning code -1, error returns -2, and the index of the option when input is finished is returned otherwise.
	//
	int SimpleOptionSelect(std::string sPrompt, std::string sTitle) 
	{
		int nInput = 0;
		std::vector<std::string> vsOptionIndicatorColours{};

		// Check if this function is meant to be used
		if (ConfigObjMain.bUseNewOptionSelect == true) {
			// Exit - not really an error.
			return -1;
		}

		// Initialise option indicator colour vector
		for (int i = 0; i < nSizeOfOptions; i++) {
			// Calculate another random colour
			vsOptionIndicatorColours.push_back(NumberToColour(RandNum(16, 1)));
		}

		// Output a newline to prevent errors with overwriting cells of text
		std::cout << '\n';

		// Display centred title
		CentreColouredText(sTitle, 1);

		// Display prompt message for selection options with underline
		std::cout << "\n";
		std::cout << wordWrap(sPrompt) << "\n\n";

		// Render options
		for (int i = 0; i < nSizeOfOptions; i++) 
		{
			// Set brackets to option indicator colour
			colour(vsOptionIndicatorColours[i], ConfigObjMain.sColourGlobalBack);
			std::cout << '[';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << i + 1;

			// Set brackets to option indicator colour
			colour(vsOptionIndicatorColours[i], ConfigObjMain.sColourGlobalBack);
			std::cout << "] ";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << sOptions[i] << "\n";
		}

		std::cout << '\n';
		while (true) {
			// Input
			nInput = NumInputi("Please input your desired option number (input 0 to exit): > ");

			if (nInput == 0) {
				return -1;
			}
			else if (nInput < 1 || nInput > nSizeOfOptions) {
				colour(RED, ConfigObjMain.sColourGlobalBack);
				std::cerr << wordWrap("Sorry, but your input is below 1 or above " + std::to_string(nSizeOfOptions) + ".\nThere is no option associated with the inputted option number. Please try again.\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			else break;
		}

		return nInput;
	}

public:

	int nSizeOfOptions = 0;
	std::string* sOptions {};

	OptionSelectEngine() {
		static int nStaticID = 10000;
		// Wrap-around to prevent overflow
		if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
		nObjectID = ++nStaticID;

		// Display only when verbose messages are turned on
		VerbosityDisplay("New OptionSelectEngine Object Created.\n", nObjectID);

		// Set values to default
		nSizeOfOptions = 0;
		sDirectionsText = "Press the 'W' key or up arrow key to move up.\nPress the 'S' key or down arrow key to move down.\nPress ENTER to continue with selection, or ESC to exit.";
	}

	~OptionSelectEngine() {
		// Display verbose destructor message
		VerbosityDisplay("OptionSelectEngine Object has been destroyed.\n", nObjectID);
	}

	// SetDirectionsText - Sets the direction text to a custom text, and replaces the default text.
	//                   - Because there is a default directions text, this function is optional to call.
	// Arguments: sText - The text to replace the default direction text with.
	// Return values: None
	//
	void SetDirectionsText(std::string sText) 
	{
		// Set directions text
		sDirectionsText = sText;

		return;
	}

	// OptionSelect - A selection UI that allows for easy arrow-key OR W/S-key navigation.
	// 
	// Pressing ESC (exit) leads to returning code -1, error returns -2, and the index of the option when ENTER is pressed is returned otherwise.
	//
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
		std::vector<std::string> sOptionIndicatorColours; // indicating colour for each option.

		// Use the simple optionselect engine mode.
		if (ConfigObjMain.bUseNewOptionSelect == false) {
			return SimpleOptionSelect(sPrompt, sTitle);
		}

		// Count the number of options
		for (int i = 0; i < nSizeOfOptions; i++) {
			if (sOptions[i] != "") nNumberOfOptions++;
		}

		// Cannot continue with 0 options
		if (nNumberOfOptions < 1) {
			VerbosityDisplay("In OptionSelectEngine::OptionSelect(): ERROR - Engine recieved sOptions with 0 valid members. Engine cannot operate with 0 options as crash may occur. Not enough information to display with stability. Exiting.\n", nObjectID);
			return -2; // error
		}

		// Initialise option indicator colour vector
		for (int i = 0; i < nSizeOfOptions; i++) {
			// Calculate another random colour
			sOptionIndicatorColours.push_back(NumberToColour(RandNum(16, 1)));
		}
		 
		// Output a newline to prevent errors with overwriting cells of text
		std::cout << '\n';

		// Check if cursor is exceeding the buffer height - if so, clear screen
		if (CheckIfCursorExceedScreenBufferHeight()) {
			if (bAnsiVTSequences) {
				std::cout << "\n\033[2J\033[1;1H";
			}
			else cls();
		}

		// Display centred title
		CentreColouredText(sTitle, 1);

		// Display prompt message for selection options with underline
		std::cout << "\n";
		std::cout << wordWrap(sPrompt) << "\n";

		// Get correct row position into nStartingRow
		GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
		int nStartingRow = csbiOptionSelect.dwCursorPosition.Y;

		// Log that session is starting
		LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session starting with " + std::to_string(nNumberOfOptions) + " options and prompt {\"" + sPrompt + "\"}.", 4, nObjectID);

		// Reiteration boolean
		bool bReiterated = false;
		int nIndexIncrease = 3; // 0 for decrease, 1 for increase, 2 for starting position, 3 for ending position, 4 for not set

		while (true) {

			// Get terminal height
			GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
			nWindowHeight = csbiOptionSelect.srWindow.Bottom - csbiOptionSelect.srWindow.Top;
			nWindowHeight = csbiOptionSelect.dwSize.Y - 1;

			/*Check if cursor is on the lowest row of the terminal screen buffer
			NOTE: THIS IS A WORKAROUND FOR THE WINDOWS TERMINAL GetConsoleScreenBufferInfo() AND SetConsoleCursorPosition() BUG.
				  THIS MAY ONLY BE TEMPORARY.
			*///////////////////////////////////////////////////////////
			if (CheckIfCursorExceedScreenBufferHeight()) {
				if (bAnsiVTSequences) {
					// Alert user that above selection has been duplicated below
					colour(BLK, YLW);
					std::cout << wordWrap("Please note that the above OptionSelect session has been duplicated below, to work around the Windows Terminal #14774 bug.");
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

					std::cout << "\n\033[2J\033[1;1H";
				}
				else {
					cls();
				}

				// Display centred title
				CentreColouredText(sTitle, 1);

				// Display prompt message for selection options with underline
				std::cout << "\n";
				std::cout << wordWrap(sPrompt) << "\n";

				GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
				nStartingRow = csbiOptionSelect.dwCursorPosition.Y;

				// Set bReiterated to false to tell the next while loop to redraw options
				bReiterated = false;
			}

			// 80 is ascii for down arrow
			bool bIndexIncreaseWasSet = false;
			if (nKey == 80 || nKey == 115) {
				nIndex++;
				nIndexIncrease = 1;
				bIndexIncreaseWasSet = true;
			}
			// 72 is ascii for up arrow
			else if (nKey == 72 || nKey == 119) {
				nIndex--;
				nIndexIncrease = 0;
				bIndexIncreaseWasSet = true;
			}

			// if statements to prevent overspill of nIndex
			if (nIndex > nNumberOfOptions) {
				nIndex = 1;
				nIndexIncrease = 2;
				bIndexIncreaseWasSet = true;
			}
			else if (nIndex < 1) {
				nIndex = nNumberOfOptions;
				nIndexIncrease = 3;
				bIndexIncreaseWasSet = true;
			}

			// Check if nIndex was set; if not, set it to 4 (4 means not set)
			if (!bIndexIncreaseWasSet) {
				nIndexIncrease = 4;
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
						// 4. Measure size of sOptions[i] and output equal number of spaces, then go to the beginning of the line
						std::cout << std::setw(sOptions[i].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ') << '\r'; // + 6 because ">> " and " <<" combined are 6 chars
					}

					// 5. Output option
					if (i == (nIndex - 1)) {
						DisplayOptionsIndicator(sOptionIndicatorColours[i]);
						colourHighlight();
						std::cout << sHighlightBuffer;

						// Put index height into nIndexHeight for ESC keypress and nIndex-only redraw
						GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
						nIndexHeight = csbiOptionSelect.dwCursorPosition.Y;
					}
					else {
						DisplayOptionsIndicator(sOptionIndicatorColours[i]);
						std::cout << sOptions[i];
					}

					// Reset to default colour
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					std::cout << "\n";
				}

				if (ConfigObjMain.bDisplayDirections) {
					// Add newlines for DirectionsDisplay
					std::cout << "\n\n";

					// Add directions on how to use using DirectionsDisplay()
					DirectionsDisplay(sDirectionsText);
				}

			}
			else // Only draw the new index option after first draw - CPU optimisation, reduces flickering
			{
				// 1. Go to index highlight height
				SetCursorPosition(0, nIndexHeight);

				// 2. Output spaces depending on previous nIndex option
				if (nIndexIncrease == 1) {
					std::cout << std::setw(sOptions[nIndex - 2].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ') << '\r';

					DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 2]);
					std::cout << sOptions[nIndex - 2];
				}
				else if (nIndexIncrease == 0) {
					std::cout << std::setw(sOptions[nIndex].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ') << '\r';

					DisplayOptionsIndicator(sOptionIndicatorColours[nIndex]);
					std::cout << sOptions[nIndex];
				}
				else if (nIndexIncrease == 2) {
					std::cout << std::setw(sOptions[nNumberOfOptions - 1].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ') << '\r';

					DisplayOptionsIndicator(sOptionIndicatorColours[nNumberOfOptions - 1]);
					std::cout << sOptions[nNumberOfOptions - 1];
				}
				else if (nIndexIncrease == 3) {
					std::cout << std::setw(sOptions[0].length() + 6 + sOptionIndicator.length()) << std::cout.fill(' ') << '\r';
					
					DisplayOptionsIndicator(sOptionIndicatorColours[0]);
					std::cout << sOptions[0];
				}
					
				// 3. Go to nIndex + nStartingRow
				SetCursorPosition(0, nIndex + nStartingRow);

				// 4. Output new sHighlightBuffer and sOptionsIndicator
				DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
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
					DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
					colour(LWHT, GRAY);
					std::cout << sHighlightBuffer;
					SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

					// Log that session is ending
					LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session manually exited with index " + std::to_string(nIndex) + " (" + sOptions[nIndex - 1] + "). Last key pressed was ASCII code " + std::to_string(nKey) + ".", 4, nObjectID);

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
					// Break if ESC pressed immediately, without any reiterations - only if console cursor exceeds screen buffer size (or windows terminal bug #14774)
					if (bReiterated == false && CheckIfCursorExceedScreenBufferHeight()) {
						break;
					}

					bIsEnter = true;
				}
				// exit with code -1 if ESC is pressed
				else if (nKey == 27) {

					// Break if ESC pressed immediately, without any reiterations - only if console cursor exceeds screen buffer size (or windows terminal bug #14774)
					if (bReiterated == false && CheckIfCursorExceedScreenBufferHeight()) {
						break;
					}

					// Darken the index highlight to indicate that this OptionSelect session isn't being used anymore
					GetConsoleScreenBufferInfo(hOptionSelect, &csbiOptionSelect);
					SetCursorPosition(0, nIndexHeight);
					DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
					colour(LWHT, GRAY);
					std::cout << sHighlightBuffer;
					SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

					// Log that session is ending
					LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session manually exited with index " + std::to_string(nIndex) + " (" + sOptions[nIndex - 1] + "). Last key pressed was ASCII code " + std::to_string(nKey) + ".", 4, nObjectID);

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
		DisplayOptionsIndicator(sOptionIndicatorColours[nIndex - 1]);
		colour(LWHT, GRAY);
		std::cout << sHighlightBuffer;
		SetCursorPosition(csbiOptionSelect.dwCursorPosition.X, csbiOptionSelect.dwCursorPosition.Y);

		// Log that session is ending
		LogFileMain.AddLogLine("In OptionSelectEngine::OptionSelect(): OptionSelect Session ended with index " + std::to_string(nIndex) + " (" + sOptions[nIndex - 1] + "). Last key pressed was ASCII code " + std::to_string(nKey) + ".", 4, nObjectID);

		// Set colour back to default and exit
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		return nIndex;
	}

};