#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>

VOID MAIN() {
	// If "dlls" folder exists, rename it to "plugins"
	if (std::filesystem::exists("dlls")) {
		std::filesystem::rename("dlls", "plugins");
	}

	// Find "plugins" folder within directory 
	std::filesystem::path DllFolder = std::filesystem::current_path() / "plugins";

	// Make sure "plugins" folder exists
	if (!std::filesystem::exists(DllFolder)) {
		// Create plugins folder
		std::filesystem::create_directory(DllFolder);
	}

	// Iterate through all files in "plugins" folder
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

