#include <mmsystem.h>
#include <dshow.h>
#include <sapi.h>
#include <Windows.h>

// BASS libs
#include "bass.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "bass.lib")

void		Exiting();
void		VerbosityDisplay(std::string);
void		UserErrorDisplay(std::string);
void		colour(std::string, std::string);
void		ClearKeyboardBuffer();
void		SetCursorAttributes();
std::string wordWrap(std::string, long long int, long long int);
std::string CentreText(std::string);

class MultimediaEngine {

protected:

	// RemoveFilters - Removes all filters from IGraphBuilder variable.
	// Arguments: pGraph for the graph to remove filters from.
	// Returns true for success, false for fail.
	//
	bool RemoveFilters(IGraphBuilder* pGraph) 
	{
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
			UserErrorDisplay("ERROR - Failed to clear all filters.\n");
			pEnum->Release();
			return false;
		}

		pEnum->Release();
		return true;
	}

public:

	// Constructor
	MultimediaEngine() {
		VerbosityDisplay("MultimediaEngine Object Created.\n");
		// Nothing to set after this
	}
	
	// Destructor
	~MultimediaEngine() {
		VerbosityDisplay("MultimediaEngine Object Destroyed.\n");
		// Nothing to delete/destroy after this
	}

	// DShowMultimediaPlayer - Plays a multimedia file using the DirectShow API.
	// Allowed filetypes are: WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, JPG, JPEG, BMP
	// Arguments: wsInputFilePath - The file path for the multimedia file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool DShowMultimediaPlayer(std::wstring wsInputFilePath) {
		IGraphBuilder* pGraph = NULL;
		IMediaControl* pControl = NULL;
		IMediaEvent* pEvent = NULL;
		std::wstring wsFilePath;
		bool bSuccess = true;
		bool bRepeatActivated = false;
		bool bUserCursorVisibilitySetting = ConfigObjMain.bShowCursor;

		std::cout << '\n';

		// Check for speechmarks in case of copy from file explorer
		if (wsInputFilePath[0] == '"' && wsInputFilePath[wsInputFilePath.length() - 1] == '"') {
			wsFilePath = wsInputFilePath.substr(1, (wsInputFilePath.length() - 2));
		}
		else wsFilePath = wsInputFilePath;

		// Initialize the COM library
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		if (FAILED(hr))
		{
			VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Failed to initialise the COM library.");
			UserErrorDisplay("ERROR: Failed to load libraries that are required for operation. Please try again later.\n");

			bSuccess = false;
			goto cleanup;
		}

	playfile:
		// Create the filter graph manager and query for interfaces.
		// CLSCTX_INPROC_SERVER is the original one
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
		if (FAILED(hr))
		{
			VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Could not create the DirectShow Filter Graph Manager.");
			UserErrorDisplay("ERROR: Failed to create the media player's management system. Please try again later.\n");

			bSuccess = false;
			goto cleanup;
		}

		// Initialise media controls
		hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
		if (FAILED(hr))
		{
			VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Could not create the DirectShow Filter Media Controls.");
			UserErrorDisplay("ERROR: Failed to initialise the media control system. Please try again later.\n");

			bSuccess = false;
			goto cleanup;
		}

		// Initialise the event manager
		hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
		if (FAILED(hr))
		{
			VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Could not create the DirectShow Filter Media Event.");
			UserErrorDisplay("ERROR: Failed to initialise the Media Event Manager. Please try again later.\n");

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
					VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Failed to get current duration.\n");
				}

				// Audio controls
				if (bRepeatActivated == false)
					std::cout << wordWrap("Press space or 'p' to pause/unpause, 'r' to activate repeating media file, and ESC or 'e' to exit.\nPress the left arrow key to go backwards, and the right arrow key to fast forward.\n\n\n\n");
				
				// Turn off cursor visibility, as it would cause flickering when outputting media time
				ConfigObjMain.bShowCursor = false;
				SetCursorAttributes();

				while (dCurrentPosition < dDuration) {

					// Get current media reading position
					hr = pPos->get_CurrentPosition(&dCurrentPosition);

					// Output position
					std::cout << "Media file: ";
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << dCurrentPosition;
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
					std::cout << " sec out of ";
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << (int)dDuration;
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
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
						colour(YLW, ConfigObjMain.sColourGlobalBack);
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
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

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
							UserErrorDisplay("An error occured when seeking forwards.\n");
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
							UserErrorDisplay("An error occured when seeking backwards.\n");
							continue;
						}

						continue;
					}
					else if (c == 'r') {
						// Set colour of messages
						colour(YLW, ConfigObjMain.sColourGlobalBack);
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
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

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
						VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Filter unloading failed, therefore repeating media failed.\n");
						UserErrorDisplay("ERROR: Failed to repeat media playback.\n");
						bSuccess = false;
						goto cleanup;
					}

					goto playfile;
				}


			}
			else {
				VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Could not play back media. Check if the file was deleted?\n");
				UserErrorDisplay("ERROR: Failed to play back media. Check if the file was deleted, and try again later.\n");
				bSuccess = false;
				goto cleanup;
			}

			// Stop playback
			pControl->Stop();
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << '\n' << CentreText("Playback finished.") << '\n';
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else {
			VerbosityDisplay("In MultimediaEngine::DShowMultimediaPlayer(): ERROR - Render file to graph operation failed. Possible bad file format.\n");
			UserErrorDisplay("ERROR: Failed to read from file. Please check if the file meets the file format requirements, and try again later.\n");
			bSuccess = false;
			goto cleanup;
		}

	cleanup:

		// Revert cursor visibility back to user default
		ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
		SetCursorAttributes();

		// Clean up in reverse order.
		RemoveFilters(pGraph);
		pEvent->Release();
		pControl->Release();
		pGraph->Release();
		CoUninitialize();

		return bSuccess;
	}

	// BASSAudioPlayer - Plays an audio file using the BASS Audio API.
	// Allowed filetypes are: MP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC
	// Arguments: sInputFilePath - The file path for the audio file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool BASSAudioPlayer(std::string sInputFilePath) {
		std::string sFilePath = "";
		bool bRepeatActivated = false;
		bool bUserCursorVisibilitySetting = ConfigObjMain.bShowCursor;

		// Check for speechmarks in case of copy from file explorer
		if (sInputFilePath[0] == '"' && sInputFilePath[sInputFilePath.length() - 1] == '"') {
			sFilePath = sInputFilePath.substr(1, (sInputFilePath.length() - 2));
		}
		else sFilePath = sInputFilePath;

		// Initialize BASS library
		if (!BASS_Init(-1, 192000, BASS_DEVICE_FREQ, 0, NULL)) {
			VerbosityDisplay("In MultimediaEngine::BASSAudioPlayer(): ERROR - Failed to initialise the BASS library.\n");
			UserErrorDisplay("ERROR: Failed to load the required libraries to start the BASS Audio Player. Please try again later.\n");

			return false;
		}

		// Load plugins for OPUS, FLAC
		HPLUGIN pluginopus = BASS_PluginLoad("bassopus.dll", 0);
		if (pluginopus == 0) {
			VerbosityDisplay("ERROR - Failed to load OPUS plugin.\nPlease check if the bassopus.dll file is in the same directory as ZeeTerminal.\nWill proceed anyway.\n");
		}
		HPLUGIN pluginflac = BASS_PluginLoad("bassflac.dll", 0);
		if (pluginflac == 0) {
			VerbosityDisplay("ERROR - Failed to load FLAC plugin.\nPlease check if the bassflac.dll file is in the same directory as ZeeTerminal.\nWill proceed anyway.\n");
		}

		do {
			// BASS_STREAM_PRESCAN is incredibly important for skipping to EOF when using BASS_ChannelSetPosition(). 
			// Provides accurate, rather than approximate, values.
			HSTREAM stream = BASS_StreamCreateFile(FALSE, sFilePath.c_str(), 0, 0, BASS_STREAM_PRESCAN);
			if (stream == 0) {
				// Error message
				VerbosityDisplay("In MultimediaEngine::BASSAudioPlayer(): ERROR - Failed to load file into stream. Possibly nonexistent file, or a bug on the developer's end.\n");
				UserErrorDisplay("ERROR: Failed to load file into stream. Possibly nonexistent file, please try again later.\n");

				BASS_PluginFree(pluginflac);
				BASS_PluginFree(pluginopus);
				BASS_Free();
				return false;
			}

			long double dDuration = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE));
			// Play the audio file
			if (!BASS_ChannelPlay(stream, bRepeatActivated)) {
				// Error message
				VerbosityDisplay("In MultimediaEngine::BASSAudioPlayer(): ERROR - Failed to play file. Bad file format/corrupted file possible.\n");
				UserErrorDisplay("ERROR: Failed to play file. Possibly a corrupt file, or an incorrect file format.\n");

				BASS_StreamFree(stream);
				BASS_PluginFree(pluginflac);
				BASS_PluginFree(pluginopus);
				BASS_Free();
				return false;
			}

			double dCurrentPosition = 0;
			char c;
			bool bWasPaused = false;
			CONSOLE_SCREEN_BUFFER_INFO csbiPlayer;
			COORD CursorPos{};

			// Media controls
			if (bRepeatActivated == false)
				std::cout << wordWrap("Press space or 'p' to pause/unpause, 'r' to activate repeating media file, and ESC or 'e' to exit.\nPress the left arrow key to seek backwards, and the right arrow key to seek forwards.\n\n\n\n");
			
			// Set cursor visibility to false to prevent flickering when showing media time
			ConfigObjMain.bShowCursor = false;
			SetCursorAttributes();
			
			while (dCurrentPosition < dDuration) {

				// Get position
				dCurrentPosition = BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetPosition(stream, BASS_POS_BYTE));
				// Output position
				std::cout << "Audio file: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << dCurrentPosition;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << " sec out of ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << (int)dDuration;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				std::cout << " sec        \r";

				if (_kbhit()) {
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

				// Pause audio playback
				if (c == ' ' || c == 'p' || c == 'P') {
					// Get cursor position and set it to one higher than media output 
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiPlayer);
					CursorPos.Y = csbiPlayer.dwCursorPosition.Y - 1;
					CursorPos.X = csbiPlayer.dwCursorPosition.X;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);

					if (!bWasPaused) {
						// Output according message to what happened with the function
						if (BASS_ChannelPause(stream)) {
							colour(YLW, ConfigObjMain.sColourGlobalBack);
							std::cout << "Paused.           ";
							colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
							bWasPaused = true;
						}
						else {
							colour(RED, ConfigObjMain.sColourGlobalBack);
							std::cerr << "Failed to pause.  ";
							colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
							continue;
						}
					}
					else {
						// Output according message to what happened with the function
						if (BASS_ChannelPlay(stream, false)) {
							colour(YLW, ConfigObjMain.sColourGlobalBack);
							std::cout << "Unpaused.         ";
							colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
							bWasPaused = false;
						}
						else {
							colour(RED, ConfigObjMain.sColourGlobalBack);
							std::cerr << "Failed to unpause.";
							colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
							continue;
						}
					}

					// Finally, reset cursor position
					CursorPos.Y = csbiPlayer.dwCursorPosition.Y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);
					continue;
				}

				// Replay audio toggle
				else if (c == 'r' || c == 'R') {
					// Get cursor co-ords
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiPlayer);
					CursorPos.Y = csbiPlayer.dwCursorPosition.Y - 2;
					CursorPos.X = csbiPlayer.dwCursorPosition.X;

					// Set cursor position in relation to media file stats output
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);

					// Set repeat boolean to true/false depending on what was set before
					if (bRepeatActivated) {
						colour(YLW, ConfigObjMain.sColourGlobalBack);
						std::cout << "Repeat deactivated."; // Spaces if deactivated previously
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
						bRepeatActivated = false;
					}
					else {
						colour(YLW, ConfigObjMain.sColourGlobalBack);
						std::cout << "Repeat activated.  "; // Spaces if deactivated previously
						colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
						bRepeatActivated = true;
					}

					CursorPos.Y = csbiPlayer.dwCursorPosition.Y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);

					continue;
				}

				// Exit playback
				else if (c == 27 || c == 'e' || c == 'E') { // 27 is ASCII for ESC
					std::cout << std::endl;
					if (!BASS_Stop()) {
						VerbosityDisplay("In MultimediaEngine::BASSAudioPlayer(): ERROR - Failed to stop audio playback before exit.\n");
					}
					else {
						Exiting();

						// Revert cursor visibility back to user default
						ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
						SetCursorAttributes();

						// Free resources
						BASS_StreamFree(stream);
						BASS_PluginFree(pluginflac);
						BASS_PluginFree(pluginopus);
						BASS_Free();
					}

					return true;
				}

				// Seek forwards
				else if (c == 77 || c == 'd' || c == 'D') { // 77 is ASCII for right arrow
					if (dCurrentPosition + 5 <= dDuration) {
						if (!BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, dCurrentPosition + 5), BASS_POS_BYTE)) {
							UserErrorDisplay("An error occured when seeking forwards.\n");
							continue;
						}
					}
					else {
						if (!BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, dDuration - 0.00001), BASS_POS_BYTE)) {
							UserErrorDisplay("An error occured when seeking forwards.\n");
							continue;
						}
					}

					continue;
				}

				// Seek backwards
				else if (c == 75 || c == 'a' || c == 'A') { // 75 is ASCII for left arrow
					if (dCurrentPosition - 5 >= 0) {
						if (!BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, dCurrentPosition - 5), BASS_POS_BYTE)) {
							UserErrorDisplay("An error occured when seeking backwards.\n");
							continue;
						}
					}
					else {
						if (!BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, 0), BASS_POS_BYTE)) {
							UserErrorDisplay("An error occured when seeking backwards.\n");
							continue;
						}
					}

					continue;
				}

			}

			// Free resources
			BASS_StreamFree(stream);

		} while (bRepeatActivated == true);

		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << '\n' << CentreText("Playback finished.") << '\n';
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Revert cursor visibility back to user default
		ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
		SetCursorAttributes();

		// Clear the BASS library memory
		BASS_PluginFree(pluginflac);
		BASS_PluginFree(pluginopus);
		BASS_Free();

		return true;
	}

	// MMAPIAudioPlayer - Plays a WAV file using the Windows MultiMedia API.
	// Arguments: wsInputFilePath - The file path for the WAV file.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool MMAPIAudioPlayer(std::string sInputFilePath) {

		std::string sFilePath;

		// Check for speechmarks in case of copy from file explorer
		if (sInputFilePath[0] == '"' && sInputFilePath[sInputFilePath.length() - 1] == '"') {
			sFilePath = sInputFilePath.substr(1, (sInputFilePath.length() - 2));
		}
		else sFilePath = sInputFilePath;

		if (PlaySoundA(sFilePath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
			return true;
		}
		else {
			VerbosityDisplay("In MultimediaEngine::MMAPIAudioPlayer(): ERROR - File not found, or incorrect path detected.\n");
			UserErrorDisplay("ERROR: File doesn't seem to be found. Please check your filepath and try again.\n");

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

		if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) {
			VerbosityDisplay("In MultimediaEngine::TTSOutput(): ERROR - Failed to initialise the COM library.\n");
			UserErrorDisplay("ERROR: The required libraries to run Text-To-Speech failed to load. Please try again later.\n");

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
			VerbosityDisplay("In MultimediaEngine::TTSOutput(): ERROR - Failed to create SAPI instance.\n");
			UserErrorDisplay("ERROR: Failed to create the handler to output the voice audio. Please try again later.\n");

			CoUninitialize();
			return false;
		}

		CoUninitialize();
		return true;
	}

	// BeepSound - Produces access to produce a low-latency, audible and constant beep sound.
	// Arguments: dFrequency - Set the frequency of the beep sound. This is measured in Hertz.
	//            dDuration - Set the duration of the sound. This is measured in MILLISECONDS.
	//            bExitOnKeyPress - Exit on keypress while sound is being outputted.
	// Return values: TRUE or 1 for uninterrupted output, and FALSE or 0 for key pressed.
	// Notes: Providing no arguments will give a 500hz beep sound for 1 second.
	//
	bool BeepSound(long double dFrequency = 500, long double dDuration = 1, bool bExitOnKeyPress = false) {
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx;
		wfx.wFormatTag = WAVE_FORMAT_PCM;
		wfx.nChannels = 1;
		wfx.nSamplesPerSec = 48000;
		wfx.nAvgBytesPerSec = 48000 * 2;
		wfx.nBlockAlign = 2;
		wfx.wBitsPerSample = 16;
		wfx.cbSize = 0;
		bool bReturnValue = true;

		const int bufferSize = wfx.nSamplesPerSec * wfx.nBlockAlign * (dDuration * 0.001);
		short int* buffer = new short int[bufferSize];

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		for (int j = 0; j < bufferSize / sizeof(short); j++)
		{
			double t = (double)j / (double)wfx.nSamplesPerSec;
			buffer[j] = (short)(32767.0 * sin(2.0 * M_PI * dFrequency * t));
		}

		WAVEHDR whdr;
		whdr.lpData = (LPSTR)buffer;
		whdr.dwBufferLength = bufferSize;
		whdr.dwFlags = 0;

		waveOutPrepareHeader(hWaveOut, &whdr, sizeof(whdr));
		waveOutWrite(hWaveOut, &whdr, sizeof(whdr));
		while ((whdr.dwFlags & WHDR_DONE) == 0) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			if (_kbhit() && bExitOnKeyPress == true) {
				waveOutReset(hWaveOut);
				// Clean keyboard buffer to clear the key that was inputted
				ClearKeyboardBuffer();
				bReturnValue = false;
				break;
			}
		}

		waveOutUnprepareHeader(hWaveOut, &whdr, sizeof(whdr));

		delete[] buffer;

		waveOutClose(hWaveOut);

		return bReturnValue;
	}
};