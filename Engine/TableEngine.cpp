
// TableEngine - A class that allows for creating tables at any point in time in your code.
// 
class TableEngine {
private:
	// Object ID
	int nObjectID;
protected:

	std::vector<std::vector<std::string>> vsTable;

	// GetLargestTableMemberSize - Gets the largest string out of an array of members passed into the function
	// Arguments: sMembers is for the array of members that are to be checked. 
	// The biggest size is returned if successful, otherwise -1 is returned if an error occured.
	size_t GetColumnSize(std::vector<std::string> vsMembers) {
		size_t nLargestSize = 0;

		for (uint64_t i = 0; i < vsMembers.size(); i++) {
			if (vsMembers[i].size() > nLargestSize) {
				nLargestSize = vsMembers[i].size();
			}
		}

		return nLargestSize;
	}

public:
	
	// TableEngine constructor
	TableEngine() {
		static int nStaticID = 10000;
		nObjectID = ++nStaticID;

		VerbosityDisplay("TableEngine Object Created.\n", nObjectID);
		return; // Nothing needs to be initialised as there's only a vector
	}

	// TableEngine destructor
	~TableEngine() {
		VerbosityDisplay("TableEngine Object Destroyed.\n", nObjectID);
		return;
	}

	// Add a new row to vsTable
	void addRow(std::vector<std::string> row) {
		vsTable.push_back(row);
		return;
	}

	// Output the table based on all user arguments
	void OutputTable() {

		std::vector<uint64_t> vnColumnSizes(vsTable[0].size(), 0); // For column sizes

		// Find the maximum width of each column
		for (const auto& row : vsTable) {
			for (uint64_t i = 0; i < row.size(); ++i) {
				// To work without max() windows macro
				vnColumnSizes[i] = (((vnColumnSizes[i]) > (static_cast<uint64_t>(row[i].size()))) ? (vnColumnSizes[i]) : (static_cast<uint64_t>(row[i].size())));
			}
		}



		// Check if nColumnWidth is too big for the screen
		CONSOLE_SCREEN_BUFFER_INFO csbiTable;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiTable);

		// Check for cursor exceeding screen buffer height (could be bug #14774 workaround on Windows Terminal GitHub)
		if (CheckIfCursorExceedScreenBufferHeight()) cls();

		for (uint64_t i = 0; i < vnColumnSizes.size(); i++) {
			if (vnColumnSizes[i] >= (csbiTable.srWindow.Right - csbiTable.srWindow.Left) / vsTable[0].size()) {
				vnColumnSizes[i] = (csbiTable.srWindow.Right - csbiTable.srWindow.Left) / vsTable[0].size();
			}
		}

		uint64_t nNumOfVertLines = 1; // For other members in the same row to adapt the length of their vertical lines - defaults to 1, for 1 line.
		for (uint64_t i = 0; i < vsTable.size(); i++) {

			for (uint64_t j = 0; j < vsTable[i].size(); j++) {

				// If string is too long, apply word wrapping around the vertical line
				if (vsTable[i][j].size() > vnColumnSizes[j]) {

					// Split long strings into multiple lines
					std::string s = vsTable[i][j];

					while (s.size() > 0) {
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiTable);
						std::cout << std::left << "\b\b| " << std::setw(vnColumnSizes[j]) << s.substr(0, vnColumnSizes[j]) << " | ";
						s.erase(0, vnColumnSizes[j]);
						// Use SetCursorPosition to prevent going out of lines
						SetCursorPosition(csbiTable.dwCursorPosition.X, (csbiTable.dwCursorPosition.Y + 1));
						nNumOfVertLines++;
					}

					// Put cursor position back to normal
					SetCursorPosition(csbiTable.dwCursorPosition.X, (csbiTable.dwCursorPosition.Y));
				}
				else {

					// Temporary CSBI for original cursor position
					CONSOLE_SCREEN_BUFFER_INFO csbiTemp;

					// Output members based on nColumnWidth width
					std::cout << std::setw(vnColumnSizes[j]) << std::left << vsTable[i][j] << " | ";
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiTemp);

					// Output correct number of vertical lines
					for (uint64_t i = 0; i < nNumOfVertLines; i++) {
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiTable);
						std::cout << "\b\b\b | ";
						SetCursorPosition(csbiTable.dwCursorPosition.X, (csbiTable.dwCursorPosition.Y + 1));
					}

					// Set cursor to original position to continue writing normally
					SetCursorPosition(csbiTemp.dwCursorPosition.X, (csbiTemp.dwCursorPosition.Y));
				}
				nNumOfVertLines = 1;
			}
			std::cout << std::endl;

			if (i == 0) {
				// Output line for table headings
				for (uint64_t j = 0; j < vnColumnSizes.size(); j++) {
					for (uint64_t k = 0; k < vnColumnSizes[j]; k++) {
						std::cout << '_';
					}
					std::cout << "_|_";
				}
				// Erase the trailing underscore line
				std::cout << "\b " << std::endl;
			}
		}
	}
};