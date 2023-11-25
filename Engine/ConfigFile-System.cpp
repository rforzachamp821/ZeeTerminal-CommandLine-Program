
void VerbosityDisplay(std::string);
void UserErrorDisplay(std::string);
bool isNumberi(const std::string);
bool isNumberll(const std::string);

extern RGBColourPresetSystem RGBPreset[3];

//
// ConfigFileSystem - Centres and manages the configuration file system of ZeeTerminal.
//
class ConfigFileSystem 
{

protected:

	const std::string sConfigFileDefaultLocation = "ZT_Config.ini";
	bool bNewFileMade = false;
	std::string sConfigFileContents = "";

	// GetFileContents - Safely gets final, complete file contents as a string by updating it first before returning it.
	// No arguments are accepted.
	// Return values: Contents that should be in file, as an std::string.
	//
	std::string UpdateConfigContents() 
	{
		// Update file contents
		//
		sConfigFileContents = "# __ZeeTerminal Configuration File__\n# Editing this file is not recommended unless you are an advanced user.\n# Modify settings from the 'settings' command instead, to prevent crashes and unexpected behaviour.\n\n"
			"# Boolean settings switches\n#\n"
			"bDisplayDirections=" + std::to_string(bDisplayDirections) + "\n"
			+ "bDisplayVerboseMessages=" + std::to_string(bDisplayVerboseMessages) + "\n"
			+ "bRandomColoursOnStartup=" + std::to_string(bRandomColoursOnStartup) + "\n"
			+ "bShowCursor=" + std::to_string(bShowCursor) + "\n"
			+ "bWordWrapToggle=" + std::to_string(bWordWrapToggle) + "\n"
			+ "bCursorBlink=" + std::to_string(bCursorBlink) + "\n"
			+ "bTermCustomThemeSupport=" + std::to_string(bTermCustomThemeSupport) + "\n"
			+ "bAutoReadableContrast=" + std::to_string(bAutoReadableContrast) + "\n"
			+ "bAnsiVTSequences=" + std::to_string(bAnsiVTSequences) + "\n\n"

			+ "# Integer Non-Switch Setting Variables\n#\n"
			+ "nSlowCharSpeed=" + std::to_string(nSlowCharSpeed) + "\n"
			+ "nCursorShape=" + std::to_string(nCursorShape) + "\n\n"

			+ "# Colour Variables\n#\n"
			+ "sColourGlobal=" + sColourGlobal + "\n"
			+ "sColourGlobalBack=" + sColourGlobalBack + "\n"
			+ "sColourHighlight=" + sColourHighlight + "\n"
			+ "sColourHighlightBack=" + sColourHighlightBack + "\n"
			+ "sColourTitle=" + sColourTitle + "\n"
			+ "sColourTitleBack=" + sColourTitleBack + "\n"
			+ "sColourSubheading=" + sColourSubheading + "\n"
			+ "sColourSubheadingBack=" + sColourSubheadingBack + "\n\n"
			
			+ "# RGB Colour Presets\n#\n"
			+ "sColourPresetForeground1=" + RGBPreset[0].sColourPresetForeground + "\n"
			+ "sColourPresetBackground1=" + RGBPreset[0].sColourPresetBackground + "\n"
			+ "sPresetName1=" + RGBPreset[0].sPresetName + "\n"
			+ "bSetByUser1=" + std::to_string(RGBPreset[0].bSetByUser) + "\n\n"

			+ "sColourPresetForeground2=" + RGBPreset[1].sColourPresetForeground + "\n"
			+ "sColourPresetBackground2=" + RGBPreset[1].sColourPresetBackground + "\n"
			+ "sPresetName2=" + RGBPreset[1].sPresetName + "\n"
			+ "bSetByUser2=" + std::to_string(RGBPreset[1].bSetByUser) + "\n\n"
			
			+ "sColourPresetForeground3=" + RGBPreset[2].sColourPresetForeground + "\n"
			+ "sColourPresetBackground3=" + RGBPreset[2].sColourPresetBackground + "\n"
			+ "sPresetName3=" + RGBPreset[2].sPresetName + "\n"
			+ "bSetByUser3=" + std::to_string(RGBPreset[2].bSetByUser);

		// Return config value to skip programming steps in some parts of config file system
		return sConfigFileContents;
	}

public:

