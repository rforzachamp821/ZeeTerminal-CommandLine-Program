//
// SystemInfo.cpp - File containing the SystemInfo class.
//

#include <intrin.h>

// SystemInfo class - Manages getting system information for the LogFileSystem class.
class SystemInfo
{
private:

	// MaxValue - Returns the largest value out of 2 variables.
	// Arguments: nValueA - First value.
	//            nValueB - Second value.
	// Return Value: unsigned long long int containing the max value.
	//
	unsigned long long int MaxValue(unsigned long long int nValueA, unsigned long long int nValueB) {
		if (nValueA > nValueB) {
			return nValueA;
		}
		else return nValueB;
	}

	// GetRegistryDword - Gets a specified DWORD value from the Windows Registry and returns it.
	// Arguments: hKey - A handle to an open registry key.
	//            subKey - The path to the key, without the actual key name.
	//            value - The registry value name.
	// Return Value: DWORD value containing the value within the value argument.
	//
	DWORD GetRegistryDword(HKEY hKey, const std::string& subKey, const std::string& value)
	{
		DWORD data{};
		DWORD dataSize = sizeof(data);

		LONG retCode = RegGetValueA(
			hKey,
			subKey.c_str(),
			value.c_str(),
			RRF_RT_REG_DWORD,
			nullptr,
			&data,
			&dataSize
		);

		if (retCode != ERROR_SUCCESS)
		{
			return 0;
		}

		return data;
	}

	// GetRegistryDword - Gets a specified string value from the Windows Registry and returns it.
	// Arguments: hKey - A handle to an open registry key.
	//            subKey - The path to the key, without the actual key name.
	//            value - The registry value name.
	// Return Value: std::string containing the value within the value argument.
	//
	std::string GetRegistryString(HKEY hKey, const std::string& subKey, const std::string& value)
	{
		DWORD dataSize{};

		LONG retCode = RegGetValueA(
			hKey,
			subKey.c_str(),
			value.c_str(),
			RRF_RT_REG_SZ,
			nullptr,
			nullptr,
			&dataSize
		);

		if (retCode != ERROR_SUCCESS)
		{
			VerbosityDisplay("In SystemInfo::GetRegistryString(): ERROR - Failed to get registry string value. Error information: " + std::to_string(GetLastError()) + ".");
			return "Failed to get data.";
		}

		std::string data;
		data.resize(dataSize / sizeof(char));

		retCode = RegGetValueA(
			hKey,
			subKey.c_str(),
			value.c_str(),
			RRF_RT_REG_SZ,
			nullptr,
			&data[0],
			&dataSize
		);

		if (retCode != ERROR_SUCCESS)
		{
			return "Failed to get data.";
		}

		// Remove trailing NUL returned by Win32 API
		DWORD stringLengthInChars = dataSize / sizeof(char);
		stringLengthInChars--;
		data.resize(stringLengthInChars);

		return data;
	}

public:

	// GetCPUModelName - Gets the full CPU name as a string, using __cpuid intristics.
	// Arguments: None
	// Return Value: CPU name string as std::string.
	//
	std::string GetCPUModelName()
	{
		char CPUName[1025]{};
		int CPUInfo[4] = { -1 };
		unsigned numOfExIds;
		__cpuid(CPUInfo, 0x80000000);
		numOfExIds = CPUInfo[0];
		unsigned long long ptr = 0;
		for (unsigned i = 0x80000000; i <= numOfExIds; ++i)
		{
			__cpuid(CPUInfo, i);
			if (i == 0x80000002)
			{
				memcpy(CPUName, CPUInfo, sizeof(CPUInfo));
				ptr = MaxValue((unsigned long long)(CPUName + sizeof(CPUInfo) / sizeof(char)), ptr);
			}
			else if (i == 0x80000003)
			{
				memcpy(CPUName + 16, CPUInfo, sizeof(CPUInfo));
				ptr = MaxValue((unsigned long long)(CPUName + (16 + sizeof(CPUInfo)) / sizeof(char)), ptr);
			}
			else if (i == 0x80000004)
			{
				memcpy(CPUName + 32, CPUInfo, sizeof(CPUInfo));
				ptr = MaxValue((unsigned long long)(CPUName + (32 + sizeof(CPUInfo)) / sizeof(char)), ptr);
			}
		}
		*(char*)ptr = '\0';

		return std::string(CPUName);
	}

	// GetSysMemorySizeInGiB - Gets the system memory size in gibibytes.
	// Arguments: None
	// Return Value: System memory size, in gibibytes, as long double.
	//
	long double GetSysMemorySizeInGiB() {
		MEMORYSTATUSEX MemorySize{};
		MemorySize.dwLength = sizeof(MemorySize);
		if (!GlobalMemoryStatusEx(&MemorySize)) {
			VerbosityDisplay("In SystemInfo::GetSysMemorySizeInGiB(): ERROR - Failed to get memory information on GlobalMemoryStatusEx(). Error code: " + std::to_string(GetLastError()) + ".");
			return 0.0;
		}

		return (long double)MemorySize.ullTotalPhys / 1024.0 / 1024.0 / 1024.0;
	}

	// GetSysPageSizeInGiB - Gets the memory page file size in gibibytes.
	// Arguments: None
	// Return Value: System page file size, in gibibytes, as long double.
	//
	long double GetSysPageSizeInGiB() {
		MEMORYSTATUSEX PageSize{};
		PageSize.dwLength = sizeof(PageSize);
		if (!GlobalMemoryStatusEx(&PageSize)) {
			VerbosityDisplay("In SystemInfo::GetSysPageSizeInGiB(): ERROR - Failed to get page file information on GlobalMemoryStatusEx(). Error code: " + std::to_string(GetLastError()) + ".");
			return 0.0;
		}

		// ullTotalPageFile is total accessible, 'true' virtual memory, and by subtracting total physical memory it gives the page file size
		return (long double)((PageSize.ullTotalPageFile - PageSize.ullTotalPhys) / 1024.0 / 1024.0 / 1024.0);
	}

