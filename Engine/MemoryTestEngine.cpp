//
// MemoryTestEngine.cpp - Responsible for the Memory Test Engine and its class, used by the MemTest command.
//

#include <vector>
#include <Windows.h>


// MemoryTestEngine - Engine containing components for memory testing and stressing.
//                  - Contains multithreading support.
//                  - Contains binary search stress testing, linear search verification and testing algorithms, etc.
//                  - The test algorithms involved are intended to fill up the host system's memory to its maximum
//                    WITHOUT restarting it, which can run the risk of memory paging. It is highly recommended to
//                    run the tests with minimal background tasks and open programs to reduce the likelihood of this 
//                    happening, and instead rely on Windows memory compression.
//
class MemoryTestEngine {

private:

	// Keyboard termination global variable - For reporting keyboard press on process execution
	bool bKeyboardTermination = false;

	// KeyboardAbortHandler termination switch
	std::atomic<bool> bKillKeyboardAbortHandler = false;

	// Thread worker termination switch
	std::atomic<bool> bKillThreads = false;

	// Number of logical cores to use for multithreading
	const unsigned int nNumOfThreads = std::thread::hardware_concurrency();

	// Boolean thread completion vector - to indicate thread completion
	std::vector<bool> vThreadCompletionIndicator;


	///////////////////////////////////////
	/*  PROPRIETARY VARIABLES / MEMBERS  */
	///////////////////////////////////////
	
	// Container for index number result for binary search
	uint64_t nIndexNum = 0;

	// To communicate to main threadcall that one thread found the correct number (Binary Search proprietary)
	std::atomic<bool> bNumberFound = false;

	// Vector for all indexes that failed (Linear Searches proprietary)
	std::vector<uint64_t> vFailedIndexes;

	// Number of current errors found in memory on current pass (Linear Searches proprietary)
	uint64_t nNumOfCurrentCheckErrors = 0;

	// Object ID
	int nObjectID;

	
	// BinarySearch - A custom multithreaded binary search algorithm with little optimisation (focused on memory stress, not searching specifically)
	//              - Binary search requires a sorted list, which is how the memory container is initialised.
	//              - This custom algorithm looks only at the memory container, and does not accept a memory container pointer argument.
	// Arguments: nSearchNum - The value to search for.
	//            bMultiThreaded - Use multithreading or not.
	//            nInitialisationThreadNumber - Thread number out of total thread count, which indicates the part of the array to search through for the thread.
	//                                          If bMultiThreaded is TRUE, this must be passed with 0 or above, to nNumOfThreads - 1.
	// Return values: Index of the found number.
	// 
	// NOTE: 0 may be returned when an error occurs. This is normal, as it sets nErrorLevel instead. See nErrorLevel for more info about the error codes.
	//
	void BinarySearch(const uint64_t nSearchNum, bool bMultiThreaded, unsigned int nInitialisationThreadNumber) {

		unsigned int nThreadCount = nNumOfThreads;
		if (bMultiThreaded == false) nThreadCount = 1;

		if (bMultiThreaded == true && (nInitialisationThreadNumber < 0 || nInitialisationThreadNumber > nNumOfThreads - 1)) {
			nErrorLevel = 3;
			VerbosityDisplay("In MemoryTestEngine::BinarySearch(): ERROR - Bad argument to nInitialisationThreadNumber parameter.\n", nObjectID);
			vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
			return;
		}

		// Firstly, set variables
		const uint64_t	nArraySize = nMemoryContainer.size();
		uint64_t		nHighPoint = ((nInitialisationThreadNumber + 1) * (nArraySize / nThreadCount));
		uint64_t		nLowPoint = (nInitialisationThreadNumber * (nArraySize / nThreadCount));
		uint64_t		nMidPoint = 0;

		// Repeat until low and high match
		while (nLowPoint <= nHighPoint && !bKillThreads && !bNumberFound) {
			nMidPoint = (uint64_t)(nLowPoint + (nHighPoint - nLowPoint) * 0.5);

			if (nMemoryContainer[nMidPoint] == nSearchNum) {

				// Memory Verification
				if (nMemoryContainer[nMidPoint] == nMidPoint) {
					nIndexNum = nMidPoint;
					vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
					bNumberFound = true;
					nErrorLevel = 0;
					return;
				}
				else {
					nErrorLevel = 4; // Error found
					vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
					nIndexNum = 0;
					return;
				}
			}
			else if (nMemoryContainer[nMidPoint] < nSearchNum) {

				// Memory Verification
				if (nMemoryContainer[nMidPoint] == nMidPoint) {
					nLowPoint = nMidPoint + 1;
				}
				else {
					nErrorLevel = 4; // Error found
					vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
					nIndexNum = 0;
					return;
				}
			}
			else if (nMemoryContainer[nMidPoint] > nSearchNum) {

				// Memory Verification
				if (nMemoryContainer[nMidPoint] == nMidPoint) {
					nHighPoint = nMidPoint - 1;
				}
				else {
					nErrorLevel = 4; // Error found
					vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
					nIndexNum = 0;
					return;
				}
			}
		}

		// Numbers didn't match as the low point exceeded the high point number or the high point went too low
		nErrorLevel = 2;
		vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
		nIndexNum = 0;
		return;
	}

