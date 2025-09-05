
//
// ZeeTerminal Main and Input Engine Components
/***
 *      _____        _____                   _             _
 *     |__  /___  __|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |
 *       / // _ \/ _ \| |/ _ \ '__| '_ ` _ \| | '_ \ / _` | |
 *      / /|  __/  __/| |  __/ |  | | | | | | | | | | (_| | |
 *     /____\___|\___||_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_|
 * 
 */
// (c) Ryan Zorkot, 2024. Licensed under MIT.
//

#include <iostream>
#include <string>
#include <limits>
#include "Core/ZTConstDefinitions.h"
#include "Core/ZTFormattingDefinitions.h"
#include "Core\ZeeTerminalCore.h"
#include "Engine\LogFile-System\LogFile-System.h"
#include "Engine\FileParse-System\FileParse-System.h"
#include "CommandFiles\CommandsFile.cpp"

// Function to manage startup tasks
void ProgramInitialisation() 
{
	// Set random colours if random colours on startup are enabled
	if (ConfigObjMain.bRandomColoursOnStartup == true) {

		// Pick random foreground colour
		int nRandForeground = (int)RandNumld(16, 1);
		ColourForegroundSwitch(&nRandForeground, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);

		// Pick random background colour
		int nRandBackground = (int)RandNumld(16, 1);
		ColourBackgroundSwitch(&nRandBackground, &ConfigObjMain.sColourGlobalBack, &ConfigObjMain.sColourGlobal);
	}

	// Check for Virtual Terminal (ANSI) Sequence Support
	if (EnableVTMode() == false) {
		// Disable ANSI virtual terminal sequences - do not refer to the configuration file
		bAnsiVTSequences = false;

		// Set the colours
		ColourTypeSwitch();

		VerbosityDisplay("This terminal cannot do Virtual Terminal Sequences.\nThis session will use the WIN32 API fallback colour set for operation.\n");
	}
	else {
		// Use user-set setting in the configuration file
		bAnsiVTSequences = ConfigObjMain.bAnsiVTSequences;

		// Set the colours
		ColourTypeSwitch();

		VerbosityDisplay("This terminal has Virtual Terminal Sequences support.\nThis session will run with ANSI RGB colour support.\n");
	}

	// Set colours to global colours that have just been retrieved from config file
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Set console cursor attributes
	SetCursorAttributes();

	// Set shutdown privileges
	if (!EnableShutdownPrivileges()) VerbosityDisplay("Failed to enable shutdown privileges. Restart and shutdown commands may not work.\n");

	// Set window title to 'ZeeTerminal'
	SetWindowTitle("ZeeTerminal");

	// Finally, close away all of the initialisation messages by clearing the screen (non-ANSI terminals fully clear the whole buffer)
	if (bAnsiVTSequences) {
		std::cout << "\033[2J\033[1;1H";
	}
	else {
		cls();
	}

	return;
}

