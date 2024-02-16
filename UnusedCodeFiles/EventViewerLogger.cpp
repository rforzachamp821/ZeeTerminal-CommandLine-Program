//
// EventViewerLogger.cpp - File containing the EventViewerLogger class.
//

// EventViewerLogger - Manages Windows Event Viewer logging.
class EventViewerLogger
{
private:
	// Object ID
	int nObjectID;

public:
	EventViewerLogger() {
		// Object ID initialisation
		static int nStaticID = 10000;
		// Wrap-around to prevent overflow
		if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
		nObjectID = ++nStaticID;

		// Clear vector
		sEventDataArray.clear();

		VerbosityDisplay("New EventViewerLogger Object Created.\n");
		return;
	}

	~EventViewerLogger() {
		VerbosityDisplay("EventViewerLogger Object has been destroyed.\n");
		return;
	}

	std::vector<std::string> sEventDataArray{};

	bool LogEvent(DWORD dwBinaryDataSize, LPVOID lpBinaryData)
	{
		// Create handle around ZeeTerminal source
		HANDLE hEventSource = RegisterEventSourceA(NULL, "ZeeTerminal");
		size_t nEventDataArraySize = sEventDataArray.size();

		// Convert std::string array to LPCSTR
		LPCSTR* lpEventData = new LPCSTR[nEventDataArraySize];
		// Use for loop
		for (size_t i = 0; i < nEventDataArraySize; i++) {
			lpEventData[i] = sEventDataArray[i].c_str();
		}

		// Report the event to event log
		if (!ReportEventA(hEventSource, EVENTLOG_ERROR_TYPE, 0, 0, NULL, nEventDataArraySize, dwBinaryDataSize, lpEventData, lpBinaryData)) {
			std::cerr << "Failed with code " << GetLastError() << "\n";
			return false;
		}

		// Uninitialise and exit
		DeregisterEventSource(hEventSource);
		delete[] lpEventData;

		return true;
	}
};