#pragma once

//defines OS functions

namespace BTD::OS
{
	//inits OS resources
	bool InitOSResources(const char* appName);

	//shutsdowns OS resources
	void ShutdownOSResources();
}