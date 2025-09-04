#pragma once

//
// ConfigFile-System.h - Interface for the configuration file system of ZeeTerminal.
//
#include "../../Core/ZTFormattingDefinitions.h"
#include <string>


//
// ConfigFileSystem - Centres and manages the configuration file system of ZeeTerminal.
//
class ConfigFileSystem
{
private:
	// Object ID
	int nObjectID;

protected:

	const std::string sConfigFileDefaultLocation = "ZT_Config.ini";
	bool bNewFileMade = false;
	std::string sConfigFileContents = "";

	// GetFileContents - Safely gets final, complete file contents as a string by updating it first before returning it.
	// No arguments are accepted.
	// Return values: Contents that should be in file, as an std::string.
	//
	std::string UpdateConfigContents();

public:

	// Settings Variables/Switches
	//
	bool bDisplayDirections = true;
	bool bDisplayVerboseMessages = false;
	bool bRandomColoursOnStartup = false;
	bool bShowCursor = true;
	bool bWordWrapToggle = true;
	bool bCursorBlink = true;
	bool bTermCustomThemeSupport = false;
	bool bAutoReadableContrast = true;
	bool bAnsiVTSequences = true;
	bool bUseNewOptionSelect = true;

	// LogFile System Settings
	bool bEnableLogging = false;
	bool bVerboseMessageLogging = true;
	bool bUserSpaceErrorLogging = false;
	bool bCommandInputInfoLogging = true;
	bool bUserInputInfoLogging = false;

	// CarDodge Game Settings
	int nCarDodgeCarTurningSpeed = 4; // chars the car will move by - cannot be more than 10, lower than 1
	int nCarDodgeGameStartupCar = 1; // Value can be from 1 to 6 (number on the menu)
	std::string sCarDodgeGameplayColourFore = LWHT; // Only affects car colours
	std::string sCarDodgeGameplayColourBack = BLK; // Only affects game background colour, borders aren't affected

	// Guess The Number Game Settings
	std::string sGTNGameplayColourFore = LWHT;
	std::string sGTNGameplayColourBack = CYN;

	// Guess The Number Extreme Game Settings
	std::string sGTNEGameplayColourFore = LWHT;
	std::string sGTNEGameplayColourBack = MAG;

	long long int nSlowCharSpeed = 32;
	long long int nCursorShape = 5; // TYPES are: block blinking (1), block steady (2), underline blinking (3), underline steady (4), bar blinking (5), bar steady (6)

	std::string sColourGlobal = LWHT;
	std::string sColourGlobalBack = BLK;

	std::string sColourHighlight = LWHT;
	std::string sColourHighlightBack = BLU;

	std::string sColourTitle = BLK;
	std::string sColourTitleBack = LCYN;

	std::string sColourSubheading = LWHT;
	std::string sColourSubheadingBack = MAG;

	// Configuration File Location
	std::string sConfigFileUserLocation = "ZT_Config.ini";

	// Constructor
	ConfigFileSystem();

	// Destructor
	~ConfigFileSystem();

	// CreateConfigFile - Creates a config file safely, using user-defined location and default location as fallback.
	// No arguments are accepted.
	// Return values are TRUE for success, and FALSE for fail.
	//
	bool CreateConfigFile();

	// WriteConfigFile - Writes to a user-defined or default configuration file, from all saved settings in object memory.
	// No arguments are accepted.
	// Return values are TRUE for success. and FALSE for fail.
	//
	bool WriteConfigFile();

	// ReadConfigFile - Attempts to read from a user-defined or the default configuration file, and loads contents into memory.
	// No arguments are accepted.
	// Return values are TRUE for success, and FALSE for fail.
	//
	bool ReadConfigFile();

	// GetConfigObjectContents - Returns object settings contents.
	// No arguments are accepted.
	// Return value: std::string, for the object contents.
	//
	inline std::string GetConfigObjectContents() {
		UpdateConfigContents();
		return sConfigFileContents;
	}

	// GetConfigFileContents - Returns configuration file contents.
	// No arguments are accepted.
	// Return value: std::string, for the file contents.
	//
	std::string GetConfigFileContents();

	// GetFileAgeInfo - Checks if a new file was made on object declaration, based on the bNewFileMade boolean variable.
	// No arguments are accepted.
	// Return values: TRUE or 1 for a new file made, FALSE or 0 for existing file discovered already.
	//
	inline bool GetFileAgeInfo() {
		return bNewFileMade;
	}

};
