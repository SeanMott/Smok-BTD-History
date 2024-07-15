//handles logging

#ifndef Logger_h
#define Logger_h

#include <string>
#include <vector>
#include <stdio.h>

class Logger
{
	//vars
private:
	static std::vector<std::string> errorTypes;
	static bool logErrorOnce; //only logs a error of a type once

	//methods
public:

	//logs a error message
	static void LogError(const std::string& type, const std::string& message);
	//logs a message
	static void LogMessage(const std::string& message);
	//logs a error message
	static void LogError(const char* type, const char* message);
	//logs a message
	static void LogMessage(const char* message);
	//logs a message no matter what
	static void LogMessageAlways(const char* message);
	//logs a message no matter what
	static void LogMessageAlways(const std::string& message);
	//logs a error message no matter what
	static void LogErrorAlways(const char* type, const char* message);
	//logs a error message no matter what
	static void LogErrorAlways(const std::string& type, const std::string& message);

	//sets the log error flag || logs error of a type only once
	inline static void SetLogErrorFlag(bool state) { logErrorOnce = state; }

private:

	//returns if a error type is already stored
	static bool IsError(const std::string& type);
	//adds a error type
	static void AddErrorType(const std::string& type);

};

#endif