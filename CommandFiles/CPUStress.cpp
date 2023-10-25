
void colour(std::string, std::string);
void ClearKeyboardBuffer();
void slowcolourfn(std::string, std::string, std::string);
void slowcharCentredFn(bool, std::string);
long double NumInput(std::string);
std::string StrInput(std::string);
void sleep(long long int);
void Exiting();

std::atomic<bool> StopCpuStress = false;
// Get logical core count of cpu
const int nLogicalCoreCount = std::thread::hardware_concurrency();
unsigned long long int nReiterationCount = 0;
unsigned long long int nCurrentReiterationNum = 0;
bool bCpuStressKeyboardTermination = false;

extern ConfigFileSystem ConfigObjMain;


// 1 for single core, 2 for multi core
void CpuStressTestWorker(short int nSingleOrMultiCore) {
	long double ldStress = 1.0;
	
	if (nSingleOrMultiCore == 1) {
		while (!_kbhit()) {
			ldStress *= 1.5;
			ldStress /= 1.1;
			ldStress += 1;
		}
		return;
	}
	else if (nSingleOrMultiCore == 2) {
		while (!StopCpuStress) {
			ldStress *= 1.5;
			ldStress /= 1.1;
			ldStress += 1;
		}
		return;
	}
	
	return;
}

// 1 for single core, 2 for multi core
void CpuBenchmarkWorker(short int nSingleOrMultiCore) {
	long double ldStress = 1.0;
	unsigned long long int lnBenchmarkReiterationCount = 0;

	if (nSingleOrMultiCore == 1) {
		while (lnBenchmarkReiterationCount <= nReiterationCount) {
			if (_kbhit()) {
				bCpuStressKeyboardTermination = true;
				break;
			}
			ldStress *= 1.5;
			ldStress /= 1.1;
			ldStress += 1;
			lnBenchmarkReiterationCount++;
			std::cout << "Progress: " << (lnBenchmarkReiterationCount * 100) / nReiterationCount << "%\r";
		}
		std::cout << "\n";
		return;
	}
	else if (nSingleOrMultiCore == 2) {
		while (!StopCpuStress) {
			ldStress *= 1.5;
			ldStress /= 1.1;
			ldStress += 1;
			lnBenchmarkReiterationCount++;
			nCurrentReiterationNum = lnBenchmarkReiterationCount;
		}
		return;
	}

	return;
}

