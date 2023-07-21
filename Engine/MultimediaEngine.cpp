#include <mmsystem.h>
#include <dshow.h>
#include <sapi.h>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "strmiids.lib")

void Exiting();
void VerbosityDisplay(std::string);
void colour(std::string, std::string);
std::string CentreText(std::string);

class MultimediaEngine {
protected:

	// RemoveFilters - Removes all filters from IGraphBuilder variable.
	// Arguments: pGraph for the graph to remove filters from.
	// Returns true for success, false for fail.
	//
	bool RemoveFilters(IGraphBuilder* pGraph) {
		// Enumerate the filters in the graph.
		IEnumFilters* pEnum = NULL;
		HRESULT hr = pGraph->EnumFilters(&pEnum);
		if (SUCCEEDED(hr))
		{
			IBaseFilter* pFilter = NULL;
			while (S_OK == pEnum->Next(1, &pFilter, NULL))
			{
				// Remove the filter.
				pGraph->RemoveFilter(pFilter);
				// Reset the enumerator.
				pEnum->Reset();
				pFilter->Release();
			}
			pEnum->Release();

			return true;
		}
		else {
			std::cerr << "ERROR - Failed to clear all filters.\n";
			pEnum->Release();
			return false;
		}

		pEnum->Release();
		return true;
	}

public:

	// MultimediaRenderer - Plays a multimedia file using the DirectShow API.
	// Allowed filetypes are: WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, JPG, JPEG, BMP
	// Arguments: wsInputFilePath - The file path for the multimedia file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool MultimediaPlayer(std::wstring wsInputFilePath) {
		IGraphBuilder* pGraph = NULL;
		IMediaControl* pControl = NULL;
		IMediaEvent* pEvent = NULL;
		std::wstring wsFilePath;
		bool bSuccess = true;
		bool bRepeatActivated = false;

		std::cout << '\n';

		// Check for speechmarks in case of copy from file explorer
		if (wsInputFilePath[0] == '"' && wsInputFilePath[wsInputFilePath.length() - 1] == '"') {
			wsFilePath = wsInputFilePath.substr(1, (wsInputFilePath.length() - 2));
		}
		else wsFilePath = wsInputFilePath;