// Main function for running platform
int main(int argc, char* argv[]) 
{
	std::string sCommandInput = "";
	std::string sCommand = "";
	std::string sCommandArgsBuffer = "";
	char cCommandInputArgs[nArgArraySize] = {};
	bool bRunCommandLoopOnce = false; // Run the command loop once, should only be used for singular command arguments

	// Get the program ready, sort out environment
	std::cout << "Getting ready...\n";
	// Initialise main() variables
	// cCommandInputArgs and sStringCommandArgs
	for (int i = 0; i < nArgArraySize; i++) {
		cCommandInputArgs[i] = ' ';
		sStringDataCommandArgs[i] = "";
		sStringOptionCommandArgs[i] = "";
	}

	// Initialise everything else in program
	ProgramInitialisation();

	// Arguments to ZeeTerminal session
	if (argc > 1) {
		std::string sArgv[2];
		sArgv[0] = argv[0];
		sArgv[1] = argv[1];


		if (sArgv[1] == "-c") 
		{
			// The command argument is nonexistent and wasn't found because the argument count is only 2 (the program and the '-c') - post error.
			if (argc <= 2) {
				UserErrorDisplay("ERROR - No command argument found with option -c. Please check that a command argument is after the -c argument, and try again.\n");
				return 0;
			}

			// vsFileParseCommands is used as bRunningFromScriptOrArgCommand will be set to TRUE, so the parser would just read the first value like FileParse.
			// The program would terminate right after the first command as bRunCommandLoopOnce will be set to TRUE, therefore no invalid memory access error should occur.
			fparse::vsFileParseCommands.clear();
			fparse::vsFileParseCommands.push_back(argv[2]);
			fparse::bRunningFromScriptOrArgCommand = true;
			bRunCommandLoopOnce = true; // One command from argument will end the terminal operation

		}
		else if (sArgv[1] == "ZeeTerminalCore.h" || sArgv[1] == "--help") {
			// Output help message for user
			std::cout << "___ZeeTerminal Help___\n\n__Syntax__:\nFor running a script: ZeeTerminal.exe <script filepath>\nFor running a singular command: ZeeTerminal.exe -c <command>\n\n"
				<< "If you would like to run a script OR command where either contains space characters, use quotation marks (\"\").\n --> For example: ZeeTerminal.exe \"C:\\Users\\Public\\A Test Script.txt\"\n\n"
				<< "__Possible Arguments__:\n  -->  '-h'  OR  '--help'\tDisplays this help message.\n  -->  -c\t\t\tUse this argument to interpret the next string as a command.\n\n"
				<< "__Examples__:\n -->  ZeeTerminal.exe -c \"echo Hello, World!\"\n -->  ZeeTerminal.exe -c devtools\n -->  ZeeTerminal.exe TestScript.txt\n -->  ZeeTerminal.exe \"Random Directory\\A Test Script.txt\"\n\n";

			// Exit after that - nothing else needs to be run
			return 0;
		}
		else {
			// Initialise FileParse system with first argument - if failed, the function will uninitialise properly immediately.
			if (!fparse::InitialiseFileParse(sArgv[1], true)) {
				UserErrorDisplay("ERROR - An error occured while initialising the FileParse System. Possibly a nonexistent file path?\n");
				return 0;
			}
		}
	}

	// If an argument was given, messages that usually would appear when a user is using it should not be displayed.
	// This is indicated by the boolean below:
	//
	if (fparse::bRunningFromScriptOrArgCommand == false)
	{
		colour(colconv::NumberToColour(RandNumld(16, 1)), ConfigObjMain.sColourGlobalBack);

		if (bAnsiVTSequences == true) std::cout << BLINK_STR;
		slowcharfn(true, "Welcome to ZeeTerminal!");
		if (bAnsiVTSequences == true) std::cout << NOBLINK_STR;

		// Alert new user about the existence of a short tutorial
		// Helps with new users to get familiar with the program
		if (ConfigObjMain.GetFileAgeInfo() == true) {
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			// Sleep statements to keep user calm
			sleep(500);
			slowcharfn(true, "\nIt looks like you haven't used this application before.");
			sleep(100);

			if (YesNoInput("\nWould you like a short tutorial on how to use it? ['y' for yes, 'n' for no]: > ")) {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Sure!\n\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				Tutorial();
			}
			else {
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << "Alright, got it.\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
		}

		colour(colconv::NumberToColour(RandNumld(16, 1)), ConfigObjMain.sColourGlobalBack);
		std::cout << "\nPress ENTER to begin...\n";
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		// Help message
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "[Type ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\"Help\" ";
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "to get all commands.]\n[Type ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\"Tutorial\"";
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << " to get a tutorial on how to use the program.]\n\n";
	}


	size_t nFileParseIterator = 0;
	while (true) 
	{
		// Reset all command processing variables to defaults
		sCommand = "";
		sCommandArgsBuffer = "";
		sCommandInput = "";
		sCommandInputRAW = "";

		// Set colours to default
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// The below if-statement is present because after the user-initiated command execution that activates FileParse is complete, the nFileParseIterator variable is incremented.
		// The nFileParseIterator variable incrementing is unwanted as no command from the actual file has been read yet, so it's essentially skipping the first line of the file,
		// hence the nFileParseIterator variable is set to 0 again and the bLastCommandWasFileParse variable is set to false.
		//
		if (fparse::bLastCommandWasFileParse && nFileParseIterator >= 1) {
			fparse::bLastCommandWasFileParse = false;
			nFileParseIterator = 0;
		}

		// Output 'command' if the display boolean is true
		if (bDisp == true) {
			// Prompt and get input
			std::cout << "Command: > ";
		}

		// Different input methods depending on running off script or actual user wanting to input
		// From script
		if (fparse::bRunningFromScriptOrArgCommand == true) {
			// Display command if wanted
			if (bDisp == true) {
				colour(LYLW, ConfigObjMain.sColourGlobalBack);
				std::cout << fparse::vsFileParseCommands[nFileParseIterator] << '\n';
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			}
			// Send the next parsed command to command input
			sCommandInput = fparse::vsFileParseCommands[nFileParseIterator];
		}
		// From actual user input
		else {
			// Get input from std::cin
			colour(LYLW, ConfigObjMain.sColourGlobalBack);
			std::getline(std::cin, sCommandInput, '\n');
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Optimisation for no input
		if (sCommandInput == "") {
			if (fparse::bRunningFromScriptOrArgCommand) {
				// Do nothing - This shouldn't be triggered but is there to prevent crashes
				// if there actually is a bug in the FileParse system.
			}
			else {
				continue;
			}
		}
		else {
			// Initialise cCommandInputArgs to make all spaces
			for (int i = 0; i < nArgArraySize; i++) {
				cCommandInputArgs[i] = ' ';
				sStringDataCommandArgs[i] = "";
				sStringOptionCommandArgs[i] = "";
			}
		}

		// Copy command from sCommandInput into sCommand until space
		//
		// Create stringstream
		std::istringstream sCommandInputIn(sCommandInput);

		// For loop to start checking from after any spaces inputted by the user
		for (size_t i = 0; i < sCommandInput.length() && !sCommandInputIn.eof(); i++) {
			std::getline(sCommandInputIn, sCommand, ' ');
			if (sCommand != "") break;
		}

		// For loop to find and remove tabs in the command string - these are unwanted, especially if they're used for intentation such as within a script
		while (true) {
			// Find next tab character
			size_t nTabLocation = sCommand.find('\t');
			// if nothing found, break out of the loop
			if (nTabLocation == std::string::npos) break;
			// Erase/remove the tab character
			sCommand.erase(nTabLocation, 1);
		}

		// Optimisation for spaces
		if (sCommand == "") {
			if (bRunCommandLoopOnce) {
				break; // No command, so just leave
			}
			else if (fparse::bRunningFromScriptOrArgCommand) {
				// Do nothing - This shouldn't be triggered but is there to prevent crashes
				// if there actually is a bug in the FileParse system.
			}
			else {
				continue; // Normal method - skip everything below
			}
		}

		// Put raw input into sCommandInputRAW (done now to prevent overwrite before making sCommand lowercase)
		sCommandInputRAW = sCommand;

		// Make all letters inside sCommand lowercase
		for (size_t i = 0; i < sCommand.length(); i++) {
			sCommand[i] = std::tolower(sCommand[i]);
		}

		// Optimisation for exit command (doesn't need to be in Commands())
		if (sCommand == "exit" || sCommand == "0" || sCommand == "2") {
			nNumOfInputtedCommands++;
			nNumOfSuccessfulInputtedCommands++;
			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nHave a good day/night!\n";
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			slowcharfn(false, "Exiting...\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Don't exit the terminal when exiting on script completion is disabled - just terminate FileParse and set up everything back to normal.
			if (!fparse::bExitOnScriptCompletion && fparse::bRunningFromScriptOrArgCommand)
			{
				// Add log line
				if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging) {
					LogFileMain.AddLogLine("Exit command executed. Exiting on completion disabled and running from script, so FileParse uninitialisation initiated.", 3);
				}

				fparse::UninitialiseFileParse();
				nFileParseIterator = 0; // zero out counter and stop counting
				fparse::bRunningFromScriptOrArgCommand = false;
				bRunCommandLoopOnce = false;

				// Display success message
				colour(LGRN, ConfigObjMain.sColourGlobalBack);
				std::cout << CentreText("___FileParse Script successfully executed!___") << "\n\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Now that FileParse has been shut off and terminated, running the continue line on the loop should be safe.
				continue;
			}
			else {
				// Add log line
				if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging) {
					LogFileMain.AddLogLine("Exit command executed. Exiting on completion enabled or user executed the command, so exit process initiated.", 3);
				}

				break; // exit terminal command loop
			}
		}

		// Copy the rest of the stringstream contents into sCommandArgsBuffer
		std::getline(sCommandInputIn, sCommandArgsBuffer, '\n');

		// Copy new sCommandArgsBuffer string to another string, as it will be modified
		const std::string sCommandArgsBufferRAW = sCommandArgsBuffer + " ";
		
		// Declare fileout stream for ToFile feature
		std::ofstream ToFile_Out{};
		// Declare std::streambuf variables so that just in case tofile feature is enabled, the previous stdout buffer can be saved
		std::streambuf* coutStreambufBuffer{};
		std::streambuf* cerrStreambufBuffer{};
		
		/* The following will be based on parsing sCommandArgsBuffer for the actual arguments. */
		// Copy the string option arguments into sStringOptionCommandArgs with correct formatting
		sCommandArgsBuffer += " ";
		sCommandArgsBuffer = " " + sCommandArgsBuffer;
		for (size_t nDashPos = 0, nSpacePos = 0, i = 0; i < nArgArraySize; i++, nDashPos = 0, nSpacePos = 0)
		{
			// Exit early if none of the -- parts can be found - optimisation
			if (sCommandArgsBuffer.find(" --\"", 0) == std::string::npos && sCommandArgsBuffer.find(" --", 0) == std::string::npos) break;

			// Firstly, check which type of string syntax is first (lower is closer to beginning)
			//
			if (sCommandArgsBuffer.find(" --\"", 0) > sCommandArgsBuffer.find(" --", 0))
			{
				// Anything with -- at the beginning
				if (sCommandArgsBuffer.find(" --", 0) != std::string::npos)
				{
					// Get next occurence of " --"
					nDashPos = sCommandArgsBuffer.find(" --", 0);
					// Get occurence of ' ' after nDashPos new location
					nSpacePos = sCommandArgsBuffer.find(" ", nDashPos + 3);

					/* Check for confliction with --" */
					//
					std::string sTest = sCommandArgsBuffer.substr((nDashPos + 3), nSpacePos - (nDashPos + 3));

					// For loop uses struct so declaration of multiple variables in for loop is possible
					//
					for (struct { size_t j = 0; bool bAlreadyErased = false; } loop; loop.j < sTest.length(); loop.j++)
					{
						if (sTest[loop.j] == '\"') {
							break;
						}
						else {

							// Only read and erase string if first time passing by the line of code
							if (loop.bAlreadyErased == false) {
								// Copy from after the dashes to the next space
								sStringOptionCommandArgs[i] = sCommandArgsBuffer.substr((nDashPos + 3), nSpacePos - (nDashPos + 3));

								// Erase the found string from the argument buffer to remove it from plain sight from parser
								sCommandArgsBuffer.erase(nDashPos, nSpacePos - (nDashPos));

								loop.bAlreadyErased = true;
							}
						}
					}
				}

			}
			else
			{
				// Anything with --" at the beginning
				if (sCommandArgsBuffer.find(" --\"", 0) != std::string::npos)
				{
					nDashPos = sCommandArgsBuffer.find(" --\"", 0);
					// Get next occurence of '"'
					nSpacePos = sCommandArgsBuffer.find("\"", nDashPos + 4);
					// Use space as fallback if there is no other speechmark
					if (nSpacePos == std::string::npos) nSpacePos = sCommandArgsBuffer.find(" ", nDashPos);

					// Copy from after the dashes to the next space/speechmark
					sStringOptionCommandArgs[i] = sCommandArgsBuffer.substr((nDashPos + 4), nSpacePos - (nDashPos + 4));

					// Erase the found string from the argument buffer to remove it from plain sight from parser
					sCommandArgsBuffer.erase(nDashPos, nSpacePos + 1 - nDashPos);

				}

			}

			// Activate ToFile feature flag if --tofile has been supplied
			if (sStringOptionCommandArgs[i] == "tofile") { 
				bToFileFeatureActivated = true; 

				// Remove the toFile argument as we don't want the command to see it
				sStringOptionCommandArgs[i] = "";
				i--; // To ensure that the current position is re-used on the next iteration
			}
		}

		// Copy the string data arguments into sStringDataCommandArgs with correct formatting
		for (size_t nFirstMarkerPos = 0, nLastMarkerPos = 0, i = 0, nViableSpacePos = 0; i < nArgArraySize; i++, nFirstMarkerPos = 0, nLastMarkerPos = 0, nViableSpacePos = 0)
		{
			// Check for next viable space location
			bool bExitLoopEarly = false; // optimisation for exiting loop early
			while (true) 
			{
				// a. Find next raw space location
				nViableSpacePos = sCommandArgsBuffer.find(" ", nViableSpacePos);

				// b. Check if raw space location is at end of string
				if (nViableSpacePos == std::string::npos || nViableSpacePos == sCommandArgsBuffer.find_last_of(" ", std::string::npos)) {
					bExitLoopEarly = true;
					break;
				}

				// c. Increment nViableSpacePos to not just run in loops when checking space location
				nViableSpacePos++;

				// d. Check next character for any conflictions; if after the space is good, exit
				if (sCommandArgsBuffer[nViableSpacePos] != ' ' && sCommandArgsBuffer[nViableSpacePos] != '-' && sCommandArgsBuffer[nViableSpacePos] != '\"') {
					nViableSpacePos--;
					break;
				}
			}

			// Exit the for loop if there is nothing left to find
			if ((sCommandArgsBuffer.find(" ", nViableSpacePos) == std::string::npos || bExitLoopEarly) && sCommandArgsBuffer.find("\"", 0) == std::string::npos) break;

			// Check what string argument type is first, and then check that first so everything in the array is in order
			if (sCommandArgsBuffer.find(" ", nViableSpacePos) < sCommandArgsBuffer.find("\"", 0)) 
			{
				if (sCommandArgsBuffer.find(" ", nViableSpacePos) != std::string::npos)
				{
					// Check for space argument first
					//
					// Check for first space
					nFirstMarkerPos = sCommandArgsBuffer.find(" ", nViableSpacePos) + 1;

					// Check for last space
					nLastMarkerPos = sCommandArgsBuffer.find(" ", nFirstMarkerPos);

					// Create new substring from these marking points
					std::string sCommandArgument = sCommandArgsBuffer.substr(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);

					sStringDataCommandArgs[i] = sCommandArgument;

					// Erase substring from arugment buffer
					sCommandArgsBuffer.erase(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);
				}
			}
			else
			{
				if (sCommandArgsBuffer.find("\"", 0) != std::string::npos)
				{
					// Check for quotation argument first
					//
					// Check for first quotation mark
					nFirstMarkerPos = sCommandArgsBuffer.find("\"", 0) + 1;

					// Check for last quotation mark
					nLastMarkerPos = sCommandArgsBuffer.find("\"", nFirstMarkerPos);

					// Create new substring from these marking points
					sStringDataCommandArgs[i] = sCommandArgsBuffer.substr(nFirstMarkerPos, nLastMarkerPos - nFirstMarkerPos);

					// Erase substring from argument buffer
					// 
					// 1 is subtracted so the first quotation is removed as well, 
					// and 1 is added on the last marker here so the ending quotation gets purged
					sCommandArgsBuffer.erase(nFirstMarkerPos - 1, (nLastMarkerPos + 1) - (nFirstMarkerPos - 1));
				}
			}
		}

		// Copy the letter after a dash into cCommandInputArgs
		for (size_t i = 0, j = 0; i < sCommandArgsBuffer.length() && j < nArgArraySize; i++) {
			if (i > 0) {
				// Character after must not be a space to prevent conflict with string parser 
				if (sCommandArgsBuffer[i - 1] != '-' && sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					cCommandInputArgs[j] = std::tolower(sCommandArgsBuffer[i + 1]);
					j++;
				}
			}
			else {
				// This time, just remove the check for sCommandArgsBuffer[nFileParseIterator - 1] to prevent OOR exception
				if (sCommandArgsBuffer[i + 1] != '-' && sCommandArgsBuffer[i] == '-') {
					cCommandInputArgs[j] = std::tolower(sCommandArgsBuffer[i + 1]);
					j++;
				}
			}

		}

		// Add a log line for command execution
		if (bConfigAndLogSystemsInitialised && ConfigObjMain.bEnableLogging && ConfigObjMain.bCommandInputInfoLogging)
		{
			// Get number of char args
			size_t nCharArraySize = 0;
			for (; nCharArraySize < nArgArraySize && cCommandInputArgs[nCharArraySize] != ' '; nCharArraySize++) {}

			// Get number of data string args
			size_t nDataStringArraySize = 0;
			for (nDataStringArraySize = nArgArraySize - 1; nDataStringArraySize >= 0 && sStringDataCommandArgs[nDataStringArraySize] == ""; nDataStringArraySize--) {}
			nDataStringArraySize++;

			// Get number of option string args
			size_t nOptionStringArraySize = 0;
			for (nOptionStringArraySize = nArgArraySize - 1; nOptionStringArraySize >= 0 && sStringOptionCommandArgs[nOptionStringArraySize] == ""; nOptionStringArraySize--) {}
			nOptionStringArraySize++;

			// Add log line
			LogFileMain.AddLogLine("Executing command [" + sCommand + "] with "
				+ std::to_string(nCharArraySize) + " character arguments, "
				+ std::to_string(nOptionStringArraySize) + " option string arguments, and "
				+ std::to_string(nDataStringArraySize) + " data string arguments (User Input: [" + sCommandInput + "]).", 3);
		}

		// Perform actions for tofile feature if the feature has been activated
		if (bToFileFeatureActivated == true) {
			// Get index of last string in data string array by calculating its array size
			size_t nLastDataStringArrayMemberIndex = 0;
			for (nLastDataStringArrayMemberIndex = nArgArraySize - 1; sStringDataCommandArgs[nLastDataStringArrayMemberIndex] == ""; nLastDataStringArrayMemberIndex--) {
				if (sStringDataCommandArgs[nLastDataStringArrayMemberIndex] == "" && nLastDataStringArrayMemberIndex == 0) {
					break;
				}
			}
			// Open file using std::ofstream object and the filepath to be the last data string in the data string array
			ToFile_Out.open(sStringDataCommandArgs[nLastDataStringArrayMemberIndex]);

			// Remove the last data string from the array as it belongs to the ToFile feature
			sStringDataCommandArgs[nLastDataStringArrayMemberIndex] = "";

			// Check for errors while opening - if error occured, output message and disable ToFile feature
			if (ToFile_Out.fail()) {
				bToFileFeatureActivated = false;
				VerbosityDisplay("In main(): ERROR - Failed to open file for writing, as failed to open std::ofstream to filepath.\nFilepath was: " + sStringDataCommandArgs[nLastDataStringArrayMemberIndex] + "\n");
				UserErrorDisplay("ERROR - Failed to open file for writing. Path does not exist, out of memory or lack of file permissions in directory.\nPlease try the ToFile feature with a different path.\n");
				ToFile_Out.close();
			}
			else {
				// Save old buffer for std::cout
				coutStreambufBuffer = std::cout.rdbuf();

				// Redirect std::cout to the new stream
				std::cout.rdbuf(ToFile_Out.rdbuf());

				// Save old buffer for std::cerr
				cerrStreambufBuffer = std::cerr.rdbuf();

				// Redirect std::cerr to the new stream
				std::cerr.rdbuf(ToFile_Out.rdbuf());
			}
		}

		// Finally, call commands function
		//
		nNumOfInputtedCommands++;
		nNumOfSuccessfulInputtedCommands++;
		Commands(sCommand, cCommandInputArgs, sCommandArgsBufferRAW);

		// If the ToFile feature was enabled previously, disable it and return everything back to normal
		if (bToFileFeatureActivated == true) {
			bToFileFeatureActivated = false;

			// Undo the streambuf modifications
			std::cout.rdbuf(coutStreambufBuffer);
			std::cerr.rdbuf(cerrStreambufBuffer);
			
			// Close the file stream
			ToFile_Out.close();
		}

		std::cout << '\n';

		// Exit on argument command completion OR exit on script completion (line position check and if exiting after script completion is enabled)
		if (bRunCommandLoopOnce == true || (nFileParseIterator >= fparse::vsFileParseCommands.size() - 1 && fparse::bExitOnScriptCompletion == true)) {
			break;
		}

		// If not exiting on script completion, just uninitialise everything related to the FileParse system and continue as normal
		else if (nFileParseIterator >= fparse::vsFileParseCommands.size() - 1 && fparse::bExitOnScriptCompletion == false) {
			fparse::UninitialiseFileParse();
			nFileParseIterator = 0; // zero out counter and stop counting
			fparse::bRunningFromScriptOrArgCommand = false;
			bRunCommandLoopOnce = false;

			// Display success message
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << CentreText("___FileParse Script successfully executed!___") << "\n\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		// Increment if running from script
		if (fparse::bRunningFromScriptOrArgCommand) nFileParseIterator++;
	}

	return 0;
}