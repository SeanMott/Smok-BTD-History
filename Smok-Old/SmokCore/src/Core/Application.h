//handles the application

#ifndef Application_h
#define Application_h

#include <string>
#include <Renderer\FrameBuffer.h>

//defines the differnt main prototypes
#ifdef Window_Build

#define EntryPoint int main(int args, char* argv[])

#elif Mac_Build

#define EntryPoint int main(int args, char* argv[])

#elif Linux_Build

#define EntryPoint int main(int args, char* argv[])

#endif

class Application
{
	//vars
private:
	static const float FIXED_UPDATE_RATE;

	//methods
public:

	static FrameBuffer* customeFrameBuffer;

	//inits the application
	static void Init(const unsigned int width, const int height, const std::string& name = "Smok");
	//destroys the application
	static void Destroy();
	//runs the application
	static void Run();
};

#endif