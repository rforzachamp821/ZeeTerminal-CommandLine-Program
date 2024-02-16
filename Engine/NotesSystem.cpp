//
// NotesSystem.cpp - Responsible for managing the notes system within this program, and contains its class.
//


// NotesSystem - System for managing the creation and saving of user-defined notes.
//             - NotesSystem has the capabilities to save both in memory and as a file.
//             - NotesSystem will wipe out all notes from memory on object destruction for security measures.
//             - NotesSystem will update memory contents with ones in file on object creation.
// 
class NotesSystem
{
private:

	// Some constants declared so whenever there's a bug/change that's needed to be done, less steps are needed.
	const int nArraySize = 1024;
	const char* sDefaultFileName = "NotesFile.txt";

	std::string* sNotes = new std::string[1024];

	// Object ID
	int nObjectID;

public:

	// Constructor
	NotesSystem()
	{
		// Firstly, initialise all members of sNotes
		for (int i = 0; i < nArraySize; i++) {
			sNotes[i] = "";
		}

		static int nStaticID = 10000;
		// Wrap-around to prevent overflow
		if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
		nObjectID = ++nStaticID;

		// Secondly, output message that a new object has been created
		VerbosityDisplay("A new NotesSystem object has been created.\n", nObjectID);

		// Thirdly, update object memory contents with ones in file
		ReadFromNotesFile();

		return;
	}

	// Destructor
	~NotesSystem()
	{
		// Firstly, re-initialise the sNotes part of the heap for security measures to 0 (so notes don't get accessed from memory by malicious actor)
		for (int i = 0; i < nArraySize; i++) {
			sNotes[i] = "\0";
		}

		// Secondly, delete sNotes
		delete[] sNotes;
		sNotes = nullptr;

		// Thirdly, output message that the object has been destroyed
		VerbosityDisplay("A NotesSystem object has been destroyed.\n", nObjectID);

		return;
	}

	// AddNoteToArray - Adds a note to a passed note index, on the notes array.
	// Arguments: nArrayIndex - Note index to save the note to, based on 0. This cannot be higher than the returned value of GetCurrentNotesCount().
	//            sNoteText - The text to be used in the note.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool AddNoteToArray(unsigned int nArrayIndex, std::string sNoteText) {
		// Check if the array index is too high
		if (nArrayIndex > GetCurrentNotesCount()) {
			VerbosityDisplay("In NotesSystem::AddNoteToArray() - ERROR: Note index is too high, and is higher than NotesSystem::GetCurrentNotesCount().\n", nObjectID);
			return false;
		}

		// Check if notes text is empty - if so, shift everything behind the option by 1 to the left (deleting a note)
		if (sNoteText == "") {
			// Use for loop to shift all elements to the left
			unsigned int nNotesCount = GetCurrentNotesCount();
			for (unsigned int i = nArrayIndex; i < nNotesCount; i++) {
				if (i < nNotesCount - 1) {
					// Assign nArrayIndex/i to the note above it
					sNotes[i] = sNotes[i + 1];
					// Make the next note empty for the next reiteration
					sNotes[i + 1] = "";
				}
				else {
					// Just make the last note empty and don't mess with anything else - can be an optimisation
					sNotes[i] = "";
				}
			}

			// To skip line after this if block - prevents accidental NULL ("") termination bug
			return true;
		}

		// Add note - Just modify the array index
		sNotes[nArrayIndex] = sNoteText;

