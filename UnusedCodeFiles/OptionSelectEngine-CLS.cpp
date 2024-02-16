
// DEPENDANCIES
void VerbosityDisplay(std::string);
void DirectionsDisplay(std::string);
void colour(int, int);
void colourHighlight();
void SetCursorPosition(int, int);
void CentreColouredText(std::string, short int);

extern std::string sColourGlobal;
extern bool bDisplayDirections;

//
// ZeeTerminal OptionSelectEngine - Class for OptionSelect function, allows for easy debugging too.
//
class OptionSelectEngineCLS {
public:
	int nSizeOfOptions = 0;
	std::string* sOptions {};
	std::string sTitle;

	OptionSelectEngineCLS() {
		// Display only when verbose messages are turned on
		VerbosityDisplay("New OptionSelectEngine Object Created.");
		// Set values to default
		int nSizeOfOptions = 0;
	}

	// OptionSelect - A selection UI that allows for easy arrow-key OR W/S-key navigation.
	// 
	// Pressing ESC leads to returning code -1, and the index of the option when ENTER is pressed is returned otherwise.
	int OptionSelect(std::string sTitle, std::string sPrompt) {
		int nNumberOfOptions = 0;
		int nIndex = 1;
		char nKey = 0;
		int nRowSize = 0;

		// Count the number of options
		for (int i = 0; i < nSizeOfOptions; i++) {
			if (sOptions[i] != "") nNumberOfOptions++;
		}


		// 13 is ascii for ENTER key
		while (nKey != 13) {

			// cls for next iteration
			cls();

			// 80 is ascii for down arrow
			if (nKey == 80 || nKey == 115) nIndex++;
			// 72 is ascii for up arrow
			else if (nKey == 72 || nKey == 119) nIndex--;

			// if statements to prevent overspill of nIndex
			if (nIndex > nNumberOfOptions) nIndex = 1;
			else if (nIndex < 1) nIndex = nNumberOfOptions;

			// Output a newline to prevent errors with overwriting cells of text
			std::cout << '\n';
			// Display title, centred with colour
			CentreColouredText(sTitle, 1);
			// Display prompt message for selection options
			std::cout << "\n\n" << sPrompt << "\n\n";

			// 1. Using nIndex, create buffer with >> first, then sOptions[nIndex], then <<
			std::string sHighlightBuffer = ">> " + sOptions[(nIndex - 1)] + " <<";
			// 2. for loop
			for (int i = 0; i < nNumberOfOptions; i++) {
				// 3. Output option
				if (i == (nIndex - 1)) {
					colourHighlight();
					std::cout << sHighlightBuffer;
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

			// while loop to skip next code on wrong input, optimisation
			while (true) {
				// Get input
				nKey = _getch();
				if (nKey == 80 || nKey == 72 || nKey == 119 || nKey == 115 || nKey == 13) {
					break;
				}
				// exit with code -1 if ESC is pressed
				else if (nKey == 27) {
					colour(sColourGlobal, sColourGlobalBack);
					return -1;
				}
				else continue;
			}

		}
		// Set colour back to default and exit
		colour(sColourGlobal, sColourGlobalBack);
		return nIndex;
	}
};