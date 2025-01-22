#include "../pch.h"
#include "Logger.h"

//Singleton instance
Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::Initialize(bool enableConsole, const std::string& logFile)
{
	if (enableConsole && !consoleOpen)
		openConsole();

	if (!logFile.empty()) {
		logFileStream.open(logFile, std::ios::out | std::ios::app);
		if (!logFileStream.is_open()) {
			log(CRITICAL, "Failed to open log file: " + logFile);
		}
	}
}

void Logger::log(Severity severity, const std::string& message) {
	std::string severityStr;

	switch (severity) {
		case INFO: severityStr = "[INFO]"; break;
		case WARNING: severityStr = "[WARNING]"; break;
		case CRITICAL: severityStr = "[ERROR]"; break;
	}

	std::string logMessage = severityStr + message;

	if (consoleOpen)
	{
		std::cout << logMessage << std::endl;
	}

	if (logFileStream.is_open()) {
		logFileStream << logMessage << std::endl;
	}
}

void Logger::close() {
	if (logFileStream.is_open()) {
		logFileStream.close();
	}
	closeConsole();
}

void Logger::openConsole() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	consoleOpen = true;
}

void Logger::closeConsole() {
	if (consoleOpen) {
		fclose(stdout);
		FreeConsole();
		consoleOpen = false;
	}
}