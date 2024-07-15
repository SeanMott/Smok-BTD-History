#include "smpch.h"
#include "Logger.h"

using namespace std;

vector<string> Logger::errorTypes;
bool Logger::logErrorOnce = false; //only logs a error of a type once


	//returns if a error type is already stored
	bool Logger::IsError(const string& type)
	{
#ifndef SMOK_DIST
		if (errorTypes.size() < 1)
			return false;

		for (int i = 0; i < errorTypes.size(); i++)
		{
			if (errorTypes[i] == type)
				return true;
		}

#endif

		return false;
	}

	//adds a error type
	void Logger::AddErrorType(const string& type)
	{
#ifndef SMOK_DIST

		if (IsError(type))
			return;

		errorTypes.emplace_back(type);

#endif
	}

	//logs a error message
	void Logger::LogError(const string& type, const string& message)
	{
#ifndef SMOK_DIST

		if (logErrorOnce)
		{
			if (IsError(type))
				return;
		}

		printf("ERROR, Type: %s || %s\n", type.c_str(), message.c_str());
		AddErrorType(type);
#endif
	}

	//logs a message
	void Logger::LogMessage(const string& message)
	{
#ifndef SMOK_DIST
		printf("%s\n", message.c_str());
#endif
	}

	//logs a error message
	void Logger::LogError(const char* type, const char* message)
	{
#ifndef SMOK_DIST

		if (logErrorOnce)
		{
			if (IsError(type))
				return;
		}

		printf("ERROR, Type: %s || %s\n", type, message);
		AddErrorType((string)type);
#endif
	}

	//logs a message
	void Logger::LogMessage(const char* message)
	{
#ifndef SMOK_DIST
		printf("%s\n", message);
#endif
	}

	//logs a message no matter what
	void Logger::LogMessageAlways(const char* message)
	{
		printf("%s\n", message);
	}

	//logs a message no matter what
	void Logger::LogMessageAlways(const string& message)
	{
		printf("%s\n", message.c_str());
	}

	//logs a error message no matter what
	void Logger::LogErrorAlways(const string& type, const string& message)
	{

		if (logErrorOnce)
		{
			if (IsError(type))
				return;
		}

		printf("ERROR, Type: %s || %s\n", type.c_str(), message.c_str());
		AddErrorType(type);
	}

	//logs a error message no matter what
	void Logger::LogErrorAlways(const char* type, const char* message)
	{

		if (logErrorOnce)
		{
			if (IsError(type))
				return;
		}

		printf("ERROR, Type: %s || %s\n", type, message);
		AddErrorType(type);
	}
