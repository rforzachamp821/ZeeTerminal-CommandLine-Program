//
// CPUStress.cpp - Responsible for the CPUStress command's inner workings.
//

std::atomic<bool> StopCpuStress = false;
// Get logical core count of cpu
const int nLogicalCoreCount = std::thread::hardware_concurrency();
uint64_t nReiterationCount = 0;
std::atomic<uint64_t> nCurrentReiterationNum = 0;
bool bCpuStressKeyboardTermination = false;

extern ConfigFileSystem ConfigObjMain;


// Worker for CPU Stress Test
void CpuStressTestWorker() {
	long double ldStress = 1.0; 

	while (!StopCpuStress) {
		ldStress *= RandNum(0, 5);
		ldStress /= RandNum(0.00000001, 5);
		ldStress += RandNum(0, 5);
	}

	return;
}

// Worker for CPU Benchmark
void CpuBenchmarkWorker() {
	long double ldStress = 1.0;

	while (!StopCpuStress) {
		ldStress *= RandNum(0, 5);
		ldStress /= RandNum(0.00000001, 5);
		ldStress += RandNum(0, 5);
		nCurrentReiterationNum++;
	}
	return;
}

// 1 for single core, 2 for multi core
void CpuBenchmark(short int nSingleOrMulti, long long int nArgNum = -1) {
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<long double> ldElapsedTime; // Save the duration of the operation here
	long long int nInput = 0;
	bool bUserCursorVisibilitySetting = true;


	// Take input
	if (nArgNum < 0) {

		if (nSingleOrMulti == 1) {
			CentreColouredText(" ___CPU SINGLE-CORE BENCHMARK___ ", 1);

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nWelcome to the Single-Core CPU Benchmark!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else if (nSingleOrMulti == 2) {
			CentreColouredText(" ___CPU MULTI-CORE BENCHMARK___ ", 1);

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nWelcome to the Multi-Core CPU Benchmark!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		std::cout << wordWrap("The default number of reiterations is 50 million (50000000).\n");

		nInput = NumInputll("Please input the number of reiterations that you want (negative number to exit, 0 for default, more is more intensive): > ");
	}
	else nInput = nArgNum;

	// Exit if input is less than 0
	if (nInput < 0) {
		Exiting();
		return;
	}
	else if (nInput == 0) {
		nInput = 50000000;
	}
	nReiterationCount = nInput;

	// Single Core
	if (nSingleOrMulti == 1) {

		// Start timer and call the cpu benchmark worker only once for single core
		std::cout << wordWrap("Starting single-core benchmark with " + std::to_string(nReiterationCount) + " reiterations, 1 logical core.\n");
		slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "Single-core benchmark has started...\n");
		ClearKeyboardBuffer();

		// Disable cursor
		bUserCursorVisibilitySetting = DisableCursorVisibility();

		start = std::chrono::steady_clock::now();

		std::thread SingleCoreWorker(CpuBenchmarkWorker);

		while (true) {

			if (_kbhit()) {
				bCpuStressKeyboardTermination = true;
				break;
			}
			else if (nCurrentReiterationNum >= nReiterationCount) {
				break;
			}

			// Output progress
			std::cout << "Progress: " << (nCurrentReiterationNum * 100) / nReiterationCount << "%    \r";

			// Optimisation to prevent output messing up with cpu speed
			sleep(10);
		}

		StopCpuStress = true;

		SingleCoreWorker.join();

		// Stop timer
		end = std::chrono::steady_clock::now();
		ldElapsedTime = end - start;

		// Output results
		if (bCpuStressKeyboardTermination == false) {
			std::cout << "Progress: 100%";
			std::cout << wordWrap("\n\nSingle-core benchmark complete. Your computer took " + std::to_string(ldElapsedTime.count()) + " seconds to complete the test.\nCompare that with your friend's scores!\n");
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			ClearKeyboardBuffer();
			std::cout << wordWrap("\n\nThe single-core benchmark was terminated by a keyboard press.");
			Exiting();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	}

	// Multi Core
	else if (nSingleOrMulti == 2) {

		// Make std::vector array for threads in next step
		std::vector<std::thread> vThreads(nLogicalCoreCount);

		// Start timer and call the cpu benchmark worker nLogicalCoreCount times
		std::cout << wordWrap("Starting multi-core benchmark with " + std::to_string(nReiterationCount) + " reiterations, " + std::to_string(nLogicalCoreCount) + " logical cores.\n");
		slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "Multi-core benchmark has started...\n");
		ClearKeyboardBuffer();

		// Disable cursor
		bUserCursorVisibilitySetting = DisableCursorVisibility();

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < nLogicalCoreCount; i++) {
			vThreads[i] = std::thread(CpuBenchmarkWorker);
		}

		while (true) {

			if (_kbhit()) {
				bCpuStressKeyboardTermination = true;
				break;
			}
			else if (nCurrentReiterationNum >= nReiterationCount) {
				break;
			}

			// Output progress
			std::cout << "Progress: " << (nCurrentReiterationNum * 100) / nReiterationCount << "%    \r";

			// Optimisation to prevent output messing up with cpu speed
			sleep(10);
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
			std::cout << "Progress: 100%";
			std::cout << wordWrap("\n\nMulti-core benchmark complete. Your computer took " + std::to_string(ldElapsedTime.count()) + " seconds to complete the test.\nCompare that with your friend's scores!\n");
		}
		else {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\n\nThe single-core benchmark was terminated by a keyboard press.");
			Exiting();
			ClearKeyboardBuffer();
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
	}

	// Reset values to default
	bCpuStressKeyboardTermination = false;
	nReiterationCount = 0;
	StopCpuStress = false;
	nCurrentReiterationNum = 0;

	// Reset cursor visibility
	ConfigObjMain.bShowCursor = bUserCursorVisibilitySetting;
	SetCursorAttributes();

	return;
}

void CpuStressTest(short int nSingleOrMulti, bool bIsArgument = false) {

	if (bIsArgument == false) {

		if (nSingleOrMulti == 1) {
			CentreColouredText(" ___CPU SINGLE-CORE STRESS TEST___ ", 1);

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nWelcome to the Single-Core CPU Stress Test!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}
		else if (nSingleOrMulti == 2) {
			CentreColouredText(" ___CPU MULTI-CORE STRESS TEST___ ", 1);

			colour(GRN, ConfigObjMain.sColourGlobalBack);
			std::cout << wordWrap("\nWelcome to the Multi-Core CPU Stress Test!\n");
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		}

		std::cout << wordWrap("Remember, you can always stop the stress test by pressing any key while it's going.\nPress any key to begin the test, or ESC to terminate...");
		char cKeyCST = _getch();
		if (cKeyCST == 27) {
			colour(YLW, ConfigObjMain.sColourGlobalBack);
			std::cout << "\nESC pressed.\nExiting...\n";
			colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
			return;
		}
	}

	slowcolourfn(LGRN, ConfigObjMain.sColourGlobalBack, "\nStress test has started...\n");
	
	// Single Core
	if (nSingleOrMulti == 1) 
	{
		// Firstly, create thread for stress test
		std::thread SingleCoreStressTest(CpuStressTestWorker);

		// Then wait for keyboard hit to kill all the processes
		while (!_kbhit()) {
			sleep(10);
		}

		// Assume keyboard has been pressed, so set StopCpuStress to true
		StopCpuStress = true;

		// Wait for thread to react
		SingleCoreStressTest.join();

		// Put back StopCpuStress to default to not affect next round
		StopCpuStress = false;

		// CpuStressTestWorker only exits when key is pressed
		colour(YLW, ConfigObjMain.sColourGlobalBack);
		std::cout << wordWrap("\nStress test terminated.\nExiting...\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	// Multi Core
	else if (nSingleOrMulti == 2) 
	{
		nSingleOrMulti = 2;

		// Make std::vector array for threads in next step
		std::vector<std::thread> vThreads(nLogicalCoreCount);

		// Create threads until max number of logical cores hit
		for (int i = 0; i < nLogicalCoreCount; i++) {
			vThreads[i] = std::thread(CpuStressTestWorker);
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
		std::cout << wordWrap("\nStress test terminated.\nExiting...\n");
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	}

	ClearKeyboardBuffer();
	return;
}

// Lucas Lehmer Primality Stress Test
/* 
long long int s = 4;
long long int randnum = RandNum(0, 50);
long long int m = std::powl(2, randnum) - 1;
int nIterator = 0;
while (++nIterator < randnum - 2) {
	s = ((s * s) - 2) % m;
}
*/
