#pragma once
#include "../pch.h"
#include "../Logging/Logger.h"

class Memory {
public:
	Memory();
	~Memory();

	bool attachToProcess(const std::wstring& processName);
	bool attachToProcess(DWORD processID);
	uintptr_t GetModuleBaseAddress(const std::string& moduleName);
	uintptr_t GetModuleBaseAddress(const std::wstring& moduleName);

	void detach();

	bool Read(uintptr_t address, void* buffer, size_t size);

	template <typename T>
	bool RPM(uintptr_t address, T& outData) {
		SIZE_T bytesRead;
		if (ReadProcessMemory(hProcess, (LPCVOID)address, &outData, sizeof(T), &bytesRead)) {
			return true;
		}
		return false;
	}

	template <typename type>
	bool ReadArray(uintptr_t address, type* buffer, size_t size) {
		SIZE_T bytesRead;
		if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), buffer, size, &bytesRead)) {
			return false;
		}
		return bytesRead == size;
	}

	template <typename T>
	T RPM(uintptr_t address) {
		T outData{};
		if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &outData, sizeof(T), nullptr)) {
			return outData;
		}
	}

	template <typename T>
	bool WPM(uintptr_t address, const T& data) {
		SIZE_T bytesWritten;
		if (WriteProcessMemory(hProcess, (LPVOID)address, &data, sizeof(T), &bytesWritten)) {
			return true;
		}

		return false;
	}

	uintptr_t scanPattern(const std::wstring& moduleName, const std::string& pattern);

private:
	HANDLE hProcess;
	DWORD processID;

	bool parsePattern(const std::string& pattern, std::vector<BYTE>& bytePattern, std::string& mask);
};

inline Memory mem;