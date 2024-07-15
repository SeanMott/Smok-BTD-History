#pragma once

//defines a logger

#include <cstdio>
#include <string>

namespace BTD::Util::Logger
{
	/*
	Genaric logger function

	app || the application that sent the message
	platform || the platform that sent it
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogMessageToConsole(const char* app, const char* platform, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s (%s), %s::%s || %s\n", app, platform, domain, callerFunc, message);
	}

	/*
	Genaric logger function

	app || the application that sent the message
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogMessageToConsole(const char* app, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s, %s::%s || %s\n", app, domain, callerFunc, message);
	}

	/*
	Logs a warning to the console

	app || the application that sent the message
	platform || the platform that sent it
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogWarningToConsole(const char* app, const char* platform, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s WARNING (%s), %s::%s || %s\n", app, platform, domain, callerFunc, message);
	}

	/*
	Logs a warning to the console

	app || the application that sent the message
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogWarningToConsole(const char* app, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s WARNING, %s::%s || %s\n", app, domain, callerFunc, message);
	}

	/*
	Logs a error to the console

	app || the application that sent the message
	platform || the platform that sent it
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogErrorToConsole(const char* app, const char* platform, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s ERROR (%s), %s::%s || %s\n", app, platform, domain, callerFunc, message);
	}

	/*
	Logs a error to the console

	app || the application that sent the message
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogErrorToConsole(const char* app, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s ERROR, %s::%s || %s\n", app, domain, callerFunc, message);
	}

	/*
	Logs a fatal error to the console

	app || the application that sent the message
	platform || the platform that sent it
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogFatalErrorToConsole(const char* app, const char* platform, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s FATAL ERROR (%s), %s::%s || %s\n", app, platform, domain, callerFunc, message);
	}

	/*
	Logs a fatal error to the console

	app || the application that sent the message
	domain || what domain or subsystem of the application sent it
	callerFunc || the name of the function that sent it
	message || the message to send
	*/
	static inline void LogFatalErrorToConsole(const char* app, const char* domain, const char* callerFunc, const char* message)
	{
		printf("%s FATAL ERROR, %s::%s || %s\n", app, domain, callerFunc, message);
	}
}