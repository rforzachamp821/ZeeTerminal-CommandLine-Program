
std::wstring s2ws(const std::string&);
std::string ws2s(const std::wstring&);
void VerbosityDisplay(std::string);
void UserErrorDisplay(std::string);

// FileOpenGUIEngine - Engine for the File Open Dialogue Box GUI.
//
class FileOpenGUIEngine {
protected:

	std::string sFinalFilePath = "";

	// ThoroughRelease - Releases an object and clears all its memory allocation automatically.
	// Please note that using this method should only be used on exit, as using this function 
	// will not allow using the same variable again.
	// 
	// Arguments - *iObject - the object to release/clear.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool ThoroughRelease(IUnknown *iObject) 
	{
		HRESULT hr = S_OK;

		// Attempt to release object.
		if (iObject) {
			hr = iObject->Release();
			if (FAILED(hr)) goto done;
		}

	done:

		// Output message if failed
		if (FAILED(hr)) {
			VerbosityDisplay("Failed to thoroughly release object.");
			return false;
		}
		else return true;
		
		return true;
	}

public:

	// Constructor
	FileOpenGUIEngine() {
		VerbosityDisplay("FileOpenGUIEngine Object Created.\n");
		sFinalFilePath = "";
	}

	// Destructor
	~FileOpenGUIEngine() {
		VerbosityDisplay("FileOpenGUIEngine Object Destroyed.\n");
		// Nothing to clear/destroy
	}

	// FileOpenDialogue - Opens a Windows file dialogue, with a custom title.
	// Arguments - sTitle: The title of the dialogue window, as a string.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool FileOpenDialogue(std::string sTitle) {
		HRESULT hr = S_OK;

		IFileOpenDialog* pFileOpen = NULL;
		IShellItem* pItem = NULL;

		LPWSTR pwszFilePath = NULL;

		// Initialise COM libraries
		hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (FAILED(hr)) {
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Could not initialise the COM library.\n");
			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to load libraries that are required for operation. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			goto done;
		}

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(
			CLSID_FileOpenDialog,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pFileOpen)
		);

		if (FAILED(hr)) { 
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Could not initialise the FileOpenDialog object.\n");
			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to create platform for the dialogue box. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			goto done; 
		}

		// Set the title
		hr = pFileOpen->SetTitle(s2ws(sTitle).c_str());

		if (FAILED(hr)) {
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to set window title of dialogue box.\n");
			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to set the title for the dialogue box. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			goto done;
		}

		// Show the file-open dialog.
		hr = pFileOpen->Show(NULL);

		if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
		{
			// User cancelled.
			hr = S_OK;
			goto done;
		}
		else if (FAILED(hr)) {
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to display the file dialogue box using current setup.\n");
			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to display the file dialogue box. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			goto done;
		}


		// Get the file name from the dialog.
		hr = pFileOpen->GetResult(&pItem);

		if (FAILED(hr)) {
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to get the full results from the File Dialogue Box.\n");
			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to get results, such as filepath, from the dialogue box platform. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			goto done;
		}

		hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);
		sFinalFilePath = ws2s(pwszFilePath);

		if (FAILED(hr)) {
			VerbosityDisplay("In FileOpenGUIEngine::FileOpenDialogue(): ERROR - Failed to get the filepath from the results from the File Dialogue Box.\n");
			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to get filepath from gathered results from the dialogue box platform. Please try again later.\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			goto done;
		}

	done:

		CoTaskMemFree(pwszFilePath);

		if (pItem)
		{
			ThoroughRelease(pItem);
		}
		if (pFileOpen)
		{
			ThoroughRelease(pFileOpen);
		}

		CoUninitialize();

		if (FAILED(hr)) return false; else return true;
	}

	// GetFileName - Gets the file name of the open dialogue that was returned to the associated object.
	// Arguments - NONE
	// Return Values - The string of the final filepath.
	//
	std::string GetFileName() {
		return sFinalFilePath;
	}
};