#pragma once
#include "../pch.h"

class Logger
{
public:
	enum Severity {
		INFO,
		WARNING,
		CRITICAL
	};

	void Initialize(bool openConsole = true, const std::string& logFile = "");
	void log(Severity severity, const std::string& message);
	void close();

	static Logger& getInstance();

private:
	Logger() = default;
	~Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::ofstream logFileStream;
	bool consoleOpen = false;

	void openConsole();
	void closeConsole();
};

inline Logger& Loggus = Logger::getInstance();