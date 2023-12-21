#include "pch.h"
#include <iostream>
#include <string>
#include <filesystem>

VOID MAIN() {
	// Find "dlls" folder within directory 
	std::filesystem::path DllFolder = std::filesystem::current_path() / "dlls";

	// Make sure "dlls" folder exists
	if (!std::filesystem::exists(DllFolder)) {
		// Create dlls folder
		std::filesystem::create_directory(DllFolder);
	}

	// Iterate through all files in "dlls" folder
	for (const auto& entry : std::filesystem::directory_iterator(DllFolder)) {
		std::string DllPath = entry.path().string();

		// Make sure it's a DLL
		if (DllPath.find(".dll") == std::string::npos) continue;

		// Load DLL
		HMODULE Dll = LoadLibraryA(DllPath.c_str());
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MAIN();
	}
	return TRUE;
}

