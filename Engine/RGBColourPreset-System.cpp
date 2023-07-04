void VerbosityDisplay(std::string);

class RGBColourPresetSystem {
public:
	std::string sColourPresetForeground =	"255;255;255";
	std::string sColourPresetBackground =	"0;0;0";

	std::string sPresetName =				"EMPTY_PRESET";
	bool bSetByUser =						false;

	RGBColourPresetSystem() {
		VerbosityDisplay("RGBColourPreset Object Created.");
		// Initialise values to default
		sColourPresetForeground = "255;255;255";
		sColourPresetBackground = "0;0;0";
		sPresetName = "EMPTY_PRESET";
		bSetByUser = false;
	}

	~RGBColourPresetSystem() {
		// Display message that object destroyed
		VerbosityDisplay("RGBColourPreset Object Destroyed.");
	}
};