	// KeyboardAbortHandler - Handler for keyboard abortion
	void KeyboardAbortHandler() {
		while (!_kbhit() && !bKillKeyboardAbortHandler) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		}

		bKeyboardTermination = true;
		ClearKeyboardBuffer();
		return;
	}

	// Reset the thread completion vector, thread kill switch
	void ResetThreads() 
	{
		// Reset thread completion vector
		for (unsigned int i = 0; i < nNumOfThreads; i++) {
			vThreadCompletionIndicator[i] = false;
		}

		// Reset failed indexes vector
		vFailedIndexes.clear();

		// Reset number of check errors
		nNumOfCurrentCheckErrors = 0;

		// Reset kill switch for threads
		bKillThreads = false;
		bKeyboardTermination = false;

		// Reset binary search number found indicator
		bNumberFound = false;

		return;
	}

protected:


	// Memory container in the form of std::vector
	std::vector<uint64_t> nMemoryContainer;

	// nErrorLevel - Error level of error that occured. Error code definitions are below:
	//             - 0: No error has occured, and all operations should be normal. 
	//             - 1: An error occured when getting the size of the host system memory.
	//             - 2: An unknown binary search error has occured, where the random search value wasn't found.
	//             - 3: A bad initialisation thread number was passed into a thread worker.
	//             - 4: An memory error was detected.
	//
	int nErrorLevel = 0;


	// InitialiseMemoryContainer - Initialise the memory container and fill it linearly, depending on host system memory capacity.
	// Arguments: None
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool InitialiseMemoryContainer()
	{
		// Post message of initialisation
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Initialising Memory Container (press any key to abort test now)...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Start thread for checking for keypress abortion
		std::thread KeyboardAbort(&MemoryTestEngine::KeyboardAbortHandler, this);

		// Initialise variables
		uint64_t nMemorySize = 0;
		uint64_t nSupported64BitIntCount = 0;

		// Get system memory in bytes
		MEMORYSTATUSEX SystemMemory = {};
		SystemMemory.dwLength = sizeof(SystemMemory);
		if (!GlobalMemoryStatusEx(&SystemMemory)) {
			nErrorLevel = 1;
			return false;
		}

		// Set how much memory to allocate
		if (bUseTotalPhysicalCapacity == true) {
			nMemorySize = SystemMemory.ullTotalPhys;
		}
		else {
			nMemorySize = SystemMemory.ullAvailPhys;
		}

		// Get the exact number of 64-bit integers that should be initialised
		nSupported64BitIntCount = nMemorySize / 8; // dividing by 16 as we're using unsigned integral values

		// Finally, fill up memory linearly
		nMemoryContainer.reserve(nSupported64BitIntCount); // reserve memory first to make process faster
		for (uint64_t i = 0; i < nSupported64BitIntCount; i++) {
			nMemoryContainer.push_back(i); // Push one integer into container

			// Keypress Detection
			if (bKeyboardTermination == true) {
				// Kill keyboard abortion handler process
				KeyboardAbort.join();
				Exiting();
				return true;
			}
		}

		// Kill keyboard abortion handler process
		bKillKeyboardAbortHandler = true; // communication switch to make handler exit
		KeyboardAbort.join();
		bKeyboardTermination = false; // because the handler would have passed by an opposite line of code upon exit
		bKillKeyboardAbortHandler = false;

		// All went well - return true
		return true;
	}

	// UninitialiseMemoryContainer - Unload and destroy the memory stored in the memory container and bring it back to 0.
	// Arguments: None
	// Return values: None
	//
	void UninitialiseMemoryContainer() {

		// Post message of uninitialisation
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "Uninitialising Memory Container...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		nMemoryContainer.clear();

		return;
	}
	
	//////////////////////////////
	/* THREADS FOR MEMORY TESTS */
	//////////////////////////////

	// PerformLinearSearchOnMemoryThread - Thread worker for PerformLinearSearchOnMemory.
	// Arguments: bMultiThreaded - Use multithreading or not.
	//            nInitialisationThreadNumber - Thread number out of total thread count, which indicates the part of the array to search through for the thread.
	//                                          If bMultiThreaded is TRUE, this must be passed with 0 or above, to nNumOfThreads - 1.
	// Does not return any values.
	//
	void PerformLinearSearchOnMemoryThread(bool bMultiThreaded, unsigned int nInitialisationThreadNumber, std::atomic_ullong& nProgressCounter) 
	{
		// Single or multi core decider
		unsigned int nThreadCount = nNumOfThreads;
		if (bMultiThreaded == false) nThreadCount = 1;

		if (bMultiThreaded == true && (nInitialisationThreadNumber < 0 || nInitialisationThreadNumber > nNumOfThreads - 1)) {
			nErrorLevel = 3;
			VerbosityDisplay("In MemoryTestEngine::PerformLinearSearchOnMemoryThread(): ERROR - Bad argument to nInitialisationThreadNumber parameter.\n", nObjectID);
			vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
			return;
		}

		// Search part of memory container for thread number
		// Optimisation to reduce number of operations made
		int nLocalProgressCounter = 0;
		uint64_t nComparisonNumber = ((nInitialisationThreadNumber + 1) * (nMemoryContainer.size() / nThreadCount));
		for (uint64_t i = nInitialisationThreadNumber * (nMemoryContainer.size() / nThreadCount); i < nComparisonNumber && !bKillThreads; i++, nLocalProgressCounter++) {
			// Check for correct digit
			if (nMemoryContainer[i] != i) {
				nNumOfCurrentCheckErrors++;
				vFailedIndexes.push_back(i);
				nErrorLevel = 3;
			}

			// Increase progress count with 100 reiterations per increment
			if (nLocalProgressCounter >= 100) {
				nProgressCounter += 101;
				nLocalProgressCounter = -1;
			}
		}

		// Communicate to threadcall that thread is done
		vThreadCompletionIndicator[nInitialisationThreadNumber] = true;

		// Return
		return;
	}

	// PerformExtendedLinearSearchOnMemoryThread - Thread worker for PerformExtendedLinearSearchOnMemory.
	// Arguments: bMultiThreaded - Use multithreading or not.
	//            nInitialisationThreadNumber - Thread number out of total thread count, which indicates the part of the array to search through for the thread.
	//                                          If bMultiThreaded is TRUE, this must be passed with 0 or above, to nNumOfThreads - 1.
	// Does not return any values.
	//
	void PerformExtendedLinearSearchOnMemoryThread(bool bMultiThreaded, unsigned int nInitialisationThreadNumber, std::atomic_ullong& nProgressCounter) 
	{
		// Single or multi core decider
		unsigned int nThreadCount = nNumOfThreads;
		if (bMultiThreaded == false) nThreadCount = 1;

		if (bMultiThreaded == true && (nInitialisationThreadNumber < 0 || nInitialisationThreadNumber > nNumOfThreads - 1)) {
			nErrorLevel = 3;
			VerbosityDisplay("In MemoryTestEngine::PerformExtendedLinearSearchOnMemoryThread(): ERROR - Bad argument to nInitialisationThreadNumber parameter.\n", nObjectID);
			vThreadCompletionIndicator[nInitialisationThreadNumber] = true;
			return;
		}

		// Search part of memory container for thread number
		// CPU optimisation to prevent constant division
		uint64_t nComparisonNumber = ((nInitialisationThreadNumber + 1) * (nMemoryContainer.size() / nThreadCount));
		// Optimisation to reduce number of operations made
		int nLocalProgressCounter = 0;
		for (uint64_t i = nInitialisationThreadNumber * (nMemoryContainer.size() / nThreadCount); i < nComparisonNumber && !bKillThreads; i++, nLocalProgressCounter++) 
		{
			// Increase progress count with 100 reiterations per increment
			if (nLocalProgressCounter >= 100) {
				nProgressCounter += 101;
				nLocalProgressCounter = -1;
			}

			// Check for correct digit
			if (nMemoryContainer[i] != i) {
				nNumOfCurrentCheckErrors++;
				vFailedIndexes.push_back(i);
				nErrorLevel = 3;

				// Increase progress count
				continue;
			}

			// Calculate random number
			uint64_t nRandomNumber = RandNum(std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint64_t>::min());
			nMemoryContainer[i] = nRandomNumber;

			// Check for correct digit
			if (nMemoryContainer[i] != nRandomNumber) {
				nNumOfCurrentCheckErrors++;
				vFailedIndexes.push_back(i);
				nErrorLevel = 3;

				// Increase progress count
				continue;
			}

			// Perform operation on memory container index
			uint64_t nRandomDivNumber = RandNum(std::numeric_limits<unsigned short int>::max(), 1); // 1 for prevention from divide by 0 exception
			nMemoryContainer[i] /= nRandomDivNumber;

			// Check for correct digit
			if (nMemoryContainer[i] != (nRandomNumber / nRandomDivNumber)) {
				nNumOfCurrentCheckErrors++;
				vFailedIndexes.push_back(i);
				nErrorLevel = 3;

				// Increase progress count
				continue;
			}

			// Reset memory container cell
			nMemoryContainer[i] = i;

			// Check for correct digit
			if (nMemoryContainer[i] != i) {
				nNumOfCurrentCheckErrors++;
				vFailedIndexes.push_back(i);
				nErrorLevel = 3;

				// Increase progress count
				continue;
			}

			// Increase progress count
		}

		// Communicate to threadcall that thread is done
		vThreadCompletionIndicator[nInitialisationThreadNumber] = true;

		// Return
		return;
	}