		return true;
	}

	// WriteToNotesFile - Write to notes file in the same directory as program folder, from contents saved in memory.
	//                  - This function will create a new file if an existing one isn't found, by default due to C++.
	// Arguments: None
	// Return values: TRUE for success, FALSE for fail.
	//
	bool WriteToNotesFile()
	{
		// 1. Open write stream
		std::ofstream NotesOut(sDefaultFileName);

		// 2. Check if failed - if so, return false; there's nothing that can be done else about that
		if (NotesOut.fail()) {
			VerbosityDisplay("In NotesSystem::WriteToNotesFile(): ERROR - Failed to open up a notes file stream, due to some unknown error. Lost access to ZeeTerminal directory?\n", nObjectID);
			NotesOut.close();
			return false;
		}

		// 3. Write every line of notes into file, with every line separated by a newline character (exit if failed)
		for (int i = 0; i < nArraySize && !NotesOut.fail(); i++) {

			// Exit when nothing found - there is no need to continue when there will be nothing else afterwards
			if (sNotes[i] == "") {
				break;
			}

			NotesOut << sNotes[i] << '\n';

			// Exit if failed
			if (NotesOut.fail()) {
				VerbosityDisplay("In NotesSystem::WriteToNotesFile(): ERROR - Failed to write to notes file, due to some unknown error. Lost access to ZeeTerminal directory/notes file?\n", nObjectID);
				NotesOut.close();
				return false;
			}
		}

		// 4. Return true as nothing bad happened, close all streams beforehand
		NotesOut.close();
		return true;
	}

	// ReadFromNotesFile - Read from notes file and put contents into memory.
	//                   - This function will stop copying when the number of lines read reach nArraySize.
	// Arguments: None
	// Return values: TRUE for success, FALSE for fail.
	//
	bool ReadFromNotesFile()
	{
		// 1. Test for notes file
		std::ifstream TestNotesIn(sDefaultFileName);

		if (TestNotesIn.fail()) {
			VerbosityDisplay("In NotesSystem::ReadFromNotesFile(): ERROR - Notes file not found. It should be in the same directory as ZeeTerminal.\n", nObjectID);
			return false; // return false - notes file not found
		}

		// 2. Close test file stream
		TestNotesIn.close();

		// 3. Open new stream
		std::ifstream FileNotesIn(sDefaultFileName);

		// 4. Assign each line to spot in notes array
		for (int i = 0; !FileNotesIn.eof() && !FileNotesIn.fail() && i < nArraySize; i++) {
			std::string sBuffer = "";
			std::getline(FileNotesIn, sBuffer, '\n');
			sNotes[i] = sBuffer;
		}

		// 5. Exit with true
		FileNotesIn.close();
		return true;
	}

	// ClearAllNotes - Clears all notes from notes file and notes array.
	//               - This is equivalent to performing a full reset of the entire Notes system.
	// Arguments: None
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	// NOTE: Any FALSE return comes from the NotesSystem::WriteToNotesFile() function, and is related to clearing the notes file.
	//
	bool ClearAllNotes() {
		// Initialise all notes to nothing
		for (int i = 0; i < nArraySize; i++) {
			sNotes[i] = "";
		}

		// Write these to the notes file
		if (WriteToNotesFile()) return true; else return false;

		return true;
	}

	// GetMemoryNotes - Gets all contents of the notes saved in memory and returns them as a singular string.
	// Arguments: None
	// Return value(s): The singular string containing the contents of the notes saved in memory.
	//
	std::string GetMemoryNotes()
	{
		// Use a for loop to convert array into a singular string in the heap
		std::string* sNotesBuffer = new std::string;

		for (int i = 0; i < nArraySize; i++) {
			if (sNotes[i] == "") break; // Exit when nothing found, as there would be nothing wanted after that
			*sNotesBuffer += sNotes[i] + "\n";
		}

		// Return
		return *sNotesBuffer;
	}


	// GetFileNotes - Gets all contents of the notes file and returns them as a singular string.
	// Arguments: None
	// Return value(s): The singular string containing the contents of the notes file.
	//
	std::string GetFileNotes()
	{
		// Declare std::string heap buffer
		std::string* sFileNotesBuffer = new std::string;

		// 1. Test for notes file
		std::ifstream TestNotesIn(sDefaultFileName);

		if (TestNotesIn.fail()) {
			VerbosityDisplay("In NotesSystem::GetFileNotes(): ERROR - Notes file not found. It should be in the same directory as ZeeTerminal.\n", nObjectID);
			return ""; // return empty string - notes file not found
		}

		// 2. Close test file stream
		TestNotesIn.close();

		// 3. Open new stream
		std::ifstream FileNotesIn(sDefaultFileName);

		// 4. Use for loop to parse lines and put into buffer in a raw manner
		while (!FileNotesIn.eof() && !TestNotesIn.fail()) {
			std::string sBuffer = "";
			std::getline(FileNotesIn, sBuffer, '\n');
			*sFileNotesBuffer += sBuffer + "\n";
		}

		// 5. Exit with heap buffer returned
		FileNotesIn.close();

		// Erase last newline as there would already be an extra one in the notes file
		sFileNotesBuffer->erase(sFileNotesBuffer->length() - 1, 1);

		return *sFileNotesBuffer;
	}

	// GetCurrentNotesCount - Gets the current number of notes in memory.
	// Arguments: None
	// Return value(s): The number of notes in memory, base 1.
	//
	unsigned int GetCurrentNotesCount() 
	{
		// Declare count variable
		unsigned int nCount = 0;

		// Use for loop to count number of notes
		for (int i = 0; i < nArraySize; i++, nCount++) {
			if (sNotes[i] == "") break; // Exit when nothing found, as there would be nothing wanted after that - final count
		}

		// Return final value
		return nCount;
	}

	// GetMaxNotesArraySize - Gets the size of the notes array.
	// Arguments: None
	// Return value(s): The size of the notes array, in the number of elements.
	//
	int GetMaxNotesArraySize() {
		return nArraySize;
	}
};

extern NotesSystem NotesMain;


class NotesSystemUI : public NotesSystem 
{
private:
	// Object ID
	int nObjectID;
public:

	NotesSystemUI() {
		static int nStaticID = 10000;
		// Wrap-around to prevent overflow
		if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
		nObjectID = ++nStaticID;

		VerbosityDisplay("NotesSystemUI Object Created (Inherited from NotesSystem).\n", nObjectID);
	}

	~NotesSystemUI() {
		VerbosityDisplay("NotesSystemUI Object Destroyed.\n", nObjectID);
	}

