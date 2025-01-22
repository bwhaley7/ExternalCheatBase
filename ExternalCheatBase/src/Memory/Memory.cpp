#include "../pch.h"
#include "../Logging/Logger.h"
#include "../Misc/Util.h"
#include "Memory.h"
#include <sstream>

Memory::Memory() : hProcess(nullptr), processID(0) {}

Memory::~Memory() {
	detach();
}

bool Memory::attachToProcess(const std::wstring& processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        Loggus.log(Loggus.CRITICAL, "Failed to create process snapshot.");
        return false;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    if (Process32First(hSnapshot, &pe)) {
        do {
            // Compare wide strings directly
            if (processName == pe.szExeFile) {
                processID = pe.th32ProcessID;
                CloseHandle(hSnapshot);
                return attachToProcess(processID);
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    Loggus.log(Loggus.CRITICAL, "Failed to find process: " + std::string(processName.begin(), processName.end()));
    return false;
}

bool Memory::attachToProcess(DWORD pid) {
    detach(); // Detach from any existing process
    processID = pid;

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (!hProcess) {
        Loggus.log(Loggus.CRITICAL, "Failed to open process with ID: " + std::to_string(processID));
        return false;
    }

    Loggus.log(Loggus.INFO, "Successfully attached to process with ID: " + std::to_string(processID));
    return true;
}

void Memory::detach() {
    if (hProcess) {
        CloseHandle(hProcess);
        hProcess = nullptr;
        processID = 0;
        Loggus.log(Loggus.INFO, "Detached from process.");
    }
}

bool Memory::Read(uintptr_t address, void* buffer, size_t size) {
    SIZE_T bytesRead;
    if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), buffer, size, &bytesRead)) {
        return true;
    }
    return false;
}

uintptr_t Memory::GetModuleBaseAddress(const std::wstring& moduleName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        Loggus.log(Loggus.CRITICAL, "Failed to create module snapshot.");
        return 0;
    }

    MODULEENTRY32 me;
    me.dwSize = sizeof(me);

    if (Module32First(hSnapshot, &me)) {
        do {
            if (moduleName == me.szModule) {
                CloseHandle(hSnapshot);
                return (uintptr_t)me.modBaseAddr;
            }
        } while (Module32Next(hSnapshot, &me));
    }

    CloseHandle(hSnapshot);
    Loggus.log(Loggus.CRITICAL, "Failed to find module: " + Util.wideCharToString(moduleName));
    return 0;
}

uintptr_t Memory::scanPattern(const std::wstring& moduleName, const std::string& pattern) {
    uintptr_t baseAddress = GetModuleBaseAddress(moduleName);
    if (!baseAddress) {
        Loggus.log(Loggus.CRITICAL, "Base address for module not found: " + Util.wideCharToString(moduleName));
        return 0;
    }

    // To-Do: Implement pattern scanning logic here
    Loggus.log(Loggus.WARNING, "Pattern scanning is not implemented yet.");
    return 0;
}

bool Memory::parsePattern(const std::string& pattern, std::vector<BYTE>& bytePattern, std::string& mask) {
    std::istringstream stream(pattern);
    std::string byteStr;
    while (stream >> byteStr) {
        if (byteStr == "?") {
            bytePattern.push_back(0);
            mask += "?";
        }
        else {
            bytePattern.push_back(static_cast<BYTE>(std::stoi(byteStr, nullptr, 16)));
            mask += "x";
        }
    }
    return !bytePattern.empty();
}

uintptr_t Memory::GetModuleBaseAddress(const std::string& moduleName) {
    std::wstring wModuleName(moduleName.begin(), moduleName.end());
    uintptr_t baseAddress = 0;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "[!] Failed to create snapshot for modules." << std::endl;
        return 0;
    }

    MODULEENTRY32W moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32W);

    if (Module32FirstW(hSnapshot, &moduleEntry)) {
        do {
            if (wModuleName == moduleEntry.szModule) {
                baseAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
                std::cout << "[+] Found Base Address for " << moduleName << " at 0x"
                    << std::hex << baseAddress << std::endl;
                break;
            }
        } while (Module32NextW(hSnapshot, &moduleEntry));
    }
    else {
        std::cerr << "[!] Failed to enumerate modules." << std::endl;
    }

    CloseHandle(hSnapshot);
    return baseAddress;
}