public:

	/* bUseTotalPhysicalCapacity - Adjusts how much memory will be reserved and checked on the host system.

	If this is set to true, the memory container will reserve all the memory available on the host system.
			 - It may cause slowdowns if there are too many programs running.
	If this is set to false, the memory container will reserve all the currently unused available memory on the host system.
			 - This may lead to a less accurate test when too much memory is being used by other programs at test starting time.
	*/
	bool bUseTotalPhysicalCapacity = false;

	MemoryTestEngine() {
		static int nStaticID = 10000;
		// Wrap-around to prevent overflow
		if (nStaticID >= std::numeric_limits<int>::max() - 1) nStaticID = 10000;
		nObjectID = ++nStaticID;

		VerbosityDisplay("MemoryTestEngine Object Created.\n", nObjectID);

		// Reset error level
		nErrorLevel = 0;

		// Set keyboard termination to false
		bKeyboardTermination = false;
		bKillKeyboardAbortHandler = false;

		// Initialise all containers and variables
		vThreadCompletionIndicator.assign(nNumOfThreads, false);

		// Reset thread variables to default
		ResetThreads();

		return;
	}

	~MemoryTestEngine() {
		VerbosityDisplay("MemoryTestEngine Object Destroyed.\n", nObjectID);

		// Clear memory container before exit
		nMemoryContainer.clear();

		return;
	}

	// FillMemoryMaximum - Fills up memory to the maximum that the host's memory can hold, and then unloads memory. Nothing more, nothing less.
	// Arugments: bKeypressBeforeUnload - Require user keypress before unloading memory. True or 1 for requiring keypress, false or 0 for not requiring it.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool FillMemoryToMaximum(bool bKeypressBeforeUnload = false)
	{
		// Record starting time point
		std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

		// Initialise memory
		if (!InitialiseMemoryContainer()) {
			VerbosityDisplay("ERROR: In MemoryTestEngine::FillMemoryToMaximum() - Memory container failed to initialise.\n" + GetLastErrorInfo() + '\n', nObjectID);

			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to initialise memory.\n", nObjectID);
			Exiting();

			return false; // Failed to initialise
		}

		// If key was pressed during the initialisation
		if (bKeyboardTermination == true) {
			UninitialiseMemoryContainer();
			return true;
		}

		// Record ending time point
		std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

		// Get elapsed seconds
		std::chrono::duration<long double> ElapsedSeconds = end - start;

		// Output message
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "Memory initialisation complete.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << "Elapsed time: ";
		colour(LCYN, ConfigObjMain.sColourGlobalBack);
		std::cout << ElapsedSeconds.count();
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << " seconds.\n\n";

		// Check for keypress if that's what is wanted
		if (bKeypressBeforeUnload == true) {
			std::cout << "Press any key to start memory deallocation...\n";
			_getch(); // keypress
		}

		// Uninitialise memory
		UninitialiseMemoryContainer();

		// All went well- return true
		return true;
	}

	// PerformBinarySearchOnMemory - Fills up memory to the maximum that the host's memory can hold, performs random number binary searches depending on the number
	//                               of passes desired, and unloads the memory.
	//                             - This function very lightly checks for memory integrity both during the binary search and after it, and is more of a memory stress test.
	// Arguments: nNumOfPasses - Number of binary search passes to perform.
	//            bMultiThreaded - Use more than 1 thread for the test when this is TRUE.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool PerformBinarySearchOnMemory(uint64_t nNumOfPasses, bool bMultiThreaded)
	{
		unsigned int nThreadCount = nNumOfThreads;

		// Initialise memory
		if (!InitialiseMemoryContainer()) {
			VerbosityDisplay("ERROR: In MemoryTestEngine::PerformBinarySearchOnMemory() - Memory container failed to initialise.\n" + GetLastErrorInfo() + '\n', nObjectID);

			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to initialise memory.\n", nObjectID);
			Exiting();

			return false; // Failed to initialise
		}

		// If key was pressed during the initialisation
		if (bKeyboardTermination == true) {
			UninitialiseMemoryContainer();
			return true;
		}

		if (bMultiThreaded == false) {
			nThreadCount = 1;
		}

		// Perform binary searches using random number
		//
		// Depending on number of passes
		std::cout << '\n';
		for (uint64_t i = 0; i < nNumOfPasses; i++) 
		{
			// Reset thread arguments for next pass
			ResetThreads();

			// Get start time point
			std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

			// Calculate random number
			uint64_t nRandNumber = RandNum(nMemoryContainer.size(), 0);

			// Perform binary search and get index number
			std::cout << "Performing binary search " << i + 1 << " on memory...\n";

			// Declare and execute keyboard handler
			std::thread KeyboardHandlerThread(&MemoryTestEngine::KeyboardAbortHandler, this);
			
			// Declare and execute threads
			std::vector<std::thread> vThreads;
			for (unsigned int j = 0; j < nThreadCount; j++) {
				// Execute a thread
				vThreads.push_back(std::thread(&MemoryTestEngine::BinarySearch, this, nRandNumber, bMultiThreaded, j));
			}

			// While waiting for thread execution completion
			while (!bKeyboardTermination) {
				unsigned int nNumOfCompletedThreads = 0;

				// Check all completion indicators during thread execution
				for (unsigned int j = 0; j < nThreadCount; j++) {
					if (vThreadCompletionIndicator[j] == true) nNumOfCompletedThreads++;
				}

				// Check thread count
				if (nNumOfCompletedThreads >= nThreadCount) {
					break;
				}

				// CPU optimisation
				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			}

			// Kill all threads
			bKillThreads = true;
			for (unsigned int j = 0; j < nThreadCount; j++) {
				vThreads[j].join();
			}
			bKillThreads = false;

			// If keyboard key was pressed
			if (bKeyboardTermination == true) 
			{
				// Kill keyboard abort handler
				bKillKeyboardAbortHandler = true;
				KeyboardHandlerThread.join();
				bKillKeyboardAbortHandler = false;
				bKeyboardTermination = false;

				// Output message and exit
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n\nKeyboard key has been pressed.\nStopping Binary Search Memory Test...\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				break;
			}

			// Kill keyboard abort handler
			bKillKeyboardAbortHandler = true;
			KeyboardHandlerThread.join();
			bKillKeyboardAbortHandler = false;
			bKeyboardTermination = false;

			// To prevent a bug where a line of code isn't meant to be executed at the end of MemoryTestEngine::BinarySearch()
			if (bNumberFound == true) {
				nErrorLevel = 0;
				nIndexNum = nRandNumber;
				bNumberFound = false;
			}

			// Output message if binary search error occured
			if (nIndexNum == 0 && nErrorLevel == 2)
			{
				// Error
				colour(RED, ConfigObjMain.sColourGlobalBack);
				UserErrorDisplay("ERROR: Binary search error occured. The randomised search value wasn't found.\nThis should not be a memory error.\nStopping memory test...\n");
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Uninitialise memory
				UninitialiseMemoryContainer();

				return false;
			}

			// Memory error check after binary
			if (nIndexNum != nRandNumber || nErrorLevel == 4)
			{
				// Memory error found
				nErrorLevel = 4;

				// Notify user of memory error
				VerbosityDisplay("In MemoryTestEngine::PerformBinarySearchOnMemory() - Memory error has been detected.\n", nObjectID);
				colour(RED, ConfigObjMain.sColourGlobalBack);
				UserErrorDisplay("A memory error has been detected during the binary search.\nStopping memory test...\n", nObjectID);
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Uninitialise memory
				UninitialiseMemoryContainer();

				return false;
			}

			// Record final time point
			std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

			// Get elapsed seconds
			std::chrono::duration<long double> ElapsedSeconds = end - start;

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nBinary Search " << i + 1 << " complete.";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << "\nTime elapsed: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << ElapsedSeconds.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << " seconds.\nNo errors have been found throughout this pass.\n\n";
		}

		// Reset threads before exit
		ResetThreads();

		// Uninitialise memory
		UninitialiseMemoryContainer();

		// All went well- return true
		return true;
	}

	// PerformLinearSearchOnMemory - Fills up memory to the maximum that the host's memory can hold, performs linear check searches depending on the number of passes
	//                               desired, and unloads the memory.
	//                             - This function heavily checks for memory integrity by checking for the right values for each byte on memory. This is more of a memory integrity test.
	// Arguments: nNumOfPasses - Number of binary search passes to perform.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool PerformLinearSearchOnMemory(uint64_t nNumOfPasses, bool bMultiThreaded)
	{
		unsigned int nThreadCount = nNumOfThreads;
		CONSOLE_SCREEN_BUFFER_INFO csbiMemTest{};

		// Initialise memory
		if (!InitialiseMemoryContainer()) {
			VerbosityDisplay("ERROR: In MemoryTestEngine::PerformLinearSearchOnMemory() - Memory container failed to initialise.\n" + GetLastErrorInfo() + '\n', nObjectID);

			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to initialise memory.\n", nObjectID);
			Exiting();

			return false; // Failed to initialise
		}

		// If key was pressed during the initialisation
		if (bKeyboardTermination == true) {
			UninitialiseMemoryContainer();
			return true;
		}

		// Check for single threading
		if (bMultiThreaded == false) {
			nThreadCount = 1;
		}

		// Perform linear check search
		uint64_t nNumOfErrorsFound = 0;
		std::vector<uint64_t> vFailedIndexes;
		for (uint64_t nPassIterator = 0; nPassIterator < nNumOfPasses; nPassIterator++)
		{
			// Reset all thread variables
			ResetThreads();

			// Record beginning time point
			std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

			// Notify user of check seatch start
			std::cout << "\nStarting Linear Check Search " << nPassIterator + 1 << ".\n";

			// Declare and execute keyboard handler
			std::thread KeyboardHandlerThread(&MemoryTestEngine::KeyboardAbortHandler, this);


			// Current search value count for progress meters
			std::atomic_ullong nCurrentProgressCount = 0;

			// Declare and execute threads
			std::vector<std::thread> vThreads;
			for (unsigned int j = 0; j < nThreadCount; j++) {
				// Execute a thread
				vThreads.push_back(std::thread(&MemoryTestEngine::PerformLinearSearchOnMemoryThread, this, bMultiThreaded, j, std::ref(nCurrentProgressCount)));
			}

			uint64_t nContainerSize = nMemoryContainer.size();
			// While waiting for thread execution completion
			while (!bKeyboardTermination) {
				unsigned int nNumOfCompletedThreads = 0;

				// Check all completion indicators during thread execution
				for (unsigned int j = 0; j < nThreadCount; j++) {
					if (vThreadCompletionIndicator[j] == true) nNumOfCompletedThreads++;
				}

				// Check thread count
				if (nNumOfCompletedThreads >= nThreadCount) {
					// Reset progress counter to 100%
					std::cout << "Progress: ";
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << "100%\r";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

					break;
				}

				std::cout << "Progress: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << ((nCurrentProgressCount * 100) / nContainerSize) << "%\nNumber of errors found: " << nNumOfCurrentCheckErrors;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Move back to the top
				// Get current cursor position
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiMemTest);
				// Move 1 up
				csbiMemTest.dwCursorPosition.Y -= 1;
				csbiMemTest.dwCursorPosition.X = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csbiMemTest.dwCursorPosition);

				// CPU optimisation
				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			}

			// Kill all threads
			bKillThreads = true;
			for (unsigned int j = 0; j < nThreadCount; j++) {
				vThreads[j].join();
			}
			bKillThreads = false;

			// If keyboard key was pressed
			if (bKeyboardTermination == true)
			{
				// Kill keyboard abort handler
				bKillKeyboardAbortHandler = true;
				KeyboardHandlerThread.join();
				bKillKeyboardAbortHandler = false;
				bKeyboardTermination = false;

				// Output message and exit
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n\nKeyboard key has been pressed.\nStopping Linear Search Memory Test...\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				break;
			}

			// Kill keyboard abort handler
			bKillKeyboardAbortHandler = true;
			KeyboardHandlerThread.join();
			bKillKeyboardAbortHandler = false;
			bKeyboardTermination = false;

			// Record final time point
			std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

			// Get elapsed seconds
			std::chrono::duration<long double> ElapsedSeconds = end - start;

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\nLinear Check Search " << nPassIterator + 1 << " complete.";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << "\nTime elapsed: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << ElapsedSeconds.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << " seconds.\nErrors found: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << nNumOfCurrentCheckErrors << "\n\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Add current check search error count to total
			nNumOfErrorsFound += nNumOfCurrentCheckErrors;
		}

		// Completed check searches
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nLinear Check Searches complete.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Memory errorlevel check after check search
		if (nErrorLevel == 3)
		{
			// Notify user of memory error
			VerbosityDisplay("In MemoryTestEngine::PerformLinearSearchOnMemory() - Memory error(s) have been detected.\n", nObjectID);
			// Failed result
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Result: Failed (" + std::to_string(nNumOfErrorsFound) + " total errors).");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << "\nFailed indexes:\n";
			for (uint64_t i = 0; i < vFailedIndexes.size(); i++) {
				std::cout << vFailedIndexes[i] << '\n';
			}
			std::cout << '\n';

			// Memory error found
			nErrorLevel = 3;

			// Uninitialise memory
			UninitialiseMemoryContainer();

			// Reset all thread variables
			ResetThreads();

			return false;
		}
		else {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Result: Passed (" + std::to_string(nNumOfErrorsFound) + " total errors).\n\n");
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
		}

		// Uninitialise memory
		UninitialiseMemoryContainer();

		// Reset all thread variables
		ResetThreads();

		// All went well- return true
		return true;
	}

	// PerformExtendedLinearSearchOnMemory - Fills up memory to the maximum that the host's memory can hold, checks each 8 bytes of memory for correct values linearly,
	//                                     - changes the cell of memory to a randomly calculated integer (and checks for validity again), and switches back to the same old
	//                                     - integer with the same validity check at the beginning.
	// Arguments: nNumOfPasses - Number of extended linear check search passes to perform.
	// Return values: TRUE or 1 for success, FALSE or 0 for fail.
	//
	bool PerformExtendedLinearSearchOnMemory(uint64_t nNumOfPasses, bool bMultiThreaded)
	{
		unsigned int nThreadCount = nNumOfThreads;
		CONSOLE_SCREEN_BUFFER_INFO csbiMemTest{};

		// Initialise memory
		if (!InitialiseMemoryContainer()) {
			VerbosityDisplay("ERROR: In MemoryTestEngine::PerformExtendedLinearSearchOnMemory() - Memory container failed to initialise.\n" + GetLastErrorInfo() + '\n', nObjectID);

			colour(RED, ConfigObjMain.sColourGlobalBack);
			UserErrorDisplay("ERROR: Failed to initialise memory.\n", nObjectID);
			Exiting();

			return false; // Failed to initialise
		}

		// If key was pressed during the initialisation
		if (bKeyboardTermination == true) {
			UninitialiseMemoryContainer();
			return true;
		}

		// Check for single threading
		if (bMultiThreaded == false) {
			nThreadCount = 1;
		}

		// Perform linear check search
		uint64_t nNumOfErrorsFound = 0;
		std::vector<uint64_t> vFailedIndexes;
		for (uint64_t nPassIterator = 0; nPassIterator < nNumOfPasses; nPassIterator++)
		{
			// Reset all thread counts
			ResetThreads();

			std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

			// Notify user of check seatch start
			std::cout << "\nStarting Extended Linear Check Search " << nPassIterator + 1 << ".\n";

			// Declare and execute keyboard handler
			std::thread KeyboardHandlerThread(&MemoryTestEngine::KeyboardAbortHandler, this);

			// Current search value count for progress meters
			std::atomic_ullong nCurrentProgressCount = 0;

			// Declare and execute threads
			std::vector<std::thread> vThreads;
			for (unsigned int j = 0; j < nThreadCount; j++) {
				// Execute a thread
				vThreads.push_back(std::thread(&MemoryTestEngine::PerformExtendedLinearSearchOnMemoryThread, this, bMultiThreaded, j, std::ref(nCurrentProgressCount)));
			}

			uint64_t nContainerSize = nMemoryContainer.size();

			// While waiting for thread execution completion
			while (!bKeyboardTermination) {
				unsigned int nNumOfCompletedThreads = 0;

				// Check all completion indicators during thread execution
				for (unsigned int j = 0; j < nThreadCount; j++) {
					if (vThreadCompletionIndicator[j] == true) nNumOfCompletedThreads++;
				}

				// Check thread count
				if (nNumOfCompletedThreads >= nThreadCount) {
					// Reset progress counter to 100%
					std::cout << "Progress: ";
					colour(LCYN, ConfigObjMain.sColourGlobalBack);
					std::cout << "100%\r";
					colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

					break;
				}

				std::cout << "Progress: ";
				colour(LCYN, ConfigObjMain.sColourGlobalBack);
				std::cout << ((nCurrentProgressCount * 100) / nContainerSize) << "%\nNumber of errors found: " << nNumOfCurrentCheckErrors;
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Move back to the top
				// Get current cursor position
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiMemTest);
				// Move 1 up
				csbiMemTest.dwCursorPosition.Y -= 1;
				csbiMemTest.dwCursorPosition.X = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csbiMemTest.dwCursorPosition);

				// CPU optimisation
				std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			}

			// Kill all threads
			bKillThreads = true;
			for (unsigned int j = 0; j < nThreadCount; j++) {
				vThreads[j].join();
			}
			bKillThreads = false;

			// If keyboard key was pressed
			if (bKeyboardTermination == true)
			{
				// Kill keyboard abort handler
				bKillKeyboardAbortHandler = true;
				KeyboardHandlerThread.join();
				bKillKeyboardAbortHandler = false;
				bKeyboardTermination = false;

				// Output message and exit
				colour(YLW, ConfigObjMain.sColourGlobalBack);
				std::cout << "\n\nKeyboard key has been pressed.\nStopping Extended Linear Search Memory Test...\n";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
				break;
			}

			// Kill keyboard abort handler
			bKillKeyboardAbortHandler = true;
			KeyboardHandlerThread.join();
			bKillKeyboardAbortHandler = false;
			bKeyboardTermination = false;

			// Record final time point
			std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();

			// Get elapsed seconds
			std::chrono::duration<long double> ElapsedSeconds = end - start;

			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << "\n\nExtended Linear Check Search " << nPassIterator + 1 << " complete.";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << "\nTime elapsed: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << ElapsedSeconds.count();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << " seconds.\nErrors found: ";
			colour(LCYN, ConfigObjMain.sColourGlobalBack);
			std::cout << nNumOfCurrentCheckErrors << "\n\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			// Add current check search error count to total
			nNumOfErrorsFound += nNumOfCurrentCheckErrors;
		}

		// Completed check searches
		colour(LGRN, ConfigObjMain.sColourGlobalBack);
		std::cout << "\n\nExtended Linear Check Searches complete.\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

		// Memory errorlevel check after check search
		if (nErrorLevel == 3)
		{
			// Notify user of memory error
			VerbosityDisplay("In MemoryTestEngine::PerformExtendedLinearSearchOnMemory() - Memory error(s) have been detected.\n", nObjectID);
			// Failed result
			colour(RED, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Result: Failed (" + std::to_string(nNumOfErrorsFound) + " total errors).");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

			std::cout << "\nFailed indexes:\n";
			for (uint64_t i = 0; i < vFailedIndexes.size(); i++) {
				std::cout << vFailedIndexes[i] << '\n';
			}
			std::cout << '\n';

			// Memory error found
			nErrorLevel = 3;

			// Reset all thread counts
			ResetThreads();

			// Uninitialise memory
			UninitialiseMemoryContainer();

			return false;
		}
		else {
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("Result: Passed (" + std::to_string(nNumOfErrorsFound) + " total errors).\n\n");
			colour(LGRN, ConfigObjMain.sColourGlobalBack);
		}

		// Uninitialise memory
		UninitialiseMemoryContainer();

		// Reset all thread counts
		ResetThreads();

		// All went well- return true
		return true;
	}

	/* Error functions */

	// GetLastErrorValue - Gets the error code of last error that occured.
	// Arguments: None
	// Return values: Error code of last error that occured.
	//
	inline int GetLastErrorValue() {
		return nErrorLevel;
	}

	// GetLastErrorInfo - Gets the error info of the last error that occured.
	// Arguments: None
	// Return values: Error info of last error that occured, as a string.
	//
	std::string GetLastErrorInfo()
	{
		// Switch for error value
		switch (nErrorLevel) {
		case 0:
			return "No error has occured.";
			break;
		case 1:
			return "An error occured while getting the size of the host system's memory.";
			break;
		case 2:
			return "An unknown binary search error occured, where the random search value wasn't found.";
			break;
		case 3:
			return "A bad initialisation thread number was passed into a thread worker.";
			break;
		case 4:
			return "One or more memory errors were detected.";
			break;
		default:
			return "An error occured when getting error information.";
			break;
		}

		return "";
	}
};