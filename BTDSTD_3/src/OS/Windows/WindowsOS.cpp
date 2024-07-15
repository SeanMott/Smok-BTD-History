#include <BTDSTD/OS.hpp>

#include <GLFW/glfw3.h>

#include <BTDSTD/Logger.hpp>

//inits OS resources
bool BTD::OS::InitOSResources(const char* appName)
{
	//inits GLFW
	if (!glfwInit())
	{
		BTD::Util::Logger::LogFatalErrorToConsole("BTDSTD", "Windows", "OS Resources", "InitOSResources", "Failed to init GLFW");
		return false;
	}

	return true;
}

//shutsdowns OS resources
void BTD::OS::ShutdownOSResources()
{
	//clean up OS
	glfwTerminate();
}