// 1 for single core, 2 for multi core
void CpuBenchmark(short int nSingleOrMulti, long long int nArgNum = -1) {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<long double> ldElapsedTime; // Save the duration of the operation here
	long long int nInput = 0;


	// Take input
	if (nArgNum < 0) {
		// Multi core is more as more cores contribute to the same workload, so less reiterations would basically be under a second
		if (nSingleOrMulti == 1) std::cout << "\nThe default number of reiterations is 100,000.\n";
		else if (nSingleOrMulti == 2) std::cout << "\nThe default number of reiterations is 1 billion.\n";

		nInput = NumInput("Please input the number of reiterations that you want (negative number to exit, 0 for default, more is more intensive): > ");
	}
	else nInput = nArgNum;

	
	// Exit if input is less than 0
	if (nInput < 0) {
		Exiting();
		return;
	}
	else if (nInput == 0) {
		if (nSingleOrMulti == 1) nInput = 100000;
		else if (nSingleOrMulti == 2) nInput = 1000000000;
	}
	nReiterationCount = nInput;

	// Single Core
	if (nSingleOrMulti == 1) {

		// Start timer and call the cpu benchmark worker only once for single core
		std::cout << "Starting single-core benchmark with " << nReiterationCount << " reiterations, 1 core.\n";
		slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "Single-core benchmark has started...\n");
		ClearKeyboardBuffer();

		start = std::chrono::steady_clock::now();

		CpuBenchmarkWorker(1);

		// Stop timer
		end = std::chrono::steady_clock::now();
		ldElapsedTime = end - start;

		// Output results
		if (bCpuStressKeyboardTermination == false) {
			std::cout << "Single-core benchmark complete. Your computer took " << ldElapsedTime.count() << " seconds to complete the test.\nCompare that with your friend's scores!\n";
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			ClearKeyboardBuffer();
			std::cout << "\nThe single-core benchmark was terminated by a keyboard press.\nExiting...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	}

	// Multi Core
	else if (nSingleOrMulti == 2) {

		// Make std::vector array for threads in next step
		std::vector<std::thread> vThreads(nLogicalCoreCount);
		unsigned long long int nPreviousReiterationNum = 0;

		// Start timer and call the cpu benchmark worker nLogicalCoreCount times
		std::cout << "Starting multi-core benchmark with " << nReiterationCount << " reiterations, " << nLogicalCoreCount << " logical cores.\n";
		slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "Multi-core benchmark has started...\n");
		ClearKeyboardBuffer();

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < nLogicalCoreCount; i++) {
			vThreads[i] = std::thread(CpuBenchmarkWorker, 2);
		}

		while (true) {

			if (_kbhit()) {
				bCpuStressKeyboardTermination = true;
				break;
			}
			else if (nCurrentReiterationNum >= nReiterationCount) {
				break;
			}


			if (nPreviousReiterationNum < nCurrentReiterationNum) { // <-- Speed is required to make the percentage output operation accurate,
				nPreviousReiterationNum = nCurrentReiterationNum;   // <-- so these two lines were put right next to each other to make that possible.
				// Output progress
				std::cout << "Progress: " << (nPreviousReiterationNum * 100) / nReiterationCount << "%    \r";
			}

		}

		StopCpuStress = true;

		// Wait for all other threads to finish using join()
		for (int i = 0; i < nLogicalCoreCount; i++) {
			vThreads[i].join();
		}
		end = std::chrono::steady_clock::now();

		ldElapsedTime = end - start;

		// Output results
		if (bCpuStressKeyboardTermination == false) {
			std::cout << "Multi-core benchmark complete. Your computer took " << ldElapsedTime.count() << " seconds to complete the test.\nCompare that with your friend's scores!\n";
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nThe multi-core benchmark was terminated by a keyboard press.\nExiting...\n";
			ClearKeyboardBuffer();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	}

	// Reset values to default
	bCpuStressKeyboardTermination = false;
	nReiterationCount = 0;
	StopCpuStress = false;
	nCurrentReiterationNum = 0;
	return;
}

void CpuStressTest(short int nSingleOrMulti, bool bIsArgument = false) {

	if (bIsArgument == false) {
		std::cout << "Remember, you can always stop the stress test by pressing any key while it's going.\nPress any key to begin the test, or ESC to terminate...";
		char cKeyCST = _getch();
		if (cKeyCST == 27) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nESC pressed. Exiting...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return;
		}
	}

	slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "\nStress test has started...\n");

	if (nSingleOrMulti == 1) {
		nSingleOrMulti = 1;
		CpuStressTestWorker(1);
		// CpuStressTestWorker only exits when key is pressed
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nStress test terminated. Exiting...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}
	else if (nSingleOrMulti == 2) {
		nSingleOrMulti = 2;

		// Make std::vector array for threads in next step
		std::vector<std::thread> vThreads(nLogicalCoreCount);

		// Create threads until max number of logical cores hit
		for (int i = 0; i < nLogicalCoreCount; i++) {
			vThreads[i] = std::thread(CpuStressTestWorker, 2);
		}
		// Then wait for keyboard hit to kill all the processes
		while (!_kbhit()) {
			sleep(10);
		}

		// Assume keyboard has been pressed, so set StopCpuStress to true
		StopCpuStress = true;

		// Wait for all other threads to finish using join()
		for (int i = 0; i < nLogicalCoreCount; i++) {
			vThreads[i].join();
		}

		// Put back StopCpuStress to default to not affect next round
		StopCpuStress = false;

		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << "\nStress test terminated. Exiting...\n";
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	ClearKeyboardBuffer();
	return;
}