		// Initialize the COM library
		HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			VerbosityDisplay("ERROR - Could not initialize COM library");
			bSuccess = false;
			goto cleanup;
		}

	playfile:
		// Create the filter graph manager and query for interfaces.
		// CLSCTX_INPROC_SERVER is the original one
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
		if (FAILED(hr))
		{
			VerbosityDisplay("ERROR - Could not create the Filter Graph Manager.");
			bSuccess = false;
			goto cleanup;
		}

		// Initialise media controls
		hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
		if (FAILED(hr))
		{
			VerbosityDisplay("ERROR - Could not create the Filter Media Controls.");
			bSuccess = false;
			goto cleanup;
		}

		// Initialise the event manager
		hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
		if (FAILED(hr))
		{
			VerbosityDisplay("ERROR - Could not create the Filter Media Event.");
			bSuccess = false;
			goto cleanup;
		}

		// Build the graph.
		hr = pGraph->RenderFile(wsFilePath.c_str(), NULL);
		if (SUCCEEDED(hr))
		{
			// Run the graph.
			hr = pControl->Run();
			if (SUCCEEDED(hr))
			{
				// Initialise variables
				char c;
				bool bWasPaused = false;
				IMediaPosition* pPos = NULL;
				double dDuration = 0;
				double dCurrentPosition = 0;
				CONSOLE_SCREEN_BUFFER_INFO csbiPlayer;
				COORD CursorPos{};

				// Image File UI
				if (wsFilePath.find(L".jpeg", wsFilePath.length() - 6) != std::string::npos || wsFilePath.find(L".jpg", wsFilePath.length() - 5) != std::string::npos || wsFilePath.find(L".bmp", wsFilePath.length() - 5) != std::string::npos) {
					std::cout << "Press any key to exit displaying image.\n";
					_getch();
					bSuccess = true;
					goto cleanup;
				}

				// Get length of file
				hr = pGraph->QueryInterface(IID_IMediaPosition, (void**)&pPos);
				hr = pPos->get_Duration(&dDuration);
				if (FAILED(hr)) {
					VerbosityDisplay("ERROR - Failed to get current duration.\n");
				}

				// Audio controls
				if (bRepeatActivated == false)
					std::cout << "Press space or 'p' to pause/unpause, 'r' to activate repeating media file, and ESC or 'e' to exit.\nPress the left arrow key to go backwards, and the right arrow key to fast forward.\n\n\n\n";
				while (dCurrentPosition < dDuration) {

					// Get current media reading position
					hr = pPos->get_CurrentPosition(&dCurrentPosition);

					// Output position
					std::cout << "Media file: ";
					colour(LCYN, sColourGlobalBack);
					std::cout << dCurrentPosition;
					colour(sColourGlobal, sColourGlobalBack);
					std::cout << " sec out of ";
					colour(LCYN, sColourGlobalBack);
					std::cout << (int)dDuration;
					colour(sColourGlobal, sColourGlobalBack);
					std::cout << " sec        \r";

					// For compatibility with check for finished playback
					if (_kbhit()) {
						// Get character
						c = _getch();
					}
					else {
						// Optimisation for putting cpu in sleep for 50/20ms every iteration
						if (bWasPaused == true) {
							std::this_thread::sleep_for(std::chrono::milliseconds(50));
						}
						else {
							std::this_thread::sleep_for(std::chrono::milliseconds(20));
						}

						continue;
					}

					// Controls
					if (c == ' ' || c == 'p' || c == 'P') {
						// Set colour of messages
						colour(YLW, sColourGlobalBack);
						// Get cursor position and set it to one higher than media output 
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiPlayer);
						CursorPos.Y = csbiPlayer.dwCursorPosition.Y - 1;
						CursorPos.X = csbiPlayer.dwCursorPosition.X;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);

						if (bWasPaused == true) {
							hr = pControl->Run();
							if (FAILED(hr))
								std::cerr << "Failed to unpause.";
							else {
								std::cout << "Unpaused.";
								bWasPaused = false;
							}
						}
						else {
							hr = pControl->Pause();
							if (FAILED(hr))
								std::cerr << "Failed to pause.";
							else {
								std::cout << "Paused.  ";
								bWasPaused = true;
							}
						}

						// Finally, reset cursor position and colours
						CursorPos.Y = csbiPlayer.dwCursorPosition.Y;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);
						colour(sColourGlobal, sColourGlobalBack);

						continue;
					}
					else if (c == 27 || c == 'e' || c == 'E') {
						std::cout << '\n';
						Exiting();
						pControl->Stop();
						bSuccess = true;
						goto cleanup;
						break;
					}
					else if (c == 77 || c == 'd' || c == 'D') { // 77 is ASCII for right arrow
						if (dCurrentPosition + 5 <= dDuration) {
							hr = pPos->put_CurrentPosition(dCurrentPosition + 5);
						}
						else hr = pPos->put_CurrentPosition(dDuration);

						if (FAILED(hr)) {
							colour(RED, sColourGlobalBack);
							std::cerr << "An error occured when fast-forwarding.\n";
							colour(sColourGlobal, sColourGlobalBack);
							continue;
						}

						continue;
					}
					else if (c == 75 || c == 'a' || c == 'A') { // 75 is ASCII for left arrow
						if (dCurrentPosition - 5 >= 0) {
							hr = pPos->put_CurrentPosition(dCurrentPosition - 5);
						}
						else hr = pPos->put_CurrentPosition(0);

						if (FAILED(hr)) {
							colour(RED, sColourGlobalBack);
							std::cerr << "An error occured when seeking backwards.\n";
							colour(sColourGlobal, sColourGlobalBack);
							continue;
						}

						continue;
					}
					else if (c == 'r') {
						// Set colour of messages
						colour(YLW, sColourGlobalBack);
						// Get cursor co-ords
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiPlayer);
						CursorPos.Y = csbiPlayer.dwCursorPosition.Y - 2;
						CursorPos.X = csbiPlayer.dwCursorPosition.X;

						// Set cursor position in relation to media file stats output
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);

						// Set repeat boolean to true/false depending on what was set before
						if (bRepeatActivated) {
							std::cout << "Repeat deactivated.";
							bRepeatActivated = false;
						}
						else {
							std::cout << "Repeat activated.  "; // Spaces if deactivated previously
							bRepeatActivated = true;
						}

						// Reset co-ords and colours to previous
						CursorPos.Y = csbiPlayer.dwCursorPosition.Y;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);
						colour(sColourGlobal, sColourGlobalBack);

						continue;
					}

				}
				// Repeat audio if activated
				if (bRepeatActivated == true) {
					// Setop audio in case
					pControl->Stop();

					// Remove filters
					if (RemoveFilters(pGraph) == true) {
						goto playfile;
					}
					else {
						VerbosityDisplay("ERROR - Failed to repeat media.\n");
						bSuccess = false;
						goto cleanup;
					}

					goto playfile;
				}


			}
			else {
				VerbosityDisplay("ERROR - Could not play back media. Check if the file was removed?\n");
				bSuccess = false;
				goto cleanup;
			}

			colour(LGRN, sColourGlobalBack);
			std::cout << '\n' << CentreText("Playback finished.") << '\n';
			colour(sColourGlobal, sColourGlobalBack);
		}
		else {
			VerbosityDisplay("ERROR - Failed to read file. Possibly wrong file format?\n");
			bSuccess = false;
			goto cleanup;
		}

	cleanup:
		// Stop playback just in case
		pControl->Stop();

		// Clean up in reverse order.
		RemoveFilters(pGraph);
		pEvent->Release();
		pControl->Release();
		pGraph->Release();
		CoUninitialize();

		return bSuccess;
	}

	// MMAPIAudioPlayer - Plays a WAV file using the Windows MultiMedia API.
	// Arguments: wsFilePath - The file path for the WAV file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool MMAPIAudioPlayer(std::wstring wsInputFilePath) {

		std::wstring wsFilePath;

		// Check for speechmarks in case of copy from file explorer
		if (wsInputFilePath[0] == '"' && wsInputFilePath[wsInputFilePath.length() - 1] == '"') {
			wsFilePath = wsInputFilePath.substr(1, (wsInputFilePath.length() - 2));
		}
		else wsFilePath = wsInputFilePath;

		if (PlaySoundW(wsFilePath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
			return true;
		}
		else {
			VerbosityDisplay("MMAPIAudioPlayer error: file not found.");
			return false;
		}

		return true;
	}

	// TTSOutput - Takes in an std::wstring (wide 'unicode' string) and outputs
	//             it through device speakers with a human-like voice.
	// Arguments: wsText - Text to be outputted as Text-To-Speech.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool TTSOutput(std::wstring wsText) {

		if (FAILED(CoInitialize(NULL))) {
			VerbosityDisplay("ERROR - Failed to initialise the COM library.\n");
			CoUninitialize();
			return true;
		}

		ISpVoice* pVoice = NULL;
		HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);

		if (SUCCEEDED(hr))
		{
			hr = pVoice->Speak(wsText.c_str(), 0, NULL);
			pVoice->Release();
			pVoice = NULL;
			delete pVoice;
		}
		else {
			VerbosityDisplay("ERROR - Failed to create SAPI instance.\n");
			CoUninitialize();
			return false;
		}

		CoUninitialize();
		return true;
	}
};