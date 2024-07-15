#include <smpch.h>
#include "FrameBuffer.h"

#include <Renderer\RenderAPI\RenderAPI.h>
#include <Renderer\RenderAPI\Opengl\OpenglFrameBuffer.h>
//#include <Renderer\RenderAPI\DirectX\DirectXFrameBuffer.h>
//#include <Renderer\RenderAPI\Vulkin\VulkinFrameBuffer.h>
//#include <Renderer\RenderAPI\Metal\MetalFrameBuffer.h>

//creates a graphic context
FrameBuffer* FrameBuffer::Create(const FrameBufferData& data)
{
	RenderAPIType type = RenderAPI::GetAPI();

	if (type == RenderAPIType::Vulkin)
	{
		Logger::LogErrorAlways("Frame Buffer", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinFrameBuffer(data);
		return new OpenglFrameBuffer(data);
	}

	else if (type == RenderAPIType::DirectX)
	{
		Logger::LogErrorAlways("Frame Buffer", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXFrameBuffer(data);
		return new OpenglFrameBuffer(data);
	}

	else if (type == RenderAPIType::Metal)
	{
		Logger::LogErrorAlways("Frame Buffer", "Metal is currently not supported, Opengl will be used.");
		//return new MetalFrameBuffer(data);
		return new OpenglFrameBuffer(data);
	}

	else
		return new OpenglFrameBuffer(data);
}