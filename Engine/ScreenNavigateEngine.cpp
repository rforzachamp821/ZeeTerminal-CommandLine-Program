
// DEPENDANCIES
void DirectionsDisplay(std::string);
void VerbosityDisplay(std::string);
void CentreColouredText(std::string, short int);
std::string CentreText(std::string);
void cls();
void colour(std::string, std::string);
void colourTitle();

extern std::string sColourGlobal;
extern std::string sColourGlobalBack;


//
// TAG3 ScreenNavigateEngine - Class for ScreenNavigate function, allows for easy debugging too.
//
class ScreenNavigateEngine {
public:
	int nSizeOfScreens = 0;
	std::string* sScreens {};

	ScreenNavigateEngine() {
		// Display verbosity message if corresponding boolean allows it
		VerbosityDisplay("New ScreenNavigateEngine Object Created.");
		// Set values to default
		nSizeOfScreens = 0;
	}

	~ScreenNavigateEngine() {
		// Display destructor verbose message
		VerbosityDisplay("ScreenNavigateEngine Object has been destroyed.");
	}

	// ScreenNavigate - An interactive display UI that allows for quick and easy screen switching in commands, using easy arrow-key OR A/D-key navigation.
	//
	// Pressing ESC leads to returning to previous command. Nothing else is used- this is just an interactive display UI.
	void ScreenNavigate(std::string sTitle = "___TITLE PLACEHOLDER___") {
		int nNumberOfScreens = 0;
		int nIndex = 1;
		int nKey = 0;

		// Count the number of screens
		for (int i = 0; i < nSizeOfScreens; i++) {
			if (sScreens[i] != "") nNumberOfScreens++;
		}

		// 27 is ascii for ESC key
		while (nKey != 27) {

			// 77 is ascii for right arrow
			if (nKey == 100 || nKey == 77) {
				nIndex++;
			}

			// 75 is ascii for left arrow
			if (nKey == 97 || nKey == 75) {
				nIndex--;
			}

			// if statements to prevent overspill of nIndex
			if (nIndex > nNumberOfScreens) nIndex = 1;
			else if (nIndex < 1) nIndex = nNumberOfScreens;

			// Clear screen for space for next screen
			cls();

			// Output title of all combined screens, centred
			CentreColouredText(sTitle, 1);
			colour(sColourGlobal, sColourGlobalBack);
			std::cout << std::endl;
			// Output directions of use using DirectionsDisplay()
			DirectionsDisplay("Press the 'A' key or left arrow key to move left.\nPress the 'D' key or right arrow key to move right.\nPress ESC to exit.\n\n");
			// Output screen number out of total screen number
			std::string sPageNum = "~~PAGE NUMBER: " + std::to_string(nIndex) + "/" + std::to_string(nNumberOfScreens) + "~~\n";
			CentreColouredText(sPageNum, 2);
			// Output correct screen
			colour(sColourGlobal, sColourGlobalBack);
			std::cout << sScreens[nIndex - 1] << std::endl;

			// while loop to skip next code on wrong input, optimisation
			while (true) {
				// Get input
				nKey = _getch();
				if (nKey == 77 || nKey == 75 || nKey == 97 || nKey == 100) {
					break;
				}
				// exit if ESC is pressed
				else if (nKey == 27) {
					return;
				}
				else continue;
			}
		}

		// Clear screen before leaving
		cls();

		return;
	}
};