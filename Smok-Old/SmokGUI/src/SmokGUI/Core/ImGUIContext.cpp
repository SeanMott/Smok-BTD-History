#include "ImGUIContext.h"

#include <Core\Logger.h>

#include <Renderer\RenderAPI\RenderAPI.h>

#include <SmokGUI\RenderAPI\Opengl\OpenglImGUIContext.h>
//#include <SmokGUI\RenderAPI\DirectX\DirectXImGUIContext.h>
//#include <SmokGUI\RenderAPI\Vulkin\VulkinImGUIContext.h>
//#include <SmokGUI\RenderAPI\Metal\MetalImGUIContext.h>

using namespace std;

//creates the context
ImGUIContext* ImGUIContext::Create()
{
	RenderAPIType type = RenderAPI::GetAPI();

	if (type == RenderAPIType::Vulkin)
	{
		Logger::LogErrorAlways("ImGUI Context", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinImGUIContext;
		return new OpenglImGUIContext;
	}

	else if (type == RenderAPIType::DirectX)
	{
		Logger::LogErrorAlways("ImGUI Context", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXImGUIContext;
		return new OpenglImGUIContext;
	}

	else if (type == RenderAPIType::Metal)
	{
		Logger::LogErrorAlways("ImGUI Context", "Metal is currently not supported, Opengl will be used.");
		//return new MetalImGUIContext;
		return new OpenglImGUIContext;
	}

	else
		return new OpenglImGUIContext;
}