	// NotesEditor - Provides an interface to edit notes.
	// Arguments: None
	// Return Value: None
	//
	void NotesEditor() {
		CentreColouredText(" ___NOTES EDITOR___ ", 1);
		std::cout << '\n';

		// Create new file if nonexistent
		if (NotesMain.ReadFromNotesFile() == false) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nNo notes file detected. Creating new file...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Attempt to write to notes file
			if (!NotesMain.WriteToNotesFile()) {
				VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and create notes file.\n", nObjectID);
				UserErrorDisplay("ERROR - Failed to create notes file. This notes session will save to memory only.\n", nObjectID);

				return;
			}
		}

		// Interface
		std::cout << "\n";
		colourSubheading();
		std::cout << "Welcome to the Notes Editor!" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nThis is where you can edit your notes.\n\n");

		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("Use the following shortcuts to make changes quicker:");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\n -> ^exit or nothing inputted - Exit and save.\n -> ^prev - Modify the previous note line.\n -> ^<num> - Modify a note line of a specific number. Put the number in place of <num>.\n\n");

		std::string sNoteBuffer = "";

		bool bIteratorChange = false;
		size_t nPreviousIterator = 0;
		for (size_t i = NotesMain.GetCurrentNotesCount(); i < NotesMain.GetMaxNotesArraySize(); i++) {
			std::cout << "Note ";
			colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
			std::cout << i + 1;
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			std::cout << ": > ";
			sNoteBuffer = StrInput("");

			// Shortcut check
			if (sNoteBuffer == "^exit" || sNoteBuffer == "") {
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "Saving and exiting...\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				if (!NotesMain.WriteToNotesFile()) {
					VerbosityDisplay("In Commands() - ERROR: Failed to write to notes file and save notes.\n", nObjectID);
					UserErrorDisplay("ERROR - Failed to save notes. Exiting anyway...\n", nObjectID);

					return;
				}

				return;
			}
			else if (sNoteBuffer == "^prev") {
				bIteratorChange = true;
				nPreviousIterator = i;
				i -= 2;
				if (i <= -1) {
					bIteratorChange = false;
					i = nPreviousIterator;
					nPreviousIterator = 0;
					NotesMain.AddNoteToArray(i, sNoteBuffer);
					// Save notes
					NotesMain.WriteToNotesFile();
				}
				else continue; // to avoid write to notes array
			}
			else if (sNoteBuffer.find("^") == 0) {
				// Possibly a number - search until the end of a string
				std::string sNumberCandidate = sNoteBuffer.substr(1, std::string::npos);
				if (isNumberull(sNumberCandidate)) {
					bIteratorChange = true;
					nPreviousIterator = i;
					i = std::stoull(sNumberCandidate);

					if (i < 1 || i > NotesMain.GetCurrentNotesCount()) {
						i = nPreviousIterator;
						nPreviousIterator = 0;
						bIteratorChange = false;
						NotesMain.AddNoteToArray(i, sNoteBuffer);
						// Save notes
						NotesMain.WriteToNotesFile();
					}
					else {
						i -= 2;
						continue; // to avoid write to notes aray
					}
				}
			}

			// Add note to note array
			NotesMain.AddNoteToArray(i, sNoteBuffer);
			// Save notes
			NotesMain.WriteToNotesFile();

			// For iterator change
			if (bIteratorChange) {
				bIteratorChange = false;
				i = nPreviousIterator - 1;
				nPreviousIterator = 0;
			}
		}
	}

	// NotesViewer - Provides an interface to view notes.
	// Arguments: None
	// Return Value: None
	//
	void NotesViewer() {
		std::cout << '\n';
		colourSubheading();
		std::cout << "Notes saved in memory:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\n";
		std::stringstream ssMemoryNotes(NotesMain.GetMemoryNotes());

		// Don't do for loop if there aren't any notes
		if (ssMemoryNotes.str() == "") {
			std::cout << "No notes are saved on memory.\n";
		}
		else {
			for (int i = 0; !ssMemoryNotes.eof(); i++) {
				std::string sNoteBuffer = "";

				// Get a line up to next newline
				std::getline(ssMemoryNotes, sNoteBuffer, '\n');
				if (ssMemoryNotes.eof()) break; // break on end of stream

				// Output line with line number appended
				std::cout << "Note ";
				colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
				std::cout << i + 1;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << ": " << sNoteBuffer << "\n";
			}
		}
		std::cout << "\n";

		colourSubheading();
		std::cout << "Notes saved in file:" << NOULINE_STR;
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\n";
		std::stringstream ssFileNotes(NotesMain.GetFileNotes());

		if (ssFileNotes.str() == "") {
			std::cout << "No notes are saved on the Notes file.\n";
		}
		else {
			for (int i = 0; !ssFileNotes.eof(); i++) {
				std::string sNoteBuffer = "";

				// Get a line up to next newline
				std::getline(ssFileNotes, sNoteBuffer, '\n');
				if (ssFileNotes.eof()) break; // break on end of stream

				// Output line with line number appended
				std::cout << "Note ";
				colour(NumberToColour(RandNum(16, 1)), ConfigObjMain.sColourGlobalBack);
				std::cout << i + 1;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << ": " << sNoteBuffer << "\n";
			}
		}

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nAll notes outputted.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
};