	// GetSysVirtualMemorySizeInGiB - Gets the system virtual memory size in gibibytes.
	// Arguments: None
	// Return Value: System virtual memory size, in gibibytes, as long double.
	//
	long double GetSysVirtualMemorySizeInGiB() {
		MEMORYSTATUSEX VirtualMemorySize{};
		VirtualMemorySize.dwLength = sizeof(VirtualMemorySize);
		if (!GlobalMemoryStatusEx(&VirtualMemorySize)) {
			VerbosityDisplay("In SystemInfo::GetSysVirtualMemorySizeInGiB(): ERROR - Failed to get virtual memory information on GlobalMemoryStatusEx(). Error code: " + std::to_string(GetLastError()) + ".");
			return 0.0;
		}

		// ullTotalPageFile is total accessible, 'true' virtual memory
		return (long double)VirtualMemorySize.ullTotalPageFile / 1024.0 / 1024.0 / 1024.0;
	}

	// GetLowestAccessibleMemoryAddress - Gets the lowest accessible memory address to any application in the system, as a string.
	// Arguments: None
	// Return Value: std::string, containing the memory address.
	//
	std::string GetLowestAccessibleMemoryAddress() {
		SYSTEM_INFO siMemAddress{};
		GetSystemInfo(&siMemAddress);

		// Send to string stream and convert to std::string - void* or LPVOID cannot be casted to a string directly, so it must be done this way
		std::ostringstream ossLowMemAddress;
		ossLowMemAddress << (void*)siMemAddress.lpMinimumApplicationAddress;

		// Return
		return ossLowMemAddress.str();
	}

	// GetHighestAccessibleMemoryAddress - Gets the highest accessible memory address to any application in the system, as a string.
	// Arguments: None
	// Return Value: std::string, containing the memory address.
	//
	std::string GetHighestAccessibleMemoryAddress() {
		SYSTEM_INFO siMemAddress{};
		GetSystemInfo(&siMemAddress);

		// Send to string stream and convert to std::string - void* or LPVOID cannot be casted to a string directly, so it must be done this way
		std::ostringstream ossHighMemAddress;
		ossHighMemAddress << (void*)siMemAddress.lpMaximumApplicationAddress;

		// Return
		return ossHighMemAddress.str();
	}

	// GetOSName - Gets the full OS name as stored in the Windows Registry.
	// Arguments: None
	// Return Value: Full OS name with build number, as a string.
	//
	std::string GetOSName() {
		std::string sProductName = "";

		sProductName += GetRegistryString(((HKEY)(ULONG_PTR)((LONG)0x80000002)), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName") + " ";

		std::string sTestBuffer = GetRegistryString(((HKEY)(ULONG_PTR)((LONG)0x80000002)), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "DisplayVersion");
		// Check for error in case of Windows 7 or something like that
		if (sTestBuffer != "Failed to get data.") {
			sProductName += sTestBuffer + " ";
		}

		sProductName += "(Build " + GetRegistryString(((HKEY)(ULONG_PTR)((LONG)0x80000002)), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuildNumber")
			+ "." + std::to_string(GetRegistryDword(((HKEY)(ULONG_PTR)((LONG)0x80000002)), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "UBR")) + ")";

		return sProductName;
	}

	// GetOSBuildInfo - Gets extra build info as a string, as stored in the Windows Registry.
	// Arguments: None
	// Return Value: OS Build Info as a string.
	//
	std::string GetOSBuildInfo() {
		std::string sBuildInfo = "";

		// Get build info
		sBuildInfo = GetRegistryString(((HKEY)(ULONG_PTR)((LONG)0x80000002)), "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "BuildLabEx");

		// Return Build Info
		return sBuildInfo;
	}

	// GetCPUCoreCount - Gets the number of processors on the CPU as an integer.
	// Arguments: None
	// Return Value: Integer containing the number of CPU cores in the system.
	//
	int GetCPUCoreCount() {
		SYSTEM_INFO SysInfoCPUCoreCount{};
		GetSystemInfo(&SysInfoCPUCoreCount);
		return (int)SysInfoCPUCoreCount.dwNumberOfProcessors;
	}

	// GetCPUArchitectureAsName - Gets the CPU architecture (x64, ARM, etc) as a custom string.
	// Arguments: None
	// Return Value: CPU architecture as a string.
	//
	std::string GetCPUArchitectureAsName()
	{

		// Get system info
		SYSTEM_INFO sysinfoarch{};
		GetSystemInfo(&sysinfoarch);

		// Convert values into string with switch
		switch (sysinfoarch.wProcessorArchitecture)
		{
		case PROCESSOR_ARCHITECTURE_AMD64:
			return "x64 (amd64)";
			break;
		case PROCESSOR_ARCHITECTURE_ARM:
			return "ARM";
			break;
		case PROCESSOR_ARCHITECTURE_ARM64:
			return "ARM64";
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			return "IA64 (Itanium)";
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			return "x86";
			break;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:
			return "Unknown";
			break;
		default:
			return "Failed to get data.";
			break;
		}

		// If somehow the switch didn't get triggered, post error
		return "Failed to get data.";
	}
};
