#include "pch.h"
#include <iostream>
#include <string>
#include <filesystem>

VOID MAIN() {
    // Create console for logging
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "[EML] Initializing" << std::endl;
    // Find "dlls" folder within directory 
    std::string DllFolder = std::filesystem::current_path().string() + "\\dlls";

    // Make sure "dlls" folder exists
    if (!std::filesystem::exists(DllFolder)) {
		std::cout << "[EML] Failed to find dlls folder" << std::endl;
        // Create dlls folder
        std::filesystem::create_directory(DllFolder);
        std::cout << "[EML] Created dlls folder" << std::endl;
	}

    std::cout << "[EML] Looking for DLLs in " << DllFolder << std::endl;
    // Iterate through all files in "dlls" folder
    for (const auto& entry : std::filesystem::directory_iterator(DllFolder)) {
		std::string DllPath = entry.path().string();
        // Make sure it's a DLL
        if (DllPath.find(".dll") == std::string::npos) continue;

        // Load DLL
		HMODULE Dll = LoadLibraryA(DllPath.c_str());
        if (Dll == NULL) {
			std::cout << "[EML] Failed to load " << DllPath << std::endl;
		}
        else {
			std::cout << "[EML] Loaded " << DllPath << std::endl;
		}
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MAIN();
	}
    return TRUE;
}

