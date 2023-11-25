void VerbosityDisplay(std::string);

extern bool bAnsiVTSequences;

class RGBColourPresetSystem {
public:
	std::string sColourPresetForeground = LWHT;
	std::string sColourPresetBackground = BLK;

	std::string sPresetName = "EMPTY_PRESET";
	bool		bSetByUser = false;

	RGBColourPresetSystem() {
		VerbosityDisplay("RGBColourPreset Object Created.\n");
		// Initialise values to default
		sColourPresetForeground = LWHT;
		sColourPresetBackground = BLK;
		sPresetName = "EMPTY_PRESET";
		bSetByUser = false;
	}

	~RGBColourPresetSystem() {
		// Display message that object destroyed
		VerbosityDisplay("RGBColourPreset Object Destroyed.\n");
	}

	// CheckIfAnsiPreset - Checks if the colours in the preset are in the ANSI RGB format.
	// Arguments: None
	// Return values: TRUE or 1 for ANSI RGB preset, FALSE or 0 for WIN32 16-colour preset.
	//
	bool CheckIfAnsiPreset() {
		if (sColourPresetForeground.find(';') != std::string::npos && sColourPresetBackground.find(';') != std::string::npos) {
			return true;
		}
		else return false;
	}
};