	// Settings Variables/Switches
	//
	bool bDisplayDirections = true;
	bool bDisplayVerboseMessages = false; // TRUE for debugging; temporary and not for final release'
	bool bRandomColoursOnStartup = false;
	bool bShowCursor = true;
	bool bWordWrapToggle = true;
	bool bCursorBlink = true;
	bool bTermCustomThemeSupport = false;
	bool bAutoReadableContrast = true;
	bool bAnsiVTSequences = true;

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
	ConfigFileSystem() {
		VerbosityDisplay("ConfigFileSystem Object has been created.\n");

		// Update configuration string contents
		UpdateConfigContents();

		// Read/auto-create configuration file to complete object contents
		ReadConfigFile();

		return;
	}

	// Destructor
	~ConfigFileSystem() {
		VerbosityDisplay("ConfigFileSystem Object has been destroyed.\n");

		return;
	}

	// CreateConfigFile - Creates a config file safely, using user-defined location and default location as fallback.
	// No arguments are accepted.
	// Return values are TRUE for success, and FALSE for fail.
	//
	bool CreateConfigFile() 
	{
		// 1. Attempt to create config file in user-defined location
		std::ofstream CreateConfigOut(sConfigFileUserLocation);

		// 2. Check if open successful; if not, use default location; if not, return false
		if (CreateConfigOut.fail() == true) {
			VerbosityDisplay("In ConfigFileSystem::CreateConfigFile(): Warning - User file location cannot be opened. Attempting to create config file in default location.\n");
			CreateConfigOut.open(sConfigFileDefaultLocation);
			if (CreateConfigOut.fail() == true) {
				VerbosityDisplay("In ConfigFileSystem::CreateConfigFile(): ERROR - Default location could not be opened. Configuration file creation failed.");
				return false;
			}
			else {
				// Point to new file
				sConfigFileUserLocation = sConfigFileDefaultLocation;
				CreateConfigOut.open(sConfigFileUserLocation);
			}
		}

		// 3. Write to file
		UpdateConfigContents();
		CreateConfigOut << sConfigFileContents;

		bNewFileMade = true;

		return true;
	}

	// WriteConfigFile - Writes to a user-defined or default configuration file, from all saved settings in object memory.
	// No arguments are accepted.
	// Return values are TRUE for success. and FALSE for fail.
	//
	bool WriteConfigFile() {
		// 1. Declare variables
		std::string sConfigFinalLocation = "";

		// 2. Create test file stream
		std::ifstream TestStreamIn(sConfigFileUserLocation);

		// 3. Test for file existence in user-set location and ZeeTerminal folder
		if (TestStreamIn.fail() == true) {
			VerbosityDisplay("In ConfigFileSystem::WriteConfigFile(): Warning- User-defined file seems to be nonexistent. Attempting to write to default location.\n");
			TestStreamIn.clear();
			TestStreamIn.open(sConfigFileDefaultLocation);

			if (TestStreamIn.fail() == true) {
				VerbosityDisplay("In ConfigFileSystem::WriteConfigFile(): Warning - Default location file not found. Attempting to create new configuration file.\n");
				if (CreateConfigFile() == false) {
					VerbosityDisplay("In ConfigFileSystem::WriteConfigFile(): ERROR - Write attempt has failed.\n");
					UserErrorDisplay("Configuration file write attempt has failed.\n");
					return false;
				}
				else sConfigFinalLocation = sConfigFileUserLocation;
			}
			else sConfigFinalLocation = sConfigFileDefaultLocation;
		} 
		else sConfigFinalLocation = sConfigFileUserLocation;

		// 4. Close test file stream
		TestStreamIn.close();

		// 5. Open main file stream; post message that write operation has began.
		std::ofstream MainStreamOut(sConfigFinalLocation);

		// Unexpected failure - just exit
		if (MainStreamOut.fail()) {
			VerbosityDisplay("In ConfigFileSystem::WriteConfigFile(): ERROR - Unexpected failure has occured. Config file write attempt failed.\n");
			UserErrorDisplay("Configuration file write attempt has failed.\n");
			MainStreamOut.close();
			return false;
		}

		VerbosityDisplay("In ConfigFileSystem::WriteConfigFile(): Note - A write operation to configuration file has began.");

		// 6. Write to config file
		UpdateConfigContents();
		MainStreamOut << sConfigFileContents;

		// 7. Close all streams
		MainStreamOut.close();

		// 8. Exit with return value true.
		return true;
	}

	// ReadConfigFile - Attempts to read from a user-defined or the default configuration file, and loads contents into memory.
	// No arguments are accepted.
	// Return values are TRUE for success, and FALSE for fail.
	//
	bool ReadConfigFile() 
	{
		// 1. Declare variables
		std::string sLineBuffer = "";
		std::string sOptionBuffer = "";
		std::string sValueBuffer = "";
		std::string sConfigFinalLocation = "";

		// 2. Create test file stream 
		std::ifstream TestStreamIn(sConfigFileUserLocation);

		// 3. Test for file existence in user-set location and ZeeTerminal folder
		if (TestStreamIn.fail() == true) {
			VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning- User-defined file seems to be nonexistent. Attempting to read from default location.\n");
			TestStreamIn.clear();
			TestStreamIn.open(sConfigFileDefaultLocation);

			if (TestStreamIn.fail() == true) {
				VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning - Default location file not found. Attempting to create new configuration file.\n");
				if (CreateConfigFile() == false) {
					VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): ERROR - Read attempt has failed.\n");
					UserErrorDisplay("Configuration file read attempt has failed.\n");
					return false;
				}
				else sConfigFinalLocation = sConfigFileUserLocation;
			}
			else sConfigFinalLocation = sConfigFileDefaultLocation;
		}
		else sConfigFinalLocation = sConfigFileUserLocation;

		// 4. Close test file stream
		TestStreamIn.close();

		// 5. Create new main file stream
		std::ifstream MainStreamIn(sConfigFinalLocation);

		// Unexpected failure - just exit
		if (MainStreamIn.fail()) {
			VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): ERROR - Unexpected failure has occured. Config file read attempt failed.\n");
			UserErrorDisplay("Configuration file read attempt has failed.\n");
			MainStreamIn.close();
			return false;
		}

		// Check every line until the end of the file
		//
		VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Note - Configuration File Read Operation has commenced.\n");
		uint64_t nLineNum = 0;
		while (!MainStreamIn.eof()) {
			nLineNum++;

			// 6. Take in line of config file, put into std::string
			std::getline(MainStreamIn, sLineBuffer);

			// Check for comment (syntax: #<comment>); if comment found, skip line
			if (sLineBuffer[0] == '#') continue;
			// Check in case line has nothing - no need to waste time searching that line
			if (sLineBuffer == "") continue;

			// 7. Using a for loop, check if there's an equal sign in parsed line
			bool bEqualSpotted = false;
			for (int i = 0; i < sLineBuffer.length(); i++) {
				if (sLineBuffer[i] == '=') bEqualSpotted = true;
			}
			if (bEqualSpotted == false) {
				VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning - Line " + std::to_string(nLineNum) + " - no equal sign found, so doesn't have correct formatting. Skipping.\n");
				continue;
			}

			// 8. Create stringstream of line string, read operation has begun
			std::stringstream LineStream;
			LineStream << sLineBuffer;

			// 9. Parse up to first equal sign and put into option buffer string
			std::getline(LineStream, sOptionBuffer, '=');

			// Check if anything is in the option string
			if (sOptionBuffer == "") {
				VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning - Line " + std::to_string(nLineNum) + " - No option string found before equal sign. Please check for option string and try again. Skipping.\n");
				continue;
			}

			// 10. Parse final contents and put into value string
			std::getline(LineStream, sValueBuffer, '\n');

			// Check if anything is in the value string
			if (sValueBuffer == "") {
				VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning - Line " + std::to_string(nLineNum) + " - No value string found after equal sign. Please check for value string and try again. Skipping.\n");
				continue;
			}

			// 11. Based on option buffer string, assign contents of value string to memory option that points to option buffer string.
			//
			// Use for loop for checking for RGB colour system settings
			bool bRGBPresetFound = false;
			for (int i = 0; i < 3; i++) {
				if (sOptionBuffer == "sColourPresetForeground" + std::to_string(i + 1)) {
					RGBPreset[i].sColourPresetForeground = sValueBuffer;
					bRGBPresetFound = true;
					break;
				}
				else if (sOptionBuffer == "sColourPresetBackground" + std::to_string(i + 1)) {
					RGBPreset[i].sColourPresetBackground = sValueBuffer;
					bRGBPresetFound = true;
					break;
				}
				else if (sOptionBuffer == "sPresetName" + std::to_string(i + 1)) {
					RGBPreset[i].sPresetName = sValueBuffer;
					bRGBPresetFound = true;
					break;
				}
				else if (sOptionBuffer == "bSetByUser" + std::to_string(i + 1)) {
					if (isNumberi(sValueBuffer)) RGBPreset[i].bSetByUser = std::stoi(sValueBuffer);
					bRGBPresetFound = true;
					break;
				}
			}

			// Switches
			if (sOptionBuffer == "bDisplayDirections") {
				if (isNumberi(sValueBuffer)) bDisplayDirections = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bDisplayVerboseMessages") {
				if (isNumberi(sValueBuffer)) bDisplayVerboseMessages = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bRandomColoursOnStartup") {
				if (isNumberi(sValueBuffer)) bRandomColoursOnStartup = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bShowCursor") {
				if (isNumberi(sValueBuffer)) bShowCursor = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bWordWrapToggle") {
				if (isNumberi(sValueBuffer)) bWordWrapToggle = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bCursorBlink") {
				if (isNumberi(sValueBuffer)) bCursorBlink = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bTermCustomThemeSupport") {
				if (isNumberi(sValueBuffer)) bTermCustomThemeSupport = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bAutoReadableContrast") {
				if (isNumberi(sValueBuffer)) bAutoReadableContrast = std::stoi(sValueBuffer);
			}
			else if (sOptionBuffer == "bAnsiVTSequences") {
				if (isNumberi(sValueBuffer)) bAnsiVTSequences = std::stoi(sValueBuffer);
			}

			// Integer Variables
			else if (sOptionBuffer == "nSlowCharSpeed") {
				if (isNumberll(sValueBuffer)) nSlowCharSpeed = std::stoll(sValueBuffer);
			}
			else if (sOptionBuffer == "nCursorShape") {
				if (isNumberll(sValueBuffer)) {
					long long int nTester = std::stoll(sValueBuffer);
					if (nTester != 1 && nTester != 2 && nTester != 3 && nTester != 4 && nTester != 5 && nTester != 6) {
						VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning - nCursorShape value incorrect. Must be 1,2,3,4,5 or 6. Value left unchanged.\n");
					}
					else nCursorShape = nTester;
				}
			}

			// Colours (strings)
			else if (sOptionBuffer == "sColourGlobal") {
				sColourGlobal = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourGlobalBack") {
				sColourGlobalBack = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourHighlight") {
				sColourHighlight = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourHighlightBack") {
				sColourHighlightBack = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourTitle") {
				sColourTitle = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourTitleBack") {
				sColourTitleBack = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourSubheading") {
				sColourSubheading = sValueBuffer;
			}
			else if (sOptionBuffer == "sColourSubheadingBack") {
				sColourSubheadingBack = sValueBuffer;
			}
			else if (bRGBPresetFound == true) continue;

			// Not a referenced option
			else {
				VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Warning - Line " + std::to_string(nLineNum) + " - Unknown/unreferenced option used. Will not read from this line.\n");
			}

			// 12. Repeat until all lines have been checked.
		}

		// 13. Close all streams, post verbose message that read operation has complete.
		MainStreamIn.close();
		UpdateConfigContents();
		VerbosityDisplay("In ConfigFileSystem::ReadConfigFile(): Note - Config File read operation has been successfully completed.\n");

		return true;
	}

	// GetConfigObjectContents - Returns object settings contents.
	// No arguments are accepted.
	// Return value: std::string, for the object contents.
	//
	std::string GetConfigObjectContents() {
		UpdateConfigContents();
		return sConfigFileContents;
	}

	// GetConfigFileContents - Returns configuration file contents.
	// No arguments are accepted.
	// Return value: std::string, for the file contents.
	//
	std::string GetConfigFileContents() 
	{
		// 1. Declare variables
		std::string sConfigFinalLocation = "";
		std::string* sLineBuffer = new std::string;
		std::string* sFileBuffer = new std::string;

		// 2. Create test file stream 
		std::ifstream TestStreamIn(sConfigFileUserLocation);

		// 3. Test for file existence in user-set location and ZeeTerminal folder
		if (TestStreamIn.fail() == true) {
			VerbosityDisplay("In ConfigFileSystem::GetConfigFileContents(): Warning - User-defined file seems to be nonexistent. Attempting to read from default location.\n");
			TestStreamIn.clear();
			TestStreamIn.open(sConfigFileDefaultLocation);

			if (TestStreamIn.fail() == true) {
				VerbosityDisplay("In ConfigFileSystem::GetConfigFileContents(): Warning - Default location file not found. Attempting to create new configuration file.\n");
				if (CreateConfigFile() == false) {
					VerbosityDisplay("In ConfigFileSystem::GetConfigFileContents(): ERROR - File Get attempt has failed.\n");
					return "\nFAILED\n";
				}
				else sConfigFinalLocation = sConfigFileUserLocation;
			}
			else sConfigFinalLocation = sConfigFileDefaultLocation;
		}
		else sConfigFinalLocation = sConfigFileUserLocation;

		// 4. Close test file stream
		TestStreamIn.close();

		// 5. Create new main file stream
		std::ifstream MainStreamIn(sConfigFinalLocation);

		// Unexpected failure - just exit
		if (MainStreamIn.fail()) {
			VerbosityDisplay("In ConfigFileSystem::GetConfigFileContents(): ERROR - Unexpected failure has occured. Config File Get attempt failed.\n");
			MainStreamIn.close();
			return "\nFAILED\n";
		}

		// 6. Load file contents into buffer, post message that get file contents operation has began
		VerbosityDisplay("In ConfigFileSystem::GetConfigFileContents(): Note - Get File Contents operation has began.\n");
		*sLineBuffer = "";
		*sFileBuffer = "";
		while (!MainStreamIn.eof()) {
			std::getline(MainStreamIn, *sLineBuffer, '\n');
			*sFileBuffer += *sLineBuffer + '\n';
		}

		// 7. Return the file contents, close stream(s)
		MainStreamIn.close();
		delete sLineBuffer;
		VerbosityDisplay("In ConfigFileSystem::GetConfigFileContents(): Note - Get File Contents operation has completed successfully.\n");

		return *sFileBuffer;
	}

	// GetFileAgeInfo - Checks if a new file was made on object declaration, based on the bNewFileMade boolean variable.
	// No arguments are accepted.
	// Return values: TRUE or 1 for a new file made, FALSE or 0 for existing file discovered already.
	//
	bool GetFileAgeInfo() {
		return bNewFileMade